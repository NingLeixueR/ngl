#include "task.h"
#include "actor_role.h"


namespace ngl
{

	class taskcheck
	{
		taskcheck() = delete;

		static std::map<ETask, taskcheck*> m_taskdata;
		virtual bool check_receives(actor_role* arole, const std::vector<int32_t>& aparmint) = 0;
		virtual void values(actor_role* arole, std::vector<int32_t>& aparmint) = 0;
	protected:
		taskcheck(ETask atype)
		{
			m_taskdata[atype] = this;
		}
	public:
		static bool check_receive(actor_role* arole, ETask atype, const std::vector<int32_t>& aparmint)
		{
			auto itor = m_taskdata.find(atype);
			if (itor == m_taskdata.end())
			{
				LogLocalError("taskcheck::check type[%] not find!!!", (int)atype);
				return false;
			}
			return itor->second->check_receives(arole, aparmint);
		}

		static bool values(actor_role* arole, ETask atype, std::vector<int32_t>& aparmint)
		{
			auto itor = m_taskdata.find(atype);
			if (itor == m_taskdata.end())
			{
				LogLocalError("taskcheck::values type[%] not find!!!", (int)atype);
				return false;
			}
			itor->second->values(arole, aparmint);
			return true;
		}

		static bool check_complete(const std::vector<int32_t>& aparmint, const std::vector<int32_t>& asumint)
		{
			for (int i = 0; i < aparmint.size() && i < asumint.size(); ++i)
			{
				if (aparmint[i] < asumint[i])
					return false;
			}
			return true;
		}
	};

	class taskcheck_rolelv
		: public taskcheck
	{
		virtual bool check_receives(actor_role* arole, const std::vector<int32_t>& aparmint)
		{
			if (aparmint.empty())
				return true;
			return arole->m_info.lv() >= aparmint[0];
		}
		virtual void values(actor_role* arole, std::vector<int32_t>& aparmint)
		{
			aparmint.clear();
			aparmint.push_back(arole->m_info.lv());
		}
	public:
		taskcheck_rolelv() :
			taskcheck(ETaskRoleLv)
		{}
	};

	taskcheck_rolelv g_taskcheck_rolelv;


	void task::update_schedule(task_complete& acomplete, pbdb::db_task::data_schedule& adata)
	{
		adata.set_m_type(acomplete.m_completetype);
		switch (acomplete.m_completetype)
		{
		case ETaskRoleLv:
		{
			adata.add_m_parmint(actor()->m_info.lv());
			assert(acomplete.m_parmint.empty() == false);
			adata.add_m_sumint(acomplete.m_parmint[0]);
		}
		break;
		}
	}

	bool task::check_complete(pbdb::db_task::data_schedule& adata)
	{
		switch (adata.m_type())
		{
		case ETaskRoleLv:
		{
			
			for (int i = 0; i < adata.m_parmint_size() && i < adata.m_sumint_size(); ++i)
			{
				if (adata.m_parmint()[i] < adata.m_sumint()[i])
				{
					return false;
				}
			}
			return true;
		}
		break;
		}
		return false;
	}

	bool task::check_complete(pbdb::db_task::data& adata)
	{
		for (pbdb::db_task::data_schedule& item : *adata.mutable_m_schedules())
		{
			if (check_complete(item) == false)
				return false;
		}
		return true;
	}

	bool task::check_complete(int32_t ataskid)
	{
		auto itor = db()->get(false).mutable_m_rundatas()->find(ataskid);
		if (itor == db()->get(false).mutable_m_rundatas()->end())
			return false;
		return check_complete(itor->second);
	}

	bool task::check_receive(int32_t ataskid)
	{
		tab_task* tab = allcsv::tab<tab_task>(ataskid);
		if (tab == nullptr)
			return false;

		const pbdb::db_task& ldbtask = get_consttask();
		auto lcompleteddatas = ldbtask.m_completeddatas();
		if (lcompleteddatas.find(ataskid) != lcompleteddatas.end())
			return false;
		auto lrundatas = ldbtask.m_rundatas();
		if (lrundatas.find(ataskid) != lrundatas.end())
			return false;
		
		for (task_receive& item : tab->m_taskreceive)
		{
			if (taskcheck::check_receive(actor(), item.m_receivetype, item.m_parmint) == false)
				return false;
		}
		return true;
	}


	void task::initdata()
	{
		pbdb::db_task& ltask = db()->get(false);
		auto lcompleteddatas = ltask.mutable_m_completeddatas();
		auto lrundatas = ltask.mutable_m_rundatas();

		std::cout << "###����ɵ�����[===" << std::endl;
		std::cout << "[===" << std::endl;
		for (const auto& [_id, _data] : *lcompleteddatas)
		{
			std::cout << _id << std::endl;
		}
		std::cout << "===]" << std::endl;
		std::cout << "###���ڽ��е�����[===" << std::endl;
		std::cout << "[===" << std::endl;
		for (const auto& [_id, _data] : *lrundatas)
		{
			std::cout << _id << std::endl;
		}
		std::cout << "===]" << std::endl;


		// ### ����Ƿ��пɽ��ܵ�����
		auto tabs = allcsv::get<manage_csv<tab_task>>();
		tabs->foreach([this](tab_task& atask)
			{
				if (check_receive(atask.m_id))
				{
					auto lrundatas = get_task(false).mutable_m_rundatas();
					std::pair<int32_t, pbdb::db_task::data> lpair;
					lpair.first = atask.m_id;
					pbdb::db_task::data& ldata = lpair.second;
					ldata.set_m_receiveutc(localtime::gettime());

					tab_task* tab = allcsv::tab<tab_task>(atask.m_id);
					if (tab == nullptr)
						return;
					for (task_complete& item : tab->m_taskcomplete)
					{
						//if (taskcheck::check(actor(), item.m_receivetype, item.m_parmint) == false)
						//	return false;
						//update_schedule(item, *ldata.add_m_schedules());
						std::vector<int32_t> lparm;
						taskcheck::values(actor(), item.m_completetype, lparm);
						auto lschedules = ldata.add_m_schedules();
						for(int32_t val : lparm)
							lschedules->add_m_parmint(val);
						for (int32_t val : item.m_parmint)
							lschedules->add_m_sumint(val);
					}
					lrundatas->insert(lpair);
					get_task(true);
				}
			});
	}
}
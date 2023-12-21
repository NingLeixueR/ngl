#pragma once

#include "actor_manage.h"
#include "actor_enum.h"
#include "actor_register.h"
#include "actor.h"
#include "net.h"
#include "db_data.h"
#include "db.h"
#include "db_pool.h"
#include "db_manage.h"
#include "actor_db.h"
#include "ttab_dbload.h"

namespace ngl
{
	class actor_dbclient_base
	{
	protected:
		pbdb::ENUM_DB m_type;
		actor_dbclient_base(pbdb::ENUM_DB atype) :
			m_type(atype)
		{}
	public:
		virtual bool isload() = 0;
		virtual void load() = 0;
		virtual void savedb() = 0;
		virtual void deldb() = 0;
		virtual void create(const actor_guid& aid) = 0;
		virtual void init(actor_manage_dbclient* amdb, actor_base* aactor, const actor_guid& aid) = 0;
		virtual void clear_modified() = 0;

		pbdb::ENUM_DB type()
		{
			return m_type;
		}
	};

	class data_modified_base
	{
	protected:
		bool m_ischange = false;
	public:
		virtual bool is_modified()const
		{
			return m_ischange;
		}

		virtual void modified()
		{
			m_ischange = true;
		}

		virtual void clear_modified()
		{
			m_ischange = false;
		}
	};

	template <typename TDBTAB>
	struct data_modified : data_modified_base
	{
	private:
		TDBTAB m_data;
		TDBTAB* m_pdata = nullptr;
	public:
		data_modified(TDBTAB* adata):
			m_pdata(adata)
		{}

		data_modified(const TDBTAB& adata) :
			m_data(adata)
		{}

		data_modified():
			m_pdata(nullptr)
		{}

		void set(const TDBTAB& adata)
		{
			m_data = adata;
			m_pdata = nullptr;
		}

		TDBTAB& get(bool achange = true)
		{
			if (achange)
				m_ischange = true;
			return m_pdata == nullptr ? m_data : *m_pdata;
		}

		const TDBTAB& getconst()const
		{
			return m_pdata == nullptr ? m_data : *m_pdata;
		}
	};

	template <EPROTOCOL_TYPE PROTYPE, pbdb::ENUM_DB TDBTAB_TYPE, typename TDBTAB>
	class actor_db;

	template <EPROTOCOL_TYPE PROTYPE, pbdb::ENUM_DB DBTYPE, typename TDBTAB, typename TACTOR>
	class actor_dbclient : public actor_dbclient_base
	{
		tab_dbload* m_tab;
	public:
		virtual void load()
		{
			Try
			{
				tab_servers* tab = ttab_servers::tab();
				// ��actor client �������Ӻ��¼�
				std::shared_ptr<actor_node_actor_connect_task> pro(new actor_node_actor_connect_task
					{
						.m_serverid = tab->m_db,
						.m_fun = std::bind(&actor_dbclient<PROTYPE, DBTYPE, TDBTAB, TACTOR>::loaddb, this, m_id),
					});
				actor_guid lclientguid = actor_guid::make(ACTOR_ADDRESS_CLIENT, tab_self_area, nconfig::m_nodeid);
				actor_base::static_send_actor(lclientguid, m_actor->guid(), pro);
			}Catch;
		}
	private:
		void init_load()
		{
			load();
		}

		i32_actordataid dbnodeid()
		{
			static i32_actordataid ldbnodeid = -1;
			if (ldbnodeid != -1)
				return ldbnodeid;
			return ttab_servers::tab()->m_db;
			return -1;
		}

		void loaddb(const actor_guid& aid)
		{
			actor_db_load<PROTYPE, DBTYPE, TDBTAB> ldata;
			ldata.m_id = aid;

			i64_actorid ldbid = actor_guid::make(actor_type<actor_db<PROTYPE, DBTYPE, TDBTAB>>::type(), tab_self_area, dbnodeid());
			nserver->sendtoserver(dbnodeid(), ldata, ldbid, m_actor->id_guid());
		}

		actor_guid m_id;
		std::map<actor_guid, data_modified<TDBTAB>> m_data;
		data_modified<TDBTAB>* m_dbdata;
		bool m_load;
		actor_manage_dbclient* m_manage_dbclient;
		actor_base* m_actor;
		std::vector<int64_t> m_dellist;
	public:

		actor_dbclient():
			m_id(actor_guid::make()),
			m_load(false),
			m_dbdata(nullptr),
			m_tab(nullptr),
			actor_dbclient_base(DBTYPE),
			m_actor(nullptr),
			m_manage_dbclient(nullptr)
		{}

		//// create
		virtual void create(const actor_guid& aid)
		{
			m_dbdata = &m_data[aid];
			m_dbdata->get().set_m_id(aid);
			m_id = aid;
		}

		void set_id(const actor_guid& aid)
		{ 
			m_id = aid;
		}

		void set_actor(actor_base* aactor)
		{
			m_manage_dbclient = aactor->get_actor_manage_dbclient();
			m_actor = aactor;
		}

		std::map<actor_guid, data_modified<TDBTAB>>& get_data()
		{ 
			return m_data; 
		}

		data_modified<TDBTAB>* get_data(const actor_guid& aid)
		{
			if (aid == m_id && m_id != -1)
				return m_dbdata;
			auto itor = m_data.find(aid);
			if (itor == m_data.end())
				return nullptr;
			return &itor->second;
		}

		data_modified<TDBTAB>* get_dbdata()
		{
			return m_dbdata;
		}

		void init(actor_manage_dbclient* amdb, actor_base* aactor, const actor_guid& aid)
		{
			Try
			{
				m_actor = aactor;
				m_manage_dbclient = amdb;
				m_id = aid;
				m_load = false;
				Assert(m_tab = ttab_dbload::get_tabdb<TDBTAB>(); m_tab != nullptr);

				static bool m_register = false;
				if (m_register == false)
				{
					m_register = true;
					actor::template register_db<PROTYPE, TACTOR, DBTYPE, TDBTAB>(nullptr);
				}
				init_load();
			}Catch;
		}

		virtual bool isload()	
		{ 
			return m_load; 
		}

		void savedb_all()		
		{ 
			savedb(-1); 
		}

		virtual void savedb()			
		{ 
			savedb(m_id); 
		}

		void savedb(const actor_guid& aid)
		{
			actor_db_save<PROTYPE, DBTYPE, TDBTAB> pro;
			std::list<data_modified<TDBTAB>*> lclearlist;
			if (aid != (int64_t)-1)
			{
				data_modified<TDBTAB>* lp = nullptr;
				if (aid == m_id)
				{
					lp = m_dbdata;
				}
				else
				{
					auto itor = m_data.find(aid);
					if (itor == m_data.end())
						return;
					lp = &itor->second;
				}
				if (lp->is_modified())
				{
					lclearlist.push_back(lp);
					pro.add(lp->getconst().m_id(), lp->getconst());
				}			
			}
			else
			{
				for (auto& [_, data] : m_data)
				{
					if (data.is_modified())
					{
						lclearlist.push_back(&data);
						pro.add(data.getconst().m_id(), data.getconst());
					}
				}
			}
			if (pro.empty() == false)
			{
				// ### �����л� ����actor_clientȷ��λ��
				i64_actorid lactorid = actor_guid::make(
					actor_type<actor_db<PROTYPE, DBTYPE, TDBTAB>>::type()
					, tab_self_area
					, dbnodeid()
				);
				i64_actorid larequestactorid = m_actor->guid();
				std::shared_ptr<pack> lpack = actor_base::net_pack(pro, lactorid, larequestactorid);
				if (lpack == nullptr)
				{
					//LogLocalError("actor_dbclient<%> actor_base::net_pack fail", TDBTAB::name());
					return;
				}
				// ### �첽����pack
				m_actor->send_actor_pack(lactorid, lpack);
				// ### ִ�����[�ü��޸�]��־λ 
				for (data_modified<TDBTAB>* dataptr : lclearlist)
				{
					dataptr->clear_modified();
				}
			}
		}

		void del(const actor_guid& aid)
		{
			m_dellist.push_back((int64_t)aid);
			m_data.erase((int64_t)aid);
		}

		virtual void deldb()
		{
			actor_db_delete<PROTYPE, DBTYPE, TDBTAB> pro;
			if (m_dellist.empty())
				return;
			pro.m_data.swap(m_dellist);
			if (pro.m_data.empty() == false)
			{
				// ### �����л� ����actor_clientȷ��λ��
				i64_actorid lactorid = actor_guid::make((ENUM_ACTOR)(ACTOR_DB + DBTYPE), tab_self_area, dbnodeid());
				i64_actorid larequestactorid = m_actor->guid();
				std::shared_ptr<pack> lpack = actor_base::net_pack(pro, lactorid, larequestactorid);
				if (lpack == nullptr)
				{
					//LogLocalError("actor_dbclient<%> actor_base::net_pack fail", TDBTAB::name());
					return;
				}
				// ### �첽����pack
				m_actor->send_actor_pack(actor_guid::make((ENUM_ACTOR)(ACTOR_DB + DBTYPE), tab_self_area, dbnodeid()), lpack);
			}
		}
	public:
		const TDBTAB* set(const actor_guid& aid, const TDBTAB& adbtab)
		{
			m_data[aid] = adbtab;
			if (aid == m_id)
				m_dbdata = &m_data[aid];
			return &m_data[aid];
		}

		data_modified<TDBTAB>* add(const actor_guid& aid, const TDBTAB& adbtab)
		{
			if (m_data.find(aid) != m_data.end())
				return nullptr;
			data_modified<TDBTAB>* lpdata = &m_data[aid];
			lpdata->set(adbtab);
			savedb(aid);
			if(aid == m_id)
				m_dbdata = lpdata;
			return lpdata;
		}

		bool loadfinish()
		{
			if (m_id != (int64_t)-1)
			{
				m_dbdata = &m_data[m_id];
			}
			m_load = true;
			m_manage_dbclient->on_load_finish(false);
			return false;
		}

		bool loadfinish(std::map<actor_guid, TDBTAB>& adata, bool aisover)
		{
			for (auto& item : adata)
			{
				m_data[item.first].set(item.second);
			}

			auto itor = m_data.find(m_id);
			if (itor != m_data.end())
				m_dbdata = &itor->second;
			if (aisover)
			{
				m_load = true;
				m_manage_dbclient->on_load_finish(true);
			}
			return true;
		}

		
		bool handle(message<actor_db_load_response<PROTYPE, DBTYPE, TDBTAB>>& adata)
		{
			Try
			{
				if (!adata.m_data->m_stat)
				{//����ʧ��  ���ݿ���û������
					return loadfinish();
				}
				loadfinish(adata.m_data->data(), adata.m_data->m_over);
			}Catch;
			return true;
		}

		virtual void clear_modified()
		{
			for (auto& [_, data] : m_data)
			{
				data.clear_modified();
			}
		}
	};

	class actor_manage_dbclient
	{
		actor_base* m_actor;
		std::map<pbdb::ENUM_DB, actor_dbclient_base*> m_typedbclientmap;
		std::map<pbdb::ENUM_DB, actor_dbclient_base*> m_dbclientmap;//�Ѿ��������
		std::function<void(bool)> m_fun;//bool db���ݿ��Ƿ��и�����
		bool m_finish;
	public:
		actor_manage_dbclient(actor_base* aactor) :
			m_actor(aactor),
			m_finish(false)
		{}

		void add(actor_dbclient_base* adbclient, const actor_guid& aid)
		{
			Try
			{
				Assert(m_typedbclientmap.find(adbclient->type()) == m_typedbclientmap.end());
				m_typedbclientmap.insert(std::make_pair(adbclient->type(), adbclient));
				init(adbclient, m_actor,  aid);
			}Catch;			
		}

		void set_loadfinish_function(const std::function<void(bool)>& afun)
		{
			m_fun = afun;
		}

		void init(actor_dbclient_base* adbclient, actor_base* aactor, const actor_guid& aid)
		{
			Try
			{
				adbclient->init(this, aactor, aid);
			}Catch;
		}

		bool on_load_finish(bool adbishave)
		{
			if (m_typedbclientmap.empty())
				return false;
			for (auto itor = m_typedbclientmap.begin(); itor != m_typedbclientmap.end();)
			{
				if (!itor->second->isload())
				{
					++itor;
					continue;
				}
				//itor->second->remove_rfun(m_actor);
				m_dbclientmap.insert(std::make_pair(itor->first, itor->second));
				itor = m_typedbclientmap.erase(itor);
			}
			if (!m_typedbclientmap.empty())
				return false;
			m_actor->db_component_init_data();
			// 1���������޸�Ϊ[�ü��޸�]
			for (auto& [_, data] : m_dbclientmap)
			{
				data->clear_modified();
			}
			// 2����һЩ��ʼ��֮��Ĺ���,������Ҫ�Ļ����䷢�͸��ͻ���
			m_fun(adbishave);
			LogLocalInfo("##############load_finish##############");
			return true;
		}

		bool isloadfinish()
		{
			return m_typedbclientmap.empty();
		}

		template <EPROTOCOL_TYPE PROTYPE, pbdb::ENUM_DB ENUM, typename TDATA, typename TACTOR>
		actor_dbclient<PROTYPE, ENUM, TDATA, TACTOR>* data(bool aloadfinish)
		{
			actor_dbclient_base** lp = ngl::tools::findmap<pbdb::ENUM_DB, actor_dbclient_base*>(aloadfinish? m_dbclientmap : m_typedbclientmap, ENUM);
			if (lp == nullptr)
				return nullptr;
			return (actor_dbclient<PROTYPE, ENUM, TDATA, TACTOR>*)(*lp);
		}

		void save()
		{
			for(auto& [id, ldbclient_base] : m_dbclientmap)
			{
				ldbclient_base->savedb();
			}
		}

		void del()
		{
			for (auto& [id, ldbclient_base] : m_dbclientmap)
			{
				ldbclient_base->deldb();
			}
		}
	};
}

namespace ngl
{
	template <EPROTOCOL_TYPE PROTYPE, pbdb::ENUM_DB DBTYPE, typename TDBTAB, typename TACTOR>
	bool actor_base::handle(message<actor_db_load_response<PROTYPE, DBTYPE, TDBTAB>>& adata)
	{
		std::unique_ptr<actor_manage_dbclient>& mdbclient = get_actor_manage_dbclient();
		if (mdbclient == nullptr)
		{
			//LogLocalError("get_actor_manage_dbclient() == nullptr, DBTYPE = [%], actorid = [%]", DBTYPE, id_guid());
			return false;
		}
		actor_dbclient<PROTYPE, DBTYPE, TDBTAB, TACTOR>* lp = mdbclient->data<PROTYPE, DBTYPE, TDBTAB, TACTOR>(false);
		if (lp == nullptr)
		{
			//LogLocalError("mdbclient->data<DBTYPE, TDBTAB>() == nullptr, DBTYPE = [%], actorid = [%]", DBTYPE, id_guid());
			return false;
		}
		return lp->handle(adata);
	}
}

#pragma once

#include "actor.h"
#include "map.h"


namespace ngl
{
	class actor_plays : public actor
	{
	protected:
		aoimap m_map;
		//std::shared_ptr<plays> m_plays;
		enum estage
		{
			estage_preparation,		// ׼���׶�
			estage_play,			// �淨�׶�
			estage_settlement,		// ����׶�
			estage_over,			// ����
		};
		estage m_stage;			// �淨�׶�
		int32_t m_begtm;		// �׶ο�ʼʱ��
		tab_plays* m_tab;
		std::map<int64_t, std::shared_ptr<unit_role>> m_role;

	public:
		actor_plays(int32_t adataid, void* data);

		virtual void init()
		{
			timerparm tparm;
			make_timerparm::make_interval(tparm, 1);
			set_timer(tparm);
		}

		static void actor_register();

		virtual ~actor_plays() {}

		virtual void loaddb_finish(bool adbishave) {}

		enum { ACTOR_TYPE = ACTOR_PLAYS };

		// ���ý׶�
		void stage(estage astage, bool astart)
		{
			switch (astage)
			{
			case estage_preparation:
				preparation(astart);
				break;
			case estage_play:
				play(astart);
				break;
			case estage_settlement:
				settlement(astart);
				break;
			}
		}

		// �ı�׶�
		bool change_stage(estage astage)
		{
			if (m_stage <= astage)
				return false;
			stage(m_stage, false);
			m_stage = astage;
			m_begtm = localtime::gettime();
			stage(m_stage, true);
			return true;
		}

		bool check_stage(estage astage)
		{
			return m_stage == astage;
		}

		void update_stage()
		{
			int32_t lnow = localtime::gettime();
			if (m_stage == estage_preparation)
			{
				if (lnow <= m_begtm + m_tab->m_preparation_tm)
				{
					change_stage(estage_play);
				}
			}
			else if (m_stage == estage_play)
			{
				if (lnow <= m_begtm + m_tab->m_play_tm)
				{
					change_stage(estage_settlement);
				}
			}
			else if (m_stage == estage_settlement)
			{
				if (lnow <= m_begtm + m_tab->m_settlement_tm)
				{
					settlement(false);
				}
			}
		}

		// ��ʼ���淨�����
		virtual void init_after() {}
		// ��ҽ���
		virtual void enter(i64_actorid aroleid) {}
		// ����뿪
		virtual void leave(i64_actorid aroleid) {}
		// ׼���׶�[��ʼor����]
		virtual void preparation(bool astart) {}
		// �淨�׶�[��ʼor����]
		virtual void play(bool astart) {}
		// ����׶�[��ʼor����]
		virtual void settlement(bool astart) {}
		// �������
		virtual void player_death(i64_actorid aroleid) {}
		// ������Ұ
		virtual void player_enterview(i64_actorid aroleid, std::set<i64_actorid>& aother) {}
		// �뿪��Ұ
		virtual void player_leaveview(i64_actorid aroleid1, std::set<i64_actorid>& aother) {}

		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, mforward<pbnet::PROBUFF_NET_ENTER_PLAYS>& adata)
		{
			if (m_role.find(adata.identifier()) != m_role.end())
				return true;
			if (m_tab->m_birthpoint.empty())
			{
				LogLocalError("actor_plays::handle(pbnet::PROBUFF_NET_ENTER_PLAYS) m_birthpoint.empty()");
				return true;
			}
			int lindex = std::rand() % m_tab->m_birthpoint.size();
			auto& item = m_role[adata.identifier()];
			item.reset(new unit_role(adata.identifier()));
			m_map.enter(item.get(), m_tab->m_birthpoint[lindex].m_x, m_tab->m_birthpoint[lindex].m_y);
			enter(adata.identifier());
			return true;
		}


		bool timer_handle(i32_threadid athread, const std::shared_ptr<pack>& apack, timerparm& adata)
		{
			update_stage();
			if (check_stage(estage_over) == true)
			{
				// ɾ��actor
				actor_base::erase_actor_byid(id_guid());
			}
			return true;
		}
	};
}
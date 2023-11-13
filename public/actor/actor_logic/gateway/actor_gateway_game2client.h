#pragma once

#include "actor_manage.h"
#include "net.h"
#include "db_data.h"
#include "db.h"
#include "db_pool.h"
#include "db_manage.h"
#include "actor_db_client.h"
#include "actor_role.h"
#include "gateway_info.h"

namespace ngl
{
	class actor_gateway_game2client : public actor
	{
		gateway_info m_info;

		actor_gateway_game2client();
	public:
		friend class actor_instance<actor_gateway_game2client>;
		static actor_gateway_game2client& getInstance()
		{
			return actor_instance<actor_gateway_game2client>::instance();
		}

		virtual ~actor_gateway_game2client();

		static void actor_register();

		enum { ACTOR_TYPE = ACTOR_GATEWAY_GAME2CLIENT};


		template <EPROTOCOL_TYPE TYPE, typename T>
		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, actor_forward<T, TYPE, true, ngl::forward>& adata)
		{
			//Game->Gate  ��Ҫ�������Ϣ���ݸ�Client������
			gateway_socket* info = nullptr;
			std::map<i32_sessionid, i64_actorid> lmap;
			if (adata.m_uid.empty())
				return true;
			if (adata.m_area[0] == -1 && adata.m_uid[0] == -1)
			{
				// �������пͻ���
				for (auto& itemfor1 : m_info.info())
				{
					for (auto& itemfor2 : itemfor1.second)
					{
						lmap.insert(std::make_pair(itemfor2.second.m_socket, actor_guid::make(ACTOR_ROBOT, itemfor2.second.m_area, itemfor2.second.m_dataid)));
					}
				}
			}
			else if (adata.m_area[0] != -1 && adata.m_uid[0] == -1)
			{
				// ����ָ�������ϵ����пͻ���
				auto itemitor = m_info.info().find(adata.m_area[0]);
				if (itemitor != m_info.info().end())
				{
					for (auto& itemfor1 : itemitor->second)
					{
						lmap.insert(std::make_pair(itemfor1.second.m_socket, actor_guid::make(ACTOR_ROBOT, itemfor1.second.m_area, itemfor1.second.m_dataid)));
					}
				}
			}
			else
			{
				for (int i = 0; i < adata.m_uid.size() && i < adata.m_area.size(); ++i)
				{
					info = m_info.get(adata.m_area[i], adata.m_uid[i]);
					if (info == nullptr)
						continue;
					lmap.insert(std::make_pair(info->m_socket, actor_guid::make(ACTOR_ROBOT, adata.m_area[i], adata.m_uid[i])));
				}
			}
			actor_forward<T, TYPE, false, ngl::forward> ltemp(adata);
			nserver->sendmore(lmap, ltemp, apack->m_head.get_request_actor());
			return true;
		}

		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, actor_gateway_info_updata& adata);
	private:
	};

}


#pragma once

#include "actor_manage.h"
#include "net.h"
#include "db_data.h"
#include "db.h"
#include "db_pool.h"
#include "db_manage.h"
#include "actor_db_client.h"
//#include "actor_role.h"
#include "gateway_info.h"

#define ROBOT_TEST

namespace ngl
{
	class actor_gateway_client2game : public actor
	{
		gateway_info m_info;
		actor_gateway_client2game();
	public:
		friend class actor_instance<actor_gateway_client2game>;
		static actor_gateway_client2game& getInstance()
		{
			return actor_instance<actor_gateway_client2game>::instance();
		}

		virtual ~actor_gateway_client2game() {}

		static void actor_register();

		enum { ACTOR_TYPE = ACTOR_GATEWAY_CLIENT2GAME};

		template <EPROTOCOL_TYPE TYPE, typename T>
		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, actor_forward<T, TYPE, false, ngl::forward>& adata)
		{
			//Client->Gate  需要把这个消息传递给Game服务器
			//adata.m_uid == socket id
			gateway_socket* info = nullptr;
			if (rebot_test::is_test)
			{
				i64_actorid lactorid = apack->m_head.get_request_actor();
				actor_guid lguid(lactorid);
				info = m_info.get(lguid.area(), lguid.actordataid());
			}
			else
			{
				info = m_info.get(apack->m_id);//m_info.get(adata.m_uid[0]);
			}
			if (info == nullptr)
				return false;
			actor_forward<T, TYPE, true, ngl::forward> ltemp(adata);
			ltemp.m_uid.push_back(info->m_dataid);
			ltemp.m_area.push_back(info->m_area);
			nserver->sendtoserver(info->m_gameid, ltemp, actor_guid::make(ACTOR_ROLE, info->m_area, info->m_dataid), apack->m_head.get_request_actor());
			return true;
		}

		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, actor_gateway_info_updata& adata)
		{
			for (auto& item : adata.m_delsocket)
			{
				m_info.remove_socket(item);
			}
			for (auto& item : adata.m_delactorid)
			{
				m_info.remove_actorid(item);
			}
			for (auto& item : adata.m_add)
			{
				m_info.updata(item);
			}
			return true;
		}
	private:
	};

}


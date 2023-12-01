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
	class actor_gateway : public actor
	{
		actor_gateway();
	public:
		friend class actor_instance<actor_gateway>;
		static actor_gateway& getInstance() 
		{ 
			return actor_instance<actor_gateway>::instance(); 
		}

		virtual ~actor_gateway();

		static void actor_register();

		enum { ACTOR_TYPE = ACTOR_GATEWAY};

		gateway_info m_info;

		// ## ֪ͨactor_server [actorid]->[gateway server id]
		void sync_actorserver_gatewayid(const actor_guid& aguid, bool aisremove);

		void update_gateway_info(actor_gateway_info_updata* ap);

		void session_close(gateway_socket* ainfo);
		// actor_login֪ͨgateway����Ѿ���¼(����¼session����Ӧ��game������)
		bool handle(message<actor_role_login>& adata);
		// ��ҵ�½
		bool handle(message<pbnet::PROBUFF_NET_ROLE_LOGIN>& adata);
		// ����л�game����
		bool handle(message<actor_switch_process<actor_switch_process_role>>& adata);
		// �Ͽ�����
		bool handle(message<actor_session_close>& adata);
	private: 
			
	};

}


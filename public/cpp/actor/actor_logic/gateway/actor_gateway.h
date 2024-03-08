#pragma once

#include "actor_manage.h"
#include "actor_role.h"
#include "gateway_info.h"
#include "ndbclient.h"
#include "db_manage.h"
#include "db_pool.h"
#include "db_data.h"
#include "net.h"
#include "db.h"

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

		static void nregister();

		gateway_info m_info;

		// ## ֪ͨactor_server [actorid]->[gateway server id]
		void sync_actorserver_gatewayid(const nguid& aguid, bool aisremove);

		void update_gateway_info(actor_gateway_info_updata* ap);

		void session_close(gateway_socket* ainfo);
		// actor_login֪ͨgateway����Ѿ���¼(����¼session����Ӧ��game������)
		bool handle(message<actor_role_login>& adata);
		// ��ҵ�½
		bool handle(message<pbnet::PROBUFF_NET_ROLE_LOGIN>& adata);
		// ��ȡkcp-session
		bool handle(message<actor_protocol_kcp>& adata);
		bool handle(message<pbnet::PROBUFF_NET_KCPSESSION>& adata);		
		// ����л�game����
		bool handle(message<actor_switch_process<actor_switch_process_role>>& adata);
		// �Ͽ�����
		bool handle(message<actor_session_close>& adata);
	};
}//namespace ngl


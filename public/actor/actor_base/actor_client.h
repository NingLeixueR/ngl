#pragma once

#include "actor.h"
#include "actor_protocol.h"
#include "xmlnode.h"
#include "impl.h"
#include "actor_address.h"
#include "net.h"

namespace ngl
{
	class actor_client : public actor
	{
		struct impl_actor_client;
		ngl::impl<impl_actor_client> m_impl_actor_client;

		actor_client();
		virtual ~actor_client();
	public:
		friend class actor_instance<actor_client>;
		static actor_client& getInstance() 
		{ 
			return actor_instance<actor_client>::instance(); 
		}
		
		// ע����Ҫ�������Ϣ
		static void actor_register();
		
		enum { ACTOR_TYPE = ACTOR_ADDRESS_CLIENT };
	private:
		void actor_server_register(i32_serverid aserverid);
	public:
		//# ��actor_serverע����
		void actor_server_register();
	private:
		// �������Ӻ�ʱ�� ����actor_dbclient��ע�����Ӻ��¼����������ݣ�
		void set_connect_fnish(i32_serverid aserverid);
		// ���ӳɹ������
		void connect_fnish();
	public:
		// ע����
		bool handle(message<actor_node_register_response>& adata);
		// actor�ͻ��˼��໥����
		bool handle(message<actor_client_node_connect>& adata);
		// ��������actor�ͻ���ͬ�������Ϣ
		bool handle(message<actor_node_update>& adata);
		// ��actor�ͻ���ͬ�������Ϣ(Ⱥ��)
		bool handle(message<actor_node_update_mass>& adata);
		// ���ӳɹ���ִ������
		bool handle(message<actor_node_actor_connect_task>& adata);
		// ͬ��actor_role��Ӧ��gateway
		bool handle(message<actor_gateway_id_updata>& adata);
	};

}

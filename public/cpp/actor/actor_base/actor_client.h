#pragma once

#include "nprotocol.h"
#include "naddress.h"
#include "xmlnode.h"
#include "actor.h"
#include "impl.h"

namespace ngl
{
	//#####################################################
	//# ÿ�����̶���Ҫ��һ��actor_client��actor_server
	//# ͨ��һ������ֻ��һ�������а���actor_server �������н��̶��������actor_client
	//# actor_client ������¼����nguid�������id�Ķ�Ӧ��ϵ��
	//# actor_client�൱��actor��ܵ�·������Ϊactor�ṩ·�ɹ���
	//# ��actor_server����ַ�����actor_client�б��ص�nguid��Ӧ��ϵ
	//#########################################################
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
		
		//# ע����Ҫ�������Ϣ
		static void nregister();
	private:
		//# ������actor_serverע��actor_client
		void actor_server_register(i32_serverid aserverid);

		//# �������Ӻ�ʱ�� ����actor_dbclient��ע�����Ӻ��¼����������ݣ�
		void set_connect_fnish(i32_serverid aserverid);

		//# ���ӳɹ������
		void connect_fnish();

		//# ��������
		void activ_connect(i32_serverid aserverid);
	public:
		//# ��actor_serverע����
		void actor_server_register();

		//# actor_client��actorid
		static i64_actorid actorid();

		//# ע����
		bool handle(message<np_actornode_register_response>& adata);

		//# actor�ͻ��˼��໥����
		bool handle(message<np_actorclient_node_connect>& adata);

		//# ��������actor�ͻ���ͬ�������Ϣ
		bool handle(message<np_actornode_update>& adata);

		//# ��actor�ͻ���ͬ�������Ϣ(Ⱥ��)
		bool handle(message<np_actornode_update_mass>& adata);

		//# ���ӳɹ���ִ������
		bool handle(message<np_actornode_connect_task>& adata);

		//# ͬ��actor_role��Ӧ��gateway
		bool handle(message<np_actor_gatewayid_updata>& adata);
	};
}//namespace ngl

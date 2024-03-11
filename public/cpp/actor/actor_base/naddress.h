#pragma once

#include "handle_pram.h"
#include "nguid.h"
#include "type.h"
#include "nlog.h"
#include "impl.h"

#include <map>

namespace ngl
{
	// ## actor_client actor_server ��������actor��ַ
	class naddress
	{
	public:
		//##[ACTOR_ID] -> SERVER_ID
		//##[ACTOR_TYPE + EARE_ID + DATA_ID] -> SERVER_ID
		using map_guidserver = std::map<nguid, i32_serverid>;
		//##[ACTOR_TYPE]  -> set<ACTOR_ID>
		//##[ACTOR_TYPE]  -> set<ACTOR_TYPE + EARE_ID + DATA_ID>
		using map_typeguid = std::map<i16_actortype, std::set<nguid>>;
		//##[SERVER_ID] -> [SESSION_ID]
		using map_servernode = std::map<i32_serverid, actor_node_session>;
		//##[ACTOR_ID] -> [GATEWAY_SERVER_ID]
		using map_rolegateway = std::map<nguid, i32_serverid>;
		//##[ergodic]�ص�
		using ergodic_callbackfun = std::function<bool(map_guidserver&, map_servernode&)>;
		//##[foreach]�ص�
		using foreach_callbackfun = std::function<bool(const actor_node_session&)>;

	private:
		struct impl_actor_address;
		ngl::impl<impl_actor_address> m_impl_actor_address;

		naddress();

		virtual ~naddress();

	public:
		static naddress& getInstance() 
		{
			static naddress ltemp;
			return ltemp;
		}

#pragma region base
		// debug ��ӡ
		void print_address();
		// ���ý��
		bool set_node(const np_actornode& anode);
		// ���actor
		void actor_add(i32_serverid aserverid, i64_actorid adataid);
		// ���һ��actor
		void actor_add(i32_serverid aserverid, const std::vector<i64_actorid>& avec);
		// ɾ��actor
		void actor_del(i64_actorid adataid);
		// ɾ��һ��actor
		void actor_del(const std::vector<i64_actorid>& avec);
		// ����session
		void set_session(i32_serverid aserverid, i32_sessionid asession);
		// ��ȡsession
		i32_sessionid get_session(i32_serverid aserverid);
		// ��ȡserver id
		i32_serverid get_server(const nguid& aguid);
		// ��ȡENUM_ACTOR ��Ӧ�ķ�����
		void get_serverlist(ENUM_ACTOR atype, std::set<i32_serverid>& avec);
#pragma endregion

#pragma region gateway
		//##[ACTOR_ID(ACTOR_ROLE��actor)] -> [GATEWAY_SERVER_ID]
		i32_serverid get_gatewayid(const nguid& aguid);
		// ��actor_role.actorid��gatewayid����
		void add_gatewayid(const nguid& aguid, i32_serverid aserverid);
		// ���actor_role.actorid��gatewayid�Ĺ���
		void remove_gatewayid(const nguid& aguid);
		// ��ȡһ��actor_role.actorid��gatewayid�Ĺ���
		void get_gatewayid(const std::set<nguid>& aactorset, std::set<i32_serverid>& aserverset);
#pragma endregion

		void foreach(const foreach_callbackfun& afun);
		void ergodic(const ergodic_callbackfun& afun);
		map_guidserver& get_actorserver_map();
		i32_sessionid sessionbyrole(i16_area aarea, i32_actordataid aroleid);
	public:
		bool handle(handle_pram& apram);
	};
}//namespace ngl
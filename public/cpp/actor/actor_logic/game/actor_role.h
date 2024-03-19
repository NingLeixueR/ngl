#pragma once

#include "actor_create.h"
#include "actor_manage.h"
#include "db_manage.h"
#include "ndbclient.h"
#include "nprotocol.h"
#include "attribute.h"
#include "autoitem.h"
#include "roleinfo.h"
#include "remakes.h"
#include "db_pool.h"
#include "db_data.h"
#include "ntimer.h"
#include "net.pb.h"
#include "task.h"
#include "bag.h"
#include "net.h"
#include "db.h"

namespace ngl
{
	class role_cmd
	{
	public:
		using callback = std::function<void(actor_role*, const char*)>;
	private:
		static std::map<std::string, callback> m_cmd;
	public:
		static void init();
		static const callback& find(const char* akey);
	};

	class actor_manage_role;
	class actor_role : public actor
	{
	public:
		remakes		 m_remakes;
		roleinfo	 m_info;
		bag			 m_bag;
		task		 m_task;
		attribute	 m_attribute;
		i32_serverid m_gatewayid;
		i64_actorid  m_playactorid;
	public:
		actor_role(i16_area aarea, i32_actordataid aroleid, void* adata);

		virtual i32_serverid get_getwayserverid();

		virtual void init();

		//# ע����Ҫ�����Э��
		static void nregister();

		virtual ~actor_role();

		virtual void loaddb_finish(bool adbishave);

		//# ִ��handle֮�����
		virtual void handle_after();

		i64_actorid roleid();

		//# ���ø��½�ɫ����
		void update_attribute(EnumModule amodule, attribute_value& avalue)
		{
			m_attribute.updata(amodule, avalue);
		}

		template <typename T>
		void send2client(std::shared_ptr<T>& adata)
		{
			actor_base::send_client(m_gatewayid, id_guid(), adata);
		}

		void sync_data_client();

		enum ecross
		{
			ecross_ordinary,			// ����ת��
			ecross_cross_ordinary,		// ���ת��
			ecross_play,				// �淨ת��(����ת����actorid��ȷ��)
		};

		//# ����(���ģ��ת��)
		template <typename T>
		ecross forward_way(T& adata)
		{
			return ecross_ordinary;
		}

		ecross forward_way(pbnet::PROBUFF_NET_CHAT& adata)
		{
			return adata.m_channelid() == 2 ? ecross_cross_ordinary : ecross_ordinary;
		}

		template <typename T>
		int32_t dataid(T& adata)
		{
			return nguid::none_actordataid();
		}

		template <ENUM_ACTOR ACTOR, typename T>
		bool handle_forward(message<T>& adata)
		{
			std::shared_ptr<mforward<T>> pro(new mforward<T>(id_guid(), *adata.m_data));
			i64_actorid lguid;
			switch (forward_way(*adata.m_data))
			{
			case ecross_ordinary:
				lguid = nguid::make(ACTOR, ttab_servers::tab()->m_area, dataid(*adata.m_data));
				break;
			case ecross_cross_ordinary:
				lguid = nguid::make(ACTOR, ttab_servers::tab()->m_crossarea, dataid(*adata.m_data));
				break;
			case ecross_play:
				lguid = m_playactorid;
				break; 
			default:
				return true;
			}
			send_actor(lguid, pro);
			return true;
		}

		//# ��¼����δ������ֵ
		void loginpay();

		//# CMD Э��
		bool handle(message<pbnet::PROBUFF_NET_CMD>& adata);

		//# ��ȡrole����
		bool handle(message<pbnet::PROBUFF_NET_ROLE_SYNC>& adata);

		//# ��ȡ������ʱ��
		bool handle(message<pbnet::PROBUFF_NET_GET_TIME>& adata);

		//# �л���·������
		bool handle(message<pbnet::PROBUFF_NET_SWITCH_LINE>& adata);

		//# ������Ʒ
		bool handle(message<np_actor_senditem>& adata);

		//# �Ͽ�����
		bool handle(message<np_actor_disconnect_close>& adata);

		//# �淨�����ɹ�  ��¼�淨actorid
		bool handle(message<pbnet::PROBUFF_NET_MATCHING_SUCCESS_RESPONSE>& adata);

		//# ���󴴽�����
		void createorder(std::string& aorder, int32_t arechargeid);
		bool handle(message<pbnet::PROBUFF_NET_RECHARGE>& adata);
		bool is_first_recharge(int32_t arechargeid);

		//# ���󴴽�����
		bool handle(message<mforward<GM::PROBUFF_GM_RECHARGE>>& adata);

		// ��ʱ��
		bool timer_handle(message<timerparm>& adata);
	};
}//namespace ngl


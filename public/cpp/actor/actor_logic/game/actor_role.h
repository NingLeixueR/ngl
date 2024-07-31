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
#include "rolekv.h"
#include "task.h"
#include "cmd.h"
#include "bag.h"
#include "net.h"
#include "db.h"

namespace ngl
{
	class actor_manage_role;
	class actor_role : public actor
	{
	public:
		remakes		 m_remakes;
		roleinfo	 m_info;
		bag			 m_bag;
		task		 m_task;
		rolekv		 m_rolekv;
		attribute	 m_attribute;
		i32_serverid m_gatewayid;
		i64_actorid  m_playactorid;
	public:
		actor_role(const actor_role&) = delete;
		actor_role& operator=(const actor_role&) = delete;

		actor_role(i16_area aarea, i32_actordataid aroleid, void* adata);

		virtual i32_serverid get_getwayserverid();

		virtual void init();

		//# ע����Ҫ�����Э��
		static void nregister();

		virtual ~actor_role();

		virtual void loaddb_finish(bool adbishave);

		using handle_php = cmd<actor_role, std::string, int, ngl::json_read&>;

		//# ִ��handle֮�����
		virtual void handle_after();

		i64_actorid roleid();

		//# ���ø��½�ɫ����
		void update_attribute(EnumModule amodule, attribute_value& avalue)
		{
			m_attribute.updata(amodule, avalue);
		}

		void sync_data_client();

		enum ecross
		{
			ecross_ordinary,			// ����ת��
			ecross_cross_ordinary,		// ���ת��
			ecross_none,				// ����ת��
		};

		//# ����forward_type��ָ��ת������
		template <typename T>
		ecross forward_type(T& adata)
		{
			return ecross_ordinary;
		}

		ecross forward_type(pbnet::PROBUFF_NET_CHAT& adata)
		{
			int lnow = localtime::gettime();
			if (lnow < m_info.notalkutc())
			{

				auto pro = std::make_shared<pbnet::PROBUFF_NET_ERROR>();
				pro->set_m_errmessage("no talk!!!!");
				send_client(id_guid(), pro);
				return ecross_none;
			}
			return adata.m_channelid() == 2 ? ecross_cross_ordinary : ecross_ordinary;
		}

		//# ����forward_before��ָ��ת��ǰ�¼�
		template <typename T>
		void forward_before(T& adata)
		{
		}

		//# ת��"��������"ǰ
		void forward_before(pbnet::PROBUFF_NET_CREATE_FAMIL& adata);

		//# ����dataid��ָ��ת��ģ���dataid
		template <typename T>
		int32_t forward_dataid(T& adata)
		{
			return nguid::none_actordataid();
		}

		template <ENUM_ACTOR ACTOR, typename T>
		bool handle_forward(message<T>& adata)
		{
			std::shared_ptr<mforward<T>> pro(nullptr);
			if (adata.get_shared_data() == nullptr)
			{
				pro = std::make_shared<mforward<T>>(id_guid(), *adata.get_data());
			}
			else
			{
				pro = std::make_shared<mforward<T>>(id_guid(), adata.get_shared_data());
			}
			i64_actorid lguid;
			switch (forward_type(*adata.get_data()))
			{
			case ecross_ordinary:
				lguid = nguid::make(ACTOR, ttab_servers::tab()->m_area, forward_dataid(*adata.get_data()));
				break;
			case ecross_cross_ordinary:
				lguid = nguid::make(ACTOR, ttab_servers::tab()->m_crossarea, forward_dataid(*adata.get_data()));
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
		using handle_cmd = cmd<actor_role, std::string, actor_role*, const char*>;
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

		//# ��ȡ������
		bool handle(message<pbnet::PROBUFF_NET_TASK_RECEIVE_AWARD>& adata);

		int32_t rechange(std::string& aorderid, int32_t arechargeid, bool agm, bool areporting);

		//# ���󴴽�����
		void createorder(std::string& aorder, int32_t arechargeid);

		//# gm����
		bool handle(message<mforward<np_gm>>& adata);

		//# �Ƿ��״γ�ֵ
		bool is_first_recharge(int32_t arechargeid);

		//# ��ʱ��
		bool timer_handle(message<timerparm>& adata);
	};
}//namespace ngl


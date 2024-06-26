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
		//rolekv		 m_rolekv;
		attribute	 m_attribute;
		i32_serverid m_gatewayid;
		i64_actorid  m_playactorid;
	public:
		actor_role(const actor_role&) = delete;
		actor_role& operator=(const actor_role&) = delete;

		actor_role(i16_area aarea, i32_actordataid aroleid, void* adata);

		virtual i32_serverid get_getwayserverid();

		virtual void init();

		//# 注册需要处理的协议
		static void nregister();

		virtual ~actor_role();

		virtual void loaddb_finish(bool adbishave);

		using handle_rechangecmd = cmd<actor_role, std::string, int, ngl::json_read&>;

		//# 执行handle之后调用
		virtual void handle_after();

		i64_actorid roleid();

		//# 设置更新角色属性
		void update_attribute(EnumModule amodule, attribute_value& avalue)
		{
			m_attribute.updata(amodule, avalue);
		}

		/*template <typename T>
		void send2client(std::shared_ptr<T>& adata)
		{
			actor_base::send_client(m_gatewayid, id_guid(), adata);
		}*/

		void sync_data_client();

		enum ecross
		{
			ecross_ordinary,			// 本服转发
			ecross_cross_ordinary,		// 跨服转发
			ecross_play,				// 玩法转发(但是转发的actorid已确认)
		};

		//# 重载(跨服模块转发)
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

		template <typename T>
		inline std::shared_ptr<mforward<T>> forward_pro(message<T>& adata)
		{
			std::shared_ptr<mforward<T>> lshared;
			if (adata.get_shared_data() == nullptr)
			{
				lshared = std::make_shared<mforward<T>>(
					id_guid(),
					adata.get_data()
				);
			}
			else
			{
				lshared = std::make_shared<mforward<T>>(
					id_guid(),
					adata.get_shared_data()
				);
			}
			return lshared;
		}

		template <ENUM_ACTOR ACTOR, typename T>
		bool handle_forward(message<T>& adata)
		{
			std::shared_ptr<mforward<T>> pro(nullptr);
			if (adata.get_shared_data() == nullptr)
			{
				pro = std::make_shared<mforward<T>>(
					id_guid(),
					*adata.get_data()
				);
			}
			else
			{
				pro = std::make_shared<mforward<T>>(
					id_guid(),
					adata.get_shared_data()
				);
			}
			i64_actorid lguid;
			switch (forward_way(*adata.get_data()))
			{
			case ecross_ordinary:
				lguid = nguid::make(
					ACTOR, 
					ttab_servers::tab()->m_area, 
					dataid(*adata.get_data()
					)
				);
				break;
			case ecross_cross_ordinary:
				lguid = nguid::make(
					ACTOR, 
					ttab_servers::tab()->m_crossarea, 
					dataid(*adata.get_data()
					)
				);
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

		//# 登录请求未发货充值
		void loginpay();

		using handle_cmd = cmd<actor_role, std::string, actor_role*, const char*>;

		//# CMD 协议
		bool handle(message<pbnet::PROBUFF_NET_CMD>& adata);

		//# 获取role数据
		bool handle(message<pbnet::PROBUFF_NET_ROLE_SYNC>& adata);

		//# 获取服务器时间
		bool handle(message<pbnet::PROBUFF_NET_GET_TIME>& adata);

		//# 切换线路服务器
		bool handle(message<pbnet::PROBUFF_NET_SWITCH_LINE>& adata);

		//# 发送物品
		bool handle(message<np_actor_senditem>& adata);

		//# 断开连接
		bool handle(message<np_actor_disconnect_close>& adata);

		//# 玩法创建成功  记录玩法actorid
		bool handle(message<pbnet::PROBUFF_NET_MATCHING_SUCCESS_RESPONSE>& adata);

		//# 领取任务奖励
		bool handle(message<pbnet::PROBUFF_NET_TASK_RECEIVE_AWARD>& adata);

		//# 创建军团
		bool handle(message<pbnet::PROBUFF_NET_CREATE_FAMIL>& adata);

		int32_t rechange(std::string& aorderid, int32_t arechargeid, bool agm, bool areporting);

		//# 请求创建订单
		void createorder(std::string& aorder, int32_t arechargeid);

		//# gm请求
		bool handle(message<mforward<np_gm>>& adata);

		//# 是否首次充值
		bool is_first_recharge(int32_t arechargeid);

		//# 定时器
		bool timer_handle(message<timerparm>& adata);
	};
}//namespace ngl


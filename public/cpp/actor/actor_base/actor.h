﻿#pragma once

#include "actor_base.h"
#include "actor_type.h"
#include "nactortype.h"
#include "nrfun.h"
#include "impl.h"

namespace ngl
{
	struct actorparm
	{
		actorparmbase m_parm;
		int m_weight = 10;
		bool m_broadcast = false;
	};

	template <typename T>
	constexpr T* null = (T*)nullptr;

	class actor : public actor_base
	{
		struct impl_actor;
		ngl::impl<impl_actor> m_impl_actor;

		std::array<nrfunbase*, EPROTOCOL_TYPE_COUNT> m_actorfun;
	public:

#pragma region register
		template <typename TDerived>
		void init_rfun()
		{
			m_actorfun[EPROTOCOL_TYPE_CUSTOM]		= &nrfun<TDerived, EPROTOCOL_TYPE_CUSTOM>::instance();
			m_actorfun[EPROTOCOL_TYPE_PROTOCOLBUFF] = &nrfun<TDerived, EPROTOCOL_TYPE_PROTOCOLBUFF>::instance();

			if (isbroadcast())
			{
				register_actornonet<EPROTOCOL_TYPE_CUSTOM, TDerived>(
					true, 
					(Tfun<actor, actor_broadcast>) & actor::handle
				);
			}
		}

		// #### 注册定时器
		template <typename TDerived>
		static void register_timer(Tfun<TDerived, timerparm> afun/* = &TDerived::timer_handle*/)
		{
			nrfun<TDerived, EPROTOCOL_TYPE_CUSTOM>::instance().template rfun_nonet<TDerived, timerparm>(afun, false);
		}

		template <pbdb::ENUM_DB DBTYPE, typename TDBTAB>
		class db_pair{};

		// #### 注册db加载
		template <EPROTOCOL_TYPE TYPE, typename TDerived, pbdb::ENUM_DB DBTYPE, typename TDBTAB>
		static void register_db(const db_pair<DBTYPE, TDBTAB>*)
		{
			using tloaddb = actor_db_load_response<TYPE, DBTYPE, TDBTAB>;
			auto lpfun = &actor_base::template handle<TYPE, DBTYPE, TDBTAB, TDerived>;
			nrfun<TDerived, TYPE>::instance().template rfun<actor_base, tloaddb>(lpfun, true);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, pbdb::ENUM_DB DBTYPE, typename TDBTAB, typename ...ARG>
		static void register_db(const db_pair<DBTYPE, TDBTAB>* ap, const ARG*... arg)
		{
			register_db<TYPE, TDerived>(ap);
			register_db<TYPE, TDerived>(arg...);
		}

		// #### 用来注册匿名函数挂载在对应actor上
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actor_s(const std::function<void(TDerived*, T&)>& afun)
		{
			nrfun<TDerived, TYPE>::instance().template rfun<TDerived, T>(afun);
		}

#pragma region register_actor

		// #### 简化[handle]方法注册
		#define dregister_fun_handle(TDerived,T)		(Tfun<TDerived, T>)&TDerived::handle
		#define dregister_fun(TDerived,T, Fun)			(Tfun<TDerived, T>)&TDerived::Fun

		// #### 注册actor成员函数
		template <
			EPROTOCOL_TYPE TYPE			// 协议类型
			, typename TDerived			// 注册的actor派生类
			, typename T				// Tfun<TDerived, T>
		>
		static void register_actor(bool aisload, ENUM_ACTOR atype, T afun)
		{
			nrfun<TDerived, TYPE>::instance().rfun(afun, atype, aisload);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_actor(bool aisload, ENUM_ACTOR atype, T afun, ARG... argfun)
		{
			register_actor<TYPE, TDerived>(aisload, atype, afun);
			register_actor<TYPE, TDerived, ARG...>(aisload, atype, argfun...);
		}

		template <EPROTOCOL_TYPE TYPE , typename TDerived , typename T>
		static void register_actor(bool aisload, T afun)
		{
			nrfun<TDerived, TYPE>::instance().rfun(afun, aisload);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_actor(bool aisload, T afun, ARG... argfun)
		{
			register_actor<TYPE, TDerived>(aisload, afun);
			register_actor<TYPE, TDerived, ARG...>(aisload, argfun...);
		}
#pragma endregion 

#pragma region register_actornonet
		// ## 与register_actor类似 只不过不注册网络层
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actornonet(bool aisload, T afun)
		{
			nrfun<TDerived, TYPE>::instance().rfun_nonet(afun, aisload);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_actornonet(bool aisload, T apdata, ARG... arg)
		{
			register_actornonet<TYPE, TDerived>(aisload, apdata);
			register_actornonet<TYPE, TDerived>(aisload, arg...);
		}
#pragma endregion 
	private:
		friend class gameclient_forward;

		// ### 注册 [forward:转发协议]
		template <EPROTOCOL_TYPE TYPE, bool IsForward, typename TDerived, typename T>
		static void register_forward(T afun)
		{
			nrfun<TDerived, TYPE>::instance().template rfun_forward<IsForward>(afun, actor_type<TDerived>::type(), false);
		}

		template <EPROTOCOL_TYPE TYPE, bool IsForward, typename TDerived, typename T, typename ...ARG>
		static void register_forward(T ap, ARG... arg)
		{
			register_forward<TYPE, IsForward, TDerived, T>(ap);
			register_forward<TYPE, IsForward, TDerived, ARG...>(arg...);
		}

		// 注册 [forward:转发协议] recvforward
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_recvforward(T afun)
		{
			nrfun<TDerived, TYPE>::instance().rfun_recvforward(afun, false);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_recvforward(T ap, ARG... arg)
		{
			register_recvforward<TYPE, TDerived>(ap);
			register_recvforward<TYPE, TDerived>(arg...);
		}
#pragma endregion 
	public:
		explicit actor(const actorparm& aparm);

		virtual ~actor();

		virtual actor_stat get_activity_stat() final;

		virtual void set_activity_stat(actor_stat astat) final;
	private:
		virtual void release() final;

		virtual bool list_empty() final;

		virtual void push(handle_pram& apram) final;

		virtual void clear_task() final;

		virtual void actor_handle(i32_threadid athreadid) final;
	public:
#pragma region ActorBroadcast
		// ############# Start[Actor 全员广播] ############# 
		// ## 间隔一段时间发起的全员(所有actor)广播
		// ## 可以在这个广播里推送一些需要处理的任务,例如 保存数据
		// ## 与actor_base::start_broadcast() 相呼应
		// ## 重载此方法实现actor_base::m_broadcast毫秒触发事件
		virtual void broadcast() {}
		// ## 广播处理函数
		bool handle(message<actor_broadcast>& adata);
		// ############# End[Actor 全员广播] ############# 
#pragma endregion

	};


}
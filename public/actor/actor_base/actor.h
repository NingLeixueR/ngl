#pragma once

#include "actor_enum.h"
#include "actor_base.h"
#include "actor_rfun.h"
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

		std::array<arfunbase*, EPROTOCOL_TYPE_COUNT> m_actorfun;		
	public:
#pragma region register
		template <typename TDerived>
		void init_rfun()
		{
			m_actorfun[EPROTOCOL_TYPE_CUSTOM] = &arfun<TDerived, EPROTOCOL_TYPE_CUSTOM>::instance();
			m_actorfun[EPROTOCOL_TYPE_PROTOCOLBUFF] = &arfun<TDerived, EPROTOCOL_TYPE_PROTOCOLBUFF>::instance();
		
			if (isbroadcast())
			{
				register_actornonet_s<EPROTOCOL_TYPE_CUSTOM, TDerived>(
					true
					, null<actor_broadcast>
				);
			}
		}

		// ע�ᶨʱ��
		template <typename TDerived>
		static void register_timer()
		{
			arfun<TDerived, EPROTOCOL_TYPE_CUSTOM>::instance().rfun_nonet<timerparm>(
					&TDerived::timer_handle
					, false
				);
		}

		template <pbdb::ENUM_DB DBTYPE, typename TDBTAB>
		class db_pair
		{
		public:
			using dbtab = TDBTAB;
			enum
			{
				dbenum = DBTYPE
			};
		};

	private:
		template <EPROTOCOL_TYPE PROTYPE, pbdb::ENUM_DB DBTYPE, typename TDBTAB, typename TACTOR>
		friend class actor_dbclient;
		// #### ע��db����
		template <EPROTOCOL_TYPE TYPE, typename TDerived, pbdb::ENUM_DB DBTYPE, typename TDBTAB>
		static void register_db(const db_pair<DBTYPE, TDBTAB>*)
		{
			arfun<TDerived, TYPE>::instance().rfun<actor_db_load_response<TYPE, DBTYPE, TDBTAB>>(
					&actor_base::template handle<TYPE, DBTYPE, TDBTAB, TDerived>
					, true
				);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, pbdb::ENUM_DB DBTYPE, typename TDBTAB, typename ...ARG>
		static void register_db(const db_pair<DBTYPE, TDBTAB>* ap, const ARG*... arg)
		{
			register_db<TYPE, TDerived>(ap);
			register_db<TYPE, TDerived>(arg...);
		}
	public:
		
		// ����ע���������������ڶ�Ӧactor��
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actor_s(const std::function<void(T&)>& afun)
		{
			arfun<TDerived, TYPE>::instance().rfun<T>(afun);
		}

#pragma region register_actor
		// ע��actor��Ա����[handle]
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actor(bool aisload, const T*)
		{
			arfun<TDerived, TYPE>::instance().rfun<T>(&TDerived::handle, aisload);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_actor(bool aisload, const T* apdata, const ARG*... arg)
		{
			register_actor<TYPE, TDerived, T>(aisload, apdata);
			register_actor<TYPE, TDerived, ARG...>(aisload, arg...);
		}
#pragma endregion 

#pragma region register_actornonet
		// ## ��register_actor���� ֻ������ע�������
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actornonet(bool aisload, const T*)
		{
			arfun<TDerived, TYPE>::instance().rfun_nonet<T>(&TDerived::handle, aisload);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_actornonet(bool aisload, const T* apdata, const ARG*... arg)
		{
			register_actornonet<TYPE, TDerived>(aisload, apdata);
			register_actornonet<TYPE, TDerived>(aisload, arg...);
		}
#pragma endregion 

	private:
		// ע��actor���handle
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actornonet_s(bool aisload, const T*)
		{
			arfun<TDerived, TYPE>::instance().rfun_nonet<T>(&actor::handle, aisload);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_actornonet_s(bool aisload, const T* apdata, const ARG*... arg)
		{
			register_actornonet_s<TYPE, TDerived>(aisload, apdata);
			register_actornonet_s<TYPE, TDerived>(aisload, arg...);
		}
	public:

	private:
		friend class gateway_game_forward;
		// ### ע�� [forward:ת��Э��]
		template <EPROTOCOL_TYPE TYPE, bool IsForward, typename TDerived, typename T>
		static void register_forward(TDerived* aderived, const T*)
		{
			arfun<TDerived, TYPE>::instance()
				.rfun_forward<T, IsForward>(
					&TDerived::handle
					, (ENUM_ACTOR)TDerived::ACTOR_TYPE
					, false
				);
		}

		template <EPROTOCOL_TYPE TYPE, bool IsForward, typename TDerived, typename T, typename ...ARG>
		static void register_forward(TDerived* aderived, const T* ap, const ARG*... arg)
		{
			register_forward<TYPE, IsForward, TDerived, T>(aderived, ap);
			register_forward<TYPE, IsForward, TDerived, ARG...>(aderived, arg...);
		}

		// ע�� [forward:ת��Э��] recvforward
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_recvforward(const T*)
		{
			arfun<TDerived, TYPE>::instance()
				.rfun_recvforward<T>(
					&TDerived::handle
					, false
				);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_recvforward(const T* ap, const ARG*... arg)
		{
			register_recvforward<TYPE, TDerived>(ap);
			register_recvforward<TYPE, TDerived>(arg...);
		}

#pragma endregion 
	public:
		actor(const actorparm& aparm);

		virtual ~actor();

		virtual actor_stat get_activity_stat();
		virtual void set_activity_stat(actor_stat astat);

	private:
		virtual void release() final;
		virtual bool list_empty();
		virtual void push(handle_pram& apram);
		virtual void clear_task();
		virtual void actor_handle(i32_threadid athreadid);
	public:
#pragma region ActorBroadcast
		// ############# Start[Actor ȫԱ�㲥] ############# 
		// ## ���һ��ʱ�䷢���ȫԱ(����actor)�㲥
		// ## ����������㲥������һЩ��Ҫ���������,���� ��������
		// ## ��actor_base::start_broadcast() ���Ӧ
		// ## ���ش˷���ʵ��actor_base::m_broadcast���봥���¼�
		virtual void broadcast() {}

		// �㲥������
		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, actor_broadcast& adata);

		// ############# End[Actor ȫԱ�㲥] ############# 
#pragma endregion

	};

}
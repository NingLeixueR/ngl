#pragma once

#include "template_arg.h"
#include "nactor_type.h"
#include "nactortype.h"
#include "actor_base.h"
#include "nrfun.h"
#include "impl.h"
#include "nlog.h"

namespace ngl
{
	struct actorparm
	{
		actorparmbase	m_parm;
		int				m_weight	= 10;			// Ȩ��:���λ�ȡ�̺߳�����Ϣ������		
		bool			m_broadcast	= false;		// �Ƿ�֧�ֹ㲥
	};

	template <typename T>
	constexpr T* null = (T*)nullptr;

	class actor : 
		public actor_base
	{
		struct impl_actor;
		ngl::impl<impl_actor> m_impl_actor;

		std::array<nrfunbase*, EPROTOCOL_TYPE_COUNT> m_actorfun;
	public:

#pragma region register // ��Ϣע��ӿ�
		template <typename TDerived, EPROTOCOL_TYPE TYPE>
		static nrfun<TDerived, TYPE>& ninst()
		{
			return nrfun<TDerived, TYPE>::instance();
		}

		template <typename TDerived>
		void init_rfun()
		{
			m_actorfun[EPROTOCOL_TYPE_CUSTOM]
				= &ninst<TDerived, EPROTOCOL_TYPE_CUSTOM>();
			m_actorfun[EPROTOCOL_TYPE_PROTOCOLBUFF]
				= &ninst<TDerived, EPROTOCOL_TYPE_PROTOCOLBUFF>();
		
			if (isbroadcast())
			{
				register_actornonet<EPROTOCOL_TYPE_CUSTOM, TDerived>(true, (Tfun<actor, np_actor_broadcast>) & actor::handle);
			}

			register_actornonet<EPROTOCOL_TYPE_CUSTOM, TDerived>(true, (Tfun<actor, np_actor_close>) & actor::handle);
		}

		//# ע�ᶨʱ��
		template <typename TDerived>
		static void register_timer(Tfun<TDerived, timerparm> afun = &TDerived::timer_handle)
		{
			ninst<TDerived, EPROTOCOL_TYPE_CUSTOM>().template rfun_nonet<TDerived, timerparm>(afun, false);
		}

		template <pbdb::ENUM_DB DBTYPE, typename TDBTAB>
		class db_pair{};

		//# ע��db����
		template <EPROTOCOL_TYPE TYPE, typename TDerived, pbdb::ENUM_DB DBTYPE, typename TDBTAB>
		static void register_db(const db_pair<DBTYPE, TDBTAB>*)
		{
			auto lfun = &actor_base::template handle<TYPE, DBTYPE, TDBTAB, TDerived>;
			ninst<TDerived, TYPE>().template rfun<actor_base, np_actordb_load_response<TYPE, DBTYPE, TDBTAB>>(lfun, true);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, pbdb::ENUM_DB DBTYPE, typename TDBTAB, typename ...ARG>
		static void register_db(const db_pair<DBTYPE, TDBTAB>* ap, const ARG*... arg)
		{
			register_db<TYPE, TDerived>(ap);
			register_db<TYPE, TDerived>(arg...);
		}

		//# ����ע���������������ڶ�Ӧactor��
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actor_s(const std::function<void(TDerived*, T&)>& afun)
		{
			ninst<TDerived, TYPE>().template rfun<TDerived, T>(afun);
		}

#pragma region register_actor

		//# ��[handle]����ע��
		#define dregister_fun_handle(TDerived,T)		(Tfun<TDerived, T>)&TDerived::handle
		#define dregister_fun(TDerived, T, Fun)			(Tfun<TDerived, T>)&TDerived::Fun

		//////////////////////////////////////////////////////////////////////
		//################ ע��actor��Ա����(�����Ƿ�handle) #################
		template <EPROTOCOL_TYPE TYPE , typename TDerived , typename T>
		static void register_actor(bool aisload, T afun)
		{
			ninst<TDerived, TYPE>().rfun(afun, aisload);
		}

		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T, typename ...ARG>
		static void register_actor(bool aisload, T afun, ARG... argfun)
		{
			register_actor<TYPE, TDerived>(aisload, afun);
			register_actor<TYPE, TDerived, ARG...>(aisload, argfun...);
		}

		//################ ע��actor��Աhandle���� #################
		template <EPROTOCOL_TYPE TYPE, typename TDerived>
		class register_actor_handle
		{
		public:
			template <typename T>
			static void func(bool aisload)
			{
				ninst<TDerived, TYPE>().rfun((Tfun<TDerived, T>) & TDerived::handle, aisload);
			}
		};

		template <EPROTOCOL_TYPE TYPE, typename TDerived>
		using type_register_actor_handle = template_arg<actor::register_actor_handle<TYPE, TDerived>, bool>;
		//////////////////////////////////////////////////////////////////////////////////////
#pragma endregion 

#pragma region register_actornonet
		//# ��register_actor���� ֻ������ע�������
		template <EPROTOCOL_TYPE TYPE, typename TDerived, typename T>
		static void register_actornonet(bool aisload, T afun)
		{
			ninst<TDerived, TYPE>().rfun_nonet(afun, aisload);
		}
#pragma endregion 
	private:
		friend class nforward;

		//# ע�� [forward:ת��Э��]
		template <EPROTOCOL_TYPE TYPE, bool IsForward, typename TDerived>
		class register_forward_handle
		{
		public:
			template <typename T>
			static void func()
			{
				ninst<TDerived, TYPE>().
					template rfun_forward<IsForward>((Tfun<TDerived, np_actor_forward<T, TYPE, IsForward, ngl::forward>>) & TDerived::handle, nactor_type<TDerived>::type(), false);
			}
		};

		template <EPROTOCOL_TYPE TYPE, bool IsForward, typename TDerived>
		using type_register_forward_handle = template_arg<actor::register_forward_handle<TYPE, IsForward, TDerived>>;

		//# ע�� [forward:ת��Э��] recvforward
		template <EPROTOCOL_TYPE TYPE, typename TDerived>
		class register_recvforward_handle
		{
		public:
			template <typename T>
			static void func()
			{
				ninst<TDerived, TYPE>().rfun_recvforward((Tfun<TDerived, T>) & TDerived::handle, false);
			}
		};

		template <EPROTOCOL_TYPE TYPE, typename TDerived>
		using type_register_recvforward_handle = template_arg<actor::register_recvforward_handle<TYPE, TDerived>>;

		//# �����ڶ���ת��
		template <EPROTOCOL_TYPE TYPE, ENUM_ACTOR ACTOR, typename TDerived>
		class register_recvforward_handle2
		{
		public:
			template <typename T>
			static void func()
			{
				ninst<TDerived, TYPE>().rfun_recvforward((Tfun<TDerived, T>) & TDerived::template handle_forward<ACTOR, T>, false);
			}
		};

		template <EPROTOCOL_TYPE TYPE, ENUM_ACTOR ACTOR, typename TDerived>
		using type_register_recvforward_handle2 = template_arg<actor::register_recvforward_handle2<TYPE, ACTOR, TDerived>>;

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
		// ############# Start[Actor ȫԱ�㲥] ############# 
		// ## ���һ��ʱ�䷢���ȫԱ(����actor)�㲥
		// ## ����������㲥������һЩ��Ҫ���������,���� ��������
		// ## ��actor_base::start_broadcast() ���Ӧ
		// ## ���ش˷���ʵ��actor_base::m_broadcast���봥���¼�
		virtual void broadcast() {}
		// ## �㲥������
		bool handle(message<np_actor_broadcast>& adata);
		// ############# End[Actor ȫԱ�㲥] ############# 
#pragma endregion

		bool handle(message<np_actor_close>& adata)
		{
			erase_actor_byid();
			return true;
		}
	};
}//namespace ngl
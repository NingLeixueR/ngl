#pragma once

#include "actor_client.h"
#include "actor_base.h"
#include "threadtools.h"
#include "naddress.h"
#include "nthread.h"
#include "pack.h"
#include "impl.h"
#include "net.h"

#include <list>
#include <map>
#include <set>

namespace ngl
{
	class actor_manage
	{
		struct impl_actor_manage;
		ngl::impl<impl_actor_manage> m_impl_actor_manage;

		actor_manage();
		~actor_manage();
	public:
		static actor_manage& getInstance()
		{
			static actor_manage ltemp;
			return ltemp;
		}

		// ��ʼ�� ���ù����߳�����
		void init(i32_threadsize apthreadnum);

		// ��ȡ�����̴��ڵ�actor����
		void get_type(std::vector<i16_actortype>& aactortype);

		// ���actor
		bool add_actor(actor_base* apactor, const std::function<void()>& afun);
		bool add_actor(ptractor& apactor, const std::function<void()>& afun);

		// �Ƴ�actor
		void erase_actor_byid(const nguid& aguid, const std::function<void()>& afun = nullptr);

		// �Ƿ����ĳ��actor
		bool is_have_actor(const nguid& aguid);

		// �����߳̽�actor��ӵ�m_actorlist
		void push(ptractor& apactor, nthread* atorthread = nullptr);

		// ��actor���������
		void push_task_id(const nguid& aguid, handle_pram& apram, bool abool);

		// ��ĳ�����͵�actor���������
		void push_task_type(ENUM_ACTOR atype, handle_pram& apram, bool aotherserver = false);

		// ��ǰ��������actor�㲥��Ϣ
		void broadcast_task(handle_pram& apram);

		// ## ��ʱ���������̣߳���ִ�е�������(�ȸ����ݱ�)
		void statrt_suspend_thread();
		void finish_suspend_thread();
	};

	class actor_suspendthread
	{
	public:
		actor_suspendthread()
		{
			LogLocalInfo("start actor_suspendthread");
			actor_manage::getInstance().statrt_suspend_thread();
		}

		~actor_suspendthread()
		{
			Try
			{
				actor_manage::getInstance().finish_suspend_thread();
				LogLocalInfo("finish actor_suspendthread");
			}Catch;			
		}
	};

	template <typename T>
	T& actor_instance<T>::instance()
	{
		static T ltemp;
		static bool first = true;
		if (first)
		{
			Try
			{
				first = false;
				T* lptemp = &ltemp;
				actor_manage::getInstance().add_actor(&ltemp, [lptemp]()
				{
						Try
						{
							lptemp->set_activity_stat(actor_stat_free);
							lptemp->init();
							lptemp->init_db_component(false);
						}
						Catch;
				});
				ltemp.template init_rfun<T>();
				T::nregister();
			}Catch;
		}
		return ltemp;
	}
}//namespace ngl

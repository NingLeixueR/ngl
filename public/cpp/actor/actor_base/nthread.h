#pragma once

#include "threadtools.h"
#include "handle_pram.h"
#include "actor_base.h"
#include "impl.h"

namespace ngl
{
	class nthread
	{
		nthread() = delete;
		nthread(const nthread&) = delete;
		nthread& operator=(const nthread&) = delete;

		struct impl_nthread;
		ngl::impl<impl_nthread> m_impl_actor_thread;
	public:
		nthread(i32_threadid aid);
		// # �����߳�id
		i32_threadid id();
		// # �Ƿ��Ծ
		bool isactivity();
		// # ���߳������actor
		void push(ptractor aactor);
	private:
		void run();
	};
}//namespace ngl




#pragma once

#include "nprotocol.h"
#include "actor.h"

namespace ngl
{
	// # ����ĳ��actor��db���ݷ����仯��Ҫͬ��������actor
	template <typename DB_TAB>
	class module_db_sync
	{
		actor* m_actor;
	public:
		module_db_sync(actor* aactor)
		void sync(std::shared_ptr<np_module_sync<DB_TAB>>& apro)
		{
			actor::static_send_actor()
			actor::static_send_actor();
		}
	};


}// namespace ngl
#include "ndbclient.h"

namespace ngl
{
	bool actor::handle(message<actor_broadcast>& adata)
	{
		// ## ��������
		if (get_actor_manage_dbclient() != nullptr)
		{
			get_actor_manage_dbclient()->save();
			get_actor_manage_dbclient()->del();
		}
		// ## actor�������Զ��崦���߼�
		broadcast();
		return true;
	}
}//namespace ngl

#include "actor_db_client.h"


namespace ngl
{
	bool actor::handle(i32_threadid athread, const std::shared_ptr<pack>& apack, actor_broadcast& adata)
	{
		// ## 保存数据
		if (get_actor_manage_dbclient() != nullptr)
		{
			get_actor_manage_dbclient()->save();
			get_actor_manage_dbclient()->del();
		}
		// ## actor派生类自定义处理逻辑
		broadcast();
		return true;
	}
}

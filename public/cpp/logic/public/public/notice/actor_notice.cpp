#include "actor_notice.h"

namespace ngl
{
	actor_notice::actor_notice() :
		actor(
			actorparm
			{
				.m_parm
				{
					.m_type = ACTOR_NOTICE,
					.m_area = ttab_servers::tab()->m_area,
					.m_manage_dbclient = true,
				},
				.m_weight = 0x7fffffff,
				.m_broadcast = true,
			})
	{
	}

	void actor_notice::nregister()
	{
		// Э��ע��
		register_actor<EPROTOCOL_TYPE_CUSTOM, actor_notice>(
			true
			, dregister_fun_handle(actor_notice, mforward<np_gm>)
		);
	}
}
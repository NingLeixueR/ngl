#pragma once

#include "actor_manage.h"
#include "actor_create.h"
#include "ndb_modular.h"
#include "nsp_server.h"
#include "nsp_client.h"
#include "db_manage.h"
#include "ndbclient.h"
#include "nprotocol.h"
#include "ranklist.h"
#include "db_data.h"
#include "db_pool.h"
#include "ntimer.h"
#include "notice.h"
#include "net.h"
#include "db.h"

namespace ngl
{
	class actor_ranklist : public actor
	{
		actor_ranklist(const actor_ranklist&) = delete;
		actor_ranklist& operator=(const actor_ranklist&) = delete;

		ranklist m_ranklist;

		using nclient = nsp_client<
			echannel_brief,
			actor_ranklist,
			pbdb::db_brief
		>;

		actor_ranklist();
	public:
		friend class actor_instance<actor_ranklist>;
		static actor_ranklist& getInstance()
		{
			return actor_instance<actor_ranklist>::instance();
		}

		virtual void init()
		{
			m_ranklist.set(this);
		}

		static void nregister()
		{
		}

		virtual ~actor_ranklist() {}

		virtual void loaddb_finish(bool adbishave) {}

		/*bool handle(message<mforward<GM::PROBUFF_GM_GET_NOTICE>>& adata)
		{
			using type = mforward<GM::PROBUFF_GM_GET_NOTICE_RESPONSE>;
			std::shared_ptr<type> pro(new type(adata.identifier()));
			get_notice_list(*pro->add_data());
			send_actor(nguid::make_self(ACTOR_GM), pro);
			return true;
		}*/
	};
}// namespace ngl
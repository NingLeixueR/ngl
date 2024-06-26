#pragma once

#include "actor_manage.h"
#include "actor_create.h"
#include "nprotocol.h"
#include "ndbclient.h"
#include "logprintf.h"
#include "db_manage.h"
#include "db_data.h"
#include "db_pool.h"
#include "ntimer.h"
#include "net.h"
#include "db.h"

#include <fstream>
#include <memory>

namespace ngl
{
	class actor_log : public actor
	{
		actor_log() = delete;
		actor_log(const actor_log&) = delete;
		actor_log& operator=(const actor_log&) = delete;

		std::shared_ptr<logfile> m_log;
	public:
		actor_log(i32_actordataid aid);

		virtual void init();

		static void nregister();

		static i64_actorid actorid(ENUM_ACTOR aactortype, ELOG_TYPE alogtype);

		virtual ~actor_log();

		bool handle(message<np_actor_logitem>& adata);
	};
}//namespace ngl
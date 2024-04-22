#include "actor_manage_activity.h"
#include "actor_manage_plays.h"
#include "actor_manage_role.h"
#include "actor_gatewayc2g.h"
#include "actor_gatewayg2c.h"
#include "actor_reloadcsv.h"
#include "actor_ranklist.h"
#include "actor_matching.h"
#include "actor_ugpalace.h"
#include "actor_calendar.h"
#include "actor_gateway.h"
#include "actor_notice.h"
#include "actor_server.h"
#include "actor_client.h"
#include "actor_create.h"
#include "actor_login.h"
#include "actor_robot.h"
#include "actor_brief.h"
#include "actor_cross.h"
#include "actor_chat.h"
#include "actor_mail.h"
#include "actor_role.h"
#include "actor_kcp.h"
#include "actor_log.h"
#include "actor_db.h"
#include "actor_gm.h"
#include "nactor_type.h"
#include "nactortype.h"
#include "enum2name.h"
#include "initproto.h"
#include "nprotocol.h"
#include "ntimer.h"
#include "net.pb.h"
#include "actor.h"

namespace ngl
{
	template <typename TK, typename TV>
	void em_actor(const TK akey, const TV aval)
	{
		em<ENUM_ACTOR>::set(akey, aval);
	}

	ENUM_ACTOR db_enum(EPROTOCOL_TYPE PROTYPE, pbdb::ENUM_DB TDBTAB_TYPE)
	{
		return (ENUM_ACTOR)(PROTYPE * 1000 + ACTOR_DB + TDBTAB_TYPE);
	}

	template <pbdb::ENUM_DB DBTYPE, typename TDB>
	void init_customs_db()
	{
		initproto::init_customs(
			EPROTOCOL_TYPE_PROTOCOLBUFF
			, null<np_actordb_load<EPROTOCOL_TYPE_PROTOCOLBUFF, DBTYPE, TDB>>
			, null<np_actordb_load_response<EPROTOCOL_TYPE_PROTOCOLBUFF, DBTYPE, TDB>>
			, null<np_actordb_save<EPROTOCOL_TYPE_PROTOCOLBUFF, DBTYPE, TDB>>
			, null<np_actordb_delete<EPROTOCOL_TYPE_PROTOCOLBUFF, DBTYPE, TDB>>
			, null<np_actortime_db_cache<EPROTOCOL_TYPE_PROTOCOLBUFF, TDB>>
		);
	}

	template <EPROTOCOL_TYPE PROTYPE, pbdb::ENUM_DB TDBTAB_TYPE, typename TDBTAB>
	void initdb()
	{
		ENUM_ACTOR lenum = db_enum(PROTYPE, TDBTAB_TYPE);
		nactor_type<
			ngl::actor_db<EPROTOCOL_TYPE_PROTOCOLBUFF, TDBTAB_TYPE, TDBTAB>
		>::inits(lenum);

		init_customs_db<TDBTAB_TYPE, TDBTAB>();
		nactor_type<ngl::actor_db<EPROTOCOL_TYPE_PROTOCOLBUFF, TDBTAB_TYPE, TDBTAB>>::inits(lenum);

		LogLocalError("init_actor_type [%]-[%]",
			boost::typeindex::type_id_with_cvr<
			ngl::actor_db<EPROTOCOL_TYPE_PROTOCOLBUFF, TDBTAB_TYPE, TDBTAB>
			>().pretty_name(),
			(int)(PROTYPE * 1000 + ACTOR_DB + TDBTAB_TYPE)
		);
	}

	template <typename TACTOR>
	void auto_actor(const TACTOR* aactor, ENUM_ACTOR aenum, const char* aname)
	{
		em_actor(aenum, aname);
		nactor_type<TACTOR>::inits(aenum);
	}

	template <typename TACTOR, typename ...ARG>
	void auto_actor(const TACTOR* aactor, ENUM_ACTOR aenum, const char* aname, const ARG&... arg)
	{
		auto_actor<TACTOR>(aactor, aenum, aname);
		auto_actor(arg...);
	}

	void init_nactor_type()
	{
		// ### 新增actor需要补全
		auto_actor(
			null<actor_client>, em_pram(ACTOR_CLIENT)
			, null<actor_create>, em_pram(ACTOR_CREATE)
			, null<actor_server>, em_pram(ACTOR_SERVER)
			, null<actor_cross>, em_pram(ACTOR_CROSS)
			, null<actor_manage_role>, em_pram(ACTOR_MANAGE_ROLE)
			, null<actor_role>, em_pram(ACTOR_ROLE)
			, null<actor_gateway>, em_pram(ACTOR_GATEWAY)
			, null<actor_gatewayc2g>, em_pram(ACTOR_GATEWAY_C2G)
			, null<actor_gatewayg2c>, em_pram(ACTOR_GATEWAY_G2C)
			, null<actor_log>, em_pram(ACTOR_LOG)
			, null<actor_login>, em_pram(ACTOR_LOGIN)
			, null<actor_reloadcsv>, em_pram(ACTOR_RELOADCSV)
			, null<actor_reloadcsv_distribute>, em_pram(ACTOR_RELOADCSV_DISTRIBUTE)
			, null<actor_robot>, em_pram(ACTOR_ROBOT)
			, null<actor_manage_robot>, em_pram(ACTOR_MANAGE_ROBOT)
			, null<actor_manage_activity>, em_pram(ACTOR_ACTIVITY_MANAGE)
			, null<actor_brief>, em_pram(ACTOR_BRIEF)
			, null<actor_chat>, em_pram(ACTOR_CHAT)
			, null<actor_gm>, em_pram(ACTOR_GM)
			, null<actor_mail>, em_pram(ACTOR_MAIL)
			, null<actor_notice>, em_pram(ACTOR_NOTICE)
			, null<actor_ranklist>, em_pram(ACTOR_RANKLIST)
			, null<actor_matching>, em_pram(ACTOR_MATCHING)
			, null<actor_manage_plays>, em_pram(ACTOR_MANAGE_PLAYS)
			, null<actor_ugpalace>, em_pram(ACTOR_PLAYS_GO_UNDERGROUNDPALACE)
			, null<actor_kcp>, em_pram(ACTOR_KCP)
			, null<actor_calendar>, em_pram(ACTOR_CALENDAR)
		);

		// 新增数据存储需要补全
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_ACCOUNT, pbdb::db_account>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_ROLE, pbdb::db_role>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_BAG, pbdb::db_bag>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_KEYVALUE, pbdb::db_keyvalue>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_MAIL, pbdb::db_mail>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_GUILD, pbdb::db_guild>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_NOTICE, pbdb::db_notice>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_ACTIVITY, pbdb::db_activity>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_BRIEF, pbdb::db_brief>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_RANKLIST, pbdb::db_ranklist>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_TASK, pbdb::db_task>();
		initdb<EPROTOCOL_TYPE_PROTOCOLBUFF, pbdb::ENUM_DB_CALENDAR, pbdb::db_calendar>();

		// 新增内部协议需要补充
		initproto::init_customs(EPROTOCOL_TYPE_CUSTOM
			, null<np_gm>				// 200000001
			, null<np_gm_response>		// 200000002
			, null<mforward<np_gm>>			// 200000003
			, null<mforward<np_gm_response>>  // 200000004
			, null<timerparm>
			, null<np_robot_pram>
			, null<np_actornode_register>
			, null<np_actornode_register_response>
			, null<np_actorclient_node_connect>
			, null<np_actornode_update>
			, null<np_actornode_update_mass>
			, null<np_actornode_connect_task>
			, null<np_actorrole_login>
			, null<np_actorserver_connect>
			, null<np_actor_session_close>
			, null<np_actor_disconnect_close>
			, null<np_actor_logitem>
			, null<np_actor_broadcast>
			, null<np_actor_reloadcsv>
			, null<np_actor_csv_verify_version>
			, null<np_actor_senditem>
			, null<np_actor_roleinfo>
			, null<np_actor_gatewayinfo_updata>
			, null<np_actor_addmail>
			, null<np_actor_activity>
			, null<np_actor_gatewayid_updata>
			, null<np_actorswitch_process<np_actorswitch_process_role>>
			, null<np_actor_kcp>
			, null<np_calendar>
		);
	}
}

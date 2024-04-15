#include "actor_role.h"
#include "ttab_task.h"
#include "drop.h"

namespace ngl
{
	bool actor_role::handle(message<pbnet::PROBUFF_NET_ROLE_SYNC>& adata)
	{
		sync_data_client();
		LogLocalError("[sync]###[%]", m_info.get()->getconst().m_base().m_name())
		return true;
	}

	bool actor_role::handle(message<pbnet::PROBUFF_NET_GET_TIME>& adata)
	{
		//auto pro = std::make_shared<pbnet::PROBUFF_NET_GET_TIME_RESPONSE>();
		//pro->set_m_utc(localtime::gettime());
		//send2client(pro);
		//std::cout << "######Get Server Time##" << localtime::gettime() << std::endl;
		
		i64_actorid lrequest = adata.m_pack->m_head.get_request_actor();
		/*std::cout
			<< " type			= " << nguid::type(lrequest)
			<< " actordataid	= " << nguid::actordataid(lrequest)
			<< " area			= " << nguid::area(lrequest)
			<< std::endl;*/

		LogLocalError("type=%,actordataid=%,area=%,NAME=%", nguid::type(lrequest), nguid::actordataid(lrequest), nguid::area(lrequest), m_info.get()->getconst().m_base().m_name());

		//LogLocalError("######Get Server Time##[%][%]", m_info.id(), m_info.db()->name())

		pbnet::PROBUFF_NET_GET_TIME_RESPONSE pro;
		pro.set_m_utc(localtime::gettime());
		sendkcp(pro, lrequest);

		//
		return true;
	}

	// PROBUFF_PROTOCOLNUM_LOGIC_SWITCH_LINE		= 18;			// [����]�л���·
	bool actor_role::handle(message<pbnet::PROBUFF_NET_SWITCH_LINE>& adata)
	{
		tab_servers* tab = ttab_servers::node_tnumber(GAME, adata.m_data->m_line());
		if (tab == nullptr)
			return false;
		i32_sessionid lsession = server_session::get_sessionid(tab->m_id);
		if (lsession == -1)
		{
			LogLocalError("LOGIC_SWITCH_LINE Error line[%] severid[%]"
				, adata.m_data->m_line(), tab->m_id
			)
			return false;
		}
		np_actorswitch_process_role pro;
		pro.m_create = false;
		pro.m_gatewayid = m_gatewayid;
		actor_create::switch_process(id_guid(), nconfig::m_nodeid, tab->m_id, pro);
		return true;
	}

	bool actor_role::handle(message<np_actor_senditem>& adata)
	{
		auto lparm = adata.m_data;
		d_remakes(this, lparm->m_src);
		m_bag.add_item(lparm->m_item);
		return true;
	}

	bool actor_role::handle(message<np_actor_disconnect_close>& adata)
	{
		erase_actor_byid();
		return true;
	}

	bool actor_role::handle(message<pbnet::PROBUFF_NET_MATCHING_SUCCESS_RESPONSE>& adata)
	{
		m_playactorid = adata.m_data->m_playsactorid();
		return true;
	}

	bool actor_role::handle(message<pbnet::PROBUFF_NET_TASK_RECEIVE_AWARD>& adata)
	{
		tab_task* tab = ttab_task::tab(adata.m_data->m_taskid());
		if (tab == nullptr)
			return true;

		auto pro = std::make_shared<pbnet::PROBUFF_NET_TASK_RECEIVE_AWARD_RESPONSE>();
		pro->set_m_taskid(adata.m_data->m_taskid());
		
		std::map<int, int> ldrop;
		if (drop::droplist(tab->m_dropid, 1, ldrop) == false)
		{
			LogLocalError("task[%] drop[%] not find!!!", adata.m_data->m_taskid(), tab->m_dropid);
			return true;
		}
		tools::copy(ldrop, *pro->mutable_m_drop());
		m_bag.add_item(ldrop);
		return true;
	}
}//namespace ngl
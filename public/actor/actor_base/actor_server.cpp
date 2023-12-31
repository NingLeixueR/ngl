﻿#include "actor_server.h"
#include "actor_register.h"

namespace ngl
{
	void actor_server::actor_register()
	{
		register_actor<EPROTOCOL_TYPE_CUSTOM, actor_server>(
			true
			, dregister_fun_handle(actor_server, actor_node_register)
			, dregister_fun_handle(actor_server, actor_node_update)
			, dregister_fun_handle(actor_server, actor_gateway_id_updata)
		);
	}

	actor_server::actor_server() :
		actor(
			actorparm
			{
				.m_parm
				{
					.m_type = ACTOR_ADDRESS_SERVER,
					.m_area = ttab_servers::tab()->m_area,
					//.m_id = nconfig::m_nodeid,
				},
				.m_weight = 0x7fffffff,
			})
	{
	}

	actor_server::~actor_server()
	{}

	bool actor_server::handle(message<actor_node_register>& adata)
	{
		Try
		{
			auto lrecv = adata.m_data;
			auto lpack = adata.m_pack;
			Assert(lpack != nullptr);

			actor_address::getInstance().set_node(lrecv->m_node);
			actor_address::getInstance().set_session(lrecv->m_node.m_serverid, lpack->m_id);
			actor_address::getInstance().actor_add(lrecv->m_node.m_serverid, lrecv->m_add);

			i32_serverid lserverid = lrecv->m_node.m_serverid;
			std::vector<i32_sessionid> lvec;
			actor_address::getInstance().foreach(
				[lrecv, &lvec, lpack](const actor_node_session& anode)->bool
				{
					if (lpack->m_id != anode.m_session)
						lvec.push_back(anode.m_session);
					return true;
				});
			{
				if (!lvec.empty())
				{
					actor_node_register_response lpram;
					lpram.m_vec.push_back(lrecv->m_node);
					nserver->sendmore(lvec, lpram, actor_guid::moreactor(), id_guid());
				}
			}
			{// -- 回复
				actor_node_register_response lpram;
				actor_address::getInstance().foreach(
					[&adata, &lpram, lpack](const actor_node_session& anode)->bool
					{
						if (lpack->m_id != anode.m_session)
							lpram.m_vec.push_back(anode.m_node);
						return true;
					});
				nserver->send(lpack->m_id, lpram, actor_guid::moreactor(), id_guid());
			}
			{// -- actor_client_node_update 给其他结点
				actor_node_update lpram
				{
					.m_id = lserverid,
					.m_add = lrecv->m_add,
				};
				if (!lvec.empty())
					nserver->sendmore(lvec, lpram, actor_guid::moreactor(), id_guid());
			}
			{
				std::map<uint32_t, actor_node_update> lmapprotocol;
				actor_address::getInstance().ergodic(
					[lrecv, &lmapprotocol](std::map<actor_guid, i32_serverid>& amap, std::map<i32_serverid, actor_node_session>& asession)->bool
					{
						std::map<i32_serverid, actor_node_session>::iterator itor;
						for (auto&& [guid, serverid] : amap)
						{
							itor = asession.find(serverid);
							if (itor == asession.end())
								continue;
							if (lrecv->m_node.m_serverid == serverid)
								continue;
							actor_node_update& pro = lmapprotocol[serverid];
							pro.m_id = serverid;
							pro.m_add.push_back(guid.id());
						}
						return true;
					});

				for (auto&& item : lmapprotocol)
				{
					nserver->send(lpack->m_id, item.second, actor_guid::moreactor(), id_guid());
				}
			}
		}Catch;
		return true;
	}

	bool actor_server::handle(message<actor_node_update>& adata)
	{
		Try
		{
			auto lrecv = adata.m_data;
			auto lpack = adata.m_pack;
			Assert(lpack != nullptr);
			uint16_t lserverid = lpack->m_id;
			actor_address::getInstance().actor_add(lserverid, lrecv->m_add);
			actor_address::getInstance().actor_del(lrecv->m_del);
			if (lrecv->m_actorservermass)
			{
				// -- 分发给其他结点
				std::vector<i32_sessionid> lvec;
				actor_address::getInstance().foreach(
					[lserverid, &lvec](const actor_node_session& anode)->bool
					{
						if (anode.m_node.m_serverid != lserverid)
							lvec.push_back(anode.m_session);
						return true;
					});
				if (!lvec.empty())
				{
					nserver->sendmore(lvec, *lrecv, actor_guid::moreactor(), id_guid());
				}
			}
		}Catch;
		return true;
	}

	bool actor_server::handle(message<actor_gateway_id_updata>& adata)
	{
		auto lrecv = adata.m_data;
		auto lpack = adata.m_pack;
		if (lrecv->m_isremove)
		{
			actor_address::getInstance().remove_gatewayid(lrecv->m_actorid);
		}
		else
		{
			actor_address::getInstance().add_gatewayid(lrecv->m_actorid, lrecv->m_gatewayid);
		}
		std::vector<i32_sessionid> lvec;
		actor_address::getInstance().foreach(
			[&adata, &lvec, lpack](const actor_node_session& anode)->bool
			{
				if (lpack->m_id != anode.m_session)
					lvec.push_back(anode.m_session);
				return true;
			});
		if (lvec.empty() == false)
		{
			nserver->sendmore(lvec, *lrecv, actor_guid::moreactor(), id_guid());
		}
		return true;
	}
}
#pragma once

#include "ttab_servers.h"
#include "net_protocol.h"
#include "xmlnode.h"

#define isystemindex (0)

namespace ngl
{
	class nets
	{
		static std::array<net_protocol*, ENET_COUNT> m_net;
		static std::map<int16_t, ukcp*> m_kcpnet;
		static int16_t m_kcpindex;
	public:
		static net_protocol* net_first();

		static ENET_PROTOCOL session2type(i32_session asession);

		static net_protocol* net(i32_session asession);

		static net_protocol* nettype(ENET_PROTOCOL atype);

		static bool init(i32_threadsize asocketthreadnum, bool aouternet);

		// 服务器只监听一个端口
		static bool check_serverkcp();

		// robot 创建随机端口
		static int16_t create_kcp();

		static ukcp* kcp(int16_t anum = isystemindex);

		template <typename T>
		static bool sendbyserver(i32_serverid aserverid, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			i32_session lsession = server_session::get_sessionid(aserverid);
			if (lsession == -1)
				return false;
			return sendbysession(lsession, adata, aactorid, arequestactorid);
		}

		template <typename T>
		static bool sendbysession(i32_session asession, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			net_protocol* lpprotocol = net(asession);
			if (lpprotocol == nullptr)
			{
				return false;
			}
			return lpprotocol->send(asession, adata, aactorid, arequestactorid);
		}

		template <typename T>
		static bool sendmore(const std::map<i32_sessionid, i64_actorid>& asession, T& adata, i64_actorid aactorid)
		{
			std::set<ENET_PROTOCOL> lset;
			for (auto itor = asession.begin(); itor != asession.end(); ++itor)
			{
				ENET_PROTOCOL ltype = session2type(itor->first);
				if (ttab_servers::isefficient(ltype))
				{
					lset.insert(ltype);
				}
			}
			std::pair<std::shared_ptr<pack>, std::shared_ptr<pack>> lpair = net_protocol::more_pack(adata, aactorid);
			if (lpair.first == nullptr)
			{
				return false;
			}
			for (ENET_PROTOCOL item : lset)
			{
				net_protocol* lpprotocol = ngl::nets::nettype(item);
				if (lpprotocol != nullptr)
				{
					lpprotocol->sendmore(asession, aactorid, lpair);
				}
			}
			return true;
		}

		template <typename T, typename TSTL>
		static bool sendmore(const TSTL& asession, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			std::set<ENET_PROTOCOL> lset;
			for (auto itor = asession.begin(); itor != asession.end(); ++itor)
			{
				ENET_PROTOCOL ltype = session2type(*itor);
				if (ttab_servers::isefficient(ltype))
				{
					lset.insert(ltype);
				}
			}
			std::pair<std::shared_ptr<pack>, std::shared_ptr<pack>> lpair = net_protocol::more_pack(adata, aactorid);
			if (lpair.first == nullptr)
			{
				return false;
			}
			for (ENET_PROTOCOL item : lset)
			{
				net_protocol* lpprotocol = ngl::nets::nettype(item);
				if (lpprotocol != nullptr)
				{
					lpprotocol->sendmore(asession, aactorid, arequestactorid, lpair);
				}
			}
			return true;
		}

		static bool sendpack(i32_sessionid asession, std::shared_ptr<pack>& apack);

		static bool sendpack(i32_sessionid asession, std::shared_ptr<void>& apack);

		static const std::string& ip(net_works const* apstruct);

		static net_works const* ipport(i32_serverid aserverid, std::pair<str_ip, i16_port>& apair);

		static bool connect(i32_serverid aserverid, const std::function<void(i32_session)>& afun, bool await, bool areconnection);
	};
}

namespace ngl
{
	template <typename TSTL>
	bool net_protocol::sendmore_stl(const TSTL& asession, i64_actorid aactorid, i64_actorid arequestactorid, std::pair<std::shared_ptr<pack>, std::shared_ptr<pack>>& apair)
	{
		for (i32_sessionid item : asession)
		{
			if (nets::session2type(item) != (ENET_PROTOCOL)m_index)
				continue;
			apair.first->set_actor(aactorid, arequestactorid);
			net_send(item, apair.first);
			if (apair.second != nullptr)
				net_send(item, apair.second);
		}
		return  true;
	}

	template <typename T>
	std::pair<std::shared_ptr<pack>, std::shared_ptr<pack>> net_protocol::more_pack(T& adata, i64_actorid aactorid)
	{
		std::pair<std::shared_ptr<pack>, std::shared_ptr<pack>> lpair;
		lpair.first = net_pack<T>::npack(&nets::net_first()->get_pool(), adata, aactorid, 0);
		if (lpair.first == nullptr)
			return std::make_pair<std::shared_ptr<pack>, std::shared_ptr<pack>>(nullptr, nullptr);

		//LogLocalWarn("SEND Session[%] Protocol Num[%] Name[%] Data[%]!", asession, (int)T::PROTOCOL, T::name(), adata);

		std::shared_ptr<pack>& lpack_ = sendpack_t::get_pack(adata);
		if (lpack_ != nullptr)
		{
			if (encryption_bytexor::check_xor(lpack_))
			{
				char* lbuff = &lpack_->m_buff[lpack_->m_pos];
				int32_t llen = lpack_->m_len - lpack_->m_pos;
				int32_t lpos = lpair.first->m_len - pack_head::size();
				ngl::encryption::bytexor(lbuff, llen, lpos);
			}
		}
		lpair.second = lpack_;
		return lpair;
	}

	template <typename T, bool IS_SEND /*= true*/>
	bool handle_pram_send<T, IS_SEND>::sendbyserver(i32_serverid aserverid, const nguid& aactorid, const nguid& arequestactorid, handle_pram& adata)
	{
		if (IS_SEND == false)
			return true;
		return nets::sendbyserver(aserverid, *(T*)adata.m_data.get(), aactorid, arequestactorid);
	}

	template <typename T>
	bool handle_pram::netsend(i32_sessionid asession, T& adata, const nguid& aactorid, const nguid& arequestactorid)
	{
		return nets::sendbysession(asession, adata, aactorid.id(), arequestactorid.id());
	}

	template <typename T>
	bool actor_base::send_server(i32_serverid aserverid, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
	{
		return nets::sendbyserver(aserverid, adata, aactorid, arequestactorid);
	}

	template <typename T>
	bool actor_base::sendpacktoserver(i32_serverid aserverid, std::shared_ptr<pack>& apack)
	{
		i32_session lsession = server_session::get_sessionid(aserverid);
		if (lsession == -1)
			return false;
		return nets::sendpack(lsession, apack);
	}

	template <typename T>
	bool actor_base::sendpackbysession(i32_sessionid asession, std::shared_ptr<pack>& apack)
	{
		return nets::sendpack(asession, apack);
	}

	template <typename T>
	std::shared_ptr<pack> actor_base::net_pack(T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
	{
		return ::ngl::net_pack<T>::npack(&nets::net_first()->get_pool(), adata, aactorid, arequestactorid);
	}

	template <typename T>
	bool actor_base::send(i32_sessionid asession, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
	{
		return nets::sendbysession(asession, adata, aactorid, arequestactorid);
	}

	template <typename T>
	bool actor_base::sendkcp(T& adata, i64_actorid aactorid, int16_t asystemindex/* = 0*/)
	{
		if (m_kcpsession == -1)
		{
			LogLocalError("m_kcpsession = -1, is_single() == [%]", is_single());
			return false;
		}
		if (iskcp() == false)
			return false;

		nets::kcp(asystemindex)->send(m_kcpsession, adata, aactorid, id_guid());
		return true;
	}

	template <typename T>
	bool actor_base::static_sendkcp(
		i32_sessionid asession
		, T& adata
		, i64_actorid aactorid
		, i64_actorid arequestactorid
		, int16_t asystemindex/* = 0*/
	)
	{
		if (iskcp() == false)
			return false;
		nets::kcp(asystemindex)->send(asession, adata, aactorid, arequestactorid);
		return true;
	}

	template <typename T>
	bool actor_base::static_sendkcp(
		const std::vector<i32_sessionid>& asession
		, T& adata
		, i64_actorid aactorid
		, i64_actorid arequestactorid
		, int16_t asystemindex/* = 0*/
	)
	{
		if (iskcp() == false)
			return false;
		nets::kcp(asystemindex)->send(asession, adata, aactorid, arequestactorid);
		return true;
	}
}//namespace ngl




	

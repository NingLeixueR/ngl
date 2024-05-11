#include "protocoltools.h"
#include "protocol.h"
#include "xmlnode.h"
#include "xmlinfo.h"

namespace ngl
{
	class impl_protocol
	{
		struct pfun
		{
			protocol::fun_pack								m_packfun;
			std::map<ENUM_ACTOR, protocol::fun_run>			m_runfun;
		};

		static std::map<EPROTOCOL_TYPE, std::map<i32_protocolnum, pfun>> m_protocolfun;
		static std::shared_mutex	m_mutex;

		static pfun* find(EPROTOCOL_TYPE aprotocoltype, i32_protocolnum aprotocolnum)
		{
			lock_read(m_mutex);
			auto itor1 = m_protocolfun.find(aprotocoltype);
			if (itor1 == m_protocolfun.end())
			{
				char m_hexstr[1024] = { 0 };
				LogLocalError("protocol::push [%] Error protocolnum[%] "
					, aprotocoltype
					, aprotocolnum
				);
				return nullptr;
			}
			auto itor2 = itor1->second.find(aprotocolnum);
			if (itor2 == itor1->second.end())
			{
				LogLocalError("protocol::push Error protocolnum[%] "
					, aprotocolnum
				);
				return nullptr;
			}
			////
			//const char* lpprotocolname = protocoltools::name(aprotocolnum, aprotocoltype);
			//LogLocalError("protocol::push Info [%]", lpprotocolname)
			////
			return &itor2->second;
		}
	public:
		static void push(protocol::tpptr& apack)
		{
			EPROTOCOL_TYPE lprotocoltype = apack->m_head.get_protocoltype();
			i32_protocolnum lprotocolnum = apack->m_head.get_protocolnumber();
			pfun* lpfun = find(lprotocoltype, lprotocolnum);
			if(lpfun == nullptr)
			{
				return;
			}
			std::shared_ptr<void> lptrpram = lpfun->m_packfun(apack);
			if (lptrpram == nullptr)
			{
				return;
			}
			ENUM_ACTOR lactortype = (ENUM_ACTOR)apack->m_head.get_actortype();
			if (lactortype == nguid::none<ENUM_ACTOR>())
			{
				for (auto itorrun = lpfun->m_runfun.begin(); itorrun != lpfun->m_runfun.end(); ++itorrun)
				{
					itorrun->second(apack, lptrpram);
				}
			}
			else
			{
				auto itorrun = lpfun->m_runfun.find(lactortype);
				if (itorrun != lpfun->m_runfun.end())
				{
					itorrun->second(apack, lptrpram);
				}
			}
			return;
		}

		static void register_protocol(
			EPROTOCOL_TYPE atype
			, int aprotocolnumber
			, ENUM_ACTOR aenumactor
			, const protocol::fun_pack& apackfun
			, const protocol::fun_run& arunfun
			, const char* aname
		)
		{
			protocoltools::push(aprotocolnumber, aname, atype);
			{
				lock_write(m_mutex);
				pfun& lprotocol					= m_protocolfun[atype][aprotocolnumber];
				lprotocol.m_packfun				= apackfun;
				lprotocol.m_runfun[aenumactor]	= arunfun;
			}
		}
	};

	std::map<EPROTOCOL_TYPE, std::map<i32_protocolnum, impl_protocol::pfun>> impl_protocol::m_protocolfun;
	std::shared_mutex impl_protocol::m_mutex;

	void protocol::push(protocol::tpptr& apack)
	{
		impl_protocol::push(apack);
	}

	void protocol::register_protocol(
		EPROTOCOL_TYPE atype
		, i32_protocolnum aprotocolnumber
		, ENUM_ACTOR aenumactor
		, const protocol::fun_pack& apackfun
		, const protocol::fun_run& arunfun
		, const char* aname)
	{
		impl_protocol::register_protocol(atype, aprotocolnumber, aenumactor, apackfun, arunfun, aname);
	}

	i32_serverid protocol::nodeid()
	{
		return nconfig::m_nodeid;
	}
}// namespace ngl
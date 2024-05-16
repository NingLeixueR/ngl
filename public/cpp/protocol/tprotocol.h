#pragma once
#include "template_arg.h"
#include "xmlprotocol.h"
#include "net.pb.h"
#include "define.h"

#include <map>

// typeid(T).hash_code() ��Ϊc++��׼��û��ǿ��Ҫ��ֻ�ǽ�������� ��ͬ�������ɲ�ͬ��hashֵ
#define NOTUSING_BOOST_TYPEINFO
#ifndef NOTUSING_BOOST_TYPEINFO 
# include <boost/type_index.hpp>
# define HASH_CODE_VALUE(_TYPE)	boost::typeindex::type_id<_TYPE>().hash_code()
#else
# define HASH_CODE_VALUE(_TYPE)	typeid(T).hash_code()
#endif

namespace ngl
{
	template <typename T, EPROTOCOL_TYPE PROTYPE, bool ISUSING, typename TREAL>
	struct np_actor_forward;

	class tprotocol
	{
	private:
		struct pinfo
		{
			EPROTOCOL_TYPE	m_type;
			int				m_protocol;
			std::string		m_name;
		};
		static std::multimap<size_t, pinfo> m_keyval;
		// net/gm		[1			-  100000000];
		// custom		[200000001	-  300000000];
		static int32_t lcustoms/* = 200000000*/;

		template <typename T>
		static size_t hash_code()
		{
			static size_t lcode = HASH_CODE_VALUE(T);
			return lcode;
		}
	public:
		//CUSTOM
		class customs
		{
		public:
			template <typename T>
			static void func(EPROTOCOL_TYPE atype)
			{
				size_t lcode = hash_code<T>();
				if (m_keyval.find(lcode) != m_keyval.end())
				{
					log()->error("init_customs({}) is same!!!", typeid(T).name());
					return;
				}
				m_keyval.insert(std::make_pair(lcode, pinfo
					{
						.m_type = atype,
						.m_protocol = ++lcustoms,
						.m_name = dtype_name(T)
					}));
				log()->info("#[{}][EPROTOCOL_TYPE_CUSTOM][{}]", lcustoms, typeid(T).name());
			}
		};
		using type_customs = template_arg<customs, EPROTOCOL_TYPE>;

		template <typename T>
		static bool init_protobufs()
		{
			static std::string lname = dtype_name(T);
			int32_t lprotocol = xmlprotocol::protocol(lname);
			if (lprotocol == -1)
			{
				log()->error("init_protobuf::init_protobufs({}) not xml!!!", lname);
				return false;
			}
			m_keyval.insert(std::make_pair(HASH_CODE_VALUE(T), pinfo
				{
					.m_type = EPROTOCOL_TYPE_PROTOCOLBUFF,
					.m_protocol = lprotocol,
					.m_name = lname
				}));
			//log()->error("#[{}][EPROTOCOL_TYPE_PROTOCOLBUFF][{}]", lprotocol, lname);
			return true;
		}

		template <typename T>
		static pinfo& get()
		{
			using TRC = std::remove_const<T>::type;
			size_t lcode = hash_code<T>();
			auto itor = m_keyval.find(lcode);
			if (itor == m_keyval.end())
			{
				//std::cout << dtype_name(TRC) << std::endl;
				if (init_protobufs<TRC>() == false)
					throw "init_protobufs<TRC>() == false";
				itor = m_keyval.find(lcode);
				if (itor == m_keyval.end())
					throw "itor == m_keyval.end()";
			}
			return itor->second;
		}

		template <typename T>
		static int32_t protocol()
		{
			pinfo& linfo = get<T>();
			return linfo.m_protocol;
		}

		template <typename T>
		static EPROTOCOL_TYPE protocol_type()
		{
			pinfo& linfo = get<T>();
			return linfo.m_type;
		}

		template <typename T>
		static const std::string& protocol_name()
		{
			pinfo& linfo = get<T>();
			return linfo.m_name;
		}
	};
}// namespace ngl
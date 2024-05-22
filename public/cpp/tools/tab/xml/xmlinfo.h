#pragma once

#include <string>
#include <map>
#include <set>

#include "tools.h"
#include "type.h"

namespace ngl
{
	struct dbarg
	{
		uint32_t	m_port;
		std::string m_ip;
		std::string m_account;
		std::string m_passworld;
		std::string m_dbname;
		dbarg() :
			m_port(0)
		{}
	};

	class xmlinfo
	{
	public:
		std::map<std::string, std::string> m_data;

		void plog();

		//# ����key����
		template <typename TVALUE>
		bool find(const char* akey, TVALUE& adata)
		{
			std::string* lp = tools::findmap<std::string, std::string>(m_data, akey);
			if (lp == nullptr)
				return false;
			adata = tools::lexical_cast<TVALUE>(*lp);
			return true;
		}
		bool find(const char* akey, bool& adata);
		bool find(const char* akey, std::string& adata);
		//# �Ƿ����key
		bool ishavekey(const char* akey);
		//# key:threadnum �߳����� 
		bool threadnum(i32_threadsize& avalue);
		//# key:actorthreadnum actor�߳����� 
		bool actorthreadnum(i32_threadsize& avalue);
		//# key:id id
		bool id(i32_id& avalue);
		//# key:port �˿�
		bool port(i16_port& avalue);
		//# key:db db������id
		bool db(i32_serverid& avalue);
		//# key:actorserver actorserver������id
		bool actorserver(i32_serverid& avalue);
		//# key:reloadcsv reloadcsv������id
		bool reloadcsv(i32_serverid& avalue);
		//# key:name ����
		bool name(std::string& avalue);
		//# key:ip ip
		bool ip(std::string& avalue);
		//# key:line ��·
		bool line(i32_line& avalue);
		//# key:area ����
		bool area(i16_area& avalue);
		//# key:varint �Ƿ���varint
		bool varint(bool& avalue);
		//# key:isxor �Ƿ�򵥼���
		bool isxor(bool& avalue);
		//# key:xor_str �򵥼���xor���ַ���
		bool xor_str(std::string& avalue);
	};

	struct dbserver_info
	{
		dbarg m_dbarg;
	};	
}// namespace ngl
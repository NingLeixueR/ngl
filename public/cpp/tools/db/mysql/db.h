#pragma once
  
#include <iostream> 
#include <cstdint>
#include <sstream> 
#include <vector> 
#include <string>
#include <map>  

#include "include3part.h"
#include "xmlinfo.h"

namespace ngl
{
	class db
	{
		db(const db&) = delete;
		db& operator=(const db&) = delete;

		bool	m_connectdb;
		MYSQL*	m_mysql;
		dbarg	m_arg;

	public:
		db();

		// # �������ݿ�
		bool connectdb(const dbarg& arg);

		// # �ر����ݿ�
		void closedb();

		// # ѡ�����ݿ�
		bool changedb(MYSQL* amysql, std::string& adbname);

		// # ִ��sql���
		bool query(const char* asql, int alen);

		// # ת�� SQL �����ʹ�õ��ַ����е������ַ�
		void escape(const char* asql, std::string& aoutsql);

		// # ��callback��ת������
		using callback = std::function<bool(MYSQL_ROW, unsigned long*, uint32_t, uint32_t)>;
		bool select(const char* asql, int asqllen, callback aback);

		char*		m_buff1;
		char*		m_buff2;
		const int	m_bufflen1;
		const int	m_bufflen2;
	};
}// namespace ngl

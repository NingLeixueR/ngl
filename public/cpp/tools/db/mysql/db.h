#pragma once
  
#include <iostream> 
#include <cstdint>
#include <sstream> 
#include <vector> 
#include <string>
#include <map>  

#include "include3part.h"
#include "malloc_buff.h"
#include "xmlinfo.h"

#define _SQL_BUFF_SIZE_ (102400)
#define _SQL_BUFF_COUNT_ (10)

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

		// # stmt ���
		bool stmt_query(const char* asql, int alen, MYSQL_BIND* abind);

		malloc_buff m_malloc;
	private:
	};
}// namespace ngl

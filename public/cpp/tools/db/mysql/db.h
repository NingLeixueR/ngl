#pragma once
  
#include <iostream> 
#include <cstdint>
#include <sstream> 
#include <vector> 
#include <string>
#include <map>  

#include "include3part.h"
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

		class ptr
		{
			db* m_db;
		public:
			char* m_buff;
			int32_t m_bufflen;

			ptr() :
				m_buff(nullptr),
				m_bufflen(0),
				m_db(nullptr)
			{}

			ptr(db* adb) :
				m_buff(nullptr),
				m_bufflen(0),
				m_db(adb)
			{}

			ptr(db* adb, char* abuff, int32_t abufflen) :
				m_buff(abuff),
				m_bufflen(abufflen),
				m_db(adb)
			{}

			~ptr()
			{
			}
		};

		bool malloc_buff(ptr& aptr, int32_t apos);

		void free_buff(ptr& aptr);

		// # stmt ���
		bool stmt_query(const char* asql, int alen, MYSQL_BIND* abind);
	private:
		std::list<std::pair<char*,int32_t>> m_bufflist;
	};
}// namespace ngl

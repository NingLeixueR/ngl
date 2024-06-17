#pragma once

#include "db.h"

namespace ngl
{
	class db_pool
	{
		db_pool() = delete;
		db_pool(const db_pool&) = delete;
		db_pool& operator=(const db_pool&) = delete;

		static std::vector<db*> m_vec;
	public:
		// # ��ʼ��db���ӳ�
		static bool init(uint32_t asize, const dbarg& arg);
		// # �����߳�id��ȡ���ж�Ӧ������
		static db* get(uint32_t aindex);
	};
}// namespace ngl

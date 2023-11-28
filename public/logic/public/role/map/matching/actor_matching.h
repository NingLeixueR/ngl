#pragma once

#include "actor.h"
#include "actor_roleitem.h"
#include "matching.h"

namespace ngl
{
	// ### ƥ���淨
	class actor_matching : public actor
	{
		actor_matching();

		matching m_matching;

	public:
		using type_roleitems = roleitems<actor_matching, pbdb::db_brief>;
		friend class actor_instance<actor_matching>;
		static actor_matching& getInstance()
		{
			return actor_instance<actor_matching>::instance();
		}

		virtual void init(){}

		static void actor_register();

		virtual ~actor_matching() {}

		virtual void loaddb_finish(bool adbishave) {}

		enum { ACTOR_TYPE = ACTOR_MATCHING};

		// ƥ���淨
		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, mforward<pbnet::PROBUFF_NET_MATCHING>& adata);
		// ȡ���淨
		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, mforward<pbnet::PROBUFF_NET_MATCHING_CANCEL>& adata);
		// ����ȷ��
		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, mforward<pbnet::PROBUFF_NET_MATCHING_CONFIRM>& adata);
		// �淨�Ѿ��������
		bool handle(i32_threadid athread, const std::shared_ptr<pack>& apack, pbnet::PROBUFF_NET_MATCHING_SUCCESS_RESPONSE& adata);
		

		bool timer_handle(i32_threadid athread, const std::shared_ptr<pack>& apack, timerparm& adata);
	};

}
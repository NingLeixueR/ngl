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

		static void nregister();

		virtual ~actor_matching() {}

		virtual void loaddb_finish(bool adbishave) {}

		// ƥ���淨
		bool handle(message<mforward<pbnet::PROBUFF_NET_MATCHING>>& adata);
		// ȡ���淨
		bool handle(message<mforward<pbnet::PROBUFF_NET_MATCHING_CANCEL>>& adata);
		// ����ȷ��
		bool handle(message<mforward<pbnet::PROBUFF_NET_MATCHING_CONFIRM>>& adata);
		// �淨�Ѿ��������
		bool handle(message<pbnet::PROBUFF_NET_MATCHING_SUCCESS_RESPONSE>& adata);
		
		bool timer_handle(message<timerparm>& adata);
	};

}
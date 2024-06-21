#pragma once

#include "nsp_server.h"
#include "nsp_client.h"
#include "matching.h"
#include "actor.h"

namespace ngl
{
	// ### ƥ���淨
	class actor_matching : public actor
	{
		actor_matching();

		matching m_matching;
	public:
		using nclient = nsp_client<
			echannel_brief,
			actor_matching,
			pbdb::db_brief
		>;

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
}// namespace ngl
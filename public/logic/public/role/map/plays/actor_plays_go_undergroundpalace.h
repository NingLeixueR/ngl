#pragma once

#include "actor_plays.h"


namespace ngl
{
	class actor_plays_go_undergroundpalace : public actor_plays
	{

	public:
		actor_plays_go_undergroundpalace(ENUM_ACTOR atype, int32_t adataid, void* data);

		virtual ~actor_plays_go_undergroundpalace() {}

		static void actor_register();

		enum { ACTOR_TYPE = ACTOR_PLAYS_GO_UNDERGROUNDPALACE};

		// ��ʼ���淨�����
		virtual void init_after() {}
		// ��ҽ���
		virtual void enter(i64_actorid aroleid) {}
		// ����뿪
		virtual void leave(i64_actorid aroleid) {}
		// ׼���׶�[��ʼor����]
		virtual void preparation(bool astart) {}
		// �淨�׶�[��ʼor����]
		virtual void play(bool astart) {}
		// ����׶�[��ʼor����]
		virtual void settlement(bool astart) {}
		// �������
		virtual void player_death(i64_actorid aroleid) {}
		// ������Ұ
		virtual void player_enterview(i64_actorid aroleid, std::set<i64_actorid>& aother) {}
		// �뿪��Ұ
		virtual void player_leaveview(i64_actorid aroleid1, std::set<i64_actorid>& aother) {}

	};
}
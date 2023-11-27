#pragma once

#include "manage_csv.h"
#include "type.h"
#include "actor_protocol.h"

namespace ngl
{
	// [plays_pram] ����չ
	struct plays_pram
	{
		int m_playstid;							// �淨id
		std::vector<i64_actorid> m_players;		// ����б�

		//##�ɸ��ݾ����淨��չ

		def_portocol(plays_pram, m_playstid, m_players);
	};

	class actor_plays;
	class plays
	{
	protected:
		enum estage
		{
			estage_preparation,		// ׼���׶�
			estage_play,			// �淨�׶�
			estage_settlement,		// ����׶�
		};
		estage m_stage;
		tab_plays* m_tab;
		int32_t m_begtm;// �׶ο�ʼʱ��
	public:
		void init(plays_pram& apram);

		void stage(estage astage, bool astart);

		bool change_stage(estage astage);
		// ��ʼ���淨�����
		virtual void init_after(plays_pram& apram) {}
		// ��ҽ���
		virtual void enter(i64_actorid aroleid) {}
		// ׼���׶�[��ʼor����]
		virtual void preparation(bool astart) {}
		// �淨�׶�[��ʼor����]
		virtual void play(bool astart) {}
		// ����׶�[��ʼor����]
		virtual void settlement(bool astart) {}

		void update();
	};
}
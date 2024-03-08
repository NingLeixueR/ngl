#pragma once

#include <cstdint>
#include <map>
#include <string>

#include "ndefine.h"
#include "csvtable.h"
#include "data.pb.h"
#include "db.pb.h"
#include "net.pb.h"

namespace ngl
{
	enum ENUM_ACTOR
	{
		ACTOR_NONE = -1,
		//#######################  �ǵ���  #####################
		ACTOR_ROLE = 1,
		ACTOR_ROBOT,										// ������
		ACTOR_GUILD,										// ����	
		ACTOR_PLAYS,										// �淨
		ACTOR_PLAYS_GO_UNDERGROUNDPALACE = ACTOR_PLAYS,		// �淨[�´��ع�]

		ACTOR_PLAYS_END = ACTOR_PLAYS + pbnet::eplays_count,
		//#######################  ����  #######################
		ACTOR_SIGNLE_START,
		ACTOR_ADDRESS_SERVER = ACTOR_SIGNLE_START,				// ���� actor address server  �����ַ���ַ������
		ACTOR_ADDRESS_CLIENT,									// ���� actor address client 
		ACTOR_LOGIN,
		ACTOR_GATEWAY,											// ����
		ACTOR_GATEWAY_CLIENT2GAME,								// ���� [Client]->[Game]
		ACTOR_GATEWAY_GAME2CLIENT,								// ���� [Game]	->[Client]
		ACTOR_CREATE,											// ��ָ��[Server]�ϴ���[Actor]
		ACTOR_LOG,
		ACTOR_KCP,
		ACTOR_MANAGE_ROLE,
		ACTOR_MANAGE_ROBOT,
		ACTOR_MANAGE_GUILD,										// ���������
		ACTOR_RELOADCSV,										// ���շַ�Ȼ������csv
		ACTOR_RELOADCSV_DISTRIBUTE,								// �ַ�csv
		ACTOR_NOTICE,											// ����
		ACTOR_GM,												// GM
		ACTOR_MAIL,												// �ʼ�
		ACTOR_CHAT,												// ����
		ACTOR_RANKLIST,											// ���а�
		ACTOR_ACTIVITY_MANAGE,									// �����
		ACTOR_BRIEF,											// brief��Ҫ��Ϣ
		ACTOR_CROSS,											// ���
		ACTOR_CROSSDB,											// ������ݿ�
		ACTOR_CROSSCHAT,										// �������
		ACTOR_MANAGE_PLAYS,										// �����淨
		ACTOR_MATCHING,											// ƥ��
		ACTOR_DB,												// ���������һ��
		ACTOR_SIGNLE_FINISH = ACTOR_DB + pbdb::ENUM_DB_COUNT,
		ACTOR_COUNT = ACTOR_SIGNLE_FINISH,
	};

	class enum_actor
	{
	public:
		static bool is_signle(ENUM_ACTOR aenum);
	};

	// ͨ�����ֻ�ȡö��
	class nactortype
	{
		nactortype();
	public:
		static nactortype& getInstance()
		{
			static nactortype ltemp;
			return ltemp;
		}

		static bool name2enum(const std::string& aenumname, ENUM_ACTOR& avalue);
		static const char* enum2name(ENUM_ACTOR aenum);
	};
}

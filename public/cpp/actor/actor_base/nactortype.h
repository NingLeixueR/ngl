#pragma once

#include "csvtable.h"
#include "ndefine.h"
#include "net.pb.h"
#include "db.pb.h"

#include <cstdint>
#include <string>
#include <map>

namespace ngl
{
	// # actor��Ӧ��ö������
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
		ACTOR_SERVER = ACTOR_SIGNLE_START,						// ���� actor address server  ����ַ���ַ������
		ACTOR_CLIENT,											// ���� actor address client 
		ACTOR_LOGIN,
		ACTOR_GATEWAY,											// ����
		ACTOR_GATEWAY_C2G,										// ���� [Client]->[Game]
		ACTOR_GATEWAY_G2C,										// ���� [Game]	->[Client]
		ACTOR_CREATE,											// ��ָ��[Server]�ϴ���[Actor]
		ACTOR_LOG,
		ACTOR_KCP,
		ACTOR_MANAGE_ROLE,
		ACTOR_MANAGE_ROBOT,
		ACTOR_MANAGE_GUILD,										// ���������
		ACTOR_CSVCLIENT,										// �ȸ�csv client
		ACTOR_CSVSERVER,										// �ȸ�csv server
		ACTOR_NOTICE,											// ����
		ACTOR_GM,												// GM
		ACTOR_MAIL,												// �ʼ�
		ACTOR_CHAT,												// ����
		ACTOR_RANKLIST,											// ���а�
		ACTOR_ACTIVITY_MANAGE,									// �����
		ACTOR_BRIEF,											// brief��Ҫ��Ϣ
		ACTOR_CROSS,											// ���
		ACTOR_MANAGE_PLAYS,										// �����淨
		ACTOR_MATCHING,											// ƥ��
		ACTOR_CALENDAR,											// �ű�����
		ACTOR_CHANNEL,											// ����/���� 
		ACTOR_KEYVALUE,											// ����key/value
		ACTOR_FAMILY,											// ���ż���
		ACTOR_DB,												// ���������һ��
		ACTOR_SIGNLE_FINISH = ACTOR_DB + pbdb::ENUM_DB_COUNT,
		ACTOR_COUNT = ACTOR_SIGNLE_FINISH,
	};

	// # �ж�ENUM_ACTORö���Ƿ�Ϊ����
	class enum_actor
	{
	public:
		static bool is_signle(ENUM_ACTOR aenum);
	};

	// # ͨ�����ֻ�ȡö��
	class nactortype
	{
		nactortype() = delete;
		nactortype(const nactortype&) = delete;
		nactortype& operator=(const nactortype&) = delete;

	public:
		// # ע�����ö��������
		static void register_enumname(ENUM_ACTOR aenum, const char* aname);

		// # ͨ�����ֻ�ȡö��
		static bool name2enum(const char* aname, ENUM_ACTOR& avalue);

		// # ͨ��ö�ٻ�ȡ����
		static const char* enum2name(ENUM_ACTOR aenum);
	};

	// # ����actor���ͻ�ȡ���Ӧ��ö��ֵ
	template <typename TACTOR>
	class nactor_type
	{
		nactor_type() = delete;
		nactor_type(const nactor_type&) = delete;
		nactor_type& operator=(const nactor_type&) = delete;

		static ENUM_ACTOR m_type;
	public:
		static void inits(ENUM_ACTOR atype)
		{
			m_type = atype;
		}

		static ENUM_ACTOR type()
		{
			if (m_type == ACTOR_NONE)
			{
				log_error()->print(
					"nactor_type<{}>::type() == ACTOR_NONE", 
					tools::type_name<TACTOR>()
				);
				Throw(
					"nactor_type<{}>::type() == ACTOR_NONE", 
					tools::type_name<TACTOR>()
				);
			}
			return m_type;
		}
	};

	template <typename TACTOR>
	ENUM_ACTOR nactor_type<TACTOR>::m_type = ACTOR_NONE;

	// # ����pbdb::ENUM_DB��ȡENUM_ACTOR
	ENUM_ACTOR db_enum(pbdb::ENUM_DB TDBTAB_TYPE);

	// # [aregister == true] ��Ҫ��ע��Э��,�������͵İ�
	// # [aregister == false] ʵ����db_actor,db server��Ҫ
	void init_nactor_type(bool aregister);
}//namespace ngl
#pragma once

#include "nactortype.h"
#include "enum2name.h"
#include "ndefine.h"
#include "type.h"

#include <format>

namespace ngl
{
	///////////////////////////////////
	// actorΨһid(64bit)			 //
	// 16λ			����ENUM_ACTOR	 //
	// 16λ			����id			 //
	// 32λ			����id			 //
	// ############ 64 bit ######### //
	// #actor_type###areaid###id#### //
	// #16bit########16bit####32bit# //
	///////////////////////////////////
	union nguid
	{
	private:
		int64_t m_id;
		int32_t m_value1[2];// m_value1[0] = type+area  m_value1[1]=actordataid
		int16_t m_value2[4];// m_value2[0] = type		m_value2[1] = area
	public:
		nguid();
		nguid(int64_t aid);
		nguid(ENUM_ACTOR atype, i16_area aareaid, i32_actordataid aid);

		//# ���Խ�unionǿתΪi64_actoridֵ
		operator i64_actorid ()const;

		//# ��ȡguididֵ
		i64_actorid id()const;

		//# ��ȡENUM_ACTOR����
		ENUM_ACTOR type()const;

		//# ��ȡ����id
		i32_actordataid actordataid()const;

		//# ��ȡ����
		i16_area area()const;

		//# ͨ��nactortype::enum2name��ȡö�ٶ�Ӧ�ַ���
		static const char* name(i64_actorid aactorid);

		//# �������͡�����������id����һ��i64_actorid
		static i64_actorid make(ENUM_ACTOR atype, i16_area aareaid, i32_actordataid aid);

		//# �������͡�����id������Ϊnone_area()����һ��i64_actorid
		static i64_actorid make(ENUM_ACTOR atype, i32_actordataid aid);

		//# �������͡�����idΪnone_actordataid()������Ϊnone_area()����һ��i64_actorid
		static i64_actorid make(ENUM_ACTOR atype);

		//# ��������none_type()������Ϊnone_area()����idΪnone_actordataid()����һ��i64_actorid
		static i64_actorid make();

		//# �������͡�����Ϊttab_servers::tab()->m_area none_actordataid()������idΪnone_actordataid����һ��i64_actorid
		static i64_actorid make_self(ENUM_ACTOR atype);

		//# �滻type
		static i64_actorid make_type(i64_actorid aactorid, ENUM_ACTOR atype);

		//# �滻area
		static i64_actorid make_area(i64_actorid aactorid, i16_area aareaid);

		//# �滻actordataid
		static i64_actorid make_actordataid(i64_actorid aactorid, i32_actordataid aid);

		//# �滻type
		i64_actorid make_type(ENUM_ACTOR atype);

		//# �滻area
		i64_actorid make_area(i16_area aareaid);

		//# �滻actordataid
		i64_actorid make_actordataid(i32_actordataid aid);

		//# ��ȡactordataid
		static i32_actordataid actordataid(i64_actorid aactorid);

		//# ��ȡtype
		static i16_actortype type(i64_actorid aactorid);

		//# ��ȡarea
		static i16_area area(i64_actorid aactorid);

		//# sendmore ���͸�ͬ���͵�����actor
		static i64_actorid moreactor(ENUM_ACTOR atype);

		//# ���޲�make()һ��
		static i64_actorid moreactor();

		//# ���޲�make()һ��
		void none();

		//# �Ƿ񷢸�ͬ���͵�����actor
		static bool is_moreactor(i64_actorid actorid, ENUM_ACTOR atype);

		bool is_moreactor(ENUM_ACTOR atype)const;

		//# actor type �Ƿ���Ч
		static bool is_actortypenone(i64_actorid actorid);

		bool is_actortypenone()const;

		//# actor area �Ƿ���Ч
		static bool is_actorareanone(i64_actorid actorid);

		//# actor area �Ƿ���Ч
		bool is_actorareanone()const;

		//# actor id �Ƿ���Ч
		static bool is_actoridnone(i64_actorid actorid);

		//# actor id �Ƿ���Ч
		bool is_actoridnone()const;

		//# ENUM_ACTOR �Ƿ���
		static bool is_single(ENUM_ACTOR atype);

		//# ��Чarea
		static i16_area none_area();

		//# ��Чtype
		static ENUM_ACTOR none_type();

		//# ��Чdataid
		static i32_actordataid none_actordataid();

		template <typename T>
		static T none()
		{
			return (T)(-1);
		}

		bool operator<(int64_t ar)const;

		bool operator<(const nguid& r)const;

		bool operator==(int64_t ar)const;

		bool operator==(const nguid& r)const;

		bool operator!=(int64_t ar)const;

		bool operator!=(const nguid& r)const;

		bool operator>(int64_t ar)const;

		bool operator>(const nguid& r)const;

		def_portocol_function(nguid, m_id)
	};

	/////////////////////////////////////////////////////
	// ��������actor_log��guid��32λdataid����		   //
	// 16λ���ڴ洢��¼��־��actor��ENUM_ACTOR		   //
	// 16λ���ڴ洢��־����(������־��������־��bi��־)//
	/////////////////////////////////////////////////////
	union nlogactor
	{
		nlogactor() = delete;

		int32_t m_value32;
		int16_t m_value16[2];	//ENUM_ACTOR aactortype, ELOG_TYPE alogtype

		nlogactor(int32_t avalue) :
			m_value32(avalue)
		{}

		nlogactor(ENUM_ACTOR avalue1, ELOG_TYPE avalue2) :
			m_value32(0)
		{
			m_value16[0] = avalue1;
			m_value16[1] = avalue2;
		}

		ENUM_ACTOR actor_type()
		{
			return (ENUM_ACTOR)m_value16[0];
		}

		ELOG_TYPE log_type()
		{
			return (ELOG_TYPE)m_value16[1];
		}

		static ENUM_ACTOR actor_type(int32_t avalue)
		{
			nlogactor ltemp(avalue);
			return ltemp.actor_type();
		}

		static ELOG_TYPE log_type(int32_t avalue)
		{
			nlogactor ltemp(avalue);
			return ltemp.log_type();
		}
	};
}//namespace ngl

template <>
struct std::formatter<ngl::nguid>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	auto format(const ngl::nguid& aval, std::format_context& ctx)const
	{
		const char* lanme = ngl::em<ngl::ENUM_ACTOR>::get_name(aval.type());
		if (lanme == nullptr)
		{
			return std::format_to(ctx.out()
				, "guid<{}-{}-{}>"
				, (int)aval.type()
				, aval.area()
				, aval.actordataid()
			);
		}
		else
		{
			return std::format_to(ctx.out()
				, "guid<{}-{}-{}>"
				, lanme
				, aval.area()
				, aval.actordataid()
			);
		}
	}
};
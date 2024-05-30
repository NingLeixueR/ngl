#pragma once

#include "serialize.h"
#include "csvtable.h"
#include "type.h"

#include <cstdint>
#include <map>

namespace ngl
{
	struct pack_head
	{
		int32_t m_data[EPH_SUM] = {0};
		int32_t m_wpos = 0;

		pack_head();

		// # ����ͷ���û��߻�ȡʱ��
		static void		head_set_time(int32_t* abuff);
		static i32_time head_get_time(const int32_t* abuff);
		void			set_time();
		i32_time		get_time()const;

		static void		head_set_version(int32_t* abuff);
		static int32_t  head_get_version(const int32_t* abuff);
		void			set_version();
		int32_t			get_version()const;

		// # ����actor 
		// # aactor:���͸��ĸ�actor 
		// # arequestactorid:�ĸ�actor���͵�
		static void head_set_actor(
			int32_t* abuff
			, i64_actorid aactor	/* aenum == ACTOR_NONE ��ֵ��Ч */
			, i64_actorid arequestactorid
		);

		void set_actor(
			i64_actorid aactor		/* aenum == ACTOR_NONE ��ֵ��Ч */
			, i64_actorid arequestactorid
		);

		void set_requestactor(i64_actorid arequestactorid);

		static void set_actor(uint32_t* abuff, i64_actorid aactor);

		// # ��ȡҪ���͸��ĸ�actor
		i64_actorid		get_actor()const;

		// # ��ȡ˭���͵�actor
		i64_actorid		get_request_actor()const;

		// # ��ȡҪ���͸���actor��type
		i16_actortype	get_actortype()const;

		// # ��ȡ˭���͵�actor��type
		i16_actortype	get_request_actortype()const;

		// # ��ȡҪ���͸���actor��area
		i16_area		get_actorarea()const;

		// # ��ȡҪ���͸���actor��dataid
		i32_actordataid get_actordataid()const;

		// # ����head
		void			reset();

		// # ��ȡEPH��Ӧ��ֵ
		int				getvalue(EPH aeph)const;

		// # ��ȡЭ���ֽ���
		int				get_bytes()const;

		// # ��ȡ��ͷ����
		static int		size();

		// # ��ͷ�Ƿ�������
		EPH_HEAD_VAL	isready()const;

		// # �ԱȰ汾��
		EPH_HEAD_VAL	isversion()const;

		// # ��ȡЭ���
		i32_protocolnum protocolnum()const;

		// # ��ȡ/����Э���
		i32_protocolnum get_protocolnumber()const;
		void			set_protocol(i32_protocolnum aprotocolnum);

		// # ��ȡ/����Э������
		EPROTOCOL_TYPE	get_protocoltype()const;
		void			set_protocoltype(EPROTOCOL_TYPE atype);
		
		EPH_HEAD_VAL push(const char*& abuff, int& alen);
		bool push(ngl::serialize& aflow);
		void reservebuff(char* abuff, int abufflen, std::pair<char*, int>& apair);
	};
}// namespace ngl

template <>
struct std::formatter<ngl::pack_head>
{
	constexpr auto parse(std::format_parse_context& ctx)
	{
		return ctx.begin();
	}

	template <typename FormatContext>
	auto format(const ngl::pack_head& val, FormatContext& ctx)const
	{
		auto out = ctx.out();
		std::format_to(out, "HEAD[");
		for (int i = 0; i < ngl::EPH_BYTES; ++i)
		{
			std::format_to(out, "{}#,", val.m_data[i]);
		}
		std::format_to(out, "]");
		return out;
	}
};
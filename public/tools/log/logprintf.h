#pragma once

#include "enum2name.h"
#include "xmlinfo.h"
#include "xmlnode.h"
#include "actor_protocol.h"

#include <fstream>
#include <memory>


namespace ngl
{
	enum ELOG
	{
		ELOG_DEBUG,
		ELOG_INFO,
		ELOG_WARN,
		ELOG_ERROR,
		ELOG_NONE,
	};

	enum ELOG_TYPE
	{
		ELOG_LOCAL = 0,
		ELOG_DEFAULT = 1,
		ELOG_BI = 2,
		ELOG_COUNT,
	};

	class logprintf
	{
	public:
		static void printf(ELOG acolor, const char* apos, const char* atimestr, const char* amsg);
	};

	struct logfile
	{
		std::ofstream m_stream;
		struct config
		{
			ELOG_TYPE m_type;				// ��־���� ELOG_TYPE
			std::string m_dir;			// �ļ���
			int m_flush_time;			// д���ļ��ļ��
		};
		config m_config;
		int m_count;
		int m_fcount;
		bool m_isactor;

		logfile(bool aisactor, const config& aconfig);
		void create(bool afirst);

		virtual void printf(const actor_logitem& alog) = 0;
		virtual void local_printf(ELOG atype, ngl::logformat& llogformat) {}

		static std::shared_ptr<logfile> create_make(bool aisactor, const config& aconfig);
	};
}
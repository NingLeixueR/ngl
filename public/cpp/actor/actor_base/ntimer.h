#pragma once

#include "time_wheel.h"
#include "nprotocol.h"
#include "serialize.h"
#include "ndefine.h"
#include "pack.h"

#include <memory>

namespace ngl
{
	struct timerparm
	{
		enum E_ACTOR_TIMER
		{
			ET_NULL,
			ET_MONTH,		// ÿ�´���
			ET_WEEK,		// ÿ�ܴ���
			ET_DAY,			// ÿ�մ���		ahourʱamin��asec��
			ET_HOUR,		// ÿСʱ����	amin��asec��
			ET_MIN,			// ÿ���Ӵ���	asec��
			ET_INTERVAL_SEC,// ���n�봥��
		};
		int							m_type = 0;
		int							m_timerid = 0;
		int64_t						m_ms = 0;					// ����ڵ�ǰʱ�� ms
		int							m_count = 1;				// ��������
		std::function<int(int64_t)> m_intervalms = nullptr;		// �������
		std::shared_ptr<void>		m_parm = nullptr;			// �Զ������
		int64_t						m_triggerms = 0;			// ����ʱ�ĺ���

		template <typename T>
		void set_parm(T* aparm)
		{
			m_parm = std::shared_ptr<void>(aparm);
		}

		def_portocol(timerparm, m_type, m_timerid, m_ms, m_count, m_triggerms)
	};

	class make_timerparm
	{
	public:
		static time_t month_ms(int anow, int autc, int amonthday = 1/*1-31*/, int ahour = 0, int amin = 0, int asec = 0)
		{
			time_t lfirst = localtime::getmothday(autc, amonthday, ahour, amin, asec);
			char lbuff[1024] = { 0 };
			ngl::localtime::time2str(lbuff, 1024, lfirst, "%y/%m/%d %H:%M:%S");
			std::cout << lbuff << std::endl;
			return (lfirst - anow) * localtime::MILLISECOND;
		}

		//ET_MONTH,		// ÿ�´���
		static void month(timerparm& aparm, int amonthday = 1/*1-31*/, int ahour = 0, int amin = 0, int asec = 0, int acount = 0x7fffffff)
		{
			assert(amonthday >= 1 && amonthday <= 31);
			assert(ahour >= 0 && ahour <= 23);
			assert(amin >= 0 && amin <= 59);
			assert(asec >= 0 && asec <= 59);
			aparm.m_type = timerparm::ET_WEEK;
			aparm.m_ms = month_ms(localtime::gettime(), amonthday, ahour, amin, asec);
			aparm.m_intervalms = [amonthday, ahour, amin, asec](int64_t ams)
				{
					return make_timerparm::month_ms(localtime::gettime(), ams / 1000 + 1, amonthday, ahour, amin, asec);
				};
			aparm.m_count = acount;
		}

		// 1-7
		static void week(timerparm& aparm, int aweek = 1/*1-7*/, int ahour = 0, int amin = 0, int asec = 0, int acount = 0x7fffffff)
		{
			assert(aweek >= 1 && aweek <= 7);
			assert(ahour >= 0 && ahour <= 23);
			assert(amin >= 0 && amin <= 59);
			assert(asec >= 0 && asec <= 59);
			aparm.m_type = timerparm::ET_WEEK;
			time_t lnow = localtime::gettime();
			time_t lfirst = localtime::getweekday(aweek >= 7 ? 0 : aweek, ahour, amin, asec);
			aparm.m_ms = (lfirst - lnow) * localtime::MILLISECOND;
			aparm.m_intervalms = [](int64_t)
				{
					return localtime::WEEK_MILLISECOND;
				};
			aparm.m_count = acount;
		}

		// ÿ�մ���  ahourʱamin��asec��
		static void day(timerparm& aparm, int ahour, int amin = 0, int asec = 0, int acount = 0x7fffffff)
		{
			assert(ahour >= 0 && ahour <= 23);
			assert(amin >= 0 && amin <= 59);
			assert(asec >= 0 && asec <= 59);
			aparm.m_type = timerparm::ET_DAY;
			time_t lnow = localtime::gettime();
			time_t lfirst = localtime::getsecond2time(ahour, amin, asec);
			aparm.m_ms = (lfirst - lnow) * localtime::MILLISECOND;
			aparm.m_intervalms = [](int64_t)
				{
					return localtime::DAY_MILLISECOND;
				};
			aparm.m_count = acount;
		}

		// ÿСʱ����  amin��asec��
		static void hour(timerparm& aparm, int amin, int asec, int acount = 0x7fffffff)
		{
			assert(amin >= 0 && amin <= 59);
			assert(asec >= 0 && asec <= 59);
			aparm.m_type = timerparm::ET_HOUR;
			time_t lnow = localtime::gettime();
			time_t lfirst = localtime::getsecond2time(amin, asec);
			aparm.m_ms = (lfirst - lnow) * localtime::MILLISECOND;
			aparm.m_intervalms = [](int64_t)
				{
					return localtime::HOUR_MILLISECOND;
				};
			aparm.m_count = acount;
		}

		// ÿ���Ӵ���  asec��
		static void min(timerparm& aparm, int asec, int acount = 0x7fffffff)
		{
			assert(asec >= 0 && asec <= 59);
			aparm.m_type = timerparm::ET_MIN;
			time_t lnow = localtime::gettime();
			time_t lfirst = localtime::getsecond2time(asec);
			aparm.m_ms = (lfirst - lnow) * localtime::MILLISECOND;
			aparm.m_intervalms = [](int64_t)
				{
					return localtime::MINUTES_MILLISECOND;
				};
			aparm.m_count = acount;
		}

		// ÿn�봥��
		static void make_interval(timerparm& aparm, int asec, int acount = 0x7fffffff)
		{
			assert(asec >= 0);
			aparm.m_type = timerparm::ET_INTERVAL_SEC;
			aparm.m_ms = asec * localtime::MILLISECOND;
			aparm.m_intervalms = [asec](int64_t)
				{
					return asec * localtime::MILLISECOND;
				};
			aparm.m_count = acount;
		}
	};

	class actor_base;

	class ntimer
	{
	public:
		// �׳�һ����ʱ��
		static int addtimer(actor_base* actor, std::shared_ptr<timerparm>& aparm);
	};
}//namespace ngl

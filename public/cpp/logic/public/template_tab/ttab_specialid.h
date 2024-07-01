#pragma once

#include "manage_csv.h"
#include "type.h"
#include "xml.h"

namespace ngl
{

	struct ttab_specialid : public manage_csv<tab_specialid>
	{
		ttab_specialid(const ttab_specialid&) = delete;
		ttab_specialid& operator=(const ttab_specialid&) = delete;

		static i32_rolelv m_rolemaxlv; // ������ȼ�
		static i32_rolevip m_rolemaxvip; // ������vip�ȼ�
		static int32_t m_createfamilconsume; // �������ŵ�����

		ttab_specialid()
		{}

		virtual void reload()
		{
			for (std::pair<const int, tab_specialid>& pair : tablecsv)
			{
				tab_specialid& ltab = pair.second;
				if (ltab.m_name == "rolemaxlv")
				{
					m_rolemaxlv = tools::lexical_cast<i32_rolelv>(ltab.m_value.c_str());
				}
				else if (ltab.m_name == "rolemaxvip")
				{
					m_rolemaxvip = tools::lexical_cast<i32_rolevip>(ltab.m_value.c_str());
				}
				else if (ltab.m_name == "createfamilconsume")
				{
					m_createfamilconsume = tools::lexical_cast<i32_rolevip>(ltab.m_value.c_str());
				}
					 
			}
		}
	};
}//namespace ngl

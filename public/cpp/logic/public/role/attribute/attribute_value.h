#pragma once

#include <functional>
#include <vector>
#include <array>
#include <set>
#include <map>

#include "ttab_attribute.h"
#include "manage_csv.h"
#include "nlog.h"
#include "net.h"

namespace ngl
{
	struct attribute_value
	{
		friend class attribute;
	private:
		// ### [absolute]		���Ծ���ֵ  
		map_absolute m_attr;
		// ### ��ֱ�����[�����ṩ��]
		map_ratio m_rattr;
		// ### ��ֱ�����[�����ṩ��]
		map_ratio m_orattr;
		// ########### ���±������� ������������ӵ����� ##########
		// ### key:�ĸ�ģ��ӵı�������
		map_moduleratio m_crattr;		// ��������[��ֱ�����]����� 
		// #### [m_attr+m_rattr] ����������
		map_attr m_fight;
		// ### ս��
		int64_t m_fightscore;

		EnumModule m_module;
	public:
		attribute_value();
	private:
		void update(map_attribute& aattr, const map_ratio& amr);

		int64_t fight(EnumAttribute atype, double avalues);

		int64_t fight();
	public:
		map_attr& get_fight()
		{
			return m_fight;
		}
		int64_t update();
		// ��ӡ����
		void printf();
		// �������
		void clear();
		// �������
		void set_attr(EnumAttribute atype, double avalues);
		// ��ӱ�����������
		void set_rattr(EnumAttribute atype, double avalues);
		// ��������������
		void set_father_rattr(EnumModule amodule, EnumAttribute atype, double avalues);
		// ��ȡ����
		double get_attr(EnumAttribute atype);
		// ��ȡ������������
		double get_rattr(EnumAttribute atype);
		// ��ȡ�����������
		double get_father_rattr(EnumModule amodule, EnumAttribute atype);

		void topb(pbnet::UnitModule& aunitmodule)
		{
			aunitmodule.set_m_mtype(m_module);
			for (std::pair<const EnumAttribute, int64_t>& item : m_fight)
			{
				pbnet::UnitAttribute* lptemp = aunitmodule.add_m_modules();
				lptemp->set_m_type(item.first);
				lptemp->set_m_value(item.second);
			}
		}
	};
}// namespace ngl
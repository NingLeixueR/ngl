#pragma once

#include <set>
#include <map>
#include <vector>
#include <array>
#include <functional>
#include "net.h"
#include "nlog.h"
#include "manage_csv.h"
#include "ttab_attribute.h"

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
	};

}
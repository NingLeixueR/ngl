#pragma once 

#include <functional>
#include <vector>
#include <array>
#include <set>
#include <map>

#include "attribute_value.h"
#include "ttab_attribute.h"
#include "manage_csv.h"
#include "net.pb.h"
#include "event.h"
#include "nlog.h"
#include "net.h"

namespace ngl
{
	class attribute
	{
		// ģ������(ֻ��ģ��䷢���仯ͨ��updata[EnumModule,attribute_value])
		std::map<EnumModule, attribute_value> m_moduledata;
		bool m_issync;

		attribute_value& root();

		void add_module(EnumModule aenum);
		void dec_module(EnumModule aenum);

		bool is_module_root(EnumModule aenum);
		bool is_module_null(EnumModule aenum);

		void update_module(EnumModule aenum);
	public:
		attribute();
		
		bool issync();

		void set_issync(bool aissync);

		// #### ��ʼ������ ��ģ����������
		void init_data(EnumModule aenum, attribute_value& avalue);

		// #### ���������ģ������ ��������������ս��
		void init();

		// #### ����ģ������
		void updata(EnumModule aenum, attribute_value& avalue);

		// #### ս��
		int64_t fight();

		const map_attr& get_attribute();

		//EnumModule aenum
		const map_attr& get_attribute(EnumModule aenum);

		void printf();

		template <typename T>
		void topb(T& apro)
		{
			for (std::pair<const EnumModule, attribute_value>& item : m_moduledata)
			{
				pbnet::UnitModule* lpmodule = apro.add_m_modules();
				item.second.topb(*lpmodule);
			}
		}
	};
	class aoimap;
	// ��̬����,������ս���иı������
	class dynamic_attribute
	{
	public:
	private:
		std::map<EnumAttribute, int64_t> m_dynamic;
		aoimap* m_map;
		int64_t m_unitid;
		int32_t m_stat;	// ״̬	 
	public:
		dynamic_attribute(aoimap* amap, int64_t aunitid) :
			m_map(amap),
			m_unitid(aunitid),
			m_stat(pbnet::eunitstat_normal)
		{}

		// ����[ģ������]���ɶ�̬����
		void init_dynamic(std::map<EnumModule, attribute_value>& amoduledata)
		{
			m_dynamic = amoduledata[EnumModule::E_ModuleRoot].get_fight();
		}

		// �Ƿ�����
		bool is_death()
		{
			return m_dynamic[E_Hp] <= 0;
		}

		// �޸Ķ�̬����
		void change_attribute(EnumAttribute aattribute, int32_t avalue)
		{
			m_dynamic[aattribute] += avalue;
			if (is_death())
			{
				event_parm_death pram;
				pram.m_unitid = -1;
				pram.m_deathunitid = m_unitid;
				event_death::execute(&pram);
				//mapevent::on_death(m_map, m_unitid);
			}
		}

		// �޷��ƶ�
		void set_stat(pbnet::eunitstat astat)
		{
			m_stat |= (int32_t)astat;
		}

		void clear_stat()
		{
			m_stat = pbnet::eunitstat_normal;
		}

		// �Ƿ�����ƶ�
		bool ismove()
		{
			return (m_stat & (int32_t)pbnet::eunitstat_nomove) == 0;
		}

		// �Ƿ������ͨ����
		bool isnormalattack()
		{
			return (m_stat & (int32_t)pbnet::eunitstat_nonormalattack) == 0;
		}

		// �Ƿ�����ͷż���
		bool isreleaseskill()
		{
			return (m_stat & (int32_t)pbnet::eunitstat_noreleaseskill) == 0;
		}
	};

	void test_attribute();
}// namespace ngl
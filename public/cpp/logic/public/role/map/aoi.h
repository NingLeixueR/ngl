#pragma once

#include <functional>
#include <iostream>
#include <cstdint>
#include <numeric>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>

#include "net.pb.h"

namespace ngl
{
	class aoi
	{
	protected:
		int32_t m_nx;  // x���������
		int32_t m_ny;  // y���������
		int32_t m_w;   // x����
		int32_t m_l;   // y�᳤��
	public:
		virtual void init(int32_t aw, int32_t al, int32_t anx, int32_t any)
		{
			m_w = aw;
			m_l = al;
			m_nx = anx;
			m_ny = any;
		}

		// x���������
		int32_t nx() 
		{ 
			return m_nx; 
		}

		// y���������
		int32_t ny() 
		{ 
			return m_ny; 
		}

		// ��������
		inline int32_t grid_count() 
		{ 
			return m_nx * m_ny; 
		}

		// ���ӿ��
		inline int32_t grid_w() 
		{ 
			return m_w / m_nx; 
		}

		// ���ӳ���
		inline int32_t grid_l() 
		{ 
			return m_l / m_ny; 
		}

		// ͨ�����ӱ�Ż�ȡ idx
		inline int32_t idx(uint32_t aid) 
		{ 
			return aid % m_nx; 
		}

		// ͨ�����ӱ�Ż�ȡ idy
		inline int32_t idy(uint32_t aid) 
		{ 
			return aid / m_nx; 
		}

		// ͨ��idx,idy��ȡ ���ӱ��
		inline int32_t id(uint32_t aidx, uint32_t aidy) 
		{ 
			return aidy * m_nx + aidx; 
		}

		// ͨ��x y�����������ӱ��
		inline int32_t idbyxy(float ax, float ay) 
		{ 
			return id(std::ceil(ax / grid_w()), std::ceil(ay / grid_l())); 
		}

		// ��ȡ������Χ��9����
		inline void idaround_list(int32_t aid, std::set<int32_t>& avec)
		{
			int lx = idx(aid);
			int ly = idy(aid);
			//���Ͻ�
			int ltx = lx - 1;
			int lty = ly - 1;
			avec.insert(aid);
			for (int i = 0; i < 3; ++i)
			{
				int ltempx = ltx + i;
				if (ltempx < 0 || ltempx >= m_nx)
					continue;
				for (int j = 0; j < 3; ++j)
				{
					int ltempy = lty + j;
					if (ltempy < 0 || ltempy >= m_ny)
						continue;
					if (ltempx != lx && ltempy != ly)
						avec.insert(id(ltempx, ltempy));
				}
			}
		}

		// ���ݸ��ӱ�ż�����Χ�Ź�����
		inline void idaround_foreach(int32_t aid, const std::function<void(int32_t)>& afun)
		{
			std::set<int32_t> lvec;
			idaround_list(aid, lvec);
			for (int32_t lid : lvec)
			{
				afun(lid);
			}
		}

		// �ڸ�����Χ���� ����ҵ����˳�
		inline void idaround_find(int32_t aid, const std::function<bool(int32_t)>& afun)
		{
			std::set<int32_t> lvec;
			idaround_list(aid, lvec);
			for (int32_t lid : lvec)
			{
				if (afun(lid) == true)
					return;
			}
		}

		// ������������
		static float distance(aoi* aaoi, int aid1, int aid2)
		{
			float lx1 = aaoi->idx(aid1);
			float ly1 = aaoi->idy(aid1);
			float lx2 = aaoi->idx(aid2);
			float ly2 = aaoi->idy(aid2);
			return distance(lx1, ly1, lx2, ly2);
		}

		// ������������
		static float distance(float ax1, float ay1, float ax2, float ay2)
		{
			float lx = ax2 - ax1;
			float ly = ay2 - ay1;
			return std::sqrt(lx * lx + ly * ly);
		}

		// ������������
		static float distance(const pbnet::VECTOR2& apos1, const pbnet::VECTOR2& apos2)
		{
			return distance(apos1.m_x(), apos1.m_y(), apos2.m_x(), apos2.m_y());
		}

		// ������������
		static float distance(const pbnet::VECTOR3& apos1, const pbnet::VECTOR3& apos2)
		{
			return distance(apos1.m_x(), apos1.m_y(), apos2.m_x(), apos2.m_y());
		}
	};
}// namespace ngl
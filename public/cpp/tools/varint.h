#pragma once

#include <cstdint>

namespace ngl
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Varint��һ��ʹ��һ�������ֽ����л������ķ��������������Ϊ�䳤�ֽڡ�
	// ����32λ�������ݾ���Varint�������Ҫ1~5���ֽڣ�С������ʹ��1��byte���������ʹ��5��bytes��
	// 64λ�������ݱ����ռ��1~10���ֽڡ�
	// ��ʵ�ʳ�����С���ֵ�ʹ����ԶԶ���ڴ����֣����ͨ��Varint������ڴ󲿷ֳ����������𵽺ܺõ�ѹ��Ч����
	
	class varint
	{
	public:
		static void		set(bool aisopen);
		
		template <typename T>
		struct parm_length
		{
			T m_value;
		};

		static int length(parm_length<int32_t>& avaluearrays);
		static int length(parm_length<int64_t>& avaluearrays);

		template <typename T>
		struct parm
		{
			T m_value;
			char* m_buf = nullptr;
			int m_len = 0;
			int32_t* m_bytes = 0;
		};

		static bool encode(parm<int64_t>& aparm);
		static bool	decode(parm<int64_t>& aparm);
		static bool	encode(parm<int32_t>& aparm);
		static bool	decode(parm<int32_t>& aparm);		
	};
}
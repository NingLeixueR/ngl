#pragma once

#include "time_wheel.h"

namespace ngl
{
	//// ���������粻�����¼�  �뼶��ʱ��
	class asio_timer
	{
		static time_wheel m_wheel;
	public:
		asio_timer() {}
		static time_wheel& wheel()
		{
			return m_wheel;
		}
	};
}

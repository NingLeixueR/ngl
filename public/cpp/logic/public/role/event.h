#pragma once

#include "type.h"

namespace ngl
{
	class aoimap;
	class mapevent
	{
	public:
		// ����
		static void on_death(aoimap* amap, int32_t aunitid);
	};
}// namespace ngl
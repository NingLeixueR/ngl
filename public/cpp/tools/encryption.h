#pragma once

#include <string>

namespace ngl
{
	class encryption
	{
	public:
		// ## ���ݼ򵥼��� ���
		static void bytexor(char* ap, int32_t aplen, int apos);
	};
}//namespace ngl
#pragma once

#include <string>

namespace ngl
{
	struct csvpair
	{
		std::string m_data;
		int m_pos;
		bool m_doublequotationmarks; // ˫����
		char m_fg;//Ĭ��,

		csvpair();
		void clear();
	};
}

#pragma once

#include <string>

namespace ngl
{
	// ����uuid
	class uuid
	{
	public:
		static std::string& make(std::string& strUUID);
	};
}
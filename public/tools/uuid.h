#pragma once

#include <string>

namespace ngl
{
	class uuid
	{
	public:
		// ����uuid
		static std::string& create(std::string& strUUID);
	};
}
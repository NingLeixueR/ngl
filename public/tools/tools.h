#pragma once

#include <string>
#include <map>
#include <unordered_map>

namespace ngl
{
	class tools
	{
	public:
		// map������װ
		template <typename TE, typename T>
		static const T* findmap(const std::map<TE, T>& amap, const TE& aid)
		{
			auto itor = amap.find(aid);
			return itor == amap.end() ? nullptr : &itor->second;
		}

		template <typename TE, typename T>
		static T* findmap(std::map<TE, T>& amap, const TE& aid)
		{
			auto itor = amap.find(aid);
			return itor == amap.end() ? nullptr : &itor->second;
		}

		template <typename TE, typename T>
		static T* findmap(std::unordered_map<TE, T>& amap, const TE& aid)
		{
			auto itor = amap.find(aid);
			return itor == amap.end() ? nullptr : &itor->second;
		}

		// �Ƿ���������ַ
		static bool is_lanip(const std::string& aip);

		static bool is_mem(const char* astr1, const char* astr2);
	};

}
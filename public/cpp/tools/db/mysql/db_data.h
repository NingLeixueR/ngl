#pragma once

#include "serialize.h"
#include "type.h"
#include "db.h"

#include <set>

namespace ngl
{
	template <typename T>
	struct dbdata;
	// ### 除了[dbdata<T>]可以直接使用 其他对象均不允许直接操纵
	template <typename T>
	struct db_data
	{
	private:
		template <typename T>
		friend struct dbdata;
		static std::map<i64_actorid, T> m_data;
	};

	template <typename T>
	std::map<i64_actorid, T> db_data<T>::m_data;

	template <typename T>
	struct dbdata
	{
		static void set(i64_actorid aid, const T& adata)
		{
			T& ldata = db_data<T>::m_data[aid];
			ldata = adata;
		}

		static void remove(i64_actorid aid)
		{
			db_data<T>::m_data.erase(aid);
		}

		static void remove(std::vector<i64_actorid>& aid)
		{
			for(i64_actorid id : aid)
				db_data<T>::m_data.erase(id);
		}
		
		static bool isload(i64_actorid aid)
		{
			auto itor = db_data<T>::m_data.find(aid);
			if (itor == db_data<T>::m_data.end())
				return false;
			return true;
		}

		static T* find(i64_actorid aid)
		{
			auto itor = db_data<T>::m_data.find(aid);
			if (itor == db_data<T>::m_data.end())
				return nullptr;
			return &itor->second;
		}

		static bool get(i64_actorid aid, T& adata)
		{
			auto itor = db_data<T>::m_data.find(aid);
			if (itor == db_data<T>::m_data.end())
				return false;
			adata = itor->second;
			return true;
		}

		static void foreach(const std::function<void(T&)>& afun)
		{
			for (std::pair<const i64_actorid, T>& item : db_data<T>::m_data)
				afun(item.second);
		}

		static void foreach_index(const std::function<void(int, T&)>& afun)
		{
			int lindex = 0;
			for (std::pair<const i64_actorid, T>& lpair : db_data<T>::m_data)
				afun(++lindex, lpair.second);
		}
	};
}// namespace ngl

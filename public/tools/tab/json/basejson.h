#pragma once

#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
#include <map>
#include <string>
#include <array>
#include <vector>
#include <set>
#include <list>
#include <map>

#include "cJSON.h"

namespace ngl
{
	class json
	{
		
	public:
		cJSON* m_json;

		json() :
			m_json(nullptr)
		{}

		json(cJSON* ajson) :
			m_json(ajson)
		{}

		virtual ~json() 
		{}

		cJSON* get()
		{
			return m_json;
		}

		void set(cJSON* ajson)
		{
			m_json = ajson;
		}
	};
}//namespace ngl


#define DEF_OJSON_MAKE(NAME,VALUE)						\
	{													\
		auto temp = std::make_pair(NAME, VALUE);		\
		ajson >> temp;									\
		VALUE = temp.second;							\
	}

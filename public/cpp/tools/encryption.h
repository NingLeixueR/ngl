#pragma once

#include <string>

namespace ngl
{
	class encryption
	{
	public:
		static void hmac_sha256(const std::string& key, const std::string& plain, std::string& value);
		static void function_sha256(char* abuff, int alen, std::string& value);

		// ## ���ݼ򵥼��� ���
		static void set_xor(bool aisxor, const char* axorkey, int32_t axorkeylen);
		static void bytexor(char* ap, int32_t aplen, int apos);
	};
}//namespace ngl
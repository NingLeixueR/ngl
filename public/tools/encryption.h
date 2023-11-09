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
		static std::string m_xorkey;
		static int32_t m_xorkeynum; //2^n-1 nΪxorkey���ַ���
		static bool m_isxor;
		static void set_xor(bool aisxor, const char* axorkey, int32_t axorkeylen);
		static void bytexor(char* ap, int32_t aplen, int apos);
	};
}
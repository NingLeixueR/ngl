#include "sysconfig.h"
#include "localtime.h"
#include "tools.h"

#include <iostream>
#include <cassert>
#include <cstdint>
#include <codecvt>
#include <cstring>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include <vector>
#include <locale>
#include <string>

#if defined(_WIN32)
#include <objbase.h>
#else
#include <uuid/uuid.h>
#endif

#define GUID_LEN 64

namespace ngl
{ 
	//A类地址：10.0.0.0--10.255.255.255
	bool is_a_address(const std::vector<std::string>& lvec)
	{
		if (lvec.empty())
			return false;
		return lvec[0] == "10";
	}

	//B类地址：172.16.0.0--172.31.255.255
	bool is_b_address(const std::vector<std::string>& lvec)
	{
		if (lvec.size() < 2)
			return false;
		if (lvec[0] != "172")
			return false;
		int lnum = tools::lexical_cast<int>(lvec[1]);
		return lnum >= 16 && lnum <= 31;
	}

	//C类地址：192.168.0.0--192.168.255.255
	bool is_c_address(const std::vector<std::string>& lvec)
	{
		if (lvec.size() < 2)
			return false;
		return lvec[0] == "192" && lvec[1] == "168";
	}

	bool tools::is_lanip(const std::string& aip)
	{
		if (aip == "127.0.0.1")
			return true;
		std::vector<std::string> lvec;
		if (splite(aip.c_str(), ".", lvec) == false)
			return false;
		return is_a_address(lvec) || is_b_address(lvec) || is_c_address(lvec);
	}

	bool tools::is_equal(const char* astr1, const char* astr2)
	{
		int llen1 = strlen(astr1);
		int llen2 = strlen(astr2);
		if (llen1 != llen2)
			return false;
		return is_equal(astr1, astr2, llen1);
	}

	bool tools::is_equal(const char* astr1, const char* astr2, int32_t abyte)
	{
		return memcmp(astr1, astr2, abyte) == 0;
	}

	int16_t tools::transformlittle(parm<int16_t>& avalues)
	{
		if constexpr (islittle())
			return avalues.m_value;
		unsigned char* value_p = reinterpret_cast<unsigned char*>(&avalues.m_value);
		avalues.m_value =
			(static_cast<int16_t>(value_p[0]) << 8)
			| static_cast<int16_t>(value_p[1]);
		return avalues.m_value;
	}

	uint16_t tools::transformlittle(parm<uint16_t>& avalues)
	{
		if constexpr (islittle())
			return avalues.m_value;
		unsigned char* value_p = reinterpret_cast<unsigned char*>(&avalues.m_value);
		avalues.m_value =
			(static_cast<uint16_t>(value_p[0]) << 8)
			| static_cast<uint16_t>(value_p[1]);
		return avalues.m_value;
	}

	int32_t tools::transformlittle(parm<int32_t>& avalues)
	{
		if constexpr (islittle())
			return avalues.m_value;
		unsigned char* value_p = reinterpret_cast<unsigned char*>(&avalues.m_value);
		avalues.m_value = (static_cast<int32_t>(value_p[0]) << 24)
			| (static_cast<int32_t>(value_p[1]) << 16)
			| (static_cast<int32_t>(value_p[2]) << 8)
			| static_cast<int32_t>(value_p[3]);
		return avalues.m_value;
	}

	uint32_t tools::transformlittle(parm<uint32_t>& avalues)
	{
		if constexpr (islittle())
			return avalues.m_value;
		unsigned char* value_p = reinterpret_cast<unsigned char*>(&avalues.m_value);
		avalues.m_value = (static_cast<uint32_t>(value_p[0]) << 24)
			| (static_cast<uint32_t>(value_p[1]) << 16)
			| (static_cast<uint32_t>(value_p[2]) << 8)
			| static_cast<uint32_t>(value_p[3]);
		return avalues.m_value;
	}

	int64_t tools::transformlittle(parm<int64_t>& avalues)
	{
		if constexpr (islittle())
			return avalues.m_value;
		unsigned char* value_p = reinterpret_cast<unsigned char*>(&avalues);
		avalues.m_value = (static_cast<uint64_t>(value_p[0]) << 56)
			| (static_cast<int64_t>(value_p[1]) << 48)
			| (static_cast<int64_t>(value_p[2]) << 40)
			| (static_cast<int64_t>(value_p[3]) << 32)
			| (static_cast<int64_t>(value_p[4]) << 24)
			| (static_cast<int64_t>(value_p[5]) << 16)
			| (static_cast<int64_t>(value_p[6]) << 8)
			| static_cast<int64_t>(value_p[7]);
		return avalues.m_value;
	}

	uint64_t tools::transformlittle(parm<uint64_t>& avalues)
	{
		if constexpr (islittle())
			return avalues.m_value;
		unsigned char* value_p = reinterpret_cast<unsigned char*>(&avalues);
		avalues.m_value = (static_cast<uint64_t>(value_p[0]) << 56)
			| (static_cast<uint64_t>(value_p[1]) << 48)
			| (static_cast<uint64_t>(value_p[2]) << 40)
			| (static_cast<uint64_t>(value_p[3]) << 32)
			| (static_cast<uint64_t>(value_p[4]) << 24)
			| (static_cast<uint64_t>(value_p[5]) << 16)
			| (static_cast<uint64_t>(value_p[6]) << 8)
			| static_cast<uint64_t>(value_p[7]);
		return avalues.m_value;
	}

    class base64_impl
    {
    public:
        static char const* get_alphabet()
        {
            static char constexpr tab[] = {
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
            return &tab[0];
        }

        static signed char const* get_inverse()
        {
            static signed char constexpr tab[] = {
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //   0-15
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, //  16-31
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, //  32-47
                52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, //  48-63
                -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,           //  64-79
                15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, //  80-95
                -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, //  96-111
                41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, // 112-127
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 128-143
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 144-159
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 160-175
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 176-191
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 192-207
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 208-223
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 224-239
                -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1  // 240-255
            };
            return &tab[0];
        }

        static std::size_t constexpr encoded_size(std::size_t n)
        {
            return 4 * ((n + 2) / 3);
        }

        static std::size_t constexpr decoded_size(std::size_t n)
        {
            return n / 4 * 3; // requires n&3==0, smaller
            //return 3 * n / 4;
        }

        /** Encode a series of octets as a padded, base64 string.

            The resulting string will not be null terminated.

            @par Requires

            The memory pointed to by `out` points to valid memory
            of at least `encoded_size(len)` bytes.

            @return The number of characters written to `out`. This
            will exclude any null termination.
        */
        static std::size_t encode(void* dest, void const* src, std::size_t len)
        {
            char* out = static_cast<char*>(dest);
            char const* in = static_cast<char const*>(src);
            auto const tab = get_alphabet();

            for (auto n = len / 3; n--;)
            {
                *out++ = tab[(in[0] & 0xfc) >> 2];
                *out++ = tab[((in[0] & 0x03) << 4) + ((in[1] & 0xf0) >> 4)];
                *out++ = tab[((in[2] & 0xc0) >> 6) + ((in[1] & 0x0f) << 2)];
                *out++ = tab[in[2] & 0x3f];
                in += 3;
            }

            switch (len % 3)
            {
            case 2:
                *out++ = tab[(in[0] & 0xfc) >> 2];
                *out++ = tab[((in[0] & 0x03) << 4) + ((in[1] & 0xf0) >> 4)];
                *out++ = tab[(in[1] & 0x0f) << 2];
                *out++ = '=';
                break;

            case 1:
                *out++ = tab[(in[0] & 0xfc) >> 2];
                *out++ = tab[((in[0] & 0x03) << 4)];
                *out++ = '=';
                *out++ = '=';
                break;

            case 0:
                break;
            }

            return out - static_cast<char*>(dest);
        }

        /** Decode a padded base64 string into a series of octets.

            @par Requires

            The memory pointed to by `out` points to valid memory
            of at least `decoded_size(len)` bytes.

            @return The number of octets written to `out`, and
            the number of characters read from the input string,
            expressed as a pair.
        */
        static std::pair<std::size_t, std::size_t> decode(void* dest, char const* src, std::size_t len)
        {
            char* out = static_cast<char*>(dest);
            auto in = reinterpret_cast<unsigned char const*>(src);
            unsigned char c3[3], c4[4];
            int i = 0;
            int j = 0;

            auto const inverse = get_inverse();

            while (len-- && *in != '=')
            {
                auto const v = inverse[*in];
                if (v == -1)
                    break;
                ++in;
                c4[i] = v;
                if (++i == 4)
                {
                    c3[0] = (c4[0] << 2) + ((c4[1] & 0x30) >> 4);
                    c3[1] = ((c4[1] & 0xf) << 4) + ((c4[2] & 0x3c) >> 2);
                    c3[2] = ((c4[2] & 0x3) << 6) + c4[3];

                    for (i = 0; i < 3; i++)
                        *out++ = c3[i];
                    i = 0;
                }
            }

            if (i)
            {
                c3[0] = (c4[0] << 2) + ((c4[1] & 0x30) >> 4);
                c3[1] = ((c4[1] & 0xf) << 4) + ((c4[2] & 0x3c) >> 2);
                c3[2] = ((c4[2] & 0x3) << 6) + c4[3];

                for (j = 0; j < i - 1; j++)
                    *out++ = c3[j];
            }

            return { out - static_cast<char*>(dest),
                    in - reinterpret_cast<unsigned char const*>(src) };
        }

    };

    std::string tools::base64_encode(const char* data, std::size_t len)
    {
        std::string dest;
        dest.resize(base64_impl::encoded_size(len));
        dest.resize(base64_impl::encode(&dest[0], data, len));
        return dest;
    }

    std::string tools::base64_encode(std::string const& s)
    {
        return base64_encode(s.data(), s.size());
    }

    std::string tools::base64_decode(char const* data, std::size_t len)
    {
        std::string dest;
        dest.resize(base64_impl::decoded_size(len));
        auto const result = base64_impl::decode(
            &dest[0], data, len);
        dest.resize(result.first);
        return dest;
    }

    std::string tools::base64_decode(std::string const& data)
    {
        return base64_decode(data.data(), data.size());
    }

    bool tools::uuid_make(std::string& astr)
    {
#if defined(_WIN32)
            char buf[GUID_LEN] = { 0 };
            GUID guid;

            if (CoCreateGuid(&guid))
            {
                return false;
            }

            sprintf(buf,
                "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
                guid.Data1, guid.Data2, guid.Data3,
                guid.Data4[0], guid.Data4[1], guid.Data4[2],
                guid.Data4[3], guid.Data4[4], guid.Data4[5],
                guid.Data4[6], guid.Data4[7]);

            astr = buf;
            return true;
#else
            uuid_t uuid;
            uuid_generate(uuid);

            char str[37];
            uuid_unparse(uuid, str);

            astr = str;
            return true;
#endif
    }

	bool tools::wasscii2asscii(const std::wstring& awstr, std::string& astr)
	{
		if (awstr.empty())
			return true;

		std::locale sys_locale("");

		const wchar_t* data_from = awstr.c_str();
		const wchar_t* data_from_end = awstr.c_str() + awstr.size();
		const wchar_t* data_from_next = 0;

		int wchar_size = 4;
		char* data_to = new char[(awstr.size() + 1) * wchar_size];
		char* data_to_end = data_to + (awstr.size() + 1) * wchar_size;
		char* data_to_next = 0;

		memset(data_to, 0, (awstr.size() + 1) * wchar_size);

		typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
		mbstate_t out_state;
		auto result = std::use_facet<convert_facet>(sys_locale).out(
			out_state, data_from, data_from_end, data_from_next,
			data_to, data_to_end, data_to_next);
		if (result == convert_facet::ok)
		{
			astr = data_to;
			delete[] data_to;
			return true;
		}
		else
		{
			delete[] data_to;
			astr.clear();
			return false;
		}
	}

	bool tools::asscii2wasscii(const std::string& astr, std::wstring& awstr)
	{
		if (astr.empty())
			return true;

		std::locale sys_locale("");

		const char* data_from = astr.c_str();
		const char* data_from_end = astr.c_str() + astr.size();
		const char* data_from_next = 0;

		wchar_t* data_to = new wchar_t[astr.size() + 1];
		wchar_t* data_to_end = data_to + astr.size() + 1;
		wchar_t* data_to_next = 0;

		wmemset(data_to, 0, astr.size() + 1);

		typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
		mbstate_t in_state;
		auto result = std::use_facet<convert_facet>(sys_locale).in(
			in_state, data_from, data_from_end, data_from_next,
			data_to, data_to_end, data_to_next);
		if (result == convert_facet::ok)
		{
			awstr = data_to;
			delete[] data_to;
			return true;
		}
		else
		{
			delete[] data_to;
			awstr.clear();
			return false;
		}
	}

	bool tools::wasscii2utf8(const std::wstring& awstr, std::string& astr)
	{
		if (awstr.empty())
			return true;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
		astr = conv.to_bytes(awstr);
		return true;
	}

	bool tools::utf82wasscii(const std::string& astr, std::wstring& awstr)
	{
		if (astr.empty())
			return false;
		std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
		awstr = conv.from_bytes(astr);
		return true;
	}

	bool tools::to_utf8(const std::string& astr1, std::string& astr2)
	{
		std::wstring lwsql;
		if (ngl::tools::asscii2wasscii(astr1, lwsql) == false)
			return false;
		if (ngl::tools::wasscii2utf8(lwsql, astr2) == false)
			return false;
		return true;
	}

	bool tools::to_asscii(const std::string& astr1, std::string& astr2)
	{
		std::wstring lwsql;
		if (ngl::tools::utf82wasscii(astr1, lwsql) == false)
			return false;
		if (ngl::tools::wasscii2asscii(lwsql, astr2) == false)
			return false;
		return true;
	}

	void tools::sregex(const std::string& apattern, const std::string& adata, const std::function<void(std::string&)>& afun)
	{
		std::regex r(apattern);
		std::sregex_iterator it(adata.begin(), adata.end(), r);
		std::sregex_iterator end;
		for (; it != end; ++it)
		{
			std::string lstr = it->str();
			afun(lstr);
		}
	}

	///---- values = std::smatch[1];
	void tools::smatch(const std::string& aexpression, const std::string& adata, const std::function<void(std::smatch&)>& afun)
	{
		std::smatch what;
		std::regex expression(aexpression);
		std::string::const_iterator start = adata.begin();
		std::string::const_iterator end = adata.end();
		for (; std::regex_search(start, end, what, expression);)
		{
			afun(what);
			start = what[0].second;
		}
	}

	void tools::replace(const std::string& aexpression, const std::string& areleace, const std::string& adata, std::string& aret)
	{
		std::regex reg(aexpression);
		aret = std::regex_replace(adata, reg, areleace);
	}

	bool tools::replace_ret(const std::string& aexpression, const std::string& areleace, std::string& adata, std::string& aret)
	{
		replace(aexpression, areleace, adata, aret);
		return aret != adata;
	}

	

	bool tools::splite(const char* abuff, const char* afg, std::vector<std::string>& avec)
	{
		if (abuff == nullptr || afg == nullptr)
			return false;
		std::string ltemp;
		for (const char* lp1 = abuff; *lp1 != '\0';)
		{
			int lpos = 0;
			bool lfg = true;
			const char* lp2 = lp1;
			for (; lp2[lpos] != '\0' && afg[lpos] != '\0'; ++lpos)
			{
				if (lp2[lpos] != afg[lpos])
				{
					lfg = false;
					break;
				}
			}
			if (lfg)
			{
				avec.push_back(ltemp);
				ltemp = "";
				lp1 += lpos;
			}
			else
			{
				ltemp += *lp1;
				++lp1;
			}
		}
		if (ltemp.empty() == false)
			avec.push_back(ltemp);
		return !avec.empty();
	}

	std::string tools::char2hex(char dec)
	{
		char dig1 = (dec & 0xF0) >> 4;
		char dig2 = (dec & 0x0F);
		if (0 <= dig1 && dig1 <= 9) dig1 += 48;    //0,48 in ascii
		if (10 <= dig1 && dig1 <= 15) dig1 += 65 - 10; //A,65 in ascii
		if (0 <= dig2 && dig2 <= 9) dig2 += 48;
		if (10 <= dig2 && dig2 <= 15) dig2 += 65 - 10;

		std::string r;
		r.append(&dig1, 1);
		r.append(&dig2, 1);
		return r;
	}

	std::string tools::url_encode(const std::string& c)
	{

		std::string escaped;
		int max = (int)c.length();
		for (int i = 0; i < max; i++)
		{
			if ((48 <= c[i] && c[i] <= 57) ||//0-9
				(65 <= c[i] && c[i] <= 90) ||//ABC...XYZ
				(97 <= c[i] && c[i] <= 122) || //abc...xyz
				(c[i] == '-' || c[i] == '_' || c[i] == '.')//(c[i]=='~' || c[i]=='-' || c[i]=='_' || c[i]=='.')
				)
			{
				escaped.append(&c[i], 1);
			}
			else
			{
				escaped.append("%");
				escaped.append(char2hex(c[i]));//converts char 255 to string "FF"
			}
		}
		return std::move(escaped);
	}

	std::string tools::url_decode(const std::string& szToDecode)
	{
		std::string result;
		int hex = 0;
		for (size_t i = 0; i < szToDecode.length(); ++i)
		{
			switch (szToDecode[i])
			{
			case '+':
				result += ' ';
				break;
			case '%':
				if (isxdigit(szToDecode[i + 1]) && isxdigit(szToDecode[i + 2]))
				{
					std::string hexStr = szToDecode.substr(i + 1, 2);
					hex = strtol(hexStr.c_str(), 0, 16);
					//字母和数字[0-9a-zA-Z]、一些特殊符号[$-_.+!*'(),] 、以及某些保留字[$&+,/:;=?@]
					//可以不经过编码直接用于URL
					if (!((hex >= 48 && hex <= 57) ||	//0-9
						(hex >= 97 && hex <= 122) ||	//a-z
						(hex >= 65 && hex <= 90) ||	//A-Z
						//一些特殊符号及保留字[$-_.+!*'(),]  [$&+,/:;=?@]
						hex == 0x21 || hex == 0x24 || hex == 0x26 || hex == 0x27 || hex == 0x28 || hex == 0x29
						|| hex == 0x2a || hex == 0x2b || hex == 0x2c || hex == 0x2d || hex == 0x2e || hex == 0x2f
						|| hex == 0x3A || hex == 0x3B || hex == 0x3D || hex == 0x3f || hex == 0x40 || hex == 0x5f
						))
					{
						result += char(hex);
						i += 2;
					}
					else result += '%';
				}
				else {
					result += '%';
				}
				break;
			default:
				result += szToDecode[i];
				break;
			}
		}
		return std::move(result);
	}


	struct varint_impl
	{
		static const int32_t m_64maxpos/* = 10*/;
		static const int32_t m_32maxpos/* = 5*/;

		static uint64_t zigzag64encode(int64_t n)
		{
			return (uint64_t)((n >> 63) ^ (n << 1));
		}

		static int64_t zigzag64decode(uint64_t n)
		{
			return (uint64_t)((n >> 1) ^ -(n & 1));
		}

		static uint32_t zigzag32encode(int32_t n)
		{
			return (uint32_t)((n >> 31) ^ (n << 1));
		}

		static int32_t zigzag32decode(uint32_t n)
		{
			return (int32_t)((n >> 1) ^ -(n & 1));
		}
	};

	const int32_t varint_impl::m_64maxpos = 10;
	const int32_t varint_impl::m_32maxpos = 5;

	int tools::varint_length(tools::parm<int64_t>& avalue)
	{
		if (sysconfig::varint())
		{
			uint64_t ln = varint_impl::zigzag64encode(avalue.m_value);
			if ((ln & (0xffffffffffff << 7)) == 0)
				return 1;
			else if ((ln & (0xffffffffffff << 14)) == 0)
				return 2;
			else if ((ln & (0xffffffffffff << 21)) == 0)
				return 3;
			else if ((ln & (0xffffffffffff << 28)) == 0)
				return 4;
			else if ((ln & (0xffffffffffff << 35)) == 0)
				return 5;
			else if ((ln & (0xffffffffffff << 42)) == 0)
				return 6;
			else if ((ln & (0xffffffffffff << 49)) == 0)
				return 7;
			else if ((ln & (0xffffffffffff << 56)) == 0)
				return 8;
			else if ((ln & (0xffffffffffff << 63)) == 0)
				return 9;
			else
				return 10;
		}
		else
			return sizeof(int64_t);
	}

	int tools::varint_length(tools::parm<int32_t>& avalue)
	{
		if (sysconfig::varint())
		{
			uint64_t ln = varint_impl::zigzag64encode(avalue.m_value);
			if ((ln & (0xffffffffffff << 7)) == 0)
				return 1;
			else if ((ln & (0xffffffffffff << 14)) == 0)
				return 2;
			else if ((ln & (0xffffffffffff << 21)) == 0)
				return 3;
			else if ((ln & (0xffffffffffff << 28)) == 0)
				return 4;
			else
				return 5;
		}
		else
			return sizeof(int32_t);
	}

	template <typename T>
	bool encodebasetype(char* buf, int len, const T* adata, int32_t adatalen, int32_t* bytes)
	{
		if (sizeof(T) > len)
			return false;
		memcpy(buf, adata, sizeof(T) * adatalen);
		*bytes += sizeof(T) * adatalen;
		return true;
	}

	bool tools::varint_encode(tools::varint_parm<int64_t>& aparm)
	{
		if (sysconfig::varint() == false)
		{
			if (encodebasetype(aparm.m_buf, aparm.m_len, &aparm.m_value, 1, aparm.m_bytes) == false)
				return false;
			return true;
		}
		else
		{
			uint64_t ln = varint_impl::zigzag64encode(aparm.m_value);
			int32_t index = 0;
			while (true)
			{
				if (index > aparm.m_len || index > varint_impl::m_64maxpos)
					return false;
				//0x7F 即　0111 1111
				//~ 表示取反  
				if ((ln & ~0x7F) == 0)
				{
					aparm.m_buf[index] = (uint8_t)(ln & 0x7F);
					break;
				}
				else
				{
					//取出7位并在第8位加上标记1
					aparm.m_buf[index] = (uint8_t)((ln & 0x7F) | 0x80);
					index++;
					//已经处理的舍去
					ln = ln >> 7;
				}
			}
			*aparm.m_bytes += index + 1;
			return true;
		}
	}

	bool tools::varint_encode(tools::varint_parm<int32_t>& aparm)
	{
		if (sysconfig::varint() == false)
		{
			if (encodebasetype(aparm.m_buf, aparm.m_len, &aparm.m_value, 1, aparm.m_bytes) == false)
				return false;
			return true;
		}
		else
		{
			uint32_t ln = varint_impl::zigzag32encode(aparm.m_value);
			int index = 0;
			while (true)
			{
				if (index > aparm.m_len || index > varint_impl::m_32maxpos)
					return false;
				//0x7F 即　0111 1111
				//~ 表示取反  
				if ((ln & ~0x7F) == 0)
				{
					aparm.m_buf[index] = (uint8_t)(ln & 0x7F);
					break;
				}
				else
				{
					//取出7位并在第8位加上标记1
					aparm.m_buf[index] = (uint8_t)((ln & 0x7F) | 0x80);
					index++;
					//已经处理的舍去
					ln = ln >> 7;
				}
			}
			*aparm.m_bytes += index + 1;
			return true;
		}
	}

	template <typename T>
	bool decodebasetype(const char* buf, int len, int32_t* bytes, T* adata, int32_t adatalen)
	{
		int llen = sizeof(T) * adatalen;
		if (llen > len)
			return false;
		memcpy(adata, buf, llen);
		*bytes += llen;
		return true;
	}

	bool tools::varint_decode(varint_parm<int64_t>& aparm)
	{
		if (sysconfig::varint() == false)
		{
			if (decodebasetype(aparm.m_buf, aparm.m_len, aparm.m_bytes, &aparm.m_value, 1) == false)
				return false;
			return true;
		}
		else
		{
			aparm.m_value = 0;
			int i = 0;
			for (; i < aparm.m_len; i++)
			{
				uint8_t b = aparm.m_buf[i];
				//0x7F 即　0111 1111
				//取出7位然后右移，因为是小端存储
				uint8_t c = (b & 0x7F);
				aparm.m_value |= (int64_t)c << (i * 7);
				// 0x80 即 1000 0000
				//第8位是0 说明后面没有字节了
				if ((uint8_t)(b & 0x80) == 0)
				{
					break;
				}
				if (i > varint_impl::m_64maxpos)
					break;
			}
			*aparm.m_bytes += i + 1;
			aparm.m_value = varint_impl::zigzag64decode(aparm.m_value);
			return true;
		}
	}

	bool tools::varint_decode(varint_parm<int32_t>& aparm)
	{
		if (sysconfig::varint() == false)
		{
			int32_t lbytes = 0;
			if (decodebasetype(aparm.m_buf, aparm.m_len, &lbytes, &aparm.m_value, 1) == false)
				return false;
			*aparm.m_bytes += lbytes;
			return true;
		}
		else
		{
			aparm.m_value = 0;
			int i = 0;
			for (; i < aparm.m_len; i++)
			{
				uint8_t b = aparm.m_buf[i];
				//0x7F 即　0111 1111
				//取出7位然后右移，因为是小端存储
				aparm.m_value |= (b & 0x7F) << (i * 7);
				// 0x80 即 1000 0000
				//第8位是0 说明后面没有字节了
				if ((uint8_t)(b & 0x80) == 0)
				{
					break;
				}
				if (i > varint_impl::m_32maxpos)
					break;
			}
			*aparm.m_bytes += i + 1;
			aparm.m_value = varint_impl::zigzag32decode(aparm.m_value);
			return true;
		}
	}

	unsigned char _hexget(unsigned char asource, unsigned char& atarget)
	{
		if (asource >= 'a' && asource <= 'f')
		{
			unsigned char lret = 10;
			atarget = lret + (asource - 'a');
			return true;
		}
		if (asource >= '0' && asource <= '9')
		{
			atarget = (asource - '0');
			return true;
		}
		return false;
	}

	void _bh(unsigned char& apso, unsigned char& apto1, unsigned char& apto2)
	{
		static const char arr[] = { '0','1','2','3','4','5', '6','7','8', '9','a','b', 'c','d','e', 'f' };
		apto1 = arr[apso >> 4];
		apto2 = arr[0x0f & apso];
	}

	bool _hb(unsigned char* apso, unsigned char* apto)
	{
		(*apto) = 0;
		unsigned char ltarget = 0;
		if (_hexget(*apso, ltarget) == false)
			return false;
		(*apto) |= ltarget << 4;
		if (_hexget(*&apso[1], ltarget) == false)
			return false;
		(*apto) |= ltarget;
		return true;
	}

	int tools::to_hex(void* apso, int alen, void* apto)
	{
		int llen = 0;
		unsigned char* lp1;
		unsigned char* lp2;
		for (int i = 0; i < alen; ++i)
		{
			lp1 = (unsigned char*)apso + i;
			lp2 = (unsigned char*)apto + (i * 2);
			_bh(*lp1, *lp2, *(lp2 + 1));
			llen += 2;
		}
		return llen;
	}

	bool tools::to_bytes(void* apso, int alen, void* apto, int& apotlen)
	{
		int llen = 0;
		for (int i = 0; i < alen / 2; ++i)
		{
			if (_hb(&((unsigned char*)apso)[i * 2], &((unsigned char*)apto)[i]) == false)
				return false;
			llen += 2;
		}
		apotlen = alen / 2;
		return true;
	}

	void tools::bytexor(char* ap, int32_t aplen, int apos)
	{
		if (sysconfig::isxor() == false)
			return;
		if (sysconfig::xorkeynum() < 1 || sysconfig::xorkey().empty())
			return;
		for (int i = 0, j = apos; i < aplen; ++i, ++j)
		{
			ap[i] = ap[i] ^ sysconfig::xorkey()[j & sysconfig::xorkeynum()];
		}
	}

}//namespace ngl

namespace ngl
{

	class md5
	{
		md5(const md5&) = delete;
		md5& operator=(const md5&) = delete;
	public:
		typedef unsigned int size_type; // must be 32bit

		md5();
		md5(const std::string& text);
		void update(const unsigned char* buf, size_type length);
		void update(const char* buf, size_type length);
		md5& finalize();
		std::string hexdigest() const;
		std::string values() const;
		friend std::ostream& operator<<(std::ostream&, md5 amd5);

	private:
		void init();
		typedef unsigned char uint1; //  8bit
		typedef unsigned int uint4;  // 32bit
		enum { blocksize = 64 }; // VC6 won't eat a const static int here

		void transform(const uint1 block[blocksize]);
		static void decode(uint4 output[], const uint1 input[], size_type len);
		static void encode(uint1 output[], const uint4 input[], size_type len);

		bool finalized;
		uint1 buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
		uint4 count[2];   // 64bit counter for number of bits (lo, hi)
		uint4 state[4];   // digest so far
		uint1 digest[16]; // the result

		// low level logic operations
		static inline uint4 F(uint4 x, uint4 y, uint4 z);
		static inline uint4 G(uint4 x, uint4 y, uint4 z);
		static inline uint4 H(uint4 x, uint4 y, uint4 z);
		static inline uint4 I(uint4 x, uint4 y, uint4 z);
		static inline uint4 rotate_left(uint4 x, int n);
		static inline void FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
		static inline void GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
		static inline void HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
		static inline void II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	};


	// Constants for MD5Transform routine.
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

///////////////////////////////////////////////
// F, G, H and I are basic MD5 functions.
	inline md5::uint4 md5::F(uint4 x, uint4 y, uint4 z) {
		return (x & y) | ((~x) & z);
	}

	inline md5::uint4 md5::G(uint4 x, uint4 y, uint4 z) {
		return (x & z) | (y & ~z);
	}

	inline md5::uint4 md5::H(uint4 x, uint4 y, uint4 z) {
		return x ^ y ^ z;
	}

	inline md5::uint4 md5::I(uint4 x, uint4 y, uint4 z) {
		return y ^ (x | ~z);
	}

	// rotate_left rotates x left n bits.
	inline md5::uint4 md5::rotate_left(uint4 x, int n) {
		return (x << n) | (x >> (32 - n));
	}

	// FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
	// Rotation is separate from addition to prevent recomputation.
	inline void md5::FF(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
		a = rotate_left(a + F(b, c, d) + x + ac, s) + b;
	}

	inline void md5::GG(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
		a = rotate_left(a + G(b, c, d) + x + ac, s) + b;
	}

	inline void md5::HH(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
		a = rotate_left(a + H(b, c, d) + x + ac, s) + b;
	}

	inline void md5::II(uint4& a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
		a = rotate_left(a + I(b, c, d) + x + ac, s) + b;
	}

	//////////////////////////////////////////////

	// default ctor, just initailize
	md5::md5()
	{
		init();
	}

	//////////////////////////////////////////////

	// nifty shortcut ctor, compute MD5 for string and finalize it right away
	md5::md5(const std::string& text)
	{
		init();
		update(text.c_str(), (size_type)text.length());
		finalize();
	}

	//////////////////////////////

	void md5::init()
	{
		finalized = false;

		count[0] = 0;
		count[1] = 0;

		// load magic initialization constants.
		state[0] = 0x67452301;
		state[1] = 0xefcdab89;
		state[2] = 0x98badcfe;
		state[3] = 0x10325476;
	}

	//////////////////////////////

	// decodes input (unsigned char) into output (uint4). Assumes len is a multiple of 4.
	void md5::decode(uint4 output[], const uint1 input[], size_type len)
	{
		for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
			output[i] = ((uint4)input[j]) | (((uint4)input[j + 1]) << 8) |
			(((uint4)input[j + 2]) << 16) | (((uint4)input[j + 3]) << 24);
	}

	//////////////////////////////

	// encodes input (uint4) into output (unsigned char). Assumes len is
	// a multiple of 4.
	void md5::encode(uint1 output[], const uint4 input[], size_type len)
	{
		for (size_type i = 0, j = 0; j < len; i++, j += 4) {
			output[j] = input[i] & 0xff;
			output[j + 1] = (input[i] >> 8) & 0xff;
			output[j + 2] = (input[i] >> 16) & 0xff;
			output[j + 3] = (input[i] >> 24) & 0xff;
		}
	}

	//////////////////////////////

	// apply MD5 algo on a block
	void md5::transform(const uint1 block[blocksize])
	{
		uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
		decode(x, block, blocksize);

		/* Round 1 */
		FF(a, b, c, d, x[0], S11, 0xd76aa478); /* 1 */
		FF(d, a, b, c, x[1], S12, 0xe8c7b756); /* 2 */
		FF(c, d, a, b, x[2], S13, 0x242070db); /* 3 */
		FF(b, c, d, a, x[3], S14, 0xc1bdceee); /* 4 */
		FF(a, b, c, d, x[4], S11, 0xf57c0faf); /* 5 */
		FF(d, a, b, c, x[5], S12, 0x4787c62a); /* 6 */
		FF(c, d, a, b, x[6], S13, 0xa8304613); /* 7 */
		FF(b, c, d, a, x[7], S14, 0xfd469501); /* 8 */
		FF(a, b, c, d, x[8], S11, 0x698098d8); /* 9 */
		FF(d, a, b, c, x[9], S12, 0x8b44f7af); /* 10 */
		FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
		FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
		FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
		FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
		FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
		FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

		/* Round 2 */
		GG(a, b, c, d, x[1], S21, 0xf61e2562); /* 17 */
		GG(d, a, b, c, x[6], S22, 0xc040b340); /* 18 */
		GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
		GG(b, c, d, a, x[0], S24, 0xe9b6c7aa); /* 20 */
		GG(a, b, c, d, x[5], S21, 0xd62f105d); /* 21 */
		GG(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
		GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
		GG(b, c, d, a, x[4], S24, 0xe7d3fbc8); /* 24 */
		GG(a, b, c, d, x[9], S21, 0x21e1cde6); /* 25 */
		GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
		GG(c, d, a, b, x[3], S23, 0xf4d50d87); /* 27 */
		GG(b, c, d, a, x[8], S24, 0x455a14ed); /* 28 */
		GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
		GG(d, a, b, c, x[2], S22, 0xfcefa3f8); /* 30 */
		GG(c, d, a, b, x[7], S23, 0x676f02d9); /* 31 */
		GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

		/* Round 3 */
		HH(a, b, c, d, x[5], S31, 0xfffa3942); /* 33 */
		HH(d, a, b, c, x[8], S32, 0x8771f681); /* 34 */
		HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
		HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
		HH(a, b, c, d, x[1], S31, 0xa4beea44); /* 37 */
		HH(d, a, b, c, x[4], S32, 0x4bdecfa9); /* 38 */
		HH(c, d, a, b, x[7], S33, 0xf6bb4b60); /* 39 */
		HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
		HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
		HH(d, a, b, c, x[0], S32, 0xeaa127fa); /* 42 */
		HH(c, d, a, b, x[3], S33, 0xd4ef3085); /* 43 */
		HH(b, c, d, a, x[6], S34, 0x4881d05); /* 44 */
		HH(a, b, c, d, x[9], S31, 0xd9d4d039); /* 45 */
		HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
		HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
		HH(b, c, d, a, x[2], S34, 0xc4ac5665); /* 48 */

		/* Round 4 */
		II(a, b, c, d, x[0], S41, 0xf4292244); /* 49 */
		II(d, a, b, c, x[7], S42, 0x432aff97); /* 50 */
		II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
		II(b, c, d, a, x[5], S44, 0xfc93a039); /* 52 */
		II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
		II(d, a, b, c, x[3], S42, 0x8f0ccc92); /* 54 */
		II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
		II(b, c, d, a, x[1], S44, 0x85845dd1); /* 56 */
		II(a, b, c, d, x[8], S41, 0x6fa87e4f); /* 57 */
		II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
		II(c, d, a, b, x[6], S43, 0xa3014314); /* 59 */
		II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
		II(a, b, c, d, x[4], S41, 0xf7537e82); /* 61 */
		II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
		II(c, d, a, b, x[2], S43, 0x2ad7d2bb); /* 63 */
		II(b, c, d, a, x[9], S44, 0xeb86d391); /* 64 */

		state[0] += a;
		state[1] += b;
		state[2] += c;
		state[3] += d;

		// Zeroize sensitive information.
		memset(x, 0, sizeof x);
	}

	//////////////////////////////

	// MD5 block update operation. Continues an MD5 message-digest
	// operation, processing another message block
	void md5::update(const unsigned char input[], size_type length)
	{
		// compute number of bytes mod 64
		size_type index = count[0] / 8 % blocksize;

		// Update number of bits
		if ((count[0] += (length << 3)) < (length << 3))
			count[1]++;
		count[1] += (length >> 29);

		// number of bytes we need to fill in buffer
		size_type firstpart = 64 - index;

		size_type i;

		// transform as many times as possible.
		if (length >= firstpart)
		{
			// fill buffer first, transform
			memcpy(&buffer[index], input, firstpart);
			transform(buffer);

			// transform chunks of blocksize (64 bytes)
			for (i = firstpart; i + blocksize <= length; i += blocksize)
				transform(&input[i]);

			index = 0;
		}
		else
			i = 0;

		// buffer remaining input
		memcpy(&buffer[index], &input[i], length - i);
	}

	//////////////////////////////

	// for convenience provide a verson with signed char
	void md5::update(const char input[], size_type length)
	{
		update((const unsigned char*)input, length);
	}

	//////////////////////////////

	// MD5 finalization. Ends an MD5 message-digest operation, writing the
	// the message digest and zeroizing the context.
	md5& md5::finalize()
	{
		static unsigned char padding[64] = {
		  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

		if (!finalized) {
			// Save number of bits
			unsigned char bits[8];
			encode(bits, count, 8);

			// pad out to 56 mod 64.
			size_type index = count[0] / 8 % 64;
			size_type padLen = (index < 56) ? (56 - index) : (120 - index);
			update(padding, padLen);

			// Append length (before padding)
			update(bits, 8);

			// Store state in digest
			encode(digest, state, 16);

			// Zeroize sensitive information.
			memset(buffer, 0, sizeof buffer);
			memset(count, 0, sizeof count);

			finalized = true;
		}

		return *this;
	}

	//////////////////////////////

	// return hex representation of digest as string
	std::string md5::hexdigest() const
	{
		if (!finalized)
			return "";

		char buf[33];
		for (int i = 0; i < 16; i++)
			sprintf(buf + i * 2, "%02x", digest[i]);
		buf[32] = 0;

		return std::string(buf);
	}
	std::string md5::values() const
	{
		return hexdigest();
	}


	//////////////////////////////

	std::ostream& operator<<(std::ostream& out, md5& md5)
	{
		return out << md5.hexdigest();
	}
	//////////////////////////////

}// namespace ngl


namespace ngl
{
	// sha-1
	class SHA1
	{
	public:
		SHA1();
		void update(const std::string& s);
		void update(std::istream& is);
		std::string final(bool abool);
		static std::string from_file(const std::string& filename);

	private:
		uint32_t digest[5];
		std::string buffer;
		uint64_t transforms;
	};


	static const size_t BLOCK_INTS = 16;  /* number of 32bit integers per SHA1 block */
	static const size_t BLOCK_BYTES = BLOCK_INTS * 4;


	inline static void reset(uint32_t digest[], std::string& buffer, uint64_t& transforms)
	{
		/* SHA1 initialization constants */
		digest[0] = 0x67452301;
		digest[1] = 0xefcdab89;
		digest[2] = 0x98badcfe;
		digest[3] = 0x10325476;
		digest[4] = 0xc3d2e1f0;

		/* Reset counters */
		buffer = "";
		transforms = 0;
	}


	inline static uint32_t rol(const uint32_t value, const size_t bits)
	{
		return (value << bits) | (value >> (32 - bits));
	}


	inline static uint32_t blk(const uint32_t block[BLOCK_INTS], const size_t i)
	{
		return rol(block[(i + 13) & 15] ^ block[(i + 8) & 15] ^ block[(i + 2) & 15] ^ block[i], 1);
	}


	/*
	 * (R0+R1), R2, R3, R4 are the different operations used in SHA1
	 */

	inline static void R0(const uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i)
	{
		z += ((w & (x ^ y)) ^ y) + block[i] + 0x5a827999 + rol(v, 5);
		w = rol(w, 30);
	}


	inline static void R1(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i)
	{
		block[i] = blk(block, i);
		z += ((w & (x ^ y)) ^ y) + block[i] + 0x5a827999 + rol(v, 5);
		w = rol(w, 30);
	}


	inline static void R2(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i)
	{
		block[i] = blk(block, i);
		z += (w ^ x ^ y) + block[i] + 0x6ed9eba1 + rol(v, 5);
		w = rol(w, 30);
	}


	inline static void R3(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i)
	{
		block[i] = blk(block, i);
		z += (((w | x) & y) | (w & x)) + block[i] + 0x8f1bbcdc + rol(v, 5);
		w = rol(w, 30);
	}


	inline static void R4(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i)
	{
		block[i] = blk(block, i);
		z += (w ^ x ^ y) + block[i] + 0xca62c1d6 + rol(v, 5);
		w = rol(w, 30);
	}


	/*
	 * Hash a single 512-bit block. This is the core of the algorithm.
	 */

	inline static void transform(uint32_t digest[], uint32_t block[BLOCK_INTS], uint64_t& transforms)
	{
		/* Copy digest[] to working vars */
		uint32_t a = digest[0];
		uint32_t b = digest[1];
		uint32_t c = digest[2];
		uint32_t d = digest[3];
		uint32_t e = digest[4];

		/* 4 rounds of 20 operations each. Loop unrolled. */
		R0(block, a, b, c, d, e, 0);
		R0(block, e, a, b, c, d, 1);
		R0(block, d, e, a, b, c, 2);
		R0(block, c, d, e, a, b, 3);
		R0(block, b, c, d, e, a, 4);
		R0(block, a, b, c, d, e, 5);
		R0(block, e, a, b, c, d, 6);
		R0(block, d, e, a, b, c, 7);
		R0(block, c, d, e, a, b, 8);
		R0(block, b, c, d, e, a, 9);
		R0(block, a, b, c, d, e, 10);
		R0(block, e, a, b, c, d, 11);
		R0(block, d, e, a, b, c, 12);
		R0(block, c, d, e, a, b, 13);
		R0(block, b, c, d, e, a, 14);
		R0(block, a, b, c, d, e, 15);
		R1(block, e, a, b, c, d, 0);
		R1(block, d, e, a, b, c, 1);
		R1(block, c, d, e, a, b, 2);
		R1(block, b, c, d, e, a, 3);
		R2(block, a, b, c, d, e, 4);
		R2(block, e, a, b, c, d, 5);
		R2(block, d, e, a, b, c, 6);
		R2(block, c, d, e, a, b, 7);
		R2(block, b, c, d, e, a, 8);
		R2(block, a, b, c, d, e, 9);
		R2(block, e, a, b, c, d, 10);
		R2(block, d, e, a, b, c, 11);
		R2(block, c, d, e, a, b, 12);
		R2(block, b, c, d, e, a, 13);
		R2(block, a, b, c, d, e, 14);
		R2(block, e, a, b, c, d, 15);
		R2(block, d, e, a, b, c, 0);
		R2(block, c, d, e, a, b, 1);
		R2(block, b, c, d, e, a, 2);
		R2(block, a, b, c, d, e, 3);
		R2(block, e, a, b, c, d, 4);
		R2(block, d, e, a, b, c, 5);
		R2(block, c, d, e, a, b, 6);
		R2(block, b, c, d, e, a, 7);
		R3(block, a, b, c, d, e, 8);
		R3(block, e, a, b, c, d, 9);
		R3(block, d, e, a, b, c, 10);
		R3(block, c, d, e, a, b, 11);
		R3(block, b, c, d, e, a, 12);
		R3(block, a, b, c, d, e, 13);
		R3(block, e, a, b, c, d, 14);
		R3(block, d, e, a, b, c, 15);
		R3(block, c, d, e, a, b, 0);
		R3(block, b, c, d, e, a, 1);
		R3(block, a, b, c, d, e, 2);
		R3(block, e, a, b, c, d, 3);
		R3(block, d, e, a, b, c, 4);
		R3(block, c, d, e, a, b, 5);
		R3(block, b, c, d, e, a, 6);
		R3(block, a, b, c, d, e, 7);
		R3(block, e, a, b, c, d, 8);
		R3(block, d, e, a, b, c, 9);
		R3(block, c, d, e, a, b, 10);
		R3(block, b, c, d, e, a, 11);
		R4(block, a, b, c, d, e, 12);
		R4(block, e, a, b, c, d, 13);
		R4(block, d, e, a, b, c, 14);
		R4(block, c, d, e, a, b, 15);
		R4(block, b, c, d, e, a, 0);
		R4(block, a, b, c, d, e, 1);
		R4(block, e, a, b, c, d, 2);
		R4(block, d, e, a, b, c, 3);
		R4(block, c, d, e, a, b, 4);
		R4(block, b, c, d, e, a, 5);
		R4(block, a, b, c, d, e, 6);
		R4(block, e, a, b, c, d, 7);
		R4(block, d, e, a, b, c, 8);
		R4(block, c, d, e, a, b, 9);
		R4(block, b, c, d, e, a, 10);
		R4(block, a, b, c, d, e, 11);
		R4(block, e, a, b, c, d, 12);
		R4(block, d, e, a, b, c, 13);
		R4(block, c, d, e, a, b, 14);
		R4(block, b, c, d, e, a, 15);

		/* Add the working vars back into digest[] */
		digest[0] += a;
		digest[1] += b;
		digest[2] += c;
		digest[3] += d;
		digest[4] += e;

		/* Count the number of transformations */
		transforms++;
	}


	inline static void buffer_to_block(const std::string& buffer, uint32_t block[BLOCK_INTS])
	{
		/* Convert the std::string (byte buffer) to a uint32_t array (MSB) */
		for (size_t i = 0; i < BLOCK_INTS; i++)
		{
			block[i] = (buffer[4 * i + 3] & 0xff)
				| (buffer[4 * i + 2] & 0xff) << 8
				| (buffer[4 * i + 1] & 0xff) << 16
				| (buffer[4 * i + 0] & 0xff) << 24;
		}
	}


	inline SHA1::SHA1()
	{
		reset(digest, buffer, transforms);
	}


	inline void SHA1::update(const std::string& s)
	{
		std::istringstream is(s);
		update(is);
	}


	inline void SHA1::update(std::istream& is)
	{
		while (true)
		{
			char sbuf[BLOCK_BYTES];
			is.read(sbuf, BLOCK_BYTES - buffer.size());
			buffer.append(sbuf, (std::size_t)is.gcount());
			if (buffer.size() != BLOCK_BYTES)
			{
				return;
			}
			uint32_t block[BLOCK_INTS];
			buffer_to_block(buffer, block);
			transform(digest, block, transforms);
			buffer.clear();
		}
	}


	/*
	 * Add padding and return the message digest.
	 */

	inline std::string SHA1::final(bool abool)
	{
		/* Total number of hashed bits */
		uint64_t total_bits = (transforms * BLOCK_BYTES + buffer.size()) * 8;

		/* Padding */
		buffer += (char)0x80;
		size_t orig_size = buffer.size();
		while (buffer.size() < BLOCK_BYTES)
		{
			buffer += (char)0x00;
		}

		uint32_t block[BLOCK_INTS];
		buffer_to_block(buffer, block);

		if (orig_size > BLOCK_BYTES - 8)
		{
			transform(digest, block, transforms);
			for (size_t i = 0; i < BLOCK_INTS - 2; i++)
			{
				block[i] = 0;
			}
		}

		/* Append total_bits, split this uint64_t into two uint32_t */
		block[BLOCK_INTS - 1] = (uint32_t)total_bits;
		block[BLOCK_INTS - 2] = (uint32_t)(total_bits >> 32);
		transform(digest, block, transforms);

		if (abool)
		{
			/* Hex std::string */
			std::ostringstream result;
			for (size_t i = 0; i < sizeof(digest) / sizeof(digest[0]); i++)
			{
				result << std::hex << std::setfill('0') << std::setw(8);
				result << digest[i];
			}

			/* Reset for next run */
			reset(digest, buffer, transforms);

			return result.str();
		}
		std::string lstr;
		lstr.append((const char*)digest, 20);

		/* Reset for next run */
		reset(digest, buffer, transforms);
		return lstr;
	}


	inline std::string SHA1::from_file(const std::string& filename)
	{
		std::ifstream stream(filename.c_str(), std::ios::binary);
		SHA1 checksum;
		checksum.update(stream);
		return checksum.final(false);
	}

}

namespace ngl
{
	std::string tools::md5(const std::string& text)
	{
		ngl::md5 ltemp(text);
		return ltemp.values();
	}

	std::string tools::sh1(const std::string& text)
	{
		SHA1 checksum;
		checksum.update(text);
		return checksum.final(false);
	}

	std::string tools::time2str(int autc)
	{
		char lbuff[1024] = { 0 };
		ngl::localtime::time2str(lbuff, 1024, autc, "%y/%m/%d %H:%M:%S");
		return lbuff;
	}

}// namespace ngl
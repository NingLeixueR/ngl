#pragma once

#include "asio_kcp.h"
#include "type.h"
#include "net_protocol.h"
#include "md5.h"

namespace ngl
{
	class ukcp
	{
		asio_kcp m_kcp;
		bpool m_pool;

		ukcp(i16_port aprot);
	public:
		static int32_t m_conv;

		static ukcp& getInstance(i16_port aprot = -1)
		{
			static bool lfirst = true;
			if (lfirst && aprot == -1)
				throw "udp_kcp::getInstance(-1) first";
			lfirst = false;
			static ukcp ltemp(aprot);
			return ltemp;
		}

#pragma region kcp_send
		template <typename T>
		bool send(i32_sessionid asession, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			std::shared_ptr<pack> lpack = net_pack<T>::npack(&m_pool, adata, aactorid, arequestactorid);
			if (lpack == nullptr)
				return false;
			return m_kcp.sendpack(asession, lpack);
		}

		template <typename T>
		bool send(const asio_udp_endpoint& aendpoint, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			std::shared_ptr<pack> lpack = net_pack<T>::npack(&m_pool, adata, aactorid, arequestactorid);
			if (lpack == nullptr)
				return false;
			return m_kcp.sendpack(aendpoint, lpack);
		}
	private:
		template <typename T, typename TITOR>
		bool send(TITOR abeg, TITOR aend, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			std::shared_ptr<pack> lpack = net_pack<T>::npack(&m_pool, adata, aactorid, arequestactorid);
			if (lpack == nullptr)
				return false;
			for (; abeg != aend; ++abeg)
				m_kcp.sendpack(*abeg, lpack);
			return true;
		}
	public:
		template <typename T>
		bool send(std::vector<i32_sessionid> avec, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			return send(avec.begin(), avec.end(), adata, aactorid, arequestactorid);
		}

		template <typename T>
		bool send(std::list<i32_sessionid> avec, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			return send(avec.begin(), avec.end(), adata, aactorid, arequestactorid);
		}

		template <typename T>
		bool send(std::set<i32_sessionid> avec, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			return send(avec.begin(), avec.end(), adata, aactorid, arequestactorid);
		}
#pragma endregion 

#pragma region udp_send
		template <typename T>
		bool sendu(const asio_udp_endpoint& aendpoint, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			std::shared_ptr<pack> lpack = net_pack<T>::npack(&m_pool, adata, aactorid, arequestactorid);
			if (lpack == nullptr)
				return false;
			return m_kcp.sendu(aendpoint, lpack->m_buff, lpack->m_len);
		}
#pragma endregion 

		// ## ��������
		void connect(const std::string& akcpsess
			, i64_actorid aactorid
			, const std::string& aip
			, i16_port aport
			, const std::function<void(i32_session)>& afun
		);
		void connect(const std::string& akcpsess
			, i64_actorid aactorid
			, const asio_udp_endpoint& aendpoint
			, const std::function<void(i32_session)>& afun
		);

		// ## ����session��Ӧ��actorid
		i64_actorid find_actorid(i32_session asession);

		// ## ����kcp-session����֤����
		static bool create_session(i64_actorid aactorid, std::string& asession);

		// ## ���kcp-session����֤����
		static bool check_session(i64_actorid aactorid, const std::string& asession);

		// ## ��������
		void reset_add(int32_t aconv, const std::string& aip, i16_port aport);
	};
}
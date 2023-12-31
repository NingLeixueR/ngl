#pragma once

#include "type.h"
#include "serialize.h"
#include "pack.h"
#include "nlog.h"
#include "encryption.h"
#include "gm.pb.h"

#define ISBYTEXOR (true)

namespace ngl
{
	class encryption_bytexor
	{
	public:
		template <typename Y>
		static int bytes(Y&)
		{
			return 0;
		}

		template <typename Y>
		static int bytes(actor_forward<Y, EPROTOCOL_TYPE_CUSTOM, true, ngl::forward>& adata)
		{
			return adata.m_recvpack->m_len - adata.m_recvpack->m_pos;
		}

		template <typename Y>
		static int bytes(actor_forward<Y, EPROTOCOL_TYPE_PROTOCOLBUFF, true, ngl::forward>& adata)
		{
			return adata.m_recvpack->m_len - adata.m_recvpack->m_pos;
		}

		template <typename Y>
		static int bytes(actor_forward<Y, EPROTOCOL_TYPE_CUSTOM, false, ngl::forward>& adata)
		{
			return adata.m_recvpack->m_len - adata.m_recvpack->m_pos;
		}

		template <typename Y>
		static int bytes(actor_forward<Y, EPROTOCOL_TYPE_PROTOCOLBUFF, false, ngl::forward>& adata)
		{
			return adata.m_recvpack->m_len - adata.m_recvpack->m_pos;
		}

		template <typename Y>
		static int recv_bytes(Y&)
		{
			return 0;
		}

		template <typename Y>
		static int recv_bytes(actor_forward<Y, EPROTOCOL_TYPE_CUSTOM, true, ngl::forward>& adata)
		{
			return adata.m_recvpack != nullptr ? adata.m_recvpack->m_len : 0;
		}

		template <typename Y>
		static int recv_bytes(actor_forward<Y, EPROTOCOL_TYPE_PROTOCOLBUFF, true, ngl::forward>& adata)
		{
			return adata.m_recvpack != nullptr ? adata.m_recvpack->m_len : 0;
		}

		template <typename Y>
		static int recv_bytes(actor_forward<Y, EPROTOCOL_TYPE_CUSTOM, false, ngl::forward>& adata)
		{
			return adata.m_recvpack != nullptr ? adata.m_recvpack->m_len : 0;
		}

		template <typename Y>
		static int recv_bytes(actor_forward<Y, EPROTOCOL_TYPE_PROTOCOLBUFF, false, ngl::forward>& adata)
		{
			return adata.m_recvpack != nullptr ? adata.m_recvpack->m_len : 0;
		}

		static bool check_xor(int aprotocolnum)
		{
			return ISBYTEXOR;
		}

		static bool check_xor(std::shared_ptr<pack>& apack)
		{
			return check_xor(apack->m_head.getvalue(EPH_PROTOCOLNUM));
		}

		template <typename Y>
		static bool check_xor(Y& adata)
		{
			return check_xor(init_protobuf::protocol<Y>());
		}
	};

	template <typename T>
	class structbytes
	{
	public:
		static bool tostruct(std::shared_ptr<pack>& apack, T& adata, bool aissetpos = false)
		{
			if (apack->m_buff != nullptr)
			{
				if (apack->m_head.getvalue(EPH_BYTES) != apack->m_pos)
				{
					LogLocalError("[##structbytes_protobuff::operator()] -> [%] != [%]", apack->m_head.getvalue(EPH_BYTES), apack->m_pos/* - llen*/);
					return false;
				}

				// ### encryption bytexor
				if (encryption_bytexor::check_xor(apack))
				{
					ngl::encryption::bytexor(apack->m_buff, apack->m_len, 0);
				}
				
				if (adata.ParseFromArray(apack->m_buff, apack->m_head.getvalue(EPH_BYTES)) == false)
					return false;
				if(aissetpos == true)
					apack->m_pos = adata.ByteSize();
			}
			return true;
		}

		static bool tobytes(std::shared_ptr<pack>& apack, T& adata, i64_actorid aactorid, i64_actorid arequestactorid)
		{
			std::pair<char*, int> lpair;
			apack->m_head.reservebuff(apack->m_buff, apack->m_len, lpair);
			if (adata.SerializeToArray(lpair.first, lpair.second) == false)
			{
				LogLocalError("[##struct2bytes::operator()] push error");
				return false;
			}

			// ### encryption bytexor
			if(encryption_bytexor::check_xor(adata))
			{
				ngl::encryption::bytexor(lpair.first, lpair.second, 0);
			}
			
			// ### sethead start ###
			//std::cout << typeid(T).name() << std::endl;
			apack->m_head.m_data[EPH_BYTES] = (apack->m_len - pack_head::size()) + encryption_bytexor::bytes(adata);

			apack->m_head.set_protocol(init_protobuf::protocol<T>());
			apack->m_head.set_actor(aactorid, arequestactorid);
			apack->m_head.set_time();
			apack->m_head.set_protocoltype(init_protobuf::protocol_type<T>());
			//apack->m_head
			// ### sethead finish ###

			ngl::serialize lser2(apack->m_buff, apack->m_len);
			if (!apack->m_head.push(lser2))
				return false;
			apack->m_pos = apack->m_len;

			return true;
		}
	};

	
}
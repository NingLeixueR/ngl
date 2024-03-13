#include "nforward.h"
#include "net.pb.h"

namespace ngl
{
	//# client��game������ ��ע��gateway��ת����game�Ĵ���
	void nforward::c2g()
	{
		register_recvforward<EPROTOCOL_TYPE_PROTOCOLBUFF>(
			null<pbnet::PROBUFF_NET_GET_TIME>
			, null<pbnet::PROBUFF_NET_CMD>
			, null<pbnet::PROBUFF_NET_SWITCH_LINE>
		);

		// ACTOR_MAIL ģ�����ת��
		register_recvforward2<EPROTOCOL_TYPE_PROTOCOLBUFF,ACTOR_MAIL>(
			null<pbnet::PROBUFF_NET_MAIL_LIST>
			, null<pbnet::PROBUFF_NET_MAIL_READ>
			, null<pbnet::PROBUFF_NET_MAIL_DRAW>
			, null<pbnet::PROBUFF_NET_MAIL_DEL>
		);

		// ACTOR_NOTICE ģ�����ת��
		register_recvforward2<EPROTOCOL_TYPE_PROTOCOLBUFF, ACTOR_NOTICE>(
			null<pbnet::PROBUFF_NET_GET_NOTICE>
		);

		// ACTOR_CHAT ģ�����ת��
		register_recvforward2<EPROTOCOL_TYPE_PROTOCOLBUFF, ACTOR_CHAT>(
			null<pbnet::PROBUFF_NET_CHAT>
		);
	}

	// ### game��client������ ��ע��gateway��ת����client�Ĵ���
	void nforward::g2c()
	{
		register_forward<EPROTOCOL_TYPE_PROTOCOLBUFF>(
			null<pbnet::PROBUFF_NET_GET_TIME_RESPONSE>
			, null<pbnet::PROBUFF_NET_ROLE_SYNC_RESPONSE>
			, null<pbnet::PROBUFF_NET_CHAT_RESPONSE>
			, null<pbnet::PROBUFF_NET_SWITCH_LINE_RESPONSE>
			, null<pbnet::PROBUFF_NET_GET_NOTICE_RESPONSE>
			, null<pbnet::PROBUFF_NET_MAIL_LIST_RESPONSE>
			, null<pbnet::PROBUFF_NET_MAIL_READ_RESPONSE>
			, null<pbnet::PROBUFF_NET_MAIL_DRAW_RESPONSE>
			, null<pbnet::PROBUFF_NET_MAIL_DEL_RESPONSE>
			, null<pbnet::PROBUFF_NET_DELIVER_GOODS_RECHARGE>
			, null<pbnet::PROBUFF_NET_ERROR_RESPONSE>
		);
	}
}//namespace ngl
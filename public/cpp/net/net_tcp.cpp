#include "protocol.h"
#include "net_tcp.h"
#include "nguid.h"

namespace ngl
{
	bool net_tcp::socket_recv(service_io* ap, const char* abuff, uint32_t abufflen)
	{
		if (net_protocol::socket_recv(ap->m_sessionid, ap->m_is_lanip, abuff, abufflen) == false)
			return false;
		return m_segpackvec[ap->m_threadid]->push(ap->m_sessionid, abuff, abufflen, ap->m_is_lanip);
	}

	bool net_tcp::init(i16_port aport, i32_threadsize asocketthreadnum, bool aouternet)
	{
		net_protocol::init(aport, asocketthreadnum, aouternet);

		int lsocketthreadnum = socketthreadnum();
		for (int i = 0; i < lsocketthreadnum; ++i)
			m_segpackvec.push_back(new segpack());

		if (lsocketthreadnum > net_config_socket_pthread_max_size || lsocketthreadnum <= 0)
			lsocketthreadnum = net_config_socket_pthread_max_size;

		std::function<bool(service_io*, const char*, uint32_t)> lfun = std::bind_front(&net_tcp::socket_recv, this);

		std::function<void(int)> lclosefun = std::bind_front(&net_tcp::close, this);
		m_server = new asio_tcp(
			m_index, port(), lsocketthreadnum, lfun, lclosefun, [](i32_sessionid asessionid, bool abool, const pack*) 
			{
				if (abool)
				{
					log_error()->print("send finish fail sessionid:{}", asessionid);
				}
			}
		);
		return true;
	}

	bool net_tcp::connect(
		const std::string& aip, 
		i16_port aport, 
		const std::function<void(i32_sessionid)>& afun
	)
	{
		m_server->connect(aip, aport, afun);
		return true;
	}

	void net_tcp::close_net(i32_sessionid asession)
	{
		m_server->close_net(asession);
	}

	void net_tcp::set_close(
		int asession, const std::string& aip, i16_port aport, const std::function<void(i32_sessionid)>& afun
	)
	{
		m_server->set_close(asession, [this, aip, aport, afun]()
			{
				connect(aip, aport, afun);
			});
	}

	bool net_tcp::net_send(i32_sessionid asession, std::shared_ptr<pack>& lpack)
	{
		return m_server->sendpack(asession, lpack);
	}

	bool net_tcp::net_send(i32_sessionid asession, std::shared_ptr<void>& lpack)
	{
		return m_server->sendpack(asession, lpack);
	}

	bool net_tcp::exist_session(i32_sessionid asession)
	{
		return m_server->exist_session(asession);
	}
}//namespace ngl
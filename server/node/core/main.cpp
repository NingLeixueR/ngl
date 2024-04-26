#include "operator_file.h"
#include "server_main.h"
#include "manage_curl.h"
#include "define_json.h"
#include "nactortype.h"
#include "initproto.h"
#include "asio_kcp.h"
#include "dumper.h"
#include "ukcp.h"
#include "rfun.h"

#include <boost/lexical_cast.hpp>

#include "event.h"

Dumper lDumper;

#include "tools.h"

int main(int argc, char** argv)
{
	nconfig::init();
	nconfig::load("config");
	ngl::allcsv::load();

	if (argc <= 1)
	{
		std::cout << "��������" << std::endl;
		return 0;
	}

	// �ò��� ���������е�zoneid
	int32_t larea = boost::lexical_cast<int32_t>(argv[2]);
	int32_t ltcount = boost::lexical_cast<int32_t>(argv[3]);
	ngl::tab_servers* tab = ngl::ttab_servers::tab(argv[1], larea, ltcount);
	nconfig::set_server(argv[1], tab->m_id);

	ngl::init_nactor_type();
	ngl::xmlprotocol::load();
	ngl::nlog::getInstance().isinitfinish() = true;

	char lname[1024] = { 0x0 };
	snprintf(lname, 1024, "node_%s_%s_%s", argv[1], argv[2], argv[3]);

#ifdef WIN32
	// ### ���ÿ���̨��������
	SetConsoleTitle(lname);
#endif
	Dumper::m_excname = lname;

	ngl::nactortype::getInstance();
	ngl::actor_base::start_broadcast();

	assert(nconfig::node_type() != ngl::FAIL);

	if (nconfig::node_type() == ngl::DB)
	{
		start_db(argc, argv);
	}
	else if (nconfig::node_type() == ngl::GAME)
	{
		start_game();
	}
	else if (nconfig::node_type() == ngl::ACTORSERVER)
	{
		start_actor();
	}
	else if (nconfig::node_type() == ngl::LOG)
	{
		start_log();		
	}
	else if (nconfig::node_type() == ngl::GATEWAY)
	{
		start_gateway();
	}
	else if (nconfig::node_type() == ngl::LOGIN)
	{
		start_login();
	}
	else if (nconfig::node_type() == ngl::WORLD)
	{
		start_world();
	}
	else if (nconfig::node_type() == ngl::RELOADCSV)
	{
		start_reloadcsv();
	}
	else if (nconfig::node_type() == ngl::ROBOT)
	{
		start_robot(argc, argv);
	}
	else if (nconfig::node_type() == ngl::CROSS)
	{
		start_cross();
	}
	else if (nconfig::node_type() == ngl::PUSHSERVERCONFIG)
	{
		start_pushserverconfig();
	}

	while (1)
	{
		ngl::sleep::seconds(1);
		ngl::logstream log(ngl::ELOG_DEBUG, ngl::ELOG_NETWORK);
		log << "123" << 456 << std::endl;
		log.print();
	}
	return 0;
}
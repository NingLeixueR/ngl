#include "operator_file.h"
#include "template_arg.h"
#include "server_main.h"
#include "manage_curl.h"
#include "define_json.h"
#include "nactortype.h"
#include "tprotocol.h"
#include "asio_kcp.h"
#include "dumper.h"
#include "event.h"
#include "tools.h"
#include "ukcp.h"
#include "rfun.h"

#include <boost/lexical_cast.hpp>

Dumper lDumper;

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

	switch (nconfig::node_type())
	{
	case ngl::DB:
		start_db(argc, argv);
		break;
	case ngl::GAME:
		start_game();
		break;
	case ngl::ACTORSERVER:
		start_actor();
		break;
	case ngl::LOG:
		start_log();
		break;
	case ngl::GATEWAY:
		start_gateway();
		break;
	case ngl::LOGIN:
		start_login();
		break;
	case ngl::WORLD:
		start_world();
		break;
	case ngl::RELOADCSV:
		start_csvserver();
		break;
	case ngl::ROBOT:
		start_robot(argc, argv);
		break;
	case ngl::CROSS:
		start_cross();
		break;
	case ngl::PUSHSERVERCONFIG:
		start_pushserverconfig();
		break;
	}

	while (1)
	{
		ngl::sleep::seconds(1);
	}
	return 0;
}
#include "event.h"
#include "map.h"

namespace ngl
{
	void init_event()
	{
		// ��ʼ��Ϊenum_event_death��Ӵ����¼�
		event_death::init();
		event_death::push([](ngl::event_parm_death* aparm)
			{
				std::cout << "ngl::event_parm_death" << std::endl;
			}
		);
	}
}
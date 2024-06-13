#include "operator_file.h"
#include "tools.h"
#include "nlog.h"
#include "csv.h"
#include "md5.h"

namespace ngl
{
	bool rcsv::read(const std::string& aname, std::string& averify)
	{
		//# ��ȡ�ļ�
		readfile lrf(aname);
		//# ����ǰ3�б�ͷ
		lrf.jumpbegin(3, true);

		if (lrf.readcurrent(m_data) == false)
		{
			std::cout << std::format("loadcsv fail #{}", aname) << std::endl;
			return false;
		}
		md5 lmd5(m_data);
		averify = lmd5.values();
		std::cout << std::format("loadcsv#{}#{}", aname, averify) << std::endl;
		return true;
	}
}// namespace ngl
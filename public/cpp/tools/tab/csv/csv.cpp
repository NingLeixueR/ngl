#include "operator_file.h"
#include "tools.h"
#include "nlog.h"
#include "csv.h"


namespace ngl
{
	
	void rcsv::read(const std::string& aname, int32_t& aversion)
	{
		//# ��ȡ�ļ�
		readfile lrf(aname);
		//# ����ǰ3�б�ͷ
		lrf.jumpbegin(3, true);

		//# ��ȡ��4��reload csv version
		std::string lversion;
		lrf.readline(lversion);

		Try
		{
			std::vector<std::string>  lvec;
			if (tools::splite(lversion.c_str(), ",", lvec) == false)
				return;
			Assert(lvec.empty() == false);
			std::string lver;
			if (tools::splite(lvec[0].c_str(), ":", lver, aversion) == false)
				return;
			Assert(lver == "version");
		}Catch;


		if (lrf.readcurrent(m_data) == false)
		{
			log_error()->print("!!!! {} !!!!", aname);
		}
	}
}// namespace ngl
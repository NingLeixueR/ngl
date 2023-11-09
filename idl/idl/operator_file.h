#pragma once

#include <string>
#include <fstream>

namespace ngl
{
	class readfile
	{
		std::ifstream m_file;
	public:
		readfile(const std::string& filename);
		~readfile();
		//����ǰ����
		void jumpbegin(int anum);
		void readline(std::string& aline);
		void readcurrent(std::string& aneirong);
		void read(std::string& aneirong);
	};

	class writefile
	{
		std::ofstream m_file;
	public:
		writefile(const std::string& filename);
		~writefile();
		void write(const std::string& aneirong);
	};


	class removefile
	{
	public:
		static bool remove(const std::string& afilename);
	};

}
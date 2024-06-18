#pragma once

#include <fstream>
#include <string>
#include <memory>
#include <vector>

namespace ngl
{
	class readfile
	{
		readfile() = delete;
		readfile(const readfile&) = delete;
		readfile& operator=(const readfile&) = delete;

		std::ifstream m_file;
	public:
		readfile(const std::string& filename);
		~readfile();
		// ����ǰanum��
		void jumpbegin(int anum, bool aiscsv);
		bool readline(std::string& aline);
		bool readcurrent(std::string& astr);
		void read(std::string& aneirong);
	};

	class writefile
	{
		writefile() = delete;
		writefile(const writefile&) = delete;
		writefile& operator=(const writefile&) = delete;

		std::ofstream m_file;
	public:
		writefile(const std::string& filename);
		~writefile();
		void write(const std::string& aneirong);
	};

	class filetools
	{
		filetools() = delete;
		filetools(const filetools&) = delete;
		filetools& operator=(const filetools&) = delete;

	public:
		static bool exist(const std::string& afilename);
		static bool remove(const std::string& afilename);
		// ��ȡdir������Ŀ¼
		static void dir(const std::string& apath, std::vector<std::string>& afilevec);
	};
}//namespace ngl
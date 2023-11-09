#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <functional>
#include "operator_file.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>  
#include <string>  
#include <iostream> 
#include <regex>
#include <set>
#include <map>
#include <boost/lexical_cast.hpp> 
#include <filesystem>


bool is_sname(const std::string& astrname, const std::string& akey)
{
    auto itor1 = astrname.rbegin();
    auto itor2 = akey.rbegin();
    for (; itor1 != astrname.rend() && itor2 != akey.rend(); ++itor1, ++itor2)
    {
        if (*itor1 != *itor2)
        {
            break;
        }
    }
    if (itor2 == akey.rend())
        return true;
    return false;
}

void find(bool awz, const std::string& atxt, const std::string& targetPath, std::set<std::string>& adir, std::set<std::string>& avec1, std::set<std::string>& avec2)
{
    std::filesystem::path myPath(targetPath);
    std::filesystem::recursive_directory_iterator endIter;
    for (std::filesystem::recursive_directory_iterator iter(myPath); iter != endIter; iter++)
    {
        if (std::filesystem::is_directory(*iter))
        {
            std::cout << "dir:[" << iter->path().string() << "]" << std::endl;
            adir.insert(iter->path().string());
            find(awz, atxt, iter->path().string(), adir, avec1, avec2);
        }
        else
        {
            std::cout << "file:[" << iter->path().string() << "]" << std::endl;
            std::string lpath = iter->path().string();
            std::string lname;
            for (auto itor = lpath.begin(); itor != lpath.end(); ++itor)
            {
                if (*itor == '/' || *itor == '\\')
                    lname = "";
                else
                    lname += *itor;
            }

            if (is_sname(lname, atxt))
            {
                if (awz)
                    avec1.insert(targetPath + lname);
                else
                    avec1.insert(lname);
                continue;
            }

           /* int lindex = lname.find(atxt);
            if (lindex > 0)
            {
                if(awz)
                    avec1.insert(targetPath + lname);
                else
                    avec1.insert(lname);
                continue;
            }*/
            //lindex = lname.find(".cc");
           // if (lindex > 0)
           // {
           //     avec2.insert(lname);
           //     continue;
           // }
        }
    }
}


#include <memory>
#include <functional>

#include "impl.h"

#include <iostream>
#include <type_traits>
#include <typeinfo>


#include <ranges>
#include <iostream>



int main(int argc, char** argv)
{


    auto const ints = { 0,4,2,3,5 };
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    // 组合视图的“管道”语法：
    for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    // 传统的“函数式”组合语法：
    for (int i : std::views::transform(std::views::filter(ints, even), square)) {
        std::cout << i << ' ';
    }




    std::set<std::string> lvec1;
    std::set<std::string> lvec2;
    std::set<std::string> lvec3;
    std::set<std::string> lvec4;
    std::set<std::string> lvec5;
    std::set<std::string> lvec6;
    std::set<std::string> ldic;

    std::stringstream m_stream;
    std::stringstream m_streamtxt;
    for (int i = 2; i < argc; ++i)
    {
        std::string targetPath = argv[i];
        ldic.insert(targetPath);
        find(false, ".cpp", targetPath, ldic, lvec1, lvec2);
        find(false, ".c", targetPath, ldic, lvec5, lvec6);
       // find(false, ".pb.cc", targetPath, ldic, lvec3, lvec4);

       
    }


    for (auto item : lvec1)
        m_stream << "#include \"" << item << "\"\n";
    for (auto item : lvec2)
        m_stream << "#include \"" << item << "\"\n";
    for (auto item : lvec3)
        m_stream << "#include \"" << item << "\"\n";

    m_stream << "extern \"C\"{\n";
    for (auto item : lvec5)
        m_stream << "#include \"" << item << "\"\n";
    m_stream << "}//extern \"C\"\n";

    for (auto item : ldic)
        m_streamtxt << "INCLUDE_DIRECTORIES(" << item << ")\n";

    std::string cname = argv[1];
    ngl::writefile lfile(cname);
    lfile.write(m_stream.str());
    cname += ".txt";
    ngl::writefile lfiletxt(cname);
    lfiletxt.write(m_streamtxt.str());
    std::cout << "##############" << cname << std::endl;
   

	return 0;
}
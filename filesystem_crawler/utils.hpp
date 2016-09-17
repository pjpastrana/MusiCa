#ifndef _UTILS_H_
#define _UTILS_H_

namespace utils 
{

void write_to_file(string file_name, string file_content)
{
    std::ofstream out(file_name);
    out << file_content;
    out.close();
}

}

#endif



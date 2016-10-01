#ifndef _UTILS_H_
#define _UTILS_H_

#include <fstream>

namespace utils 
{
void write_to_file(string file_name, string file_content)
{
    std::ofstream out(file_name);
    out << file_content;
    out.close();
}

string read_from_file(string filename)
{
    std::ifstream ifs(filename);
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(ifs) ),
                  ( std::istreambuf_iterator<char>()) );
    return content;
}

// print_list
    // for (std::list<double>::iterator it=audio_data_.begin(); it != audio_data_.end(); ++it)
    //     std::cout << ' ' << *it;

}

#endif



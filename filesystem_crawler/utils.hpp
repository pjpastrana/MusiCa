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

// print_list
    // for (std::list<double>::iterator it=audio_data_.begin(); it != audio_data_.end(); ++it)
    //     std::cout << ' ' << *it;

}

#endif



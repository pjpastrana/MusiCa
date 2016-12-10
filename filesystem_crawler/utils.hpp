#ifndef _UTILS_H_
#define _UTILS_H_

#include <fstream>

namespace utils 
{

inline void write_to_file(std::string file_name, std::string file_content)
{
    std::ofstream out(file_name);
    out << file_content;
    out.close();
}

inline std::string read_from_file(std::string filename)
{
    std::ifstream ifs(filename);
    std::string content;
    content.assign( (std::istreambuf_iterator<char>(ifs) ),
                  ( std::istreambuf_iterator<char>()) );
    return content;
}

// TODO: this method should be generic to different datatypes
inline std::vector<double> extract_col_from_vector_matrix(std::vector< std::vector<double> > vector_matrix, int column_idx)
{
    std::vector<double> column_of_interest(vector_matrix.size(), 0.0);
    int i = 0;
    for(auto row : vector_matrix)
    {
        column_of_interest.at(i++) = row[column_idx];
    }
    return column_of_interest;
}

}

#endif



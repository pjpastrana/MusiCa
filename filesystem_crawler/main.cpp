#include <iostream>
#include "filesystem_crawler.hpp"

int main(int argc, char* argv[])
{

    FilesystemCrawler filesystem_crawler("/Volumes/MRJONES/Music");
    filesystem_crawler.crawl();
    // if (argc < 2)
    // {
    //     cout << "Usage: tut2 path\n";
    //     return 1;
    // }

    // path p(argv[1]);  // avoid repeated path construction below

    // if (exists(p))    // does path p actually exist?
    // {
//     if (is_regular_file(p))        // is path p a regular file?
    //         cout << p << " size is " << file_size(p) << '\n';

    //     else if (is_directory(p))      // is path p a directory?
    //         cout << p << " is a directory\n";

    //     else
    //         cout << p << " exists, but is not a regular file or directory\n";
    // }
    // else
    //     cout << p << " does not exist\n";

    return 0;
}

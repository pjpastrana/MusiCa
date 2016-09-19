#include <iostream>
#include "filesystem_crawler.hpp"
#include "properties.hpp"

using namespace std;

void crawl_filesystem(Properties* properties);

int main(int argc, const char* argv[])
{
    if(argc != 2)
    {
        cerr << "Invalid number of input arguments" << endl;
        exit(1);
    }

    string properties_file(argv[1]);
    Properties properties(properties_file);
    crawl_filesystem(&properties);

    return 0;
}


void crawl_filesystem(Properties* properties)
{
    FilesystemCrawler filesystem_crawler(properties);
    filesystem_crawler.crawl();
}


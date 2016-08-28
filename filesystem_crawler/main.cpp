#include <iostream>
#include "filesystem_crawler.hpp"

int main(int argc, char* argv[])
{

    FilesystemCrawler filesystem_crawler("/Volumes/MRJONES/Music");
    filesystem_crawler.crawl();
    return 0;
}

#include <iostream>
#include "filesystem_crawler.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // TODO: input validation
    string starting_directory(argv[1]);
    FilesystemCrawler filesystem_crawler(starting_directory);
    filesystem_crawler.crawl();
    return 0;
}

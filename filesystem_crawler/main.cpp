#include <iostream>
#include "filesystem_crawler.hpp"
#include "properties.hpp"

using namespace std;

void read_properties_file(string filename);

void crawl_filesystem(Properties* properties);

// class FileSystem
// {
//     public:
//       string something;
//       static FileSystem& instance(string pedro)
//       {
//         static FileSystem *instance = new FileSystem(pedro);
//         return *instance;
//       }

//     private:
//       FileSystem(string pedro) {
//         something = pedro;
//       }
// };

int main(int argc, char* argv[])
{
    // FileSystem fs = FileSystem::instance("pedro");
    // cout << fs.something << endl;
    // TODO: input validation
    string properties_file(argv[1]);
    Properties properties(properties_file);
    // Properties properties = Properties::instance(properties_file);
    // // cout << "starting_directory " << properties.get_string("starting_directory") << endl;
    crawl_filesystem(&properties);

    return 0;
}


void crawl_filesystem(Properties* properties)
{
    FilesystemCrawler filesystem_crawler(properties);
    filesystem_crawler.crawl();
}


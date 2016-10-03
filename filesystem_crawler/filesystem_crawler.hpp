#ifndef _FILESYSTEM_CRAWLER_H_
#define _FILESYSTEM_CRAWLER_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

#include "crawl_worker_factory.hpp"
#include "file_metadata.hpp"
#include "properties.hpp"

using namespace std;

using boost::filesystem::recursive_directory_iterator;
using boost::filesystem::path;

class FilesystemCrawler
{
    string starting_directory_;
    vector< shared_ptr<CrawlWorker> > crawl_workers_;

    public:
        FilesystemCrawler(Properties* properties);
        ~FilesystemCrawler();
        void crawl();
        void execute_crawl_workers(const path file);
};


#endif

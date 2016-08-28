#ifndef _FILESYSTEM_CRAWLER_H_
#define _FILESYSTEM_CRAWLER_H_

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

#include "tag_extractor_crawl_worker.hpp"

// TODO: what is the best way to have use or include namespace items
using namespace std;
using namespace boost::filesystem;


class FilesystemCrawler
{
    string root_directory;
    CrawlWorker* crawl_worker;

    public:
        FilesystemCrawler();
        ~FilesystemCrawler();
        void crawl();
};


#endif

#ifndef _FILESYSTEM_CRAWLER_H_
#define _FILESYSTEM_CRAWLER_H_

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

#include "tag_extractor_crawl_worker.hpp"

using namespace std;
// TODO: check if including namespace elements is a good practice
using boost::filesystem::recursive_directory_iterator;
using boost::filesystem::path;


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

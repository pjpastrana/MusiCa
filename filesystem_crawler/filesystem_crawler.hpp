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
    string starting_directory_;
    CrawlWorker* crawl_worker;

    public:
        FilesystemCrawler(string starting_directory);
        ~FilesystemCrawler();
        void crawl();
};


#endif

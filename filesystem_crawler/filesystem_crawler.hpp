#ifndef _FILESYSTEM_CRAWLER_H_
#define _FILESYSTEM_CRAWLER_H_

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

#include "music_file_metadata_extractor_crawl_worker.hpp"
#include "file_metadata.hpp"

using namespace std;
// TODO: check if including namespace elements is a good practice
using boost::filesystem::recursive_directory_iterator;
using boost::filesystem::path;

// template<class T>
class FilesystemCrawler
{
    string starting_directory_;
    CrawlWorker* crawl_worker_;
    // TODO: move repository to its own class
    vector<FileMetadata*> file_system_repository_;

    public:
        FilesystemCrawler(string starting_directory);
        ~FilesystemCrawler();
        void crawl();
        // TODO: this method is part of the repository class to be created
        void persist_repository();
};


#endif

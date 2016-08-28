#include "filesystem_crawler.hpp"

FilesystemCrawler::FilesystemCrawler(string starting_directory)
{
    // TODO: dependency injection, how to do that in c++
    crawl_worker = new TagExtractorCrawlWorker();
    starting_directory_ = starting_directory;
}

FilesystemCrawler::~FilesystemCrawler()
{
    delete crawl_worker;
    crawl_worker = NULL;
}

void FilesystemCrawler::crawl()
{
    // TODO: verify the directory exists, catch error if the directory does not exists
    cout << "starting_directory " << starting_directory_ << endl;
    recursive_directory_iterator iter(starting_directory_);
    recursive_directory_iterator end;
    for (; iter != end; ++iter) {
        // check for things like is_directory(iter->status()), iter->filename() ....
        // optionally, you can call iter->no_push() if you don't want to
        // enter a directory
        // see all the possibilities by reading the docs.
        //cout << iter->path().filename() << endl;
        // crawl_worker->do_something(iter->path().filename().string());
        crawl_worker->do_something(iter->path());
    }
}
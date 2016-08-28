#include "filesystem_crawler.hpp"

FilesystemCrawler::FilesystemCrawler()
{
    // TODO: dependency injection, how to do that in c++
    crawl_worker = new TagExtractorCrawlWorker();
}

FilesystemCrawler::~FilesystemCrawler()
{
    delete crawl_worker;
    crawl_worker = NULL;
}

void FilesystemCrawler::crawl()
{
    cout << "ma look at me crawling" << endl;
    recursive_directory_iterator iter("./");
    recursive_directory_iterator end;
    for (; iter != end; ++iter) {
        // check for things like is_directory(iter->status()), iter->filename() ....
        // optionally, you can call iter->no_push() if you don't want to
        // enter a directory
        // see all the possibilities by reading the docs.
        //cout << iter->path().filename() << endl;
        crawl_worker->do_something(iter->path().filename().string());
    }
}
#include "filesystem_crawler.hpp"

FilesystemCrawler::FilesystemCrawler(Properties* properties)
{
    vector<string> crawl_worker_names = properties->get_string_array("crawl_workers");
    starting_directory_ = properties->get_string("starting_directory");

    // create workers
    for (auto worker_name : crawl_worker_names)
    {
        cout << "INFO@FilesystemCrawler: Creating crawl_worker: " << worker_name << endl;
        crawl_workers_.push_back(CrawlWorkerFactory::get_crawl_worker(worker_name, properties));
    }
}

FilesystemCrawler::~FilesystemCrawler()
{}

void FilesystemCrawler::crawl()
{
    cout << "INFO@FilesystemCrawler.crawl: starting_directory " << starting_directory_ << endl;
    recursive_directory_iterator iter(starting_directory_);
    recursive_directory_iterator end;
    for (; iter != end; ++iter)
    {
        execute_crawl_workers(iter->path());
    }
}

void FilesystemCrawler::execute_crawl_workers(const path file)
{
    for(vector< shared_ptr<CrawlWorker> >::iterator it = crawl_workers_.begin() ; it != crawl_workers_.end(); ++it)
    {
        (*it)->do_something( file );
    }
}

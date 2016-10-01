#include "filesystem_crawler.hpp"
#include "music_file_metadata.hpp"

#include <rapidjson/prettywriter.h>
#include <fstream>

using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;

FilesystemCrawler::FilesystemCrawler(Properties* properties)
{
    vector<string> crawl_worker_names = properties->get_string_array("crawl_workers");
    starting_directory_ = properties->get_string("starting_directory");

    // create workers
    for (auto worker_name : crawl_worker_names)
    {
        cout << "Creating crawl_worker: " << worker_name << endl;
        crawl_workers_.push_back(CrawlWorkerFactory::get_crawl_worker(worker_name, properties));
    }
}

FilesystemCrawler::~FilesystemCrawler()
{}

void FilesystemCrawler::crawl()
{
    // TODO: verify the directory exists, catch error if the directory does not exists
    cout << "starting_directory " << starting_directory_ << endl;
    recursive_directory_iterator iter(starting_directory_);
    recursive_directory_iterator end;
    for (; iter != end; ++iter)
    {
        cout << "sending " << iter->path().string() << endl;
        execute_crawl_workers(iter->path());
    }
}

shared_ptr<FileMetadata> FilesystemCrawler::execute_crawl_workers(const path file)
{
    shared_ptr<FileMetadata> file_metadata_ptr = NULL;
    for(vector< shared_ptr<CrawlWorker> >::iterator it = crawl_workers_.begin() ; it != crawl_workers_.end(); ++it)
    {
        file_metadata_ptr = (*it)->do_something( file );
    }
    return file_metadata_ptr;
}

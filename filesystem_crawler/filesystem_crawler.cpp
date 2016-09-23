#include "filesystem_crawler.hpp"
#include "music_file_metadata.hpp"

#include <rapidjson/prettywriter.h>
#include <fstream>

using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;

void utils_write_to_file(string file_name, string file_content)
{
    std::ofstream out(file_name);
    out << file_content;
    out.close();
}

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
    // int items_added = 0;
    recursive_directory_iterator iter(starting_directory_);
    recursive_directory_iterator end;
    for (; iter != end; ++iter)
    {
        cout << "sending " << iter->path().string() << endl;
        execute_crawl_workers(iter->path());
        // TODO: move the validation to fileMetadata object
        // if(file_metadata && file_metadata->file_name_ != "")
        // {
        //     cout << "File Name @ crawler --> " << file_metadata->file_name_ << endl;
        //     cout << "saving in repository " << items_added++ << endl;
        //     file_system_repository_.push_back(file_metadata);
        // }
    }
    // cout << "items added to repository " << items_added << endl;
    // cout << "There are " << file_system_repository_.size() << " items in repository " << endl;
    // persist_repository();
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

void FilesystemCrawler::persist_repository()
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);

    writer.StartObject();
    writer.String("data");
    writer.StartArray();
    // TODO: need to pass the type dynamically...this class should not know of the existance of MusicFileMetadata
    vector<FileMetadata*>::const_iterator repository_itr = file_system_repository_.begin();
    for (; repository_itr != file_system_repository_.end(); ++repository_itr)
    {
        FileMetadata* file_metadata_ptr = *repository_itr;
        MusicFileMetadata* music_file_metadata_ptr = dynamic_cast<MusicFileMetadata*>(file_metadata_ptr);
        if(music_file_metadata_ptr)
        {
            music_file_metadata_ptr->serialize(writer);
        }
    }
    writer.EndArray();
    writer.EndObject();

    utils_write_to_file("music-repository.json", sb.GetString());
}
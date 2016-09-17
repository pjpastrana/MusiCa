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
    string crawl_worker_name = properties->get_string("crawl_workers");
    starting_directory_ = properties->get_string("starting_directory");

    crawl_worker_ = CrawlWorkerFactory::get_crawl_worker(crawl_worker_name);
}

FilesystemCrawler::~FilesystemCrawler()
{
    delete crawl_worker_;
    crawl_worker_ = NULL;

    vector<FileMetadata*>::const_iterator repository_itr = file_system_repository_.begin();
    for (; repository_itr != file_system_repository_.end(); ++repository_itr)
    {
        FileMetadata* file_metadata_ptr = *repository_itr;
        MusicFileMetadata* music_file_metadata_ptr = dynamic_cast<MusicFileMetadata*>(file_metadata_ptr);
        if(music_file_metadata_ptr)
        {
            delete music_file_metadata_ptr;
            music_file_metadata_ptr = NULL;
        }
    }
}

void FilesystemCrawler::crawl()
{
    // TODO: verify the directory exists, catch error if the directory does not exists
    cout << "starting_directory " << starting_directory_ << endl;
    int items_added = 0;
    recursive_directory_iterator iter(starting_directory_);
    recursive_directory_iterator end;
    for (; iter != end; ++iter)
    {
        cout << "sending " << iter->path().string() << endl;
        FileMetadata* file_metadata = crawl_worker_->do_something(iter->path());
        // TODO: move the validation to fileMetadata object
        if(file_metadata && file_metadata->file_name_ != "")
        {
            cout << "File Name @ crawler --> " << file_metadata->file_name_ << endl;
            cout << "saving in repository " << items_added++ << endl;
            file_system_repository_.push_back(file_metadata);
        }
    }
    cout << "items added to repository " << items_added << endl;
    cout << "There are " << file_system_repository_.size() << " items in repository " << endl;
    persist_repository();
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
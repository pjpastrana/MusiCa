#include "filesystem_crawler.hpp"
#include "audio_file_metadata.hpp"

#include <rapidjson/prettywriter.h>
#include <fstream>

using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;

void write_to_file(string file_name, string file_content)
{
    std::ofstream out(file_name);
    out << file_content;
    out.close();
}

FilesystemCrawler::FilesystemCrawler(string starting_directory)
{
    // TODO: dependency injection, how to do that in c++
    crawl_worker_ = new TagExtractorCrawlWorker();
    starting_directory_ = starting_directory;
}

FilesystemCrawler::~FilesystemCrawler()
{
    delete crawl_worker_;
    crawl_worker_ = NULL;
}

void FilesystemCrawler::crawl()
{
    // TODO: verify the directory exists, catch error if the directory does not exists
    cout << "starting_directory " << starting_directory_ << endl;
    recursive_directory_iterator iter(starting_directory_);
    recursive_directory_iterator end;
    for (; iter != end; ++iter)
    {
        FileMetadata* file_metadata = crawl_worker_->do_something(iter->path());
        // TODO: move the validation to fileMetadata object
        if(file_metadata->file_name_ != "")
        {
            file_system_repository_.push_back(file_metadata);
        }
    }
    persist_repository();
}

void FilesystemCrawler::persist_repository()
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);

    writer.StartArray();
    // TODO: need to pass the type dynamically...this class should not know of the existance of AudioFileMetadata
    vector<FileMetadata*>::const_iterator repository_itr = file_system_repository_.begin();
    for (; repository_itr != file_system_repository_.end(); ++repository_itr)
    {
        FileMetadata* file_metadata_ptr = *repository_itr;
        AudioFileMetadata* audio_file_metadata = dynamic_cast<AudioFileMetadata*>(file_metadata_ptr);
        if(audio_file_metadata)
        {
            audio_file_metadata->serialize(writer);
        }
        
    }
    writer.EndArray();

    // cout << sb.GetString() << endl;

    write_to_file("music-repository.json", sb.GetString());
}
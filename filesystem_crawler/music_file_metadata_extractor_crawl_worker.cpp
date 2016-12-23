#include "music_file_metadata_extractor_crawl_worker.hpp"

MusicFileMetadataExtractorCrawlWorker::MusicFileMetadataExtractorCrawlWorker(Properties* properties)
{
    music_file_metadata_ = NULL;
    persistence_directory_ = properties->get_string("persistence_directory");
}

MusicFileMetadataExtractorCrawlWorker::~MusicFileMetadataExtractorCrawlWorker()
{}

void MusicFileMetadataExtractorCrawlWorker::do_something(const path file)
{
    if(exists(file) && is_regular_file(file) && is_valid_file(file))
    {
        // only working with user/data files (i.e. not hidden or system files)
        cout << "INFO@MusicFileMetadataExtractorCrawlWorker.do_something: " << file.string() << endl;
        extract_tags_from_file(file);
        persist_metadata();
    }
}

bool MusicFileMetadataExtractorCrawlWorker::is_valid_file(const path file_path)
{
    bool is_valid = false;
    // TODO: refactor. create some sort of class or enum with the valid types
    if(file_path.extension() == ".flac")
        is_valid = true;
    return is_valid;
}

void MusicFileMetadataExtractorCrawlWorker::extract_tags_from_file(const path file_path)
{
    TagLib::FileRef file(file_path.c_str());

    if(!file.isNull() && file.tag())
    {
        music_file_metadata_ = make_shared<MusicFileMetadata>();

        TagLib::Tag *tag = file.tag();
        music_file_metadata_->file_name_ = file_path.filename().string();
        music_file_metadata_->file_location_ = file_path.string();
        music_file_metadata_->file_size_ = file_size(file_path);
        music_file_metadata_->title_ = tag->title().to8Bit();
        music_file_metadata_->artist_ = tag->artist().to8Bit();
        music_file_metadata_->album_ = tag->album().to8Bit();
        music_file_metadata_->year_ = to_string(tag->year());
        music_file_metadata_->track_ = to_string(tag->track());
        music_file_metadata_->genre_ = tag->genre().to8Bit();

        if(file.audioProperties())
        {
            TagLib::AudioProperties *properties = file.audioProperties();

            music_file_metadata_->bitrate_ = properties->bitrate();
            music_file_metadata_->sample_rate_ = properties->sampleRate();
            music_file_metadata_->channels_ = properties->channels();
            music_file_metadata_->length_in_seconds_ = properties->length();
        }
    }
}

void MusicFileMetadataExtractorCrawlWorker::persist_metadata()
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);

    music_file_metadata_->serialize(writer);
    utils::write_to_file(persistence_directory_+"/"+music_file_metadata_->file_name_+".json", sb.GetString());

};
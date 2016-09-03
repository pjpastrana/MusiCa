#include "tag_extractor_crawl_worker.hpp"

using namespace std;

TagExtractorCrawlWorker::TagExtractorCrawlWorker()
{
    audio_file_metadata_ = new AudioFileMetadata();
}

TagExtractorCrawlWorker::~TagExtractorCrawlWorker()
{
    delete audio_file_metadata_;
    audio_file_metadata_ = NULL;
}

FileMetadata* TagExtractorCrawlWorker::do_something(const path file)
{
    if(exists(file) && is_regular_file(file) && is_valid_file(file))
    {
        // only working with user/data files (i.e. not hidden or system files)
        cout << "Doing something to item " << file.string() << endl;
        extract_tags_from_file(file);
    }
    FileMetadata* file_metadata = dynamic_cast<FileMetadata*>(audio_file_metadata_);
    return file_metadata;
}

bool TagExtractorCrawlWorker::is_valid_file(const path file_path)
{
    bool is_valid = false;
    // TODO: refactor. create some sort of class or enum with the vaid types
    if(file_path.extension() == ".mp3")
        is_valid = true;
    return is_valid;
}

void TagExtractorCrawlWorker::extract_tags_from_file(const path file_path)
{
    TagLib::FileRef file(file_path.c_str());
    AudioFileMetadata audio_file_metadata;

    if(!file.isNull() && file.tag())
    {
        TagLib::Tag *tag = file.tag();
        audio_file_metadata_->file_name_ = file_path.filename().string();
        audio_file_metadata_->file_location_ = file_path.string();
        // TODO: how do I get the file size
        // audio_file_metadata.file_size_;
        audio_file_metadata_->title_ = tag->title().to8Bit();
        audio_file_metadata_->artist_ = tag->artist().to8Bit();
        audio_file_metadata_->album_ = tag->album().to8Bit();
        audio_file_metadata_->year_ = to_string(tag->year());
        audio_file_metadata_->track_ = to_string(tag->track());
        audio_file_metadata_->genre_ = tag->genre().to8Bit();

        if(file.audioProperties())
        {
            TagLib::AudioProperties *properties = file.audioProperties();

            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;

            audio_file_metadata_->bitrate_ = to_string(properties->bitrate());
            audio_file_metadata_->sample_rate_ = to_string(properties->sampleRate());
            audio_file_metadata_->channels_ = to_string(properties->channels());
            audio_file_metadata_->length_in_minutes_ = to_string(minutes);
            audio_file_metadata_->length_in_seconds_ = to_string(seconds);
        }
    }
}
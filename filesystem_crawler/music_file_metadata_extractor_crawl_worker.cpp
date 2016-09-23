#include "music_file_metadata_extractor_crawl_worker.hpp"

MusicFileMetadataExtractorCrawlWorker::MusicFileMetadataExtractorCrawlWorker(Properties* properties)
{
    music_file_metadata_ = NULL;
}

MusicFileMetadataExtractorCrawlWorker::~MusicFileMetadataExtractorCrawlWorker()
{}

shared_ptr<FileMetadata> MusicFileMetadataExtractorCrawlWorker::do_something(const path file)
{
    shared_ptr<FileMetadata> file_metadata = NULL;
    if(exists(file) && is_regular_file(file) && is_valid_file(file))
    {
        // only working with user/data files (i.e. not hidden or system files)
        cout << "MusicFileMetadataExtractorCrawlWorker Doing something to item " << file.string() << endl;
        extract_tags_from_file(file);
        file_metadata = dynamic_pointer_cast<FileMetadata>(music_file_metadata_);
    }
    return file_metadata;
}

bool MusicFileMetadataExtractorCrawlWorker::is_valid_file(const path file_path)
{
    bool is_valid = false;
    // TODO: refactor. create some sort of class or enum with the vaid types
    if(file_path.extension() == ".mp3")
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
        // TODO: how do I get the file size
        // music_file_metadata.file_size_;
        music_file_metadata_->title_ = tag->title().to8Bit();
        music_file_metadata_->artist_ = tag->artist().to8Bit();
        music_file_metadata_->album_ = tag->album().to8Bit();
        music_file_metadata_->year_ = to_string(tag->year());
        music_file_metadata_->track_ = to_string(tag->track());
        music_file_metadata_->genre_ = tag->genre().to8Bit();

        if(file.audioProperties())
        {
            TagLib::AudioProperties *properties = file.audioProperties();
            // TODO: check time, seems to be a bug
            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;

            music_file_metadata_->bitrate_ = to_string(properties->bitrate());
            music_file_metadata_->sample_rate_ = to_string(properties->sampleRate());
            music_file_metadata_->channels_ = to_string(properties->channels());
            music_file_metadata_->length_in_minutes_ = to_string(minutes);
            music_file_metadata_->length_in_seconds_ = to_string(seconds);
        }

    }
}
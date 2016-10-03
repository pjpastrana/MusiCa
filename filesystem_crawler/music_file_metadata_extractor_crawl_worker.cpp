#include "music_file_metadata_extractor_crawl_worker.hpp"

MusicFileMetadataExtractorCrawlWorker::MusicFileMetadataExtractorCrawlWorker(Properties* properties)
{
    music_file_metadata_ = NULL;
    repository_ = properties->get_string("database");
}

MusicFileMetadataExtractorCrawlWorker::~MusicFileMetadataExtractorCrawlWorker()
{}

void MusicFileMetadataExtractorCrawlWorker::do_something(const path file)
{
    if(exists(file) && is_regular_file(file) && is_valid_file(file))
    {
        // only working with user/data files (i.e. not hidden or system files)
        cout << "MusicFileMetadataExtractorCrawlWorker Doing something to item " << file.string() << endl;
        extract_tags_from_file(file);
        persist_metadata();
    }
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

void MusicFileMetadataExtractorCrawlWorker::persist_metadata()
{
    try
    {
        SQLite::Database database(repository_, SQLite::OPEN_READWRITE);
        SQLite::Transaction transaction(database);
        SQLite::Statement query(database, "INSERT INTO music_file_metadata VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
        query.bind(1, music_file_metadata_->file_name_);
        query.bind(2, music_file_metadata_->file_location_);
        query.bind(3, music_file_metadata_->title_);
        query.bind(4, music_file_metadata_->artist_);
        query.bind(5, music_file_metadata_->album_);
        query.bind(6, music_file_metadata_->year_);
        query.bind(7, music_file_metadata_->genre_);
        query.bind(8, music_file_metadata_->bitrate_);
        query.bind(9, music_file_metadata_->sample_rate_);
        query.exec();
        transaction.commit();
    }
    catch (std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
};
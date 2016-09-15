#ifndef _MUSIC_FILE_METADATA_H_
#define _MUSIC_FILE_METADATA_H_

#include <string>
#include "file_metadata.hpp"

using std::string;

class MusicFileMetadata : public FileMetadata
{
    public:
        string title_;
        string artist_;
        string album_;
        string year_;
        string track_;
        string genre_;
        string bitrate_;
        string sample_rate_;
        string channels_;
        string length_in_minutes_;
        string length_in_seconds_;

        MusicFileMetadata() {};
        ~MusicFileMetadata() {};

        template <typename Writer>
        void serialize(Writer& writer) const 
        {
            writer.StartObject();

            FileMetadata::serialize(writer);

            writer.String("title");
            writer.String(title_.c_str());

            writer.String("artist");
            writer.String(artist_.c_str());

            writer.String("album");
            writer.String(album_.c_str());

            writer.String("year");
            writer.String(year_.c_str());

            writer.String("track");
            writer.String(track_.c_str());

            writer.String("genre");
            writer.String(genre_.c_str());

            writer.String("bitrate");
            writer.String(bitrate_.c_str());

            writer.String("sample_rate");
            writer.String(sample_rate_.c_str());

            writer.String("channels");
            writer.String(channels_.c_str());

            writer.String("length_in_minutes");
            writer.String(length_in_minutes_.c_str());

            writer.String("length_in_seconds");
            writer.String(length_in_seconds_.c_str());

            writer.EndObject();
        }
};


#endif

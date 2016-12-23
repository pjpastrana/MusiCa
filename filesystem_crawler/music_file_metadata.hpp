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
        int bitrate_;
        int sample_rate_;
        int channels_;
        int length_in_seconds_;

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
            writer.Int(bitrate_);

            writer.String("sample_rate");
            writer.Int(sample_rate_);

            writer.String("channels");
            writer.Int(channels_);

            writer.String("length_in_seconds");
            writer.Int(length_in_seconds_);

            writer.EndObject();
        }
};


#endif

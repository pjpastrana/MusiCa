#ifndef _FILE_METADATA_H_
#define _FILE_METADATA_H_

#include <string>
#include <rapidjson/prettywriter.h>

using std::string;

class FileMetadata
{
    public:
        string file_name_;
        unsigned int file_size_;
        string file_location_;

        FileMetadata(){};
        // NOTE: A base class destructor's should be either public and virtual, or protected and nonvirtual
        virtual ~FileMetadata(){};

        template <typename Writer>
        void serialize(Writer& writer) const 
        {
            writer.String("file_name");
            writer.String(file_name_.c_str());
            
            writer.String("file_location");
            writer.String(file_location_.c_str());

            writer.String("file_size_in_bytes");
            writer.Uint(file_size_);
        };
};


#endif

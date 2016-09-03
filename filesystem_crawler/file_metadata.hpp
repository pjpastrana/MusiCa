#ifndef _FILE_METADATA_H_
#define _FILE_METADATA_H_

#include <string>
#include <rapidjson/prettywriter.h>

using std::string;

class FileMetadata
{
    public:
        string file_name_;
        // string file_size_;
        string file_location_;

        FileMetadata(){};
        // TODO: why? A base class destructor should be either public and virtual, or protected and nonvirtual
        virtual ~FileMetadata(){};

        template <typename Writer>
        void serialize(Writer& writer) const 
        {
            writer.String("file_name");
            writer.String(file_name_.c_str());
            
            writer.String("file_location");
            writer.String(file_location_.c_str());
        };
};


#endif

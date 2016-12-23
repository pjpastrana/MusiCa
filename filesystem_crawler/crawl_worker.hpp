#ifndef _CRAWL_WORKER_H_
#define _CRAWL_WORKER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <boost/filesystem.hpp>
#include <rapidjson/prettywriter.h>

#include "file_metadata.hpp"

using namespace std;
using boost::filesystem::path;
using rapidjson::StringBuffer;
using rapidjson::PrettyWriter;

// abstract class
class CrawlWorker 
{
    protected:
        string persistence_directory_;
        
    public:
        virtual ~CrawlWorker(){};
        virtual void do_something (const path file) = 0;
        virtual bool is_valid_file(const path file) = 0;
        virtual void persist_metadata(){};
};

#endif
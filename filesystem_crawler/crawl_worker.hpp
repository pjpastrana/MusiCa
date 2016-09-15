#ifndef _CRAWL_WORKER_H_
#define _CRAWL_WORKER_H_

#include <string>
#include <boost/filesystem.hpp>

#include "file_metadata.hpp"

using boost::filesystem::path;

// abstract class
class CrawlWorker 
{
    public:
        virtual ~CrawlWorker(){};
        virtual FileMetadata* do_something (const path file) = 0;
        virtual bool is_valid_file(const path file) = 0;
};

#endif
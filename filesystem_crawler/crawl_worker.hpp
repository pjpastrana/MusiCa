#ifndef _CRAWL_WORKER_H_
#define _CRAWL_WORKER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <boost/filesystem.hpp>

#include "file_metadata.hpp"
#include "storage_manager.hpp"

using namespace std;
using boost::filesystem::path;

// abstract class
class CrawlWorker 
{
    protected: 
        string repository_;

    public:
        virtual ~CrawlWorker(){};
        virtual void do_something (const path file) = 0;
        virtual bool is_valid_file(const path file) = 0;
        virtual void persist_metadata(){};
};

#endif
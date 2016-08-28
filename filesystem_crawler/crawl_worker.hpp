#ifndef _CRAWLWORKER_H_
#define _CRAWLWORKER_H_

#include <string>
#include <boost/filesystem.hpp>

using boost::filesystem::path;

// abstract class
class CrawlWorker 
{
    public:
        virtual ~CrawlWorker(){};
        virtual void do_something (const path item_path) = 0;
};

#endif
#ifndef _CRAWLWORKER_H_
#define _CRAWLWORKER_H_

#include <string>

// abstract class
class CrawlWorker 
{
    public:
        virtual ~CrawlWorker(){};
        virtual void do_something (std::string item) = 0;
};

#endif
#include "tag_extractor_crawl_worker.hpp"

TagExtractorCrawlWorker::TagExtractorCrawlWorker()
{}

TagExtractorCrawlWorker::~TagExtractorCrawlWorker()
{}

void TagExtractorCrawlWorker::do_something(const path file)
{
    if(exists(file))
    {
        if (is_regular_file(file))
        {
            // only working with user/data files (i.e. not hidden or system files)
            std::cout << "Doing something to item " << file.filename().string() << std::endl;
        }
    }

}
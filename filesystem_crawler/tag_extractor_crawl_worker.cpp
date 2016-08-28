#include "tag_extractor_crawl_worker.hpp"

TagExtractorCrawlWorker::TagExtractorCrawlWorker()
{}

TagExtractorCrawlWorker::~TagExtractorCrawlWorker()
{}

void TagExtractorCrawlWorker::do_something(const path item_path)
{
    std::cout << "Doing something to item " << item_path.filename().string() << std::endl;
}
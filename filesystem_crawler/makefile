PROJECT_NAME = filesystem-crawler
CC = g++
CFLAGS = -c -Wall -g -std=c++11
INCLUDES = -I/opt/local/include -I/opt/local/include/taglib -I$(HOME)/usr/include
LIBPATH = -L/opt/local/lib
LIBS = -lboost_filesystem-mt -lboost_system-mt -ltag


all: $(PROJECT_NAME)

$(PROJECT_NAME):  main.o filesystem_crawler.o tag_extractor_crawl_worker.o
	$(CC) main.o filesystem_crawler.o tag_extractor_crawl_worker.o -o $(PROJECT_NAME) $(LIBPATH) $(LIBS)
    
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) main.cpp filesystem_crawler.hpp

filesystem_crawler.o: tag_extractor_crawl_worker.hpp filesystem_crawler.cpp filesystem_crawler.hpp file_metadata.hpp audio_file_metadata.hpp
	$(CC) $(CFLAGS) $(INCLUDES) filesystem_crawler.cpp filesystem_crawler.hpp tag_extractor_crawl_worker.hpp file_metadata.hpp audio_file_metadata.hpp

tag_extractor_crawl_worker.o: crawl_worker.hpp tag_extractor_crawl_worker.hpp tag_extractor_crawl_worker.cpp
	$(CC) $(CFLAGS) $(INCLUDES) crawl_worker.hpp tag_extractor_crawl_worker.cpp tag_extractor_crawl_worker.hpp

clean:
	rm -rf *.o $(PROJECT_NAME) *.gch* *~ *.dSYM
	#clear

run:
	./$(PROJECT_NAME)

memleak:
	valgrind -v --leak-check=full ./$(PROJECT_NAME)
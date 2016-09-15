PROJECT_NAME = filesystem-crawler
CC = g++
CFLAGS = -c -Wall -g -std=c++11
INCLUDES = -I/opt/local/include -I/opt/local/include/taglib -I$(HOME)/usr/include
LIBPATH = -L/opt/local/lib
LIBS = -lboost_filesystem-mt -lboost_system-mt -ltag
SRC_DIR = ../


all: $(PROJECT_NAME)

$(PROJECT_NAME):  main.o filesystem_crawler.o music_file_metadata_extractor_crawl_worker.o
	$(CC) main.o filesystem_crawler.o music_file_metadata_extractor_crawl_worker.o -o $(PROJECT_NAME) $(LIBPATH) $(LIBS)
    
main.o: $(SRC_DIR)main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)main.cpp

filesystem_crawler.o: $(SRC_DIR)filesystem_crawler.cpp 
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)filesystem_crawler.cpp 

music_file_metadata_extractor_crawl_worker.o: $(SRC_DIR)music_file_metadata_extractor_crawl_worker.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)music_file_metadata_extractor_crawl_worker.cpp

clean:
	rm -rf *.o $(PROJECT_NAME) *.gch* *~ *.dSYM
	#clear

run:
	./$(PROJECT_NAME) /Users/kingsman/Music/MundoNuevoRecordings

memleak:
	valgrind -v --leak-check=full ./$(PROJECT_NAME)
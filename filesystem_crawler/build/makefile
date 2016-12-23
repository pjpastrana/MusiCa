PROJECT_NAME = filesystem-crawler
CC = g++
CFLAGS = -static -c -Wall -g -std=c++11
INCLUDES = -I/opt/local/include -isystem /opt/local/include/taglib -I$(HOME)/usr/include
LIBPATH = -L/opt/local/lib -L$(HOME)/usr/lib
LIBS = -lboost_filesystem-mt -lboost_system-mt -ltag -lfftw3 -lm -lsndfile  -lopencv_core -lopencv_highgui -lopencv_imgcodecs
SRC_DIR = ../

all: $(PROJECT_NAME)

$(PROJECT_NAME):  main.o filesystem_crawler.o music_file_metadata_extractor_crawl_worker.o audio_reader_crawl_worker.o properties.o crawl_worker_factory.o fft_processor.o
	$(CC) main.o filesystem_crawler.o music_file_metadata_extractor_crawl_worker.o audio_reader_crawl_worker.o properties.o crawl_worker_factory.o fft_processor.o -o $(PROJECT_NAME) $(LIBPATH) $(LIBS)

main.o: $(SRC_DIR)main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)main.cpp

filesystem_crawler.o: $(SRC_DIR)filesystem_crawler.cpp 
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)filesystem_crawler.cpp 

music_file_metadata_extractor_crawl_worker.o: $(SRC_DIR)music_file_metadata_extractor_crawl_worker.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)music_file_metadata_extractor_crawl_worker.cpp

audio_reader_crawl_worker.o: $(SRC_DIR)audio_reader_crawl_worker.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)audio_reader_crawl_worker.cpp

properties.o: $(SRC_DIR)properties.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)properties.cpp

crawl_worker_factory.o: $(SRC_DIR)crawl_worker_factory.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)crawl_worker_factory.cpp

fft_processor.o: $(SRC_DIR)fft_processor.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC_DIR)fft_processor.cpp

clean:
	rm -rf *.o $(PROJECT_NAME) *.gch* *~ *.dSYM
	#clear

run:
	./$(PROJECT_NAME) properties.json

check:
	valgrind -v --track-origins=yes --leak-check=full ./$(PROJECT_NAME) properties.json
CFLAGS=-g -Wall -lm -ggdb

all: interface/deduper

interface/deduper: interface/interface.o model_runner/model_runner.o deduplicator/deduplicator.o model_input_generator/model_input_generator.o file_allocation/file_allocation.o file_similarity/file_similarity.o file_popularity/file_popularity.o deduplication_model/deduplication_model.o random/random.o

clean:
	rm -f interface/interface.o
	rm -f model_runner/model_runner.o
	rm -f deduplicator/deduplicator.o
	rm -f model_input_generator/model_input_generator.o
	rm -f file_allocation/file_allocation.o
	rm -f file_similarity/file_similarity.o
	rm -f file_popularity/file_popularity.o
	rm -f deduplication_model/deduplication_model.o
	rm -f random/random.o

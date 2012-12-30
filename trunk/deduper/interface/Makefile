CFLAGS=-g -Wall -lm

all: deduper

deduper: interface.o ../model_runner/model_runner.o ../model_input_generator/model_input_generator.o ../deduplication_model/deduplication_model.o ../file_similarity/file_similarity.o ../file_popularity/file_popularity.o ../file_allocation/file_allocation.o ../deduplicator/deduplicator.o 

clean:
	rm -f interface.o

run:
	./deduper

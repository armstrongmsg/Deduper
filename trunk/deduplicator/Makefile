CFLAGS=-g -Wall

all: deduplicator_test

deduplicator_test: deduplicator.o ../file_allocation/file_allocation.o ../file_similarity/file_similarity.o 

clean:
	rm -f deduplicator_test

run:
	./deduplicator_test

CFLAGS=-g -Wall -lm

all: deduplication_model_test

deduplication_model_test: ../file_allocation/file_allocation.o ../file_similarity/file_similarity.o ../file_popularity/file_popularity.o deduplication_model.o

clean:
	rm -f deduplication_model_test

run:
	./deduplication_model_test	

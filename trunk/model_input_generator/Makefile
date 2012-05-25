CFLAGS=-g -Wall -lm

all: model_input_generator_test

model_input_generator_test: ../file_allocation/file_allocation.o  ../file_popularity/file_popularity.o model_input_generator.o ../file_similarity/file_similarity.o ../matrixes/matrixes.o

clean:
	rm -f model_input_generator_test

run:
	./model_input_generator_test

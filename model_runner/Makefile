CFLAGS=-g -Wall -lm

all: model_runner_test

model_runner_test: ../model_input_generator/model_input_generator.o ../file_similarity/file_similarity.o ../file_popularity/file_popularity.o ../file_allocation/file_allocation.o ../deduplicator/deduplicator.o ../random/random.o model_runner.o ../deduplication_model/deduplication_model.o ../timer/timer.o

clean:
	rm -f model_runner_test

run:
	./model_runner_test

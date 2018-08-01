CC=gcc
BIN=./bin
CFLAGS=-Wall -Werror -g -lm -lpthread

PROG=glob philo buf peluquero ph sem_open sem_wait sem_post sem_unlink

LIST=$(addprefix $(BIN)/, $(PROG))

.PHONY: all
all: $(LIST)

$(BIN)/%: %.c
	$(CC) -o $@ $< $(CFLAGS)

%: %.c
	$(CC) -o $(BIN)/$@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BIN)/sem_* $(BIN)/philo $(BIN)/ph $(BIN)/buf $(BIN)/peluquero

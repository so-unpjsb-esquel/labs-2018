CC=gcc
BIN=./bin
CFLAGS=-Wall -Werror -g -lrt

PROG=ej3 ej4 
SHM_EJ=shm_create shm_read shm_unlink shm_write
MQ_EJ=mq_open mq_getattr mq_send mq_receive mq_unlink

LIST=$(addprefix $(BIN)/, $(PROG))

.PHONY: all
all: $(LIST) shm mq

.PHONY: shm
shm: $(addprefix $(BIN)/, $(SHM_EJ))

.PHONY: mq
mq: $(addprefix $(BIN)/, $(MQ_EJ))

$(BIN)/%: %.c
	$(CC) -o $@ $< $(CFLAGS)

%: %.c
	$(CC) -o $(BIN)/$@ $< $(CFLAGS)

html: README.md
	pandoc README.md -f markdown_github -t html -s -o README.html

pdf: README.md
	pandoc README.md -f markdown_github -s -o README.pdf

.PHONY: clean
clean:
	rm -f $(BIN)/ej* $(BIN)/shm_* $(BIN)/mq_*


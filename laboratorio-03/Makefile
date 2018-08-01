CC=gcc
BIN=./bin
CFLAGS=-Wall -g -lpthread

PROG=ej1 ej2 ej3 ej4 sh fork_vs_thread

LIST=$(addprefix $(BIN)/, $(PROG))

.PHONY: all
all: $(LIST)

$(BIN)/%: %.c
	$(CC) -o $@ $< $(CFLAGS)

%: %.c
	$(CC) -o $(BIN)/$@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BIN)/ej* $(BIN)/sh $(BIN)/fork_vs_thread

CC=gcc
BIN=./bin
CFLAGS=-Wall -Werror -g -lm -lpthread

PROG=ej1 ej3 

LIST=$(addprefix $(BIN)/, $(PROG))

.PHONY: all
all: $(LIST)

$(BIN)/%: %.c
	$(CC) -o $@ $< $(CFLAGS)

%: %.c
	$(CC) -o $(BIN)/$@ $< $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(BIN)/ej*


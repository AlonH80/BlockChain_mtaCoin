CFLAGS=-Wall -pthread -lz
LDFLAGS=-lm
CC=gcc -std=c99
ECHO=echo "going to compile for target $@"
SRCDIR=src
MAIN_FILE=server
PROG=$(MAIN_FILE)
PROG_OBJS=bitcoin.o miner.o dummy_miner.o server.o utility.o linked_list.o

$(PROG): $(PROG_OBJS)
	@$(ECHO)
	$(CC) -o $(PROG) $(CFLAGS) $^

%.o: $(SRCDIR)/%.c
	@$(ECHO)
	$(CC) -c $(CFLAGS) $<

test:
	@echo going to run test...
	sudo ./$(PROG)

clean:
	rm -vf $(PROG)

clean_all: clean
	rm -vf *.o *.gch


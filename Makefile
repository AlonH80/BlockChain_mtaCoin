CFLAGS=-Wall
LDFLAGS=-lm
CC=gcc -std=c99
ECHO=echo "going to compile for target $@"

MAIN_FILE=server
PROG=$(MAIN_FILE)

all:$(PROG) test

$(PROG): %.o
	@$(ECHO)
	$(CC) -o $(PROG) $(CFLAGS) $<

%.o: src/%.c
	@$(ECHO)
	$(CC) $(CFLAGS) -c $<

test:
	@echo going to run test...
	sudo ./$(PROG)

clean:
	rm -vf $(PROG)

clean_all: clean
    rm -vf *.o *.gch


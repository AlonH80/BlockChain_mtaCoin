CFLAGS=-Wall -std=gnu11
LDFLAGS=-lm
CC=gcc -std=c99 -g
ECHO=echo "going to compile for target $@"

MAIN_FILE=ex3_q1
PROG=$(MAIN_FILE)

all:$(PROG) test

$(PROG): $(PROG_OBJS) %.o
	@$(ECHO)
	$(CC) -o $(PROG) $(CFLAGS) $(PROG_OBJS)

%.o: %.c
	@$(ECHO)
	$(CC) $(CFLAGS) -c $<

test:
	@echo going to run test...
	./ex3_q1 abc xyz out.log < in.txt 2> err.log

clean:
	rm -vf *.o *.gch subst $(PROG) *.log *.tmp

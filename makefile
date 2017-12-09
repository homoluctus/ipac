CC=gcc
SRCS=ipv4.c main.c
OBJS=$(SRCS:.c=.o)
CFLAGS=-Wall -std=c11 -lm -g

all: main $(SRCS) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) -c $^

main: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean: main $(OBJS)
	rm -i $^

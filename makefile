CC=gcc
SRCS=ipv4.c main.c
OBJS=$(SRCS:.c=.o)
CFLAGS=-Wall -std=c11 -lm -g

all: ipac $(SRCS) $(OBJS)

$(OBJS): $(SRCS)
	$(CC) -c $^

ipac: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean: ipac $(OBJS)
	rm -i $^

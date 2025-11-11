CC = gcc
CFLAGS = -Wall -O2

SRCS = $(wildcard *.c)
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS) *.o a.out


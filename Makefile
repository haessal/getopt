CC = gcc
CFLAGS = -g -Wall
OBJS = getopt.o
TARGETS = getopt


.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGETS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $<

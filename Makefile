CC=gcc
OPTIONS=-g -std=gnu23 -I include/
LIB=-lpthread -levent -levent_pthreads
TARGET=mdus

SRCS = src/main.c src/server.c src/options.c src/util.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LIB) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(LIB) $(OPTIONS) -c $< -o $@

clean:
	rm src/*.o

CC=gcc
CFLAGS=-Wall -Wextra -std=c17 -g $(shell pkg-config --cflags sdl3)
LDFLAGS=$(shell pkg-config --libs sdl3)

TARGET=sdl3-hello
SRC=Hello.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

debug: all
	gdb ./$(TARGET)

clean:
	rm -f $(TARGET)
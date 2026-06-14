CC=gcc

CFLAGS=-Wall -Wextra -std=c17 \
-Iinclude \
$(shell pkg-config --cflags sdl3)

LDFLAGS=$(shell pkg-config --libs sdl3)

SRC=src/main.c src/game.c src/paddle.c src/ball.c src/collision.c

TARGET=pong

all:
	$(CC) $(CFLAGS) $(SRC) \
	-o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
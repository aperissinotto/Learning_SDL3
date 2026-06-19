CC=gcc

CFLAGS=-Wall -Wextra -std=c17 \
-Iinclude \
$(shell pkg-config --cflags sdl3 sdl3-ttf)

LDFLAGS=$(shell pkg-config --libs sdl3 sdl3-ttf) \
-lm

SRC=src/main.c src/experiment.c src/world.c src/ball.c src/collision.c src/text.c

TARGET=physics

all:
	$(CC) $(CFLAGS) $(SRC) \
	-o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
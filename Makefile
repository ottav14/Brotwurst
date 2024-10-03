TARGET = program

SRC = src/main.c src/draw.c

CC = gcc

CFLAGS = -Iinclude -Wall -Wextra -O2 -lSDL2 -lm

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) 

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)


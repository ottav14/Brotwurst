TARGET = Beerbrot

SRC = src/main.c src/graphics.c src/util.c

CC = gcc

CFLAGS = -Iinclude -Wall -Wextra -fsanitize=address -lglfw -lm -lGL -lGLEW

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) 

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)


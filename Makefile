CC = gcc
CFLAGS = -Wall -g
LIBS = -lraylib -lm
TARGET = BrickC
SRCS = main.c game.c score.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)
CC = clang
CFLAGS = -Wall -Wextra -g
TARGET = xsh.out
SRC = main.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

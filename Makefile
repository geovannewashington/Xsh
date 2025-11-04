# .PHONY says that targets do not produce a file
.PHONY: all clean

CFLAGS = -Wall -Wextra -g -O0
SRCS = main.c shell/builtin.c shell/config.c shell/executor.c shell/parser.c
OBJS = $(SRCS:.c=.o)

all: xsh.out

xsh.out: $(OBJS)
	$(CC) -o xsh.out $(OBJS) $(CFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJS) xsh.out

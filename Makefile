# .PHONY says that targets do not produce a file
.PHONY: all clean

CFLAGS = -Wall -Wextra -g -O0
SRCS = main.c builtin.c config.c executor.c parser.c
OBJS = $(SRCS:.c=.o)

xsh.out: $(OBJS)
	.c.o:
	$(CC) -o xsh.out $(OBJS) $(CFLAGS) -c $< $@

clean:
	rm -f $(OBJS) $(TARGET)

CC = gcc
CFLAGS = -Wall -Wextra

SRCS =  option_s.c avl_s.c valeurs_s.c
OBJS = $(SRCS:.c=.o)
EXEC = exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

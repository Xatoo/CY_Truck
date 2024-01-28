CC = gcc
CFLAGS = -Wall -Wextra 

SRCS =  option_t.c arbre_t.c 
OBJS = $(SRCS:.c=.o)
EXEC = exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)

CC=gcc-8
LFLAGS = -lncurses

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
MAIN = maze

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
.c.o:
	$(CC) $(CCFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm -f $(MAIN) $(OBJS)

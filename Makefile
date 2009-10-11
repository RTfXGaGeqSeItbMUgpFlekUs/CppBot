BIN = bot
SRCS= main.cpp bot.cpp
OBJS= $(SRCS:.c=.o)

CC= g++
CCFLAGS= -g -Wall -Iinclude -O0 -pipe
LD= g++
LDFLAGS= -g $(LIBS)

all: $(BIN)

.c.o:
	$(CC) $(CCFLAGS) $(LIBS) -o $@ -c $<

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

clean:
	-rm -f *.o $(BIN)

.PHONY: all clean

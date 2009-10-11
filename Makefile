BIN = bot
SRCS= main.cpp bot.cpp network_utils.cpp socket.cpp string_utils.cpp
OBJS= $(SRCS:.cpp=.o)

CC= g++
CCFLAGS= -g -Wall -I. -O0 -pipe
LD= g++
LDFLAGS= -g $(LIBS)

all: $(BIN)

%.o: %.cpp
	$(CC) $(CCFLAGS) $(LIBS) -o $@ -c $<

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

clean:
	-rm -f *.o $(BIN)

.PHONY: all clean

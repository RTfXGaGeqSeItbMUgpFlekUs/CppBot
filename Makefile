BIN = bot
SRCS= main.cpp bot.cpp network_utils.cpp socket.cpp string_utils.cpp irc_socket.cpp
OBJS= $(SRCS:.cpp=.o)

TEST_SRCS= sockettest.cpp network_utils.cpp socket.cpp string_utils.cpp irc_socket.cpp
TEST_OBJS= $(TEST_SRCS:.cpp=.o)

CC= g++
CCFLAGS= -g -Wall -I. -O0 -pipe
LD= g++
LDFLAGS= -g $(LIBS)

all: $(BIN) test

%.o: %.cpp
	$(CC) $(CCFLAGS) $(LIBS) -o $@ -c $<

$(BIN): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

test: $(TEST_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(TEST_OBJS)

dist:
	-rm cppbot.tar.bz2
	(cd ..; tar cjf cppbot.tar.bz2 cppbot; mv cppbot.tar.bz2 cppbot/)

clean:
	-rm -f *.o $(BIN)

dist-clean: clean
	-rm cppbot.tar.bz2

.PHONY: all dist clean

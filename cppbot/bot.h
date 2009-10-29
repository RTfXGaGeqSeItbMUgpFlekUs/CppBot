#ifndef BOT_H
#define BOT_H

#include <string>
#include "irc_socket.h"
#include "network_utils.h"

class CBot {
public:
	int InitConnection(char const *nick, char const *server,
		char const *port);
	int Raw(std::string str);
	int Privmsg(std::string who, std::string what);
	int Notice(std::string who, std::string what);
	int Join(std::string channel);
	int Part(std::string channel, std::string message);
	int Quit(std::string message);
private:
	char *m_nick;
	char *m_server;
	char *m_port;
	//int m_socket;
	Network::IrcSocket m_socket;
};

#endif

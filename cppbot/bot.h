#ifndef BOT_H
#define BOT_H

class CBot {
public:
	int InitConnection(char const *nick, char const *server,
		char const *port);
private:
	char *m_nick;
	char *m_server;
	char *m_port;
	int m_socket;
};

#endif

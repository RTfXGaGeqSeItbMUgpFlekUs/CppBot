#include "bot.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int CBot::InitConnection(char const *nick, char const *server,
		char const *port)
{
	struct addrinfo hints = {0};
	struct addrinfo *res;

	m_nick = new char[strlen(nick)+1];
	strcpy(m_nick, nick);

	m_server = new char[strlen(server)+1];
	strcpy(m_server, server);

	m_port = new char[strlen(port)+1];
	strcpy(m_port, port);

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	res = new struct addrinfo;
	if (getaddrinfo(server, port, &hints, &res) != 0) {
		fprintf(stderr, "Error %u", errno);
	}

	m_socket = socket(res->ai_family, res->ai_socktype,
		res->ai_protocol);

	delete res;

	return 0;
}

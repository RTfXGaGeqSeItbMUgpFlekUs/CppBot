#include "bot.h"
#include "irc_socket.h"
#include "network_utils.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <string>

int CBot::InitConnection(char const *nick, char const *server,
		char const *port)
{
	Network::IrcSocket m_socket;
	std::string bit_ip;
	Network::get_host_by_name("irc.eighthbit.net", bit_ip);

	m_socket.connect(bit_ip, 6667);
	m_socket.send("NICK " "CBot" "\r\nUSER " "CBot" " - - :" "CBot"
		"\r\nJOIN #bots\r\n");

	while (1)
		;
	return 0;
}

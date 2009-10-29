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

#include <iostream>
#include <sstream>

int CBot::InitConnection(char const *nick, char const *server,
		char const *port)
{
	std::string bit_ip;
	Network::get_host_by_name("irc.eighthbit.net", bit_ip);

	m_socket.connect(bit_ip, 6667);
	std::stringstream ss;
	ss << "NICK " << nick << "\r\nUSER " << nick << " 0 0 :" << nick << "\r\n";
	Raw(ss.str());

	while (1)
		;
	return 0;
}

int CBot::Raw(std::string str)
{
	if ( m_server != "" ) {
		std::cout << str;
		m_socket.send(str);
	} else {
		std::cout << "No socket!" << std::endl;
		return 1;
	}
	return 0;
}

int CBot::Privmsg(std::string who, std::string what)
{
	Raw( (std::string)"PRIVMSG " + who + (std::string)" :" + what );
	return 0;
}

int CBot::Notice(std::string who, std::string what)
{
	Raw( (std::string)"NOTICE " + who + (std::string)" :" + what );
	return 0;
}

int CBot::Join(std::string channel)
{
	Raw( (std::string)"JOIN " + channel);
	return 0;
}

int CBot::Part(std::string channel, std::string message = "Leaving...")
{
	Raw( (std::string)"PART " + channel + (std::string)" :" + message);
	return 0;
}

int CBot::Quit(std::string message = "CBot::Quit() called with no args")
{
	Raw( (std::string)"Quit :" + message);
	return 0;
}

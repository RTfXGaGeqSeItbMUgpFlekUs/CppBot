/*
Copyright (c) 2009 James Spahlinger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include "irc_socket.h"

#ifdef WIN32
	#include <winsock.h>
	typedef char raw_data;
	typedef int socklen_t;
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <fcntl.h>
	#include <string.h>
	typedef void raw_data;
#endif
#include <errno.h>
#include <cassert>

Network::IrcSocket::IrcSocket(int const socket_id) : Socket(socket_id) {
	recv_buffer.erase();
}
Network::IrcSocket::IrcSocket(void) : Socket() {
	recv_buffer.erase();
}

int Network::IrcSocket::recv(std::string &data) {
	//lets check the recv buffer, if we can return something
	//from there, do so, otherwise try looking to recv something
	size_t newline_loc = recv_buffer.find("\r\n");
	if (std::string::npos == newline_loc) { //try looking at the sock
		std::string buffer = "";
		int size = Socket::recv(buffer);
		if(0 >= size) { return -1; }
		recv_buffer += buffer;

		//see if recv buffer has a new line now.
		newline_loc = recv_buffer.find("\r\n");
	}
	
	//new if we have a new line...
	if(std::string::npos != newline_loc) {
		data = recv_buffer.substr(0,newline_loc);
		recv_buffer.erase(0,newline_loc + 2);
		return 0;
	} else { data = ""; return 1; }
	
}

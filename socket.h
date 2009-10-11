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

#ifndef SOCKET_H
#define SOCKET_H

#include <string>

#ifdef WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
namespace Network {
class Socket {
public:
	//This class is meant to be inherited.
	Socket(int const socket_id);
	Socket(void);
public:
	~Socket(void);
	
	//bind to a port. Returns any error messages it may get.
	int bind(unsigned short port);
	Socket *accept(void);
	int connect(const std::string url,const unsigned short port);
	//we are goign to make a promise that all given data will be sent.
	int send(const std::string data);

	int recv(std::string &data); //data will be changed.
	int listen(const int backlog);
	int close(void);
	//does not fully close the socket, only removes one or both
	//ways of communicating through it.
	int shutdown(const int how);
	
	//This is different on windows of course :<
	void set_nonblocking(void);

	//getter and setter functions:
	int get_socketid(void);
	unsigned short get_local_port(void);
	unsigned short get_remote_port(void);
	std::string get_url(void);

	unsigned short get_peer_port(void) { return ntohs(peeraddr.sin_port); }
	std::string get_peer_address(void) { return inet_ntoa(peeraddr.sin_addr); }
private:
	void initialize_winsock(void);
	sockaddr_in create_address(unsigned short port,
	                           std::string addr = "");
	Socket(const Socket &sock);
	void operator=(const Socket &sock);


private:
	int socket_id; //socket file descriptor.
	unsigned short local_port; //port on local computer
	unsigned short remote_port; //port on remote computer.
	int max_buffer_size;
	struct sockaddr_in peeraddr;
};
}

#endif


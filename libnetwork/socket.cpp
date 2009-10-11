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

#include "socket.h"

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
#include <iostream>

#include <cstdio>

#define MAX_BUFFER_SIZE 512
using namespace Network;

#ifdef WIN32
//We are only supposed to start winsock one time.
static bool is_winsock_started = false;
#endif
void Socket::initialize_winsock(void) {
#ifdef WIN32
	if(false == is_winsock_started) {
		WORD wVR;
		WSADATA wsaData;
		wVR = MAKEWORD(2,0);
		if(WSAStartup(wVR,&wsaData) != 0) {
		exit(666);
		}
		is_winsock_started = true;
	}
#endif


}
Socket::Socket(void) : max_buffer_size(MAX_BUFFER_SIZE) {
	//initialize winsock
	initialize_winsock();

	// SOCK_STREAM: We don't care about datagram sockets.
	// 0: according to beej, this will work.
	socket_id = socket(AF_INET,SOCK_STREAM,0);
    socklen_t len = sizeof peeraddr;
	getpeername(this->socket_id, (sockaddr*)&peeraddr, &len);
	if(0 > socket_id) {
		//we should actually deal with errors, but at this point
		//if we can't make a socket, just blow up.
		assert(0);
	}
}
Socket::Socket(int const socket_ida) : max_buffer_size(MAX_BUFFER_SIZE) {
	//We don't actually have to make a socket, as we presume that a socket
	//has already been made.
	this->socket_id = socket_ida;
	//We actually have to run getpeername to find out who we are connected to
	socklen_t len = sizeof peeraddr;
	getpeername(this->socket_id, (sockaddr*)&peeraddr, &len);

}
Socket::~Socket(void) {
	close();
}

int Network::Socket::bind(unsigned short port) {
	//We can't bind using a socket that is not open.
	assert(-1 != socket_id);

	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	memset(my_addr.sin_zero, '\0', sizeof my_addr.sin_zero);
#ifdef WIN32
	char yes = '1';
#else
	int yes = 1;
#endif
	if (setsockopt(socket_id,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
	perror("setsockopt bind failed");
		assert(0);
	} 
	int result = ::bind(socket_id, (struct sockaddr *)&my_addr, sizeof my_addr);
	if(0 > result) { //error
		return -1;//TODO
	} else {
		local_port = port;
		return 0;
	}
}

sockaddr_in Network::Socket::create_address( unsigned short port,
                                             std::string addr) {
	sockaddr_in ad;
	ad.sin_family = AF_INET;
	ad.sin_port = htons(port);
	if( "" == addr) { //assume localhost
		ad.sin_addr.s_addr = htonl(INADDR_ANY);
	} else { //do as requested
		ad.sin_addr.s_addr = inet_addr(addr.c_str());
	}
	memset(ad.sin_zero, '\0', sizeof ad.sin_zero);

	return ad;
}
int Network::Socket::connect(const std::string address,
                             const unsigned short port) {
	struct sockaddr_in dest_addr = create_address(port,address);

	int result = ::connect (socket_id,(struct sockaddr *)&dest_addr, sizeof dest_addr);
	if(0 <= result) { //no error
		remote_port = port;
		peeraddr = dest_addr;
		return 0;
	} else { //errors
		std::cerr << "result is: " << result << std::endl <<
		          "port: " << port << " " << "address: " <<
		          address << std::endl;
		//		assert(0); //TODO
		return -1;
	}
}
int Network::Socket::listen(const int backlog) {
	//check that we have a working socket, otherwise this is an
	//obvious implentation.
	assert(-1 != socket_id);
	int result = ::listen(socket_id,backlog);
	if(0 <= result) {
		return 0;
	} else {
		assert(0);
	}
}
int Network::Socket::close(void) {

#ifdef WIN32
	::closesocket(socket_id);
#else
	::close(socket_id);
#endif
	socket_id = -1;
	return 0;
}

int Network::Socket::send(const std::string data) {
	//we have to have a working socket...
	assert(-1 != socket_id);
	int data_length = data.length();
	std::string buffer = data;
	while (0 < data_length) { 
	//as long as we have stuff to send:
		int sent = ::send(socket_id, buffer.c_str(), data_length, 0);
		data_length -= sent;
		if (0 == sent) { //no data left to send
			return 0;
		} else if (0 < sent) { //still data left... bad
			buffer = buffer.substr(sent - 1); //substr is 0 based.
		} else { // error, check errno
			std::cerr << "data_length is: " << data_length 
			          << std::endl;
			std::cerr << "sent: " << sent << std::endl;
			std::cerr << "trying to send: " <<
			          data << std::endl;
			perror("sent");
			assert(0); //TODO
		}
	}

	return 0;
}

int Network::Socket::recv(std::string &data) {
	assert(-1 != socket_id);
	char *buffer = new char[max_buffer_size];
	memset (buffer, 0, max_buffer_size);
	int result = ::recv(socket_id, buffer, max_buffer_size -1, 0);

	data = buffer;
	delete[] buffer;
	return result;
}

Socket *Network::Socket::accept(void) {
	int newSocket = ::accept(socket_id, NULL, 0);
	if(0 <= newSocket) {
		return new Socket(newSocket); 
	} else {
		assert(0);
	}
}
void Network::Socket::set_nonblocking(void) {
	assert(-1 != socket_id);
#ifdef WIN32
	unsigned long mode = 0;
	ioctlsocket (socket_id, FIONBIO, &mode);
#else
	fcntl(socket_id, F_SETFL, O_NONBLOCK);
#endif
}

int Network::Socket::get_socketid(void) {
	return socket_id;
}

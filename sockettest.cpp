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
#include <iostream>
#include <string>

#include "socket.h"
#include "network_utils.h"

using namespace Network;
using namespace std;
int main() {
//Lets see how hard it is to connect to eighthbit as a test of sockets...
	cout << "Starting test of socket client functions..." << endl;
	Socket *sock = new Socket;
	
	//we have a socket, lets try to resolve eighthbit.
	string bit_ip = "";
	//using ares, because its pings make sense and are easy to 
	//duplicate using this primitive test.
	get_host_by_name("irc.eighthbit.net",bit_ip);

	cout << "IP of irc.eighthbit.net is: " << bit_ip << endl;
	
	//now attempt to connect to eightbit:
	sock->connect(bit_ip,6667);
	
	sock->send("NICK testtest\r\nUSER foo foo foo :foo\r\nJOIN #bots\r\n");

	string data = "";
	string olddata = "";
	size_t loc = string::npos;
	while(1){
		sock->recv(data);
		data = olddata + data;
		while(1) {
		loc = data.find("\r\n");
		if(loc != string::npos) {
			string line = data.substr(0,loc);
			data = data.substr(loc+2);
			cout << line << endl;
		if(line.find("asdf") != string::npos) {
			sock->send("PRIVMSG #bots :you called?\r\n");
		}
		} else { olddata = data; break;}
		olddata = "";
		}
	}
	delete sock;
}

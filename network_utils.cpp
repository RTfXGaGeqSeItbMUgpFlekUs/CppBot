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

#include <network_utils.h>
#ifdef WIN32
	#include <winsock.h>

	//to make linker errors go away:
	#pragma comment(lib, "winmm.lib")
	#pragma comment(lib, "wsock32.lib")
	#pragma comment(lib, "advapi32.lib")
#else
	#include <netdb.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif
int Network::get_host_by_name(const std::string name, std::string &address) {
	struct hostent *host;
	host = gethostbyname(name.c_str());

	if(NULL == host) { //we have a problem
		return 1;
	}
	//get the address we care about.
	address = inet_ntoa(*((struct in_addr *)host->h_addr));
	return 0;

}

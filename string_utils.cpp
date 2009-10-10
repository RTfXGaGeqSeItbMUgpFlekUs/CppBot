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

#include "string_utils.h"

namespace Utils {

/* This function derived from 
 * http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html#ss7.3
 * License at:
 * http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-22.html
 */
std::vector<std::string> tokenize(const std::string &str,
                                  const std::string delimiter) {
	std::vector<std::string> args;
	std::string::size_type last_pos = str.find_first_not_of(delimiter, 0);
	std::string::size_type pos     = str.find_first_of(delimiter, last_pos);

	while(std::string::npos != pos || std::string::npos != last_pos) {
		args.push_back(str.substr(last_pos, pos - last_pos));
		//skip delimeter
		last_pos = str.find_first_not_of(delimiter, pos);
		//find next non-delimeter.
		pos = str.find_first_of(delimiter, last_pos);
	}
	return args;
}
}


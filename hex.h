#ifndef hex_h
#define hex_h

#include <string>
#include <bitset>

namespace HEX {
	constexpr char map[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	std::string toString(std::string s) {
		std::string result = "";
		for(auto i = 0; i < s.length(); i += 2) {
			std::string byte = s.substr(i,2);
	    	char ch = (char)(int)strtol(byte.c_str(), nullptr, 16);
	    	result.push_back(ch);
		}
		return result;
	}

	std::string toHex(std::string in) {
	    std::string input = in;
		std::string output = "";
		for(int i = 0; i < input.length(); i += 4)
	        output += map[std::stoi(input.substr(i,4), nullptr, 2)];
	    return output;
	}
}
#endif
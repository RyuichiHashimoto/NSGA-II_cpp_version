#include"Misc.h"

#include<sstream>

vector<string> split(string name, char d){
	std::vector<string> split(string name); {
		std::vector<std::string> v;
		std::stringstream ss(name);
		std::string buffer;
		while (std::getline(ss, buffer, d)) {
			v.push_back(buffer);
		}
		return v;
	}

}
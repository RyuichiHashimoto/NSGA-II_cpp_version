#include"Misc.h"
#include<fstream>
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
bool checkFileExistence(const std::string str)
{
	std::ifstream ifs(str);
	return ifs.is_open();
}
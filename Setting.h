#pragma once
#include"Solution.h"
#include<string>
#include<map>
#include<iostream>
class Setting {
private:
	const char FILEDEMILITER = ':';
	const char OPTIONDEMILITER = '-';
	map<string, string> map_;
public:
	void print();
	void FileReading(string );
	void ComamandLineReading(int,  char**);
	void Subscript(string );
	void allScript(ofstream &);
	void BaseScript(ofstream &,string );
	void clear();
	void add(string , string );
	void remove(string );
	void addForce(string , string );
	bool	getAsBool(string );
	int		getAsInt(string );
    double	getAsDouble(string );
	string 	getAsStr(string );
	bool    containKey(string );
	void   set(string , string );
	string get(string );
	map<string,string> getmap() const { return map_; };
	Setting &operator=(const Setting &);
};

void assertion(bool,string );
void ErrorMassage(string d);
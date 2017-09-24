#include"ProblemToolbox.h"
#include<string>
#include<map>
#include"DTLZ1.h"
#include"DTLZ2.h"
#include"DTLZ3.h"
#include"DTLZ4.h"
#include"DTLZ5.h"
#include"DTLZ6.h"
#include"DTLZ7.h"
#include"Setting.h"
#include<iostream>
#include"MAZDA.h"

using namespace std;
Problem* getProblem(string  name, Setting &map){
	Problem *ret;
	ret = &DTLZ1(1, 1);
	int numberofObjectieves = -1; int numberOfVariables = 10;
	int K = -1, L = -1, M = -1;
	string name_ = "NumberOfObjectives";
	if (map.containKey(name_)) {
		numberofObjectieves = map.getAsInt(name_);
	}
	name_ = "NumberOfVariables";
	if (map.containKey(name_)) {
		numberOfVariables = map.getAsInt(name_);
	}
/*	if (map.find("M") != map.end()) {
		M = map["M"];
	}
	if (map.find("L") != map.end()) {
		L = map["L"];
	}
	if (map.find("K") != map.end()) {
		K = map["K"];
	}
*/

	if (name == "DTLZ1") {
		numberOfVariables = numberofObjectieves + 4;
		ret = new DTLZ1(numberOfVariables, numberofObjectieves);
	}else if (name == "DTLZ2") {
		numberOfVariables = numberofObjectieves + 9;
		ret = new DTLZ2(numberOfVariables, numberofObjectieves);
	}
	else if (name == "DTLZ3") {
		numberOfVariables = numberofObjectieves + 9;
		ret = new DTLZ3(numberOfVariables, numberofObjectieves);
	}
	else if (name == "DTLZ4") {
		numberOfVariables = numberofObjectieves + 9;
		ret = new DTLZ4(numberOfVariables, numberofObjectieves);
	}
	else if (name == "DTLZ5") {
		numberOfVariables = numberofObjectieves + 9;
		ret = new DTLZ5(numberOfVariables, numberofObjectieves);
	}
	else if (name == "DTLZ6") {
		numberOfVariables = numberofObjectieves + 9;
		ret = new DTLZ6(numberOfVariables, numberofObjectieves);
	}
	else if (name == "DTLZ7") {
		numberOfVariables = numberofObjectieves + 19;
		ret = new DTLZ7(numberOfVariables, numberofObjectieves);
	}
	else if (name == "mazda" || name == "MAZDA") {
		ret = new mazda(map);
	} /*else if (name == "WFG1") {
		ret = new WFG1(numberOfVariables, numberofObjectieves);
	} else if (name == "WFG2") {
		ret = new WFG2(numberOfVariables, numberofObjectieves);
	}else if (name == "WFG3") {
		ret = new WFG3(numberOfVariables, numberofObjectieves);
	}
	else if (name == "WFG4") {
	ret = new WFG4(numberOfVariables, numberofObjectieves);
	}else if (name == "WFG5) {
		ret = new WFG5(numberOfVariables, numberofObjectieves);
	}else if (name == "WFG6") {
		ret = new WFG6(numberOfVariables, numberofObjectieves);
	}else if (name == "WFG7") {
		ret = new WFG7(numberOfVariables, numberofObjectieves);
	}else if (name == "WFG8") {
		ret = new WFG8(numberOfVariables, numberofObjectieves);
	}else if (name == "WFG9") {
		ret = new WFG9(numberOfVariables, numberofObjectieves);
	}

	*/else if(name == "Knapsack") {
	//	ret = new Knapsack(numberofObjectieves);
	}

	else {
		ErrorMassage("the problem name " + name + " is not found");
	}




	return ret;
}
#include"Problem.h"
#include<Map>
#include<cassert>
#include<iostream>
using namespace std;
//constructor
/****************************************/
Problem::Problem() {
	cout << "Problem ";
	numberOfObjective_ = 1; ;
	numberOfValue_ =1;
	numberOfConstrain_ = 1;
	problemname_ = "problem";
}
Problem::Problem(const map<string,void *> & temp) {
	parameter_ = temp;
	problemname_ = "problem";
}
/********************************/
//Destructor
/********************************/
Problem::~Problem() {
}
/********************************/
//Copyconstructor
/********************************/

Problem::Problem(const Problem &test) {
	
	problemname_ = test.getName();
	numberOfObjective_ = test.getNumberOfObjective();
	numberOfValue_ = test.getNumberOfValue();
	numberOfConstrain_ = test.getNumberOfConstrain();
	parameter_ = test.getParameter();
	UpperLimit_.resize(numberOfValue_);
	LowerLimit_.resize(numberOfValue_);
	for (int i = 0; i < numberOfValue_; i++) {
		UpperLimit_[i] = test.getUpperLimit(i);
		LowerLimit_[i] = test.getLowerLimit(i);
	}

}

/********************************/
//Operator
/**********************************/
Problem &Problem::operator=(const Problem &copy){
	problemname_ = copy.getName();
	numberOfObjective_ = copy.getNumberOfObjective();
	numberOfValue_ = copy.getNumberOfValue();
	numberOfConstrain_ = copy.getNumberOfConstrain();
	parameter_ = copy.getParameter();

	UpperLimit_.resize(numberOfValue_);
	LowerLimit_.resize(numberOfValue_);
	for (int i = 0; i < numberOfValue_; i++) {
		UpperLimit_[i] = copy.getUpperLimit(i);
		LowerLimit_[i] = copy.getLowerLimit(i);
	}


	return (*this);
}



/*********************************/

double Problem::getUpperLimit(int key)const {
	return UpperLimit_[key]; 
}
double Problem::getLowerLimit(int key)const {
	return LowerLimit_[key]; 
};

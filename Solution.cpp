#include"Solution.h"
#include"Problem.h"
#include"MT.h"
#include<Algorithm>
#include<iostream>
#include<cassert>
using namespace std;
//constructor
/*****************************/
Solution::Solution(int numberOfValue, int numberOfObject,int numberofConstrain){

	NumberOfObjective = numberOfObject;
	NumberOfVariables = numberOfValue; 
	NumberOfConstrain = numberofConstrain;
	SolutionType_ = -1;
	Rank_ = INTMAX_MAX;
	Variables.resize(NumberOfVariables);
	Constrain_.resize(NumberOfConstrain);
	Objective_.resize(NumberOfObjective);
	Lowerlimit_.resize(NumberOfVariables);
	Upperlimit_.resize(NumberOfVariables);
	ID_ = 0;
	CrowdingDistance_ = DBL_MIN;

	for (int i = 0; i < NumberOfVariables; i++) {
		Variables[i] = 0;
		Lowerlimit_[i] = 0;
		Upperlimit_[i] = 0;
	}
	for (int i = 0; i < NumberOfObjective; i++) {
		Objective_[i] = 0;
	}

	for (int i = 0; i < NumberOfConstrain; i++) {
		Constrain_[i] = 0;
	}
	Fiesible_ = true;
	Violation_ = 0;
}
Solution::Solution(int d) {

	NumberOfObjective = d;
	NumberOfVariables = d;
	NumberOfConstrain = d;
	SolutionType_ = -1;
	Rank_ = INTMAX_MAX;
	Variables.resize(NumberOfVariables);
	Constrain_.resize(NumberOfConstrain);
	Objective_.resize(NumberOfObjective);
	Lowerlimit_.resize(NumberOfVariables);
	Upperlimit_.resize(NumberOfVariables);

	ID_ = 0;
	CrowdingDistance_ = DBL_MIN;

	for (int i = 0; i < NumberOfVariables; i++) {
		Variables[i] = 0;
		Lowerlimit_[i] = 0;
		Upperlimit_[i] = 0;
	}
	for (int i = 0; i < NumberOfObjective; i++) {
		Objective_[i] = 0;
	}

	for (int i = 0; i < NumberOfConstrain; i++) {
		Constrain_[i] = 0;
	}
	Fiesible_ = true;
	Violation_ = 0;

}

Solution::Solution() {
	ID_ = 0;
	CrowdingDistance_ = DBL_MIN;
	Rank_ = INTMAX_MAX;
	NumberOfObjective = 1;
	NumberOfVariables = 1;
	NumberOfConstrain = 1;
	SolutionType_ = 0;
	Fiesible_ = true;
	Violation_ = 0;
}

Solution::Solution(Problem * problem_) {
	Rank_ = INTMAX_MAX;
	SolutionType_ = problem_->getSolutionType();
	NumberOfObjective = problem_->getNumberOfObjective();
	NumberOfVariables = problem_->getNumberOfValue();
	NumberOfConstrain = problem_->getNumberOfConstrain();
	Variables.resize(NumberOfVariables);
	Constrain_.resize(NumberOfConstrain);
	Objective_.resize(NumberOfObjective);
	Upperlimit_.resize(NumberOfVariables);
	Lowerlimit_.resize(NumberOfVariables);
	normalizeObjective_.resize(NumberOfObjective);
	normalizeObjectiveWithConstrain_.resize(NumberOfObjective);
	dis_.resize(NumberOfObjective);
	p_i.resize(NumberOfObjective);

	ID_ = 0;
	CrowdingDistance_ = DBL_MIN;
	Fiesible_ = true;
	Violation_ = 0;
	for (int i = 0; i < NumberOfVariables; i++) {
		Upperlimit_[i] = problem_->getUpperLimit(i);
		Lowerlimit_[i] = problem_->getLowerLimit(i);
	}
	remake();
}

/*****************************/
//Destructor
/*****************************/
Solution::~Solution() {

}
/*****************************/
// Copy Constructor
/*****************************/
/*
Solution::Solution(const Solution &test) {
	SolutionType_ = test.getSolutionType();
	NumberOfObjective = test.getNumberOfObjectives();
	NumberOfVariables = test.getNumberOfVariables();
	NumberOfConstrain = test.getNumberOfConstraint();

	Variables.resize(NumberOfVariables);
	Constrain_.resize(NumberOfConstrain);
	Objective_.resize(NumberOfObjective);


	Upperlimit_.resize(NumberOfVariables);
	Lowerlimit_.resize(NumberOfVariables);
	ID_ = test.getID();;
	CrowdingDistance_ = test.getCrowdingDistance();
	Rank_ = test.getRank();

	for (int i = 0; i < NumberOfObjective; i++) {
		Objective_[i] = test.getObjective(i);
	}

	for (int i = 0; i < NumberOfVariables; i++) {
		Upperlimit_[i] = test.getUpperLimit(i);
		Lowerlimit_[i] = test.getLowerLimit(i);

		Variables[i] = test.getValue(i);

	}


	for (int i = 0; i < NumberOfConstrain; i++) {
		Constrain_[i] = test.getConstrain(i);
	}

	Fiesible_ = test.getFiesible();
	Violation_ = test.getViolation();

};
*/
/*****************************/
// class method
/*****************************/
void Solution::subscriptObjective() {
	for (int i = 0; i < NumberOfObjective; i++) {
		std::cout << Objective_[i] << " ";
	}
	std::cout << std::endl;
}

void Solution::subscriptConstrain() {
	for (int i = 0; i < NumberOfConstrain; i++) {
		std::cout << Constrain_[i] << " ";
	}
	std::cout << std::endl;
}

void Solution::subscriptValue() {
	for (int i = 0; i < NumberOfVariables; i++) {
		std::cout << Variables[i] << " ";
	}
	std::cout << std::endl;
}

double Solution::getObjective(const int key) const {
	return Objective_[key]; 
};

double Solution::getValue(const int key) const {
	return Variables[key]; 
};
double Solution::getConstrain(const int key) const {
	return Constrain_[key];
}

void Solution::setObjective(int key, double d) { 
	Objective_[key] = d;
};
void Solution::setValue(int key, double d) { 
	Variables[key] = d;
};
void Solution::setConstrain(int key, double d) { 
//	assert(key < NumberOfVariables && ("index is wrong"));
	Constrain_[key] = d;
};

double Solution::getUpperLimit(int key) const {
//	assert(key < NumberOfVariables && ("index is wrong"));
	return Upperlimit_[key];
};
double Solution::getLowerLimit(int key)const {
//	assert(key < NumberOfVariables && ("index is wrong"));
	return Lowerlimit_[key];
};


void Solution::remake() {
	if (SolutionType_ == 1) {
		for (int i = 0; i < NumberOfVariables; i++) {
			int size = round((Upperlimit_[i] - Lowerlimit_[i] + 1));
			Variables[i] = genrand_int32() % (size)+Lowerlimit_[i];
		}
	}
	else if (SolutionType_ == 2){
		for (int i = 0; i < NumberOfVariables; i++) {
			Variables[i] = nextDoubleII() *(Upperlimit_[i] - Lowerlimit_[i]) + Lowerlimit_[i];
		}
	}
	else {
		assert(false && "remake:: SolutionType が1 でも　2でもない");
	}

}
/*
Solution &Solution::operator=(const Solution &copy) {
	ID_ = copy.getID();
	CrowdingDistance_ = copy.getCrowdingDistance();
	NumberOfObjective = copy.getNumberOfObjectives();
	NumberOfVariables = copy.getNumberOfVariables();
	NumberOfConstrain = copy.getNumberOfConstraint();
	Rank_ = copy.getRank();

	//=の左辺は初期化などで以下のプロパティをnew してメモリを確保しているため，delete する必要あり
	//別のポインタにつなげなおす
	Variables.resize(NumberOfVariables);
	Constrain_.resize(NumberOfConstrain);
	Objective_.resize(NumberOfObjective);
	Upperlimit_.resize(NumberOfVariables);
	Lowerlimit_.resize(Numbe	rOfVariables);

	Fiesible_ = copy.getFiesible();
	Violation_ = copy.getViolation();


	for (int i = 0; i < NumberOfVariables; i++) {
		Variables[i] = copy.getValue(i);
		Upperlimit_[i] = copy.getUpperLimit(i);
		Lowerlimit_[i] = copy.getLowerLimit(i);
	}
	for (int i = 0; i < NumberOfObjective; i++) {
		Objective_[i] = copy.getObjective(i);
	}
	for (int i = 0; i < NumberOfConstrain; i++) {
		Constrain_[i] = copy.getConstrain(i);
	}


	return (*this);	
};
*/


void Solution::configFisibleSolution() {
	Violation_ = 0;
	Fiesible_ = false;
	numberOfFeasibleConstrain = 0;
	for (int i = 0; i < NumberOfConstrain; i++) {
		if (Constrain_[i] >= 0) {
			numberOfFeasibleConstrain++;
		} else {
			Violation_ -= Constrain_[i];
			
		}
	}
	if (numberOfFeasibleConstrain == NumberOfConstrain) {
		Fiesible_ = true;
	}
}


void Solution::setV_max(double d) {
	V_max =	d;
}

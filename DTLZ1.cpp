#include"DTLZ1.h"
#include<iostream>

DTLZ1::DTLZ1() {
	SolutionType_ = 2;
	problemname_ = "DTLZ1";

	UpperLimit_.resize(0);
	LowerLimit_.resize(0);

	numberOfObjective_ =1;
	numberOfValue_ = 1;
	numberOfConstrain_ = 1;
}

DTLZ1::DTLZ1(int  numberOfVariables, int  numberOfObjectives) {

	numberOfValue_ = numberOfVariables;
	numberOfObjective_ = numberOfObjectives;
	numberOfConstrain_ = 0;
	cout << "DTLZ1";
	problemname_ = "DTLZ1";

	LowerLimit_.resize(numberOfValue_);
	UpperLimit_.resize(numberOfValue_);

	for (int var = 0; var < numberOfVariables; var++) {
		LowerLimit_[var] = 0.0;
		UpperLimit_[var] = 1.0;
	} //for
	SolutionType_ = 2;
}

DTLZ1::~DTLZ1() {
};

void DTLZ1::repair(Solution &solution){

}

void DTLZ1::evaluate(Solution &solution) {

	double* x = new double[numberOfValue_];
	double* f = new double[numberOfValue_];
	int k = numberOfValue_ - numberOfObjective_ + 1;

	for (int i = 0; i < numberOfValue_; i++)
		x[i] = solution.getValue(i);

	double g = 0.0;
	for (int i = numberOfValue_ - k; i < numberOfValue_; i++)
		g += (x[i] - 0.5)*(x[i] - 0.5) -cos(20.0 * PI * (x[i] - 0.5));

	g = 100 * (k + g);
	for (int i = 0; i < numberOfObjective_; i++)
		f[i] = (1.0 + g) * 0.5;

	for (int i = 0; i < numberOfObjective_; i++) {
		for (int j = 0; j < numberOfObjective_ - (i + 1); j++)
			f[i] *= x[j];
		if (i != 0) {
			int aux = numberOfObjective_ - (i + 1);
			f[i] *= 1 - x[aux];
		} //if
	}//for

	for (int i = 0; i < numberOfObjective_; i++)
		solution.setObjective(i, f[i]);

	delete[] x;
	delete[] f;

} // evaluate

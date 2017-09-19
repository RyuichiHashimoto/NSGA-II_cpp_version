#include"DTLZ5.h"


DTLZ5::DTLZ5() {
	SolutionType_ = 2;
	problemname_ = "DTLZ5";

	UpperLimit_.resize(0);
	LowerLimit_.resize(0);

	numberOfObjective_ =0;
	numberOfValue_ = 0;
	numberOfConstrain_ = 0;
}

DTLZ5::DTLZ5(int  numberOfVariables, int  numberOfObjectives) {

	numberOfValue_ = numberOfVariables;
	numberOfObjective_ = numberOfObjectives;
	numberOfConstrain_ = 0;
	
	problemname_ = "DTLZ5";

	LowerLimit_.resize(numberOfValue_);
	UpperLimit_.resize(numberOfValue_);

	for (int var = 0; var < numberOfVariables; var++) {
		LowerLimit_[var] = 0.0;
		UpperLimit_[var] = 1.0;
	} //for

	SolutionType_ = 2;

}

DTLZ5::~DTLZ5() {

};

void DTLZ5::repair(Solution &solution){

}


void DTLZ5::evaluate(Solution &solution) {

	double* x = new double[numberOfValue_];
	double* f = new double[numberOfValue_];
	double * theta = new double[numberOfObjective_];
	double g = 0.0;
	    int k = numberOfValue_ - numberOfObjective_ + 1;

	    for (int i = 0; i < numberOfValue_; i++)
	      x[i] = solution.getValue(i);

	    for (int i = numberOfValue_ - k; i < numberOfValue_; i++)
	      g += (x[i] - 0.5)*(x[i] - 0.5);

	    double t = PI  / (4.0 * (1.0 + g));

	    theta[0] = x[0] * PI / 2.0;
	    for (int i = 1; i < (numberOfObjective_-1); i++)
	      theta[i] = t * (1.0 + 2.0 * g * x[i]);

	    for (int i = 0; i < numberOfObjective_; i++)
	      f[i] = 1.0 + g;

	    for (int i = 0; i < numberOfObjective_; i++){
	      for (int j = 0; j < numberOfObjective_ - (i + 1); j++)
	        f[i] *= cos(theta[j]);
	        if (i != 0){
	          int aux = numberOfObjective_ - (i + 1);
	          f[i] *= sin(theta[aux]);
	        } // if
	    } //for

	    for (int i = 0; i < numberOfObjective_; i++)
	      solution.setObjective(i,f[i]);

	delete[] x;
	delete[] f;
	delete[] theta;
} // evaluate

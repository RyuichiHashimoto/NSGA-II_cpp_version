#include"DTLZ7.h"


DTLZ7::DTLZ7() {
	SolutionType_ = 2;
	problemname_ = "DTLZ7";

	UpperLimit_.resize(0);
	LowerLimit_.resize(0);

	numberOfObjective_ =0;
	numberOfValue_ = 0;
	numberOfConstrain_ = 0;
}

DTLZ7::DTLZ7(int  numberOfVariables, int  numberOfObjectives) {

	numberOfValue_ = numberOfVariables;
	numberOfObjective_ = numberOfObjectives;
	numberOfConstrain_ = 0;
	
	problemname_ = "DTLZ7";

	LowerLimit_.resize(numberOfValue_);
	UpperLimit_.resize(numberOfValue_);

	for (int var = 0; var < numberOfVariables; var++) {
		LowerLimit_[var] = 0.0;
		UpperLimit_[var] = 1.0;
	} //for

	SolutionType_ = 2;

}

DTLZ7::~DTLZ7() {
};

void DTLZ7::repair(Solution &solution){

}


void DTLZ7::evaluate(Solution &solution) {

	double* x = new double[numberOfValue_];
	double* f = new double[numberOfValue_];
		    int k = numberOfValue_ - numberOfObjective_ + 1;

	    for (int i = 0; i < numberOfValue_; i++)
	      x[i] = solution.getValue(i);

	    //Calculate g
	    double g = 0.0;
	    for (int i = numberOfValue_ - k; i < numberOfValue_; i++)
	      g += x[i] ;

	    g = 1 + (9.0 * g) / k;
	    //<-

	    //Calculate the value of f1,f2,f3,...,fM-1 (take acount of vectors start at 0)
		  for (int i = 0; i < numberOfObjective_; i++) {
			  f[i] = x[i];
		  }
		  
		  //<-

	    //->Calculate fM
	    double h = 0.0;
	    for (int i = 0; i < numberOfObjective_ -1; i++)
	      h += (f[i]/(1.0 + g))*(1 + sin(3.0 * PI * f[i]));

	    h = numberOfObjective_ - h;

	    f[numberOfObjective_-1] = (1 + g) * h;
	    //<-

	    //-> Setting up the value of the objetives
	    for (int i = 0; i < numberOfObjective_; i++)
	      solution.setObjective(i,f[i]);
	delete[] x;
	delete[] f;

} // evaluate

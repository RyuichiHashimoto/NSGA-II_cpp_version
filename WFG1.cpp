#include"WFG1.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG1Problem::WFG1Problem():WFG1Problem(){

	problemname_ = "WFG1Problem";
	SolutionType_ = 2;
}


WFG1Problem::WFG1Problem(int k_, int l_, int m_) : WFG1Problem(k_,l_,m_){
	problemname_ = "WFG1";	
}
WFG1Problem::~WFG1Problem() {

}

void WFG1Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}
	
	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG1(val, k_, M_);
	
	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG1Problem::repair(Solution  &a) {

};

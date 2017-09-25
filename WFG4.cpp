#include"WFG4.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG4Problem::WFG4Problem():WFG4Problem(){

	problemname_ = "WFG4Problem";
	SolutionType_ = 2;
}


WFG4Problem::WFG4Problem(int k_, int l_, int m_) : WFG4Problem(k_,l_,m_){
	problemname_ = "WFG4";	
}
WFG4Problem::~WFG4Problem() {

}

void WFG4Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}
	
	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG4(val, k_, M_);
	
	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG4Problem::repair(Solution  &a) {

};

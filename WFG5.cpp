#include"WFG5.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG5Problem::WFG5Problem():WFG5Problem(){

	problemname_ = "WFG5Problem";
	SolutionType_ = 2;
}


WFG5Problem::WFG5Problem(int k_, int l_, int m_) : WFG5Problem(k_,l_,m_){
	problemname_ = "WFG5";	
}
WFG5Problem::~WFG5Problem() {

}

void WFG5Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}
	
	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG5(val, k_, M_);
	
	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG5Problem::repair(Solution  &a) {

};

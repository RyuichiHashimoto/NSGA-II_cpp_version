#include"WFG3.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG3Problem::WFG3Problem():WFG3Problem(){

	problemname_ = "WFG3Problem";
	SolutionType_ = 2;
}


WFG3Problem::WFG3Problem(int k_, int l_, int m_) : WFG3Problem(k_,l_,m_){
	problemname_ = "WFG3";	
}
WFG3Problem::~WFG3Problem() {

}

void WFG3Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}
	
	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG3(val, k_, M_);
	
	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG3Problem::repair(Solution  &a) {

};

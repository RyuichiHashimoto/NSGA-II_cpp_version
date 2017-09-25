#include"WFG2.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG2Problem::WFG2Problem() :WFG2Problem() {

	problemname_ = "WFG2Problem";
	SolutionType_ = 2;
}


WFG2Problem::WFG2Problem(int k_, int l_, int m_) : WFG2Problem(k_, l_, m_) {
	problemname_ = "WFG2";
}
WFG2Problem::~WFG2Problem() {

}

void WFG2Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}

	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG2(val, k_, M_);

	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG2Problem::repair(Solution  &a) {

};

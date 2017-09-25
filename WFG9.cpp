#include"WFG9.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG9Problem::WFG9Problem() :WFG9Problem() {

	problemname_ = "WFG9Problem";
	SolutionType_ = 2;
}


WFG9Problem::WFG9Problem(int k_, int l_, int m_) : WFG9Problem(k_, l_, m_) {
	problemname_ = "WFG9";
}
WFG9Problem::~WFG9Problem() {

}

void WFG9Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}

	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG9(val, k_, M_);

	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG9Problem::repair(Solution  &a) {

};

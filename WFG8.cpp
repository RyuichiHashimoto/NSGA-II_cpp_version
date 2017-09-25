#include"WFG8.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG8Problem::WFG8Problem() :WFG8Problem() {

	problemname_ = "WFG8Problem";
	SolutionType_ = 2;
}


WFG8Problem::WFG8Problem(int k_, int l_, int m_) : WFG8Problem(k_, l_, m_) {
	problemname_ = "WFG8";
}
WFG8Problem::~WFG8Problem() {

}

void WFG8Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}

	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG8(val, k_, M_);

	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG8Problem::repair(Solution  &a) {

};

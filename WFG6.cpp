#include"WFG6.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG6Problem::WFG6Problem() :WFG6Problem() {

	problemname_ = "WFG6Problem";
	SolutionType_ = 2;
}


WFG6Problem::WFG6Problem(int k_, int l_, int m_) : WFG6Problem(k_, l_, m_) {
	problemname_ = "WFG6";
}
WFG6Problem::~WFG6Problem() {

}

void WFG6Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}

	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG6(val, k_, M_);

	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG6Problem::repair(Solution  &a) {

};

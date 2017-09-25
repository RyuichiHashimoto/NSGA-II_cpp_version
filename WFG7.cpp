#include"WFG7.h"
#include"WFG.h"
#include"ExampleProblems.h"


WFG7Problem::WFG7Problem() :WFG7Problem() {

	problemname_ = "WFG7Problem";
	SolutionType_ = 2;
}


WFG7Problem::WFG7Problem(int k_, int l_, int m_) : WFG7Problem(k_, l_, m_) {
	problemname_ = "WFG7";
}
WFG7Problem::~WFG7Problem() {

}

void WFG7Problem::evaluate(Solution &sol) {
	vector<double> val(sol.getNumberOfVariables());
	for (int i = 0; i < sol.getNumberOfVariables(); i++) {
		val[i] = sol.getValue(i);
	}

	vector<double> obj = WFG::Toolkit::Examples::Problems::WFG7(val, k_, M_);

	for (int i = 0; i < sol.getNumberOfObjectives(); i++) {
		sol.setObjective(i, obj[i]);
	}
};

void WFG7Problem::repair(Solution  &a) {

};

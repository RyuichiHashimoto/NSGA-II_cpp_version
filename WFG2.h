#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG2Problem : public WFGProblem {
private:

public:
	WFG2Problem();
	WFG2Problem(int, int, int);
	~WFG2Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
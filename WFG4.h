#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG4Problem : public WFGProblem {
private:

public:
	WFG4Problem();
	WFG4Problem(int, int, int);
	~WFG4Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
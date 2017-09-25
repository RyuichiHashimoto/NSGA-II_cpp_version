#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG5Problem : public WFGProblem {
private:

public:
	WFG5Problem();
	WFG5Problem(int, int,int);
	~WFG5Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG3Problem : public WFGProblem {
private:

public:
	WFG3Problem();
	WFG3Problem(int, int,int);
	~WFG3Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG9Problem : public WFGProblem {
private:

public:
	WFG9Problem();
	WFG9Problem(int, int,int);
	~WFG9Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
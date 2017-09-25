#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG7Problem : public WFGProblem {
private:

public:
	WFG7Problem();
	WFG7Problem(int, int,int);
	~WFG7Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
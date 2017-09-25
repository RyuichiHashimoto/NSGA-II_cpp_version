#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG6Problem : public WFGProblem {
private:

public:
	WFG6Problem();
	WFG6Problem(int, int, int);
	~WFG6Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
#pragma once
#include"Problem.h"
#include"WFG.h"

class WFG8Problem : public WFGProblem {
private:

public:
	WFG8Problem();
	WFG8Problem(int, int, int);
	~WFG8Problem();

	void evaluate(Solution &);
	void repair(Solution  &);

};
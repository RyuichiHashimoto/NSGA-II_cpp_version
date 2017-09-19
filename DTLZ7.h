#pragma once
#include"Problem.h"


class DTLZ7 : public Problem {
private:

public:
	DTLZ7();
	DTLZ7(int , int );
	~DTLZ7();

	void evaluate(Solution &);
	void repair(Solution  &);


};
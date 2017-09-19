#pragma once
#include"Problem.h"


class DTLZ5 : public Problem {
private:

public:
	DTLZ5();
	DTLZ5(int , int );
	~DTLZ5();

	void evaluate(Solution &);
	void repair(Solution  &);


};
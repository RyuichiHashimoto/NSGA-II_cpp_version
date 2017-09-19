#pragma once
#include"Problem.h"


class DTLZ1 : public Problem {
private:

public:
	DTLZ1();
	DTLZ1(int , int );
	~DTLZ1();

	void evaluate(Solution &);
	void repair(Solution  &) ;


};
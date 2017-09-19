#pragma once
#include"Problem.h"


class DTLZ6 : public Problem {
private:

public:
	DTLZ6();
	DTLZ6(int , int );
	~DTLZ6();

	void evaluate(Solution &);
	void repair(Solution  &);


};
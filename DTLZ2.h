#pragma once
#include"Problem.h"


class DTLZ2 : public Problem {
private:

public:
	DTLZ2();
	DTLZ2(int , int );
	~DTLZ2();

	void evaluate(Solution &);
	void repair(Solution  &);


};
#pragma once
#include"Problem.h"


class DTLZ3 : public Problem {
private:

public:
	DTLZ3();
	DTLZ3(int , int );
	~DTLZ3();

	void evaluate(Solution &);
	void repair(Solution  &);


};
#pragma once
#include"Problem.h"


class DTLZ4 : public Problem {
private:

public:
	DTLZ4();
	DTLZ4(int , int );
	~DTLZ4();

	void evaluate(Solution &);
	void repair(Solution  &);


};
#pragma once
#include<String>
#include"Solution.h"
#define _USE_MATH_DEFINES
#include"math.h"
#include<Map>
#include<vector>

//ÉNÉâÉXÇÃêÈåæÇÇ±Ç±Ç≈çsÇ§
class Solution;
//

class Problem {
protected:
	int SolutionType_;
	std::string problemname_;
	std::vector<double> UpperLimit_;
	std::vector<double> LowerLimit_;
	const double PI = M_PI;
	int numberOfObjective_ = -1;
	int numberOfValue_ = -1;
	int numberOfConstrain_ = -1;
	std::map<std::string, void *> parameter_;

public:
	Problem();
	Problem(const std::map<std::string, void *> &);
	virtual ~Problem() = 0;
	Problem(const Problem &);


	int getSolutionType() const { return SolutionType_; }
	int  getNumberOfObjective() const { return numberOfObjective_; };
	int  getNumberOfValue()const { return numberOfValue_; };
	int  getNumberOfConstrain() const { return numberOfConstrain_; };
	std::string getName() const {return problemname_;} ;
	std::map<std::string, void *>  getParameter() const { return parameter_; };
	virtual void evaluate(Solution &) = 0;
	virtual void repair(Solution  &) = 0;
	double getUpperLimit(int ) const ; 
	double getLowerLimit(int )const;
	Problem &operator=(const Problem &);


}; 

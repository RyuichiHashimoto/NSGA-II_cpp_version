#pragma once
#include"Problem.h"
#include<cassert>
#include<vector>
using namespace std;
class Problem;

class Solution {

protected:
	int NumberOfObjective;
	int NumberOfVariables;
	int NumberOfConstrain;
	int ID_;
	int Rank_;
	double CrowdingDistance_;
	vector<double> Variables;
	vector<double> Upperlimit_; //以下と同文
	vector<double> Lowerlimit_; //　コピーコンストラクタなどに引っかからないようにする

	vector<double> Constrain_;
	vector<double> Objective_;
	vector<double> normalizeObjective_;
	vector<double> normalizeObjectiveWithConstrain_;

	int SolutionType_;
	bool Fiesible_;
	double Violation_;
	int numberOfFeasibleConstrain;
	double V_max;

	vector<double> dis_;
	vector<double> p_i;
public:
	void setDistance(int key,double d) { dis_[key] = d; }
	void setp_i(int key,double d) { p_i[key] = d; }
	double getDistance(int key) const { return  dis_[key]; }
	double getp_i(int key) const { return p_i[key]; }

	Solution();
	Solution(Problem *);
	Solution(int);
	Solution(int, int, int);
	~Solution();
	std::vector<double> getObjective() {return Objective_;};
	void configFisibleSolution();
	int getSolutionType() const { return SolutionType_; }
	int getNumberOfObjectives() const { return NumberOfObjective; }
	int getNumberOfVariables()const { return NumberOfVariables; }
	int getNumberOfConstraint() const { return NumberOfConstrain; };
	int getRank() const { return Rank_; }
	void setRank(int b) {Rank_ = b;	}
	double getUpperLimit(int key) const;
	double getLowerLimit(int key)const;
	double getCrowdingDistance() const { return CrowdingDistance_; }
	void   setCrowdingDistance(double te) { CrowdingDistance_ = te; };
	int getID()const { return ID_; }
	void   setID(int te) { ID_ = te; };
	double getViolation()const {return Violation_;}
	bool   getFiesible() const { return Fiesible_; }
	double getV_max() const {return  V_max;}
	void   CalcV_max();
	double getObjective(const int t) const;
	double getValue(const int key) const;
	double getConstrain(const int key) const;
	double getNormalizationObjective(const int key)const { return normalizeObjective_[key]; }
	void setNormalization(const int key, const double d)  { normalizeObjective_[key] = d; }
	double getNormalizationWithConstrainNorm(const int key) const{ return normalizeObjectiveWithConstrain_[key]; }
	void setNormalizationWithConstrainNorm(const int key, const double d){ normalizeObjectiveWithConstrain_[key] = d; }
	void setViolation(double d) {	Violation_ = d;}
	void setV_max(double);
	void setObjective(int key, double d) ;
	void setValue(int key, double d);
	void setConstrain(int key, double d);
	void subscriptObjective();
	void subscriptValue();
	void remake();
	void setNormalizeObjective(int key, double d){ normalizeObjective_[key] = d; };
	void subscriptConstrain();	
};
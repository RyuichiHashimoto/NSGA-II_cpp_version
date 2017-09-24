#pragma once

#include<iostream>
#include"Solution.h"

class Population{
private:
	char DEMILITER = '	';
	Solution *population_;
	int populationSize_;
	int capacity_;
public:
	Population();  //このコンストラクタはあまり使用するべきではない
	Population(int capacity_); //このコンストラクタを推奨
	~Population();
	Population(const Population &);
	void setID();
	void getPoint() { std::cout << population_; };
	void add(const Solution &);
	Solution &get (int key) const;
	void resetMAXSize(const int );
	void remove(const int );
	void replace(const int, const Solution &);
	void clear();
	void SubscriptAllObjective();
	int  size()const  { return populationSize_; };
	int  getMax() const  { return capacity_; };

	Population &operator=(const Population &d);
	void merge(const Population &);
	Population &operator+(const Population &test);
	void poplast() {
		populationSize_--;
	};

	std::vector<double> getMax(bool isMAX);
	std::vector<double> getMin(bool isMAX);
	double CalcRationOfFiesibleSolution();
	void NormalizationConstrain();
	void CalcV_max();
	void Normalization(bool );
	void NormalizationWithConstrain(bool , double );
	void SubscriptObjectiveToFile(const  std::string &);
	void SubscriptVariablesToFile(const std::string &);
	void SubscriptConstrainToFile(const std::string &);
	void SubscriptFeasibeObjectiveToFile(const std::string &);
	void SubscriptInFeasibeObjectiveToFile(const std::string &);
	void SubscriptFunakoshiStyle(int,const std::string &);
};
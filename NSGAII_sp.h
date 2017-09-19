#pragma once
#include"Global.h"
#include"Population.h"
#include<String>
#include"Setting.h"


class NSGAII_sp {
protected:
	char DIRECTORYDEMILITER = '/';
	int evaluation_ = 0;
	int maxEvaluations = 40000;
	int populationSize = 100;
	double CrossoverProbablity = 0.0;;
	double CrossoverDistribution = 0.0;
	double MutationProbablity = 0.0;
	double MutationDistribution = 0.0;
	bool   isMAX_ = false;
	Setting setting_;
	string crossoverName_;
	std::vector<double> parameter_;
	void Sort(Population &, int, int, int);
	void SortCrowding(Population &, int, int);

	void CrowdingDistance(Population &);
	void MakeDirectory(string name);
	void MakeDirectory();
	Problem *problem;
	Population population_;
	Population offSpring_;
	string directory;
//	int    compareCrowding(const Solution &, const  Solution &, int);
	
public:
	NSGAII_sp(Problem *, Setting &);
	void config();
	void setting(int);
	void execute(int time);
	void initialization();
	int binaryTounament();
	void calc_dis();
	bool makeOffSpring();
	int compare(const Solution &, const Solution &);
	int compareCrowdingWithNormalize(const Solution &, const Solution &,int);
	void selectEnvironment(Population &merge);
};
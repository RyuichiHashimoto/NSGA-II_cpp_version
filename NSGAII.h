#pragma once
#include"Global.h"
#include"Population.h"
#include<String>
#include"Setting.h"


class NSGAII{


protected:
	bool normConstrain_ = false;
	const char DIRECTORYDEMILITER = '/';
	int evaluation_ = 0;
	int maxEvaluations = 40000;
	int populationSize = 100;
	double CrossoverProbablity = 0.0;;
	double CrossoverDistribution = 0.0;
	double MutationProbablity = 0.0;
	double MutationDistribution = 0.0;
	bool   isMAX_ = false;
	Setting setting_;
	void Sort(Population &, int,int, int);
	void SortCrowding(Population &, int, int);
	std::vector<double> parameter_;
	void CrowdingDistance(Population &);
	void MakeDirectory(string name);
	void MakeDirectory();
	string crossoverName;
	Problem *problem;
	Population population_;
	Population offSpring_;
	string directory;
	int    compareCrowding(const Solution &, const  Solution &, int);
public:
	NSGAII(Problem *,Setting &);
	void config();
	void setting(int ); 
	void execute(int time);
	void initialization();


	int binaryTounament();

	bool makeOffSpring();


	int compare(const Solution &, const Solution &);
	void selectEnvironment(Population &merge);

};
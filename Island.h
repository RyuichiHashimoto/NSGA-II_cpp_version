#pragma once
#include"Global.h"
#include"Population.h"
#include<String>
#include"Setting.h"


class Island {


protected:
	const char DIRECTORYDEMILITER = '/';
	int evaluation_ = 0;
	int maxEvaluations = 40000;
	std::vector<int> populationSize;

	double CrossoverProbablity = 0.0;;
	double CrossoverDistribution = 0.0;
	double MutationProbablity = 0.0;
	double MutationDistribution = 0.0;
	bool   isMAX_ = false;
	double rmp = 0;
	int numberOfIsland = 0;
	int numberOfParents = 0;
	Setting setting_;
	void Sort(Population &, int, int, int);
	void SortCrowding(Population &, int, int);
	void SortNSGAIIsp(Population &, int, int, int);
	std::vector<double> parameter_;
	void CrowdingDistance(Population &);
	void MakeDirectory(string name);
	void MakeDirectory();
	string crossoverName;
	Problem *problem;
	std::vector<Population> population_;
	std::vector<Population> offSpring_;
	string directory;
	int    compareCrowding(const Solution &, const  Solution &, int);
public:
	Island(Problem *, Setting &);
	void config();
	void setting(int);
	void execute(int time);
	void initialization();
	void selectEnvironment();
	Solution& binaryTounament(int);
	int binaryTounament(Population &);
	bool makeOffSpring();
	int compare(const Solution &, const Solution &);
	int compareCrowdingWithNormalize(const Solution&, const Solution&,int);
	void selectEnvironment(Population &,Population &);
	void CrowdingDistanceForNSGAIIsp(Population &);
	void selectNSGAIIsp(Population &, Population &);	
	void selectCNSGAII(Population &, Population &);
	

};
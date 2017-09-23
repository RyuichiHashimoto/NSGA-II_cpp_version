#pragma once
#include"Solution.h"



void Crossover(string name,vector<Solution> &, vector<Solution> &, double crossoverprobability, std::vector<double> );

void SBXCrossover2(vector<Solution> &, vector<Solution> &,  double crossoverprobability, std::vector<double> );

void DECrossover(vector<Solution> &, vector<Solution> & , double , std::vector<double>);

void PolynominalMutation(Solution &, double crossoverprobability, double crossoverDistributionIndex);


void CrossoverMutation(Solution &solution, Solution &two, double ,double);

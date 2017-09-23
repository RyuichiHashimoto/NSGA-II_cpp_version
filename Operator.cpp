#include"Operator.h"
#include"MT.h"
#include"Global.h"
#include<iostream>
#include"Setting.h"

void Crossover(string name, vector<Solution> &p, vector<Solution> &o, double cp, std::vector<double> para) {
	if (name == "SBXCrossover") {
		SBXCrossover2(p,o,cp,para);
	}
	else if(name == "DECrossover"){
		DECrossover(p, o, cp, para);
		ErrorMassage("the crossover name " + name + " is not found");
	}
	else {
		ErrorMassage("the crossover name " + name + " is not found");
	}
}


void SBXCrossover2(vector<Solution> &parents, vector<Solution> &offSpring,double crossoverprobability, std::vector<double> parameter){
	double probability = crossoverprobability;
	double distributionIndex_ = parameter[0];
	offSpring.resize(2);
	offSpring[0] = parents[0];
	offSpring[1] = parents[1];
	double x1 = 0.0;
	double x2 = 0.0;
	double c1, c2;
	double rand;
	double X_MAX = 0;
	double X_MIN = 0;
	double beta;
	double betaq;
	double alpha;
	int numberOfVariables = parents[0].getNumberOfVariables();
	if (nextDoubleIE() <= probability) {
		for (int i = 0; i<numberOfVariables; i++) {
			if (nextDoubleIE() <= 0.5){
				if (abs(parents[0].getValue(i) - parents[1].getValue(i)) > 1.0E-14) {
					if (parents[0].getValue(i) > parents[1].getValue(i)) {
						x2 = parents[0].getValue(i);
						x1 = parents[1].getValue(i);
					}
					else if (parents[0].getValue(i) < parents[1].getValue(i)) {
						x2 = parents[1].getValue(i);
						x1 = parents[0].getValue(i);
					}
					else {
						ErrorMassage("something is wrong in SBX");
					}

					X_MAX = parents[0].getUpperLimit(i);
					X_MIN = parents[1].getLowerLimit(i);
					rand = nextDoubleIE();

					beta = 1.0 + 2.0 * (x1 - X_MIN) / (x2 - x1);
					alpha = 2.0 - pow(beta, -(distributionIndex_ + 1));

					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand*alpha), 1.0 / (distributionIndex_ + 1));
					}
					else {
						betaq = pow(1.0 / (2 - (rand*alpha)), 1.0 / (distributionIndex_ + 1));
					}
					c1 = 0.5 *((x1 + x2) - betaq * (x2 - x1));
					beta = 1.0 + (2.0*(X_MAX - x2) / (x2 - x1));
					alpha = 2.0 - pow(beta, -(distributionIndex_ + 1.0));

					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand*alpha), 1.0 / (distributionIndex_ + 1));
					}
					else {
						betaq = pow(1.0 / (2 - (rand*alpha)), 1.0 / (distributionIndex_ + 1));
					}
					c2 = 0.5 *((x1 + x2) + betaq * (x2 - x1));

					if (c1 < X_MIN) c1 = X_MIN;
					if (c1 > X_MAX) c1 = X_MAX;
					if (c2 < X_MIN) c2 = X_MIN;
					if (c2 > X_MAX) c2 = X_MAX;

					if (nextDoubleIE() <0.5) {
						offSpring[0].setValue(i, c1);
						offSpring[1].setValue(i, c2);
					}
					else {
						offSpring[0].setValue(i, c2);
						offSpring[1].setValue(i, c1);
					}
				}
				else {
					offSpring[0].setValue(i, parents[0].getValue(i));
					offSpring[1].setValue(i, parents[1].getValue(i));
				}
			}
			else {
				offSpring[0].setValue(i, parents[0].getValue(i));
				offSpring[1].setValue(i, parents[1].getValue(i));
			}
		}
	}
	else {
		for (int i = 0; i<numberOfVariables; i++) {
			offSpring[0].setValue(i, parents[0].getValue(i));
			offSpring[1].setValue(i, parents[1].getValue(i));
		}
	}
};

void PolynominalMutation(Solution &solution,double mutationProbability,double distributionIndex) {
	double pro = mutationProbability;
	double distributionIndex_ = distributionIndex;
	int NumberOfVariables = solution.getNumberOfVariables();
	pro = pro >= 0 ? pro : -1.0 * pro / NumberOfVariables;	
	double rnd, delta1, delta2, mut_pow, deltaq;
	double y, yl, yu, val, xy;
	for (int var = 0; var < NumberOfVariables; var++) {
		if (nextDoubleII() <= pro) {
			y = solution.getValue(var);
			yl = solution.getLowerLimit(var);
			yu = solution.getUpperLimit(var);
			delta1 = (y - yl) / (yu - yl);
			delta2 = (yu - y) / (yu - yl);
			rnd = nextDoubleII();
			mut_pow = 1.0 / (distributionIndex_ + 1.0);
			if (rnd <= 0.5) {
				xy = 1.0 - delta1;
				val = 2.0*rnd + (1.0 - 2.0*rnd)*(pow(xy, (distributionIndex_ + 1.0)));
				deltaq = pow(val, mut_pow) - 1.0;
			}
			else {
				xy = 1.0 - delta2;
				val = 2.0*(1.0 - rnd) + 2.0*(rnd - 0.5)*(pow(xy, (distributionIndex_ + 1.0)));
				deltaq = 1.0 - (pow(val, mut_pow));
			}
			y = y + deltaq*(yu - yl);
			if (y<yl)
				y = yl;
			if (y>yu)
				y = yu;
			solution.setValue(var, y);
		}
	}

}



void DECrossover(vector<Solution> &parents, vector<Solution> &offSpring, double crossover, std::vector<double> parameter) {
	ErrorMassage("Are you want to use DE Crossover? ");
	offSpring.resize(1);
	offSpring[0] = parents[0];

	double CR = parameter[0];
	double F = parameter[1];
	int size = parents[0].getNumberOfVariables();
	if(nextDoubleIE() < crossover){
		int jrand = genrand_int31() % size;
		for (int val = 0; val < size ; val++) {
			double variable = 0;
			if (nextDoubleIE() < CR || jrand == val) {
				variable = parents[0].getValue(val) + F*(parents[1].getValue(val) - parents[2].getValue(val));

				if (variable > parents[0].getUpperLimit(val))
					variable = parents[0].getUpperLimit(val);
				if (variable < parents[0].getLowerLimit(val))
					variable = parents[0].getLowerLimit(val);

			}
			else {
//				variable = parents[rand].getValue(val);
			}

			offSpring[0].setValue(val,variable);
		}
	}
	else {
		int rand = genrand_int31() % 3;
		offSpring[0] = parents[rand];
	}
}

void CrossoverMutation(Solution &solution,Solution &otherSolution,double mutationProbability,double para){
	double probability = mutationProbability;
	int numberOfVariables = otherSolution.getNumberOfVariables();
	probability = probability > 0 ? probability : -1.0 * probability / numberOfVariables;
	double distributionIndex_ = para;
	double x1 = 0.0;
	double x2 = 0.0;
	double c1, c2;
	double rand;
	double X_MAX = 0;
	double X_MIN = 0;
	double beta;
	double betaq;
	double alpha;
	if (nextDoubleIE() <= 1) {
		for (int i = 0; i<numberOfVariables; i++) {
			if (nextDoubleIE() <= probability) {
				if (abs(otherSolution.getValue(i) - solution.getValue(i)) > 1.0E-14) {
					if (solution.getValue(i) > otherSolution.getValue(i)) {
						x2 = solution.getValue(i);
						x1 = otherSolution.getValue(i);
					}
					else if (solution.getValue(i) < otherSolution.getValue(i)) {
						x1 = solution.getValue(i);
						x2 = otherSolution.getValue(i);
					}
					else {
						ErrorMassage("something is wrong in SBX");
					}

					X_MAX = solution.getUpperLimit(i);
					X_MIN = otherSolution.getLowerLimit(i);
					rand = nextDoubleIE();

					beta = 1.0 + 2.0 * (x1 - X_MIN) / (x2 - x1);
					alpha = 2.0 - pow(beta, -(distributionIndex_ + 1));

					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand*alpha), 1.0 / (distributionIndex_ + 1));
					}
					else {
						betaq = pow(1.0 / (2 - (rand*alpha)), 1.0 / (distributionIndex_ + 1));
					}
					c1 = 0.5 *((x1 + x2) - betaq * (x2 - x1));
					beta = 1.0 + (2.0*(X_MAX - x2) / (x2 - x1));
					alpha = 2.0 - pow(beta, -(distributionIndex_ + 1.0));

					if (rand <= (1.0 / alpha)) {
						betaq = pow((rand*alpha), 1.0 / (distributionIndex_ + 1));
					}
					else {
						betaq = pow(1.0 / (2 - (rand*alpha)), 1.0 / (distributionIndex_ + 1));
					}
					c2 = 0.5 *((x1 + x2) + betaq * (x2 - x1));

					if (c1 < X_MIN) c1 = X_MIN;
					if (c1 > X_MAX) c1 = X_MAX;
					if (c2 < X_MIN) c2 = X_MIN;
					if (c2 > X_MAX) c2 = X_MAX;

					if (nextDoubleIE() <0.5) {
						solution.setValue(i, c1);
//						otherSolution.setValue(i, c2);
					}
					else {
						solution.setValue(i, c2);
//						otherSolution.setValue(i, c1);
					}
				}
				else {
					solution.setValue(i, solution.getValue(i));
//					otherSolution.setValue(i, otherSolution.getValue(i));
				}
			}
			else {
				solution.setValue(i, solution.getValue(i));
//				otherSolution.setValue(i, otherSolution.getValue(i));
			}
		}
	}
	else {
		for (int i = 0; i<numberOfVariables; i++) {
			solution.setValue(i, solution.getValue(i));
//			otherSolution.setValue(i, otherSolution.getValue(i));
		}
	}
}
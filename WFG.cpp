#include"WFG.h"

WFGProblem::WFGProblem(int k, int  l, int  M) {
	k_ = k;
	l_ = l;
	M_ = M;
	numberOfValue_ = k_ + l_;
	numberOfObjective_ = M_;
	problemname_ = "WFGProblem";

	LowerLimit_.resize(numberOfValue_);
	UpperLimit_.resize(numberOfValue_);

	for (int var = 0; var < numberOfValue_; var++) {
		LowerLimit_[var] = 0;
		UpperLimit_[var] = 2 * (var + 1);
	}
	for (int var = 0; var < numberOfValue_; var++) {
		LowerLimit_[var] = 0;
		UpperLimit_[var] = 2 * (var + 1);
	}

	SolutionType_ = 2;
} // WFGProblem

WFGProblem::WFGProblem() {
	k_ = 10;
	l_ = 10;
	M_ = 4;
	numberOfValue_ = k_ + l_;
	numberOfObjective_ = M_;
	problemname_ = "WFGProblem";
	LowerLimit_.resize(numberOfValue_);
	UpperLimit_.resize(numberOfValue_);

	for (int var = 0; var < numberOfValue_; var++) {
		LowerLimit_[var] = 0;
		UpperLimit_[var] = 2 * (var + 1);
	}
	for (int var = 0; var < numberOfValue_; var++) {
		LowerLimit_[var] = 0;
		UpperLimit_[var] = 2 * (var + 1);
	}
	SolutionType_ = 2;
}

std::vector<double>  WFGProblem::calculate_x(std::vector<double>  t){
	std::vector<double>  x(M_);

	for (int i = 0; i < M_ - 1; i++) {
		x[i] = max(t[M_ - 1], A_[i]) * (t[i] - (double)0.5) + (double)0.5;
	}

	x[M_ - 1] = t[M_ - 1];

	return x;
} // calculate_x

std::vector<double>  WFGProblem::normalise(std::vector<double>  z) {
	std::vector<double>  result(z.size());
	for (int i = 0; i < z.size(); i++) {
		double bound = (double)2.0 * (i + 1);
		result[i] = z[i] / bound;
		result[i] = correct_to_01(result[i]);
	}

	return result;
} // normalize

double WFGProblem::correct_to_01(double a) {
	double min = (double)0.0;
	double max = (double)1.0;

	double min_epsilon = min - epsilon;
	double max_epsilon = max + epsilon;

	if ((a <= min && a >= min_epsilon) || (a >= min && a <= min_epsilon)) {
		return min;
	}
	else if ((a >= max && a <= max_epsilon) || (a <= max && a >= max_epsilon)) {
		return max;
	}
	else {
		return a;
	}
} // correct_to_01

std::vector<double>  subVector(std::vector<double>  z, int head, int tail) {
	int size = tail - head + 1;
	std::vector<double>  result(size);

	for (int i = 0; i < tail + 1 - head; i++) {
		result[i + head - head] = z[i + head];
	}

	return result;
} // subVector


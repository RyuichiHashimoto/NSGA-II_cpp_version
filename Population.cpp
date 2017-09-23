#include"Population.h"
#include"Solution.h"
#include"misc.h"
#include<cassert>
#include<iostream>
#include<fstream>
#include"Setting.h"
// constructor
/*** ***************************/
Population::Population(){
	population_ = new Solution[10];
	populationSize_ = 0;
	capacity_ = 10;
}

Population::Population(int numberOfSolution) {
	populationSize_ = 0;
	capacity_ = numberOfSolution;
	population_ = new Solution[numberOfSolution ];
}


// Destructor
//*******************************************************************//
Population::~Population(){
	if (population_ != NULL )delete[] population_;
}

//Copyconstructor
//*******************************************************************//
Population::Population(const Population &test) {
	populationSize_ = test.size();
	capacity_ = test.getMax();
	population_ = new Solution[capacity_ + 10];
	for (int i = 0; i < populationSize_; i++) {
		population_[i] = test.get(i);
	}
}

std::vector<double> Population::getMin(bool isMAX){
	vector<double> ret = population_[0].getObjective();
	for (int i = 0; i < populationSize_; i++) {
		for (int ja = 0; ja < ret.size(); ja++) {
			if ((ret[ja] > population_[i].getObjective(ja))) {
				ret[ja] = population_[i].getObjective(ja);
			}
		}
	}
	return ret;
}
std::vector<double> Population::getMax(bool isMAX){
	vector<double> ret = population_[0].getObjective();
	for (int i = 0; i < populationSize_; i++) {
		for (int ja = 0; ja < ret.size(); ja++) {
			if (ret[ja] < population_[i].getObjective(ja)) {
				ret[ja] = population_[i].getObjective(ja);
			}
		}
	}
	return ret;
}

double Population::CalcRationOfFiesibleSolution(){
	int numberOfFiesibleSols = 0;
	for (int i = 0; i < populationSize_; i++) {
		if (population_[i].getFiesible()) {
			numberOfFiesibleSols++;
		}
	}
	return  (double)numberOfFiesibleSols / populationSize_;
}

// Operator
//*******************************************************************//

Population &Population::operator=(const Population &copy) {
	populationSize_ = copy.size();
	capacity_ = copy.getMax();
	delete[] population_;

	population_ = new Solution[capacity_];


	for (int i = 0; i < populationSize_; i++) {
		population_[i] = copy.get(i);
	}
	return (*this);
}

Population & Population::operator+(const Population &a){
	Population ret(a.size() + populationSize_);

	for (int i = 0; i < (*this).size(); i++) {
		ret.add(population_[i]);
	}
	for (int i = 0; i < a.size(); i++) {
		ret.add(a.get(i));
	}
	return ret;
}

void Population::merge(const Population &test){
	for (int i = 0; i < test.size(); i++) {
		add(test.get(i));
	}
}

void Population::NormalizationConstrain() {
	for (int p = 0; p < populationSize_; p++) {
		population_[p].setViolation(0);
	}

	int cSize = population_[0].getNumberOfConstraint();
	for (int c = 0; c < cSize;c++){
		double min = DBL_MAX;
		for (int p = 0; p < populationSize_; p++) {
			if (min > population_[p].getConstrain(c)) {
				min = population_[p].getConstrain(c);
			}
		}

		if (min >= 0) {
			continue;
		}

		for (int p = 0; p < populationSize_; p++) {
			if(population_[p].getConstrain(c) < 0){
				double emp = population_[p].getViolation();
				emp += population_[p].getConstrain(c) / min;
				population_[p].setViolation(emp);
			}
		}
	}
}

// class Method
//*******************************************************************//
void Population::add(const Solution &d) {
		population_[populationSize_++] = d;
	
}

void Population::resetMAXSize(const int test) {
	assert(test > populationSize_ && "changing populaiton size is wrong");
	Solution* d = population_;
	delete[] population_;
	population_ = new Solution[test];
	for (int i = 0; i < populationSize_; i++) {
		population_[i] = d[i];
	}
	capacity_ = test;
};


void Population::remove(const int key) {
	for (int i = key; i < populationSize_-1; i++) {
		population_[i] = population_[i + 1];
	}
	populationSize_--;
};




void Population::replace(const int index, const Solution &d) {
	population_[index] = d;
};


//クリアしても前のやつはの残る．
//消えるフラグが立っただけ
void Population::clear() {
	populationSize_ = 0;
};


void Population::SubscriptAllObjective() {
	for (int i = 0; i < populationSize_; i++) {
		population_[i].subscriptObjective();
	}
};

Solution& Population::get(int key)const {
	return population_[key];
}

void Population::SubscriptObjectiveToFile(const std::string &path ) {
	ofstream output(path);

	for (int i = 0; i < populationSize_; i++) {
		Solution a = population_[i];
		for (int j = 0; j < a.getNumberOfObjectives() - 1; j++) {
			output << a.getObjective(j) << "	";
		}
		output << -1 * a.getObjective(a.getNumberOfObjectives() - 1) << endl;
//		output << 1 * a.getObjective(a.getNumberOfObjectives() - 1) << endl;

	}
}

void Population::SubscriptVariablesToFile(const std::string &path ) {
	ofstream output(path);

	for (int i = 0; i < populationSize_; i++) {
		Solution a = population_[i];
		for (int j = 0; j < a.getNumberOfVariables() - 1; j++) {
			output << a.getValue(j) << "	";
		}
		output << a.getValue(a.getNumberOfVariables() - 1) << endl;
	}
}

void Population::SubscriptConstrainToFile(const std::string &path) {
	ofstream output(path);

	for (int i = 0; i < populationSize_; i++) {
		Solution a = population_[i];
		for (int j = 0; j < a.getNumberOfConstraint() - 1; j++) {
			output << a.getValue(j) << "	";
		}
		output << a.getValue(a.getNumberOfVariables() - 1) << endl;
	}
}



void Population::SubscriptFeasibeObjectiveToFile(const std::string &path) {
	ofstream output(path);

	for (int i = 0; i < populationSize_; i++) {
		Solution a = population_[i];
		if (a.getFiesible()) {
			for (int j = 0; j < a.getNumberOfObjectives() - 1; j++) {
				output << a.getObjective(j) << "	";
			}
			output << -1 * a.getObjective(a.getNumberOfObjectives() - 1) << endl;
		}
	}
}
void Population::SubscriptInFeasibeObjectiveToFile(const std::string &path) {
		ofstream output(path);

	for (int i = 0; i < populationSize_; i++) {
		Solution a = population_[i];
		if (!a.getFiesible()) {
			for (int j = 0; j < a.getNumberOfObjectives() - 1; j++) {
				output << a.getObjective(j) << DEMILITER;
			}
			output << -1*a.getObjective(a.getNumberOfObjectives() - 1)<<DEMILITER << a.getRank() << DEMILITER<< a.getViolation() << endl;
		}
	}
}

void Population::SubscriptFunakoshiStyle(int d,const std::string &path){
	int numberOfConstraint = population_[0].getNumberOfConstraint();
	int numberOfVariables = population_[0].getNumberOfVariables();
	if (!checkFileExistence(path)) {
		ofstream output(path, ios::app);

		output << "#gen" << DEMILITER << "Feasible" << DEMILITER << "f" << to_string(1) << DEMILITER << "f" << to_string(2) << DEMILITER;
		for (int i = 0; i < numberOfConstraint; i++) {
			output << "c" << to_string(i) << DEMILITER;
		}
		for (int i = 0; i < numberOfVariables - 1; i++) {
			output << "x" << to_string(i + 1) << DEMILITER;
		}
		output << "x" << to_string(numberOfVariables - 1) << endl;
	
	}
	ofstream output(path, ios::app);

	for (int popnum = 0; popnum < populationSize_; popnum++) {
		output << to_string(d) << DEMILITER;
		int a = population_[popnum].getFiesible() ? 1 : 0;
		
		output << a << DEMILITER << population_[popnum].getObjective(0) <<DEMILITER<< -1 *population_[popnum].getObjective(1) << DEMILITER;

		for (int i = 0; i < numberOfConstraint; i++) {
			output << population_[popnum].getConstrain(i) << DEMILITER;
		}
		for (int i = 0; i < numberOfVariables - 1; i++) {
			output << population_[popnum].getValue(i) << DEMILITER;
		}
		output << population_[popnum].getValue(numberOfVariables - 1) << endl;
	}

		
}




void Population::setID() {
	for (int i = 0; i < populationSize_; i++) {
		population_[i].setID(i);
	}
}

void Population::Normalization(bool isMAX_){
	vector<double> max = getMax(isMAX_);
	vector<double> min = getMin(isMAX_);
	for (int i = 0; i<populationSize_ ; i++) {
		vector<double> value_ = population_[i].getObjective();
		for (int ja = 0; ja < max.size(); ja++) {
			population_[i].setNormalizeObjective(ja, (value_[ja] - min[ja]) / (max[ja] - min[ja]));
		}
	}
}

void Population::CalcV_max(){
	for (int p = 0; p < populationSize_; p++) {
		population_[p].setV_max(0);
	}
	int cSize = population_[0].getNumberOfConstraint();
	for (int c = 0; c < cSize; c++) {
		double min = 1.0E40;
		for (int p = 0; p < populationSize_; p++) {
			if (min > population_[p].getConstrain(c)) {
				min = population_[p].getConstrain(c);
			}
		}
		if (min >= 0) {
			continue;
		}

		for (int p = 0; p < populationSize_; p++) {
			if (population_[p].getConstrain(c) < 0) {
				double V = population_[p].getV_max();
				V += population_[p].getConstrain(c) / (min*cSize);
				population_[p].setV_max(V);
			}
		}
	}
}

void Population::NormalizationWithConstrain(bool isMAX_) {
	Normalization(isMAX_);
	// V_max = (制約違反量の総和)/(最大制約違反量*制約数)
	CalcV_max();
/*	for (int i = 0; i < populationSize_; i++) {
//		cout << population_[i].getV_max()<<endl;
	}
*/
	int Objectives = population_[0].getNumberOfObjectives();
	double ration = CalcRationOfFiesibleSolution();
	//0なら距離変数はV_maxとなる(つまり制約のみをみる)	
	if (fabs(ration) <1.0E-14) {
		for (int p = 0; p < populationSize_; p++) {
			for (int obj = 0; obj < Objectives; obj++) {
				population_[p].setDistance(obj, population_[p].getV_max());
			}
		}
	}	else {
		for (int p = 0; p < populationSize_; p++) {
			for (int obj = 0; obj < Objectives; obj++) {
				population_[p].setDistance(obj, sqrt(  pow(population_[p].getV_max(), 2) + pow( population_[p].getNormalizationObjective(obj), 2) ) );
			}
		}
	}
	
	//penarutyparamter の設定
	for (int obj = 0; obj < Objectives; obj++) {
		for(int p = 0;p< populationSize_;p++){
			vector<double> X(Objectives), Y(Objectives);
			double x, y;
			if (fabs(ration) < 1.0E-14) {
				x = 0;
			}
			else {
				x = population_[p].getV_max();
			}	

			if (fabs(population_[p].getV_max()) < 1.0E-14) {
				y = 0;
			}
			else {
				y = population_[p].getNormalizationObjective(obj);
			}

			population_[p].setp_i(obj,(1 - ration)*x + ration*y);
		}
	}
	
	for (int p = 0; p < populationSize_; p++) {
		for (int obj = 0; obj < Objectives; obj++) {
			population_[p].setNormalizationWithConstrainNorm(obj, population_[p].getp_i(obj) + population_[p].getDistance(obj));
		}

	}
	
}

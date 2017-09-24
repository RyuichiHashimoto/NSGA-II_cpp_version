#include"MT.h"
#include<math.h>
#include"Operator.h"
#include"Ranking.h"
#include<direct.h>
#include"Setting.h"
#include<sstream>
#include"MyNSGAII_sp.h"
#include"Misc.h"
#include"Setting.h"

void NSGAII_sp::initialization() {
	for (int i = 0; i < populationSize; i++) {
		Solution a(problem);
		problem->repair(a);
		problem->evaluate(a);
		population_.add(a);
		evaluation_++;
	}
}


NSGAII_sp::NSGAII_sp(Problem *d, Setting &test) {
	problem = d;
	setting_ = test;
}


void NSGAII_sp::setting(int d) {
	evaluation_ = 0;
	maxEvaluations = setting_.getAsInt("maxEvaluation");
	cout << maxEvaluations;
	populationSize = setting_.getAsInt("populationSize");
	population_ = Population(populationSize);
	offSpring_ = Population(populationSize);
	directory = "result/NSGAII_sp/" + problem->getName() + "/" + to_string(problem->getNumberOfObjective()) + "OBJ/" + to_string(d);
	CrossoverProbablity = setting_.getAsDouble("CrossoverProbability");
	CrossoverDistribution = setting_.getAsDouble("CrossoverDistribution");
	MutationProbablity = setting_.getAsDouble("MutationProbability");
	MutationDistribution = setting_.getAsDouble("MutationDistribution");;
	crossoverName_ = setting_.getAsStr("Crossover");
	parameter_.resize(1);
	parameter_[0] = CrossoverDistribution;
	isMAX_ = setting_.getAsBool("isMAX");
	MakeDirectory();
	setting_.Subscript(directory + "/setting/setting.ini");
}


bool NSGAII_sp::makeOffSpring() {
	offSpring_ = Population(populationSize);
	for (int i = 0; i < populationSize; i++) {
		vector<Solution> offSpring(2);
		vector<Solution> parents(2);

		int one = binaryTounament();
		int two = binaryTounament();

		while (one == two) {
			two = binaryTounament();
		}
		parents[0] = population_.get(one);
		parents[1] = population_.get(two);
		SBXCrossover2(parents, offSpring, CrossoverProbablity, parameter_);
		int rand = genrand_int31() % offSpring.size();

		PolynominalMutation(offSpring[rand], MutationProbablity, MutationDistribution);
		problem->repair(offSpring[rand]);
		problem->evaluate(offSpring[rand]);
		evaluation_++;
		offSpring_.add(offSpring[rand]);
		if (evaluation_ == maxEvaluations) {
			return false;
		}
		
/*
		PolynominalMutation(offSpring[1], MutationProbablity, MutationDistribution);
		problem->repair(offSpring[1]);
		problem->evaluate(offSpring[1]);
		offSpring_.add(offSpring[1]);
		evaluation_++;
		if (evaluation_ == maxEvaluations) {
			return false;
		}
*/
	}
	return true;


}


void NSGAII_sp::MakeDirectory() {
	cout << directory << endl;;
	MakeDirectory(directory + "/Setting");
	MakeDirectory(directory + "/ALLFUN");
	MakeDirectory(directory + "/FeasibleFUN");
	MakeDirectory(directory + "/InFeasibleFUN");
	MakeDirectory(directory + "/ALLVAR");
	MakeDirectory(directory + "/FeasibleVAR");
	MakeDirectory(directory + "/InFeasibleVAR");
	MakeDirectory(directory + "/FUNAKOSHISTYLE");
}

void NSGAII_sp::MakeDirectory(string name) {
	vector<string > v = split(name, DIRECTORYDEMILITER);
	string f = v[0];
	_mkdir(f.c_str());
	f += DIRECTORYDEMILITER;
	for (int i = 1; i < v.size(); i++) {
		f += v[i];
		_mkdir(f.c_str());
		f += DIRECTORYDEMILITER;
	}
}
int NSGAII_sp::binaryTounament() {

	int one = genrand_int32() % population_.size();
	int two = genrand_int32() % population_.size();
	while (one == two) {
		two = genrand_int32() % population_.size();
	}

	if (compare(population_.get(one), population_.get(two)) == 1) {
		return one;
	}
	else {
		return two;
	}
}
int NSGAII_sp::compare(const Solution &one, const Solution &two) {

	if (one.getRank() < two.getRank()) {
		return 1;
	}
	else if (two.getRank() < one.getRank()) {
		return -1;
	}

	if (one.getCrowdingDistance() > two.getCrowdingDistance()) {
		return 1;
	}
	else if (one.getCrowdingDistance() < two.getCrowdingDistance()) {
		return -1;
	}

	if (nextBoolean()) {
		return 1;
	}
	else {
		return -1;
	}
	return 0;
}


void NSGAII_sp::execute(int time) {

	bool flag;

	setting(time);

	initialization();


	int generation = 0;

	population_.SubscriptObjectiveToFile(directory + "/ALLFUN/InitialFUN" + to_string(generation) + ".dat");
	population_.SubscriptFeasibeObjectiveToFile(directory + "/FeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
	population_.SubscriptInFeasibeObjectiveToFile(directory + "/InFeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
	population_.NormalizationWithConstrain(isMAX_);
	population_.SubscriptFunakoshiStyle(time, directory + "/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");

	//population_.NormalizationWithConstrain(isMAX_);
	do {
		cout << ++generation << "gen" << endl;
		flag = makeOffSpring();
	
		//offSpring_.NormalizationWithConstrain(isMAX_);
		
		Population merge_(populationSize * 2);
		
		merge_.merge(population_);
		
//		offSpring_.SubscriptObjectiveToFile(directory + "/ALLFUN/InitialFUN" + to_string(generation) + ".dat");
//		offSpring_.SubscriptVariablesToFile(directory + "/ALLVAR/InitialVAR" + to_string(generation) + ".dat");
		offSpring_.SubscriptFeasibeObjectiveToFile(directory + "/FeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
		offSpring_.SubscriptInFeasibeObjectiveToFile(directory + "/InFeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
		offSpring_.SubscriptFunakoshiStyle(time, directory + "/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");


		merge_.merge(offSpring_);

		selectEnvironment(merge_);


	} while (flag);


	generation++;
//	population_.SubscriptObjectiveToFile(directory + "/ALLFUN/InitialFUN" + to_string(generation) + ".dat");
//	population_.SubscriptVariablesToFile(directory + "/ALLVAR/InitialVAR" + to_string(generation) + ".dat");
	population_.SubscriptFeasibeObjectiveToFile(directory + "/FeasibleFUN/FinalFUN" + to_string(generation) + ".dat");
//	population_.SubscriptInFeasibeObjectiveToFile(directory + "/InFeasibleFUN/InitialFUN" + to_string(generation) + ".dat");

	
//	population_.SubscriptFunakoshiStyle(time, directory + "/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");


}



void NSGAII_sp::selectEnvironment(Population &merge_) {
	merge_.NormalizationWithConstrain(isMAX_);
	vector<Population> ranking = RankingForConstrainNSGAIIsp(merge_, isMAX_);
//	vector<Population> ranking = RankingForConstrain(merge_, isMAX_);

	population_.clear();	
	int rank = 0;
	while (population_.size() + ranking[rank].size() < populationSize) {
		CrowdingDistance(ranking[rank]);
		population_.merge(ranking[rank]);
		rank++;
	}

	int rest = populationSize - population_.size();

	if (rest == 0) return;

	CrowdingDistance(ranking[rank]);

	SortCrowding(ranking[rank], 0, ranking[rank].size() - 1);


	int size = ranking[rank].size();

	for (int i = 0; i < size - rest; i++) {
		ranking[rank].poplast();
	}
	CrowdingDistance(ranking[rank]);

	for (int i = 0; i < ranking[rank].size(); i++) {
		population_.add(ranking[rank].get(i));
	}

}

void NSGAII_sp::SortCrowding(Population &d, int left, int right) {
	for (int i = 0; i < d.size(); i++) {
		for (int ja = d.size() - 1; ja >= i; ja--) {
			if (compare(d.get(i), d.get(ja)) == -1) {
				std::swap(d.get(i), d.get(ja));
			}
		}
}


	/*	if (left >= right){
	return;
	}

	int i = left;
	int j = right;
	Solution pivot = d.get((left + right) / 2);
	cout << left << "	" << right << endl;
	while (1) {
	while (	compare(pivot,d.get(i)) == 1 && i < right)
	i++;
	while (compare(d.get(j), pivot) == 1 && j > left) {
	j--;
	cout << j << "	";
	}
	if (i >= j)
	break;
	std::swap(d.get(i), d.get(j));
	i++;
	j--;
	}
	cout << left << "	" << right << endl;
	cout << i << "	" << j << endl;
	cout << endl;
	SortCrowding(d, left, i );
	SortCrowding(d, j , right);
	*/
}
/*
void NSGAII_sp::Sort(Population &d, int objective, int left, int right) {

int i = left;
int j = right;

Solution pivot = d.get((left + right) / 2);


while (1) {
while (compareCrowding(pivot, d.get(i), objective) == 1)
i++;
while (compareCrowding(d.get(j), pivot, objective) == 1)
j--;
if (i >= j)
break;
std::swap(d.get(i), d.get(j));
i++;
j--;
}

if (left < i - 1)
Sort(d, objective,left, i - 1);
if (j + 1 <  right)
Sort(d,objective, j + 1, right);
}
*/


int NSGAII_sp::compareCrowdingWithNormalize(const Solution &a, const  Solution &b, int Objective) {
	if (b.getNormalizationWithConstrainNorm(Objective) > a.getNormalizationWithConstrainNorm(Objective)) {
		return 1;
	}
	else if (b.getNormalizationWithConstrainNorm(Objective) < a.getNormalizationWithConstrainNorm(Objective)) {
		return -1;
	}
	if (a.getID() > b.getID()) {
		return 1;
	}
	else if (a.getID() < b.getID()) {
		return -1;
	}

	return 0;
};

/*

int NSGAII_sp::compareCrowding(const Solution &a, const  Solution &b, int Objective) {
	if (b.getObjective(Objective) > a.getObjective(Objective)) {
		return 1;
	}
	else if (b.getObjective(Objective) < a.getObjective(Objective)) {
		return -1;
	}
	if (a.getID() > b.getID()) {
		return 1;
	}
	else if (a.getID() < b.getID()) {
		return -1;
	}

	return 0;
};
*/

void NSGAII_sp::Sort(Population &d, int objective, int left, int right) {

	int i = left;                      /* ソートする配列の一番小さい要素の添字 */
	int j = right;                     /* ソートする配列の一番大きい要素の添字 */

	Solution pivot = d.get((left + right) / 2); /* 基準値を配列の中央付近にとる */


	while (1) {                    /* 無限ループ */
		while (compareCrowdingWithNormalize(pivot, d.get(i), objective) == 1)       /* pivot より大きい値が */
			i++;                   /* 出るまで i を増加させる */
		while (compareCrowdingWithNormalize(d.get(j), pivot, objective) == 1)        /* pivot より小さい値が */
			j--;                   /*  出るまで j を減少させる */
		if (i >= j)                /* i >= j なら */
			break;                 /* 無限ループから抜ける */
		std::swap(d.get(i), d.get(j));
		i++;                       /* 次のデータ */
		j--;
	}

	if (left < i - 1)              /* 基準値の左に 2 以上要素があれば */
		Sort(d, objective, left, i - 1);     /* 左の配列を Q ソートする */
	if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
		Sort(d, objective, j + 1, right);    /* 右の配列を Q ソートする */
}


void NSGAII_sp::CrowdingDistance(Population &a) {
	for (int i = 0; i< a.size(); i++) {
		a.get(i).setCrowdingDistance(0.0);
	}
	a.setID();
	int Objectives = a.get(0).getNumberOfObjectives();
	double max, min;
	double em;
	for (int key = 0; key< Objectives; key++) {
		Sort(a, key, 0, a.size() - 1);

		a.get(0).setCrowdingDistance(DBL_MAX);
		a.get(a.size() - 1).setCrowdingDistance(DBL_MAX);
		min = a.get(a.size() - 1).getNormalizationWithConstrainNorm(key);
		max = a.get(0).getNormalizationWithConstrainNorm(key);
		if (max - min < 1.0E-14) {
			continue;
		}
		for (int n = 1; n < a.size() - 1; n++) {
			em = a.get(n).getCrowdingDistance();
			em += (a.get(n - 1).getNormalizationWithConstrainNorm(key) - a.get(n + 1).getNormalizationWithConstrainNorm(key)) / (max - min);
			a.get(n).setCrowdingDistance(em);
		}
	}
}









#include"OCIsland.h"
#include"Operator.h"
#include"MT.h"
#include"Ranking.h"
#include<direct.h>
#include<sstream>
#include"Misc.h"
#include"Setting.h"

OCIsland::OCIsland(Problem *d, Setting &test) {
	problem = d;
	setting_ = test;
}

void OCIsland::initialization() {
	for (int land = 0; land<numberOfOCIsland; land++) {
		for (int p = 0; p < populationSize[land]; p++) {
			Solution a(problem);
			problem->repair(a);
			problem->evaluate(a);
			population_[land].add(a);
			evaluation_++;
		}
	}
}



void OCIsland::setting(int d) {
	evaluation_ = 0;
	maxEvaluations = setting_.getAsInt("maxEvaluation");
	cout << maxEvaluations;
	rmp = setting_.getAsDouble("rmp");
	numberOfOCIsland = setting_.getAsInt("numberOfOCIsland");
	population_.resize(numberOfOCIsland);
	offSpring_.resize(numberOfOCIsland);
	populationSize.resize(numberOfOCIsland);
	numberOfParents = setting_.getAsInt("numberOfParents");
	for (int i = 0; i < numberOfOCIsland; i++) {
		populationSize[i] = setting_.getAsInt("populationSize" + to_string(i + 1));
		offSpring_[i] = Population(populationSize[i]);
		population_[i] = Population(populationSize[i]);
	}
	directory = "result/OCIsland/" + problem->getName() + "/" + to_string(problem->getNumberOfObjective()) + "OBJ/" + to_string(d);
	CrossoverProbablity = setting_.getAsDouble("CrossoverProbability");
	MutationProbablity = setting_.getAsDouble("MutationProbability");
	MutationDistribution = setting_.getAsDouble("MutationDistribution");;
	isMAX_ = setting_.getAsBool("isMAX");
	crossoverName = setting_.getAsStr("Crossover");
	parameter_.resize(1);
	CrossoverDistribution = setting_.getAsDouble("CrossoverDistribution");
	parameter_[0] = CrossoverDistribution;
	MakeDirectory();
	setting_.Subscript(directory + "/setting/setting.ini");
}

Solution &OCIsland::binaryTounament(int time) {
		return  population_[time].get(binaryTounament(population_[time]));
}

/*
int OCIsland::binaryTounament_base(int time) {

if (time == 0) {

}
else {

}


return 0;
}
*/


bool OCIsland::makeOffSpring() {

	for (int land = 0; land < numberOfOCIsland; land++) {
		offSpring_[land].clear();
		vector<Solution> child(2);
		vector<Solution> parents(2);
		for (int p = 0; p < populationSize[land]; p++) {
			parents[0] = binaryTounament(land);
			parents[1] = binaryTounament(land);

			Crossover(crossoverName, parents, child, CrossoverProbablity, parameter_);
			int rand_ = (genrand_int31() % child.size());
			CrossoverMutation(child[rand_], binaryTounament((land + 1) % 2), MutationProbablity, MutationDistribution);
			problem->repair(child[rand_]);
			problem->evaluate(child[rand_]);
			evaluation_++;
			offSpring_[land].add(child[rand_]);
			if (evaluation_ == maxEvaluations) {
				return false;
			}
		}
	}
	return true;
}


void OCIsland::MakeDirectory() {
	MakeDirectory(directory + "/Setting");
	MakeDirectory(directory + "/" + "ALL" + "/FUNAKOSHISTYLE");
	for (int i = 0; i < numberOfOCIsland ; i++) {
		MakeDirectory(directory + "/" + "Island" + to_string(i + 1) + "/FUNAKOSHISTYLE");
		MakeDirectory(directory + "/" + "Island" + to_string(i + 1) + "/FeasibleFUN");
		MakeDirectory(directory + "/" + "Island" + to_string(i + 1) + "/InFeasibleFUN");
		MakeDirectory(directory + "/" + "Island" + to_string(i + 1) + "/ALLFUN");
		MakeDirectory(directory + "/" + "Island" + to_string(i + 1) + "/ALLVAR");
		MakeDirectory(directory + "/" + "Island" + to_string(i + 1) + "/FeasibleVAR");
		MakeDirectory(directory + "/" + "Island" + to_string(i + 1) + "/InFeasibleVAR");
	}
}


void OCIsland::MakeDirectory(string name) {
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

int OCIsland::binaryTounament(Population &pop) {
	int size = pop.size();
	int one = genrand_int32() % size;
	int two = genrand_int32() % size;
	while (one == two) {
		two = genrand_int32() % size;
	}
	if (compare(pop.get(one), pop.get(two)) == 1) {
		return one;
	}
	else {
		return two;
	}
}
int OCIsland::compare(const Solution &one, const Solution &two) {

	if (one.getRank() < two.getRank()) {
		return 1;
	}
	else if (one.getRank() > two.getRank()) {
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


void OCIsland::execute(int time) {

	bool flag = true;

	setting(time);

	initialization();


	int generation = 1;


	for (int land = 0; land<numberOfOCIsland; land++) {
		population_[land].SubscriptFunakoshiStyle(time, directory + "/ALL/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");
		population_[land].SubscriptObjectiveToFile(directory + "/" + "Island" + to_string(land + 1) + "/ALLFUN/InitialFUN" + to_string(generation) + ".dat");
		population_[land].SubscriptFeasibeObjectiveToFile(directory + "/" + "Island" + to_string(land + 1) + "/FeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
		population_[land].SubscriptInFeasibeObjectiveToFile(directory + "/" + "Island" + to_string(land + 1) + "/InFeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
		population_[land].SubscriptFunakoshiStyle(time, directory + "/" + "Island" + to_string(land + 1) + "/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");
	}


	do {
		cout << ++generation << "gen" << endl;
		flag = makeOffSpring();
		for (int land = 0; land<numberOfOCIsland; land++) {
			offSpring_[land].SubscriptFunakoshiStyle(time, directory + "/ALL/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");
			offSpring_[land].SubscriptObjectiveToFile(directory + "/" + "Island" + to_string(land + 1) + "/ALLFUN/InitialFUN" + to_string(generation) + ".dat");
			offSpring_[land].SubscriptFeasibeObjectiveToFile(directory + "/" + "Island" + to_string(land + 1) + "/FeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
			offSpring_[land].SubscriptInFeasibeObjectiveToFile(directory + "/" + "Island" + to_string(land + 1) + "/InFeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
			offSpring_[land].SubscriptFunakoshiStyle(time, directory + "/" + "Island" + to_string(land + 1) + "/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");
		}
		selectEnvironment();


	} while (flag);

	generation++;
	/*	for (int land = 0; land<numberOfOCIsland; land++) {
	offSpring_[land].SubscriptObjectiveToFile(directory + "/ALLFUN/InitialFUN" + to_string(generation) + ".dat");
	offSpring_[land].SubscriptFeasibeObjectiveToFile(directory + "/FeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
	offSpring_[land].SubscriptInFeasibeObjectiveToFile(directory + "/InFeasibleFUN/InitialFUN" + to_string(generation) + ".dat");
	population_[land].SubscriptFunakoshiStyle(time, directory + "/" + "OCIsland" + to_string(land + 1) + "/FUNAKOSHISTYLE/" + to_string(time) + "_" + to_string(generation) + "gen.dat");
	}
	*/
}

void OCIsland::selectEnvironment() {

	for (int land = 0; land< numberOfOCIsland; land++) {
		if (land == 0) {
			selectCNSGAII(population_[land], offSpring_[land]);
		}
		else if (land == 1) {
			selectNSGAIIsp(population_[land], offSpring_[land]);
		}
		else {
			ErrorMassage("this model don't consider more than 3 OCIslands");
		}
		/*
		int populationSize = population_[land].size();
		Population merge = Population(population_[land].size() + offSpring_[land].size());
		for (int i = 0; i < population_[land].size(); i++) {
		merge.add(population_[land].get(i));
		}
		for (int i = 0; i < offSpring_[land].size(); i++) {
		merge.add(offSpring_[land].get(i));
		}
		assertion(merge.size() == offSpring_[land].size() + population_[land].size(), " the test is wrong");
		vector<Population> ranking = RankingForConstrain(merge, isMAX_);
		population_[land].clear();
		int rank = 0;
		while (population_[land].size() + ranking[rank].size() < populationSize) {
		CrowdingDistance(ranking[rank]);
		population_[land].merge(ranking[rank]);
		rank++;
		}
		int rest = populationSize - population_[land].size();
		if (rest == 0) continue;
		CrowdingDistance(ranking[rank]);
		SortCrowding(ranking[rank], 0, ranking[rank].size() - 1);

		int size = ranking[rank].size();

		for (int i = 0; i < size - rest; i++) {
		ranking[rank].poplast();
		}
		CrowdingDistance(ranking[rank]);

		for (int i = 0; i < ranking[rank].size(); i++) {
		population_[land].add(ranking[rank].get(i));
		}
		assertion(population_[land].size() == populationSize, "the two population is wrong " + to_string(population_[land].size()) + "	" + to_string(populationSize));
		*/
	}
}

void OCIsland::selectNSGAIIsp(Population &currentPopulation, Population &child) {
	int populationSize = currentPopulation.size();
	Population merge = Population(currentPopulation.size() + child.size());
	for (int i = 0; i < currentPopulation.size(); i++) {
		merge.add(currentPopulation.get(i));
	}
	for (int i = 0; i < child.size(); i++) {
		merge.add(child.get(i));
	}
	merge.NormalizationWithConstrain(isMAX_);
	vector<Population> ranking = RankingForConstrainNSGAIIsp(merge, isMAX_);

	//	vector<Population> ranking = RankingForConstrain(merge_, isMAX_);

	currentPopulation.clear();
	int rank = 0;
	while (currentPopulation.size() + ranking[rank].size() <= populationSize) {
		CrowdingDistanceForNSGAIIsp(ranking[rank]);
		currentPopulation.merge(ranking[rank]);
		rank++;
	}

	int rest = populationSize - currentPopulation.size();

	if (rest == 0) return;

	CrowdingDistanceForNSGAIIsp(ranking[rank]);

	SortCrowding(ranking[rank], 0, ranking[rank].size() - 1);



	int size = ranking[rank].size();

	for (int i = 0; i < size - rest; i++) {
		ranking[rank].poplast();
	}
	CrowdingDistanceForNSGAIIsp(ranking[rank]);

	for (int i = 0; i < ranking[rank].size(); i++) {
		currentPopulation.add(ranking[rank].get(i));
	}
}

void  OCIsland::selectCNSGAII(Population &currentPopulation, Population &offSpring) {
	int populationSize = currentPopulation.size();
	Population merge = Population(currentPopulation.size() + offSpring.size());
	for (int i = 0; i < currentPopulation.size(); i++) {
		merge.add(currentPopulation.get(i));
	}
	for (int i = 0; i < offSpring.size(); i++) {
		merge.add(offSpring.get(i));
	}
	//	assertion(merge.size() == offSpring.size() + currentPopulation.size(), " the test is wrong");
	vector<Population> ranking = RankingForConstrain(merge, isMAX_);
	currentPopulation.clear();
	int rank = 0;
	while (currentPopulation.size() + ranking[rank].size() < populationSize) {
		CrowdingDistance(ranking[rank]);
		currentPopulation.merge(ranking[rank]);
		rank++;
	}
	int rest = populationSize - currentPopulation.size();
	if (rest == 0) return;
	CrowdingDistance(ranking[rank]);
	SortCrowding(ranking[rank], 0, ranking[rank].size() - 1);

	int size = ranking[rank].size();

	for (int i = 0; i < size - rest; i++) {
		ranking[rank].poplast();
	}
	CrowdingDistance(ranking[rank]);

	for (int i = 0; i < ranking[rank].size(); i++) {
		currentPopulation.add(ranking[rank].get(i));
	}

}


/*
void OCIsland::selectEnvironment(Population &currentpop,Population &currentOffspring) {

for(int land = 0;land< numberOfOCIsland;land++){
int populationSize = population_[].size();
Population merge = Population(currentpop.size() + currentOffspring.size());

for (int i = 0; i < currentpop.size(); i++) {
merge.add(currentpop.get(i));
}
for (int i = 0; i < currentOffspring.size(); i++) {
merge.add(currentOffspring.get(i));
}
assertion(merge.size() == currentOffspring.size() + currentpop.size(), " the test is wrong");
vector<Population> ranking = RankingForConstrain(merge, isMAX_);
currentpop.clear();
int rank = 0;
while (currentpop.size() + ranking[rank].size() < populationSize) {
CrowdingDistance(ranking[rank]);
currentpop.merge(ranking[rank]);
rank++;
}
int rest = populationSize - currentpop.size();
if (rest == 0) continue;
CrowdingDistance(ranking[rank]);
SortCrowding(ranking[rank], 0, ranking[rank].size() - 1);


int size = ranking[rank].size();

for (int i = 0; i < size - rest; i++) {
ranking[rank].poplast();
}
CrowdingDistance(ranking[rank]);

for (int i = 0; i < ranking[rank].size(); i++) {
currentpop.add(ranking[rank].get(i));
}
assertion(currentpop.size() == populationSize, "the two population is wrong "  + to_string(currentpop.size()) + "	" + to_string(populationSize));
}
}
*/

void OCIsland::SortCrowding(Population &d, int left, int right) {
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
void OCIsland::Sort(Population &d, int objective, int left, int right) {

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
Sort(d, objective, left, i - 1);
if (j + 1 < right)
Sort(d, objective, j + 1, right);
}
*/
int OCIsland::compareCrowding(const Solution &a, const  Solution &b, int Objective) {
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



void OCIsland::Sort(Population &d, int objective, int left, int right) {

	int i = left;                      /* ソートする配列の一番小さい要素の添字 */
	int j = right;                     /* ソートする配列の一番大きい要素の添字 */

	Solution pivot = d.get((left + right) / 2); /* 基準値を配列の中央付近にとる */


	while (1) {                    /* 無限ループ */
		while (compareCrowding(pivot, d.get(i), objective) == 1)       /* pivot より大きい値が */
			i++;                   /* 出るまで i を増加させる */
		while (compareCrowding(d.get(j), pivot, objective) == 1)        /* pivot より小さい値が */
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


void OCIsland::CrowdingDistance(Population &a) {
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
		min = a.get(a.size() - 1).getObjective(key);
		max = a.get(0).getObjective(key);
		if (max - min < 1.0E-14) {
			continue;
		}
		for (int n = 1; n < a.size() - 1; n++) {
			em = a.get(n).getCrowdingDistance();
			em += (a.get(n - 1).getObjective(key) - a.get(n + 1).getObjective(key)) / (max - min);
			a.get(n).setCrowdingDistance(em);
		}
	}
}


void OCIsland::CrowdingDistanceForNSGAIIsp(Population &a) {
	for (int i = 0; i< a.size(); i++) {
		a.get(i).setCrowdingDistance(0.0);
	}

	a.setID();
	int Objectives = a.get(0).getNumberOfObjectives();
	double max, min;
	double em;
	for (int key = 0; key< Objectives; key++) {
		SortNSGAIIsp(a, key, 0, a.size() - 1);

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



void OCIsland::SortNSGAIIsp(Population &d, int objective, int left, int right) {

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
		SortNSGAIIsp(d, objective, left, i - 1);     /* 左の配列を Q ソートする */
	if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
		SortNSGAIIsp(d, objective, j + 1, right);    /* 右の配列を Q ソートする */
}

int OCIsland::compareCrowdingWithNormalize(const Solution &a, const  Solution &b, int Objective) {
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
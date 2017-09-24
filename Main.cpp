#include<iostream>
#include"Problem.h"
#include"NSGAII.h"
#include<map>
#include"MyNSGAII_sp.h"
#include"ProblemToolbox.h"
#include"MT.h"
#include"Ranking.h"
#include"Setting.h"
#include"Island.h"
#include"OCIsland.h"
#include"OCWMIsland.h"
#include"NSGAIIsp.h"

int  main(int argc,char** argv){
	int seed;
	Setting  setting;
	string name = "test.st";
	setting.ComamandLineReading(argc, argv);
	setting.FileReading(name);
	seed = setting.getAsInt("seed");
	int nowTrial = setting.getAsInt("nowTrial");
	init_genrand(seed);
	int trial_ = setting.getAsInt("trial");
	bool stop = setting.getAsBool("stop");
	string pname = setting.getAsStr("Problem");
	string AlgorithmName = setting.getAsStr("AlgorithmName");
	Problem *p;


	for(int i=0;i<trial_ ;i++){		

		cout << "‘æ " << nowTrial + i << "‰ñ–Ú" << endl;;
		init_genrand(seed + nowTrial + i);
		p = getProblem(pname, setting);

		if (AlgorithmName == "CNSGAII") {
			NSGAII* nsgaii;
			nsgaii = new NSGAII(p, setting);
			nsgaii->execute(nowTrial + i);
			delete p;
			delete nsgaii;
		}
		else if (AlgorithmName == "NSGAII_sp") {
			NSGAIIsp* nsgaiisp;
			nsgaiisp = new NSGAIIsp(p, setting);
			nsgaiisp->execute(nowTrial + i);
			delete p;
			delete nsgaiisp;
		}
		else if (AlgorithmName == "NewNSGAII_sp") {
			NewNSGAII_sp* nsgaiisp;
			nsgaiisp = new NewNSGAII_sp(p, setting);
			nsgaiisp->execute(nowTrial + i);
			delete p;
			delete nsgaiisp;
		}
		else if (AlgorithmName == "Island") {
			Island *island;
			island = new Island(p, setting);
			island->execute(nowTrial + i);
		}
		else if (AlgorithmName == "OCIsland") {
			OCIsland *island;
			island = new OCIsland(p, setting);
			island->execute(nowTrial + i);
		}
		else if (AlgorithmName == "OCWMIsland") {
			OCWMIsland *island;
			island = new OCWMIsland(p, setting);
			island->execute(nowTrial + i);
		}

		else if (AlgorithmName == "test") {
			NSGAII* nsgaii;
			nsgaii = new NSGAII(p, setting);
			nsgaii->config();
			delete p;
			delete nsgaii;
		}
		else {
				ErrorMassage("the algorithm name " + AlgorithmName + " was not found" );
		}
	}
	
	int test = 0;
	std::cout << "ŽÀŒøI—¹";
	
	if(stop)
		std::cin >> test;


	return 0;
}


void NSGAII::config() {

	Solution a(2);
	Population pop(30);

	a.setObjective(0, 18);
	a.setObjective(1, 18);
	pop.add(a);
	a.setObjective(0, 18);
	a.setObjective(1, 18);
	pop.add(a);
	a.setObjective(0, 12);
	a.setObjective(1, 18);
	pop.add(a);
	a.setObjective(0, 16);
	a.setObjective(1, 16);
	pop.add(a);
	a.setObjective(0, 18);
	a.setObjective(1, 12);
	pop.add(a);
	a.setObjective(0, 10);
	a.setObjective(1, 16);
	pop.add(a);
	a.setObjective(0, 14);
	a.setObjective(1, 14);
	pop.add(a);
	a.setObjective(0, 15);
	a.setObjective(1, 9);
	pop.add(a);
	a.setObjective(0, 18);
	a.setObjective(1, 6);
	pop.add(a);
	a.setObjective(0, 4);
	a.setObjective(1, 14);
	pop.add(a);
	a.setObjective(0, 9);
	a.setObjective(1, 13);
	pop.add(a);
	a.setObjective(0, 12);
	a.setObjective(1, 11);
	pop.add(a);
	a.setObjective(0, 16);
	a.setObjective(1, 4);
	pop.add(a);
	a.setObjective(0, 2);
	a.setObjective(1, 12);
	pop.add(a);
	a.setObjective(0, 8);
	a.setObjective(1, 10);
	pop.add(a);
	a.setObjective(0, 12);
	a.setObjective(1, 8);
	pop.add(a);
	a.setObjective(0, 14);
	a.setObjective(1, 4);
	pop.add(a);
	a.setObjective(0, 16);
	a.setObjective(1, 0);
	pop.add(a);
	a.setObjective(0, 2);
	a.setObjective(1, 8);
	pop.add(a);
	a.setObjective(0, 6);
	a.setObjective(1, 6);
	pop.add(a);
	a.setObjective(0, 10);
	a.setObjective(1, 2);
	pop.add(a);
	a.setObjective(0, 10);
	a.setObjective(1, 2);
	pop.add(a);
	a.setObjective(0, 10);
	a.setObjective(1, 2);
	pop.add(a);
	a.setObjective(0, 2);
	a.setObjective(1, 2);
	pop.add(a);

	
	vector<Population> d = RankingForConstrain(pop, false);
	for (int i = 0; i < d.size(); i++) {
		
		CrowdingDistance(d[i]);
		for (int ia = 0; ia < d[i].size(); ia++) {
			cout << d[i].get(ia).getObjective(0) << "	" << d[i].get(ia).getObjective(1) << "	" << i+1 << "rank	" << d[i].get(ia).getCrowdingDistance() << endl;;
		}
		cout << endl;
		cout << endl;

	}
	int string_ = 0;
	cin >> string_;

	//pop.SubscriptAllObjective();

	

}



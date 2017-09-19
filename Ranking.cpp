#include"Ranking.h"
#include"Solution.h"
#include<math.h>
#include"Global.h"
#include<time.h>
#include"Setting.h"


int ComparatorForRanking(Solution &one, Solution &two, bool isMAX_) {

	int d = one.getNumberOfObjectives();
	for (int i = 0; i<d; i++) {
		if (fabs(one.getObjective(i) - two.getObjective(i)) > 1.0E-14) {
			if ((isMAX_) == (one.getObjective(i) < two.getObjective(i))) {
				return 1;
			}
			else {
				return -1;
			}
		}
	}
	return 0;

}
/*
void sort(Population &d,bool isMAX_) {
for (int i = 0; i < d.size(); i++) {
for (int ia = d.size()-1; ia >i ; ia--) {
if (ComparatorForRanking(d.get(i), d.get(ia), isMAX_) == 1) {
std::swap(d.get(i), d.get(ia));
}
}
}
}

*/
void quickSortForRanking(Population &d, int left, int right, bool isMAX_) {

	int i = left;                      /* ソートする配列の一番小さい要素の添字 */
	int j = right;                     /* ソートする配列の一番大きい要素の添字 */


	int  pivot = (left + right) / 2; /* 基準値を配列の中央付近にとる */

	while (1) {                    /* 無限ループ */

		while (ComparatorForRanking(d.get(pivot), d.get(i), isMAX_) == 1) /* pivot より大きい値が */
			i++;                   /* 出るまで i を増加させる */

		while (ComparatorForRanking(d.get(j), d.get(pivot), isMAX_) == 1)       /* pivot より小さい値が */
			j--;                   /*  出るまで j を減少させる */
		if (i >= j)                /* i >= j なら */
			break;                 /* 無限ループから抜ける */

		std::swap(d.get(i), d.get(j));
		i++;                       /* 次のデータ */
		j--;
	}

	if (left < i - 1)              /* 基準値の左に 2 以上要素があれば */
		quickSortForRanking(d, left, i - 1, isMAX_);     /* 左の配列を Q ソートする */
	if (j + 1 <  right)            /* 基準値の右に 2 以上要素があれば */
		quickSortForRanking(d, j + 1, right, isMAX_);    /* 右の配列を Q ソートする */
}

int isDominanceForMAX(const Solution &me, const  Solution &you);
int isDominanceForMIN(const Solution &me, const  Solution &you);

int isDominanceForMAXForNSGAIIsp(const Solution &me, const  Solution &you);
int isDominanceForMINForNSGAIIsp(const Solution &me, const  Solution &you);

int isDominanced(const Solution &me, const  Solution &you, bool isMAX_) {

	if (isMAX_) {
		return isDominanceForMAX(me, you);
	}
	else {
		return isDominanceForMIN(me, you);
	}
}

int RankingSolution(Solution &sol, vector<Population> &object, bool isMAX_) {
	int x = object.size() - 1;
	int k = 0;
	bool flag = true;
	while (true) {
		flag = true;
		for (int i = object[k].size() - 1; i >= 0; i--) {
			if (isDominanced(object[k].get(i), sol, isMAX_) == 1) {
				flag = false;
				break;
			}
		}

		if (flag) {
			return k;
		}
		else {
			k++;
			if (k > x) {
				return x + 1;
			}
		}
	}
}

vector<Population> Ranking(Population& pop, bool isMAX_) {
	pop.setID();
	quickSortForRanking(pop, 0, pop.size() - 1, isMAX_);
	vector<Population> object(0);
	Population eee(pop.size());

	pop.get(0).setRank(1);
	eee.add(pop.get(0));
	object.push_back(eee);


	for (int i = 1; i < pop.size(); i++) {
		int k = RankingSolution(pop.get(i), object, isMAX_);
		if (object.size() == k) {
			Population d(pop.size() - i);
			object.push_back(d);
			pop.get(i).setRank(k + 1);
			object[k].add(pop.get(i));
		}
		else {
			pop.get(i).setRank(k + 1);
			object[k].add(pop.get(i));
		}
	}
	return object;
};


int isDominanceForMAX(const Solution &me, const  Solution &you) {
	int size = me.getNumberOfObjectives();
	for (int i = 0; i< size; i++) {
		if (me.getObjective(i) < you.getObjective(i)) {
			return -1;
		}
	}
	for (int i = 0; i< size; i++) {
		if (me.getObjective(i) > you.getObjective(i)) {
			return 1;
		}
	}
	return 0;
}

int isDominanceForMIN(const Solution &me, const  Solution &you) {
	int size = me.getNumberOfObjectives();
	for (int i = 0; i< size; i++) {
		if (me.getObjective(i) > you.getObjective(i)) {
			return -1;
		}
	}

	for (int i = 0; i< size; i++) {
		if (me.getObjective(i) < you.getObjective(i)) {
			return 1;
		}
	}
	return 0;
}



int CompareTwoSolution_NDS(Solution &one, Solution &two, bool isMAX_) {
	if (!one.getFiesible() && two.getFiesible()) {
		return -1;
	}
	else if (one.getFiesible() && !two.getFiesible()) {
		return 1;
	}
	else if (one.getFiesible() && two.getFiesible()) {
		return isDominanced(one, two, isMAX_);
	}
	else if (!one.getFiesible() && !two.getFiesible()){

		if (one.getViolation() > two.getViolation()) {
			return -1;
		}
		else if (one.getViolation() < two.getViolation()) {
			return 1;
		}
		else {
			return 0;
		}

	}
	else {
		ErrorMassage("そんな状態はない");
	}
}



int isDominancedForNSGAIIsp(const Solution &me, const  Solution &you, bool isMAX_) {

	if (isMAX_) {
		return isDominanceForMAXForNSGAIIsp(me, you);
	}
	else {
		return isDominanceForMINForNSGAIIsp(me, you);
	}
}


int isDominanceForMAXForNSGAIIsp(const Solution &me, const  Solution &you) {
	int size = me.getNumberOfObjectives();
	for (int i = 0; i< size; i++) {
		if (me.getNormalizationWithConstrainNorm(i) < you.getNormalizationWithConstrainNorm(i)) {
			return -1;
		}
	}
	for (int i = 0; i< size; i++) {
		if (me.getNormalizationWithConstrainNorm(i) > you.getNormalizationWithConstrainNorm(i)) {
			return 1;
		}
	}
	return 0;
}

int isDominanceForMINForNSGAIIsp(const Solution &me, const  Solution &you) {
	int size = me.getNumberOfObjectives();
	for (int i = 0; i< size; i++) {
		if (me.getNormalizationWithConstrainNorm(i) > you.getNormalizationWithConstrainNorm(i)) {
			return -1;
		}
	}
	for (int i = 0; i< size; i++) {
		if (me.getNormalizationWithConstrainNorm(i) < you.getNormalizationWithConstrainNorm(i)) {
			return 1;
		}
	}
	return 0;
}



int CompareTwoSolution_NDSForNSGAIIsp(Solution &one, Solution &two, bool isMAX_) {
	return isDominancedForNSGAIIsp(one, two, isMAX_);
}

vector<Population> RankingForConstrain(Population &mg, bool isMAX) {
	std::vector<int> Sp_;
	std::vector<int> F_i;
	int size = mg.size();
	std::vector<int >Np_(size);
	std::vector<std::vector<int> >	Sp_all;
	std::vector<std::vector<int> >	F_all;

	for (int p = 0; p < size; p++) {
		Sp_.clear();
		Np_[p] = 0;
		for (int q = 0; q < size; q++) {
			if (CompareTwoSolution_NDS(mg.get(p), mg.get(q), isMAX) == 1) {
				Sp_.push_back(q);
			}
			else if (CompareTwoSolution_NDS(mg.get(q), mg.get(p), isMAX) == 1) {
				Np_[p] = Np_[p] + 1;
			}
		}
		if (Np_[p] == 0) {
			mg.get(p).setRank(1);
			F_i.push_back(p);
		}
		Sp_all.push_back(Sp_);
	}

	int i = 1;
	std::vector<int> Q(0);
	F_all.push_back(F_i);
	while (F_i.size() != 0) {
		Q.clear();

		for (int j = 0; j < F_i.size(); j++) {
			int p = F_i[j];
			std::vector<int> Sp(Sp_all[p]);
			for (int k = 0; k < Sp.size(); k++) {
				int q = Sp[k];
				Np_[q] = Np_[q] - 1;
				if (Np_[q] == 0) {
					mg.get(q).setRank(i + 1);
					Q.push_back(q);
				}
			}
		}
		i = i + 1;
		F_i = Q;
		F_all.push_back(F_i);
	}

	std::vector<Population> ret(0);
	ret.clear();

	for (int i = 0; i < F_all.size(); i++) {
		Population d(F_all[i].size());
		std::vector<int> ind = F_all[i];
		for (int ja = 0; ja < ind.size(); ja++) {
			d.add(mg.get(ind[ja]));
		}
		if (ind.size() != 0) {
			ret.push_back(d);
		}
	}
	return ret;
}

vector<Population> RankingForConstrainNSGAIIsp(Population &mg, bool isMAX) {
	std::vector<int> Sp_;
	std::vector<int> F_i;
	int size = mg.size();
	std::vector<int >Np_(size);
	std::vector<std::vector<int> >	Sp_all;
	std::vector<std::vector<int> >	F_all;

	for (int p = 0; p < size; p++) {
		Sp_.clear();
		Np_[p] = 0;
		for (int q = 0; q < size; q++) {
			if (CompareTwoSolution_NDSForNSGAIIsp(mg.get(p), mg.get(q), isMAX) == 1) {
				Sp_.push_back(q);
			}
			else if (CompareTwoSolution_NDSForNSGAIIsp(mg.get(q), mg.get(p), isMAX) == 1) {
				Np_[p] = Np_[p] + 1;
			}
		}
		if (Np_[p] == 0) {
			mg.get(p).setRank(1);
			F_i.push_back(p);
		}
		Sp_all.push_back(Sp_);
	}

	int i = 1;
	std::vector<int> Q(0);
	F_all.push_back(F_i);
	while (F_i.size() != 0) {
		Q.clear();

		for (int j = 0; j < F_i.size(); j++) {
			int p = F_i[j];
			std::vector<int> Sp(Sp_all[p]);
			for (int k = 0; k < Sp.size(); k++) {
				int q = Sp[k];
				Np_[q] = Np_[q] - 1;
				if (Np_[q] == 0) {
					mg.get(q).setRank(i + 1);
					Q.push_back(q);
				}
			}
		}
		i = i + 1;
		F_i = Q;
		F_all.push_back(F_i);
	}

	std::vector<Population> ret(0);
	ret.clear();

	for (int i = 0; i < F_all.size(); i++) {
		Population d(F_all[i].size());
		std::vector<int> ind = F_all[i];
		for (int ja = 0; ja < ind.size(); ja++) {
			d.add(mg.get(ind[ja]));
		}
		if (ind.size() != 0) {
			ret.push_back(d);
		}
	}
	return ret;
}



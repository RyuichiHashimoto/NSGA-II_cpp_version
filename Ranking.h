#pragma once

#include"Population.h"



vector<Population> Ranking(Population &,bool);

vector<Population> RankingForConstrain(Population &, bool);


vector<Population> RankingForConstrainNSGAIIsp(Population &, bool);

void quickSortForRanking(Population &, int, int,bool);
#include"Setting.h"
#include<string>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<iostream>
#include"Misc.h"



Setting &Setting::operator=(const Setting &arg){
	map_ = arg.getmap();
	return *(this);
}

//上書き保存はしない
void Setting::add(string s, string m) {
	if(!containKey(s))
		map_[s] = m;
};

//上書き保存をする
void Setting::addForce(string s, string m) {
	map_[s] = m;
};

bool Setting::getAsBool(string name) {
	string abo = get(name);

	std::transform(abo.cbegin(), abo.cend(), abo.begin(), toupper);
	

	if (abo == "TRUE" || abo == "MAX") {
		return true;
	}
	else {
		return false;
	}
}

string Setting::get(string name){
	if (containKey(name)){
		return map_[name];
	}
	else {
		cerr << "error has occurred ：：I crash this program because setting doesn't have \"" << name<<"\"" <<endl;
		cerr << "please put any key if you finish this program" << endl;;
		int error;
		cin >> error;
		exit(-1);
	}
}

int		Setting::getAsInt(string name) {
	return stoi(get(name));
};
double	Setting::getAsDouble(string name) {
	string abo = get(name);
	return stod(abo);
};
string 	Setting::getAsStr(string name) {
	return get(name);
	;
};

bool Setting::containKey(string name) {
	if (map_.find(name) == map_.end()) {
		return false;
	}
	else {
		return true;
	}
}
void    Setting::set(string a, string b) {
	map_[a] = b;
}

void Setting::FileReading(string name) {
		std::ifstream read(name);
		std::string str;
		if (read.fail()) {
			char d;
			std::cerr << "失敗：文字を入力し，終了してください" << std::endl;
			cin >> d;
			exit(-1);
		}
		while (getline(read, str)) {
			std::vector<std::string> fi = split(str, FILEDEMILITER);
			add(fi[0], fi[1]);
		}
}

void Setting::ComamandLineReading( int argc, char** t){	
	for (int i = 1; i < argc; i++){
		if (t[i][0] == OPTIONDEMILITER) {
			string name = t[i];
			string output = t[i+1];
			name.erase(name.begin());
			add(name, output);
		}	
	}
}


void Setting::BaseScript(ofstream &output, string name) {
	if (containKey(name)) {
		output << name << "	" << map_[name] << endl;
		remove(name);
	}
}


void Setting::remove(string name) {
	auto itr = map_.find(name);
	if (itr != map_.end())         // キーの要素が存在している場合
		map_.erase(itr);
}

void Setting::allScript(ofstream &output) {
	for (auto itr = map_.begin(); itr != map_.end(); ++itr) {
		if (itr->first[0] == '-') {
			continue;
		}
		output << itr->first   <<"	"<< itr->second << endl;    // 値を表示
	}
}

void Setting::print() {
	for (auto itr = map_.begin(); itr != map_.end(); ++itr) {
		cout << itr->first << "	" << itr->second << endl;    // 値を表示
	}
}

void Setting::clear() {
	map_.clear();
}

void Setting::Subscript(string name_) {
	ofstream output(name_);
	
	output << "----------------------------Main Property---------------------" << endl;;
	BaseScript(output, "AlgorithmName");
	string name = "Problem";
	BaseScript(output, name);
	name = "NumberOfObjectives";
	BaseScript(output, name);
	 name = "DistanceVariables";
	BaseScript(output, name);
	 name = "populationSize";
	BaseScript(output, name);
	 name = "Crossover";
	BaseScript(output, name);
	 name = "CrossoverProbability";
	BaseScript(output, name);
	 name = "CrossoverDistribution";
	BaseScript(output, name);
	 name = "Mutation";
	BaseScript(output, name);
	 name = "MutationProbablity";
	BaseScript(output, name);
	 name = "MutationDistributionIndex";
	BaseScript(output, name);
	 name = "MutationDistributionIndex";
	BaseScript(output, name);
	 name = "trial";
	BaseScript(output, name);
	BaseScript(output, "seed");

	output << "----------------------------Sub Property---------------------" << endl;;
	allScript(output);
	output.close();
}


void ErrorMassage(string d) {
	std::cerr << d << std::endl;;
	std::cerr << "please put any key to crash this program";
	int dd;
	std::cin >> d;
	std::exit(-1);
}

void assertion(bool d, string name) {
	if (!d) {
		ErrorMassage(name);
	}
}
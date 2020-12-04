#ifndef PLAYERTYPE_H
#define PLAYERTYPE_H
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include<utility>
#include<random>
#include<cassert>
#include "stateType.h"
using namespace std;

class playerType
{
public:
	double step_size;
	double epsilon;
	vector<stateType> states;
	vector<int> greedy;
	int symbol;
	map<int, double> estimations;

	playerType();
	playerType(double step, double eps, int sym, map<int, stateType>& all_states);
	// estimations ~ like dictionary {state_hash: value}
	// step_size ~like learning rate, update estimations
	// epsilon : random exploration probability
	// states: state list(vector)
	// greedy : a list(vector) record action(choice), 1: greedy choice, 0: random choice
	// symbol : 1 | -1 | 
	void reset();
	// reset states
	// reset greedy
	void record_state(stateType s);
	// record state and greddy
	void set_symbol(int sym, map<int, stateType>& all_states);
	// symbol
	void backup();
	// update estimation
	double random_proba();
	// return a proba 0~1
	pair<int,int> action();
	// action choice function
	void save_policy(string path);
	// save policy (estimations dict) as a txt file
	void load_policy(string path);
	// load policy (read txt file)
};

playerType::playerType()
{
	step_size = 0.1;
	epsilon = 0.1;
}

playerType::playerType(double step, double eps, int sym, map<int, stateType>& all_states)
{
	step_size = step;
	epsilon = eps;
	set_symbol(sym, all_states);
}

void playerType::reset()
{
	states.clear();
	greedy.clear();
}

void playerType::record_state(stateType s)
{
	states.push_back(s);
	greedy.push_back(1);
}

void playerType::set_symbol(int sym, map<int,stateType>& all_states)
{
	symbol = sym;
	// all_states : all states a dict {hash_val:state}
	map<int, stateType>::iterator iter;
	int hash_val;
	stateType state;
	for (iter = all_states.begin(); iter != all_states.end(); iter++)
	{
		hash_val = iter->first;
		state = iter->second;
		if (state.is_end())
		{
			if (state.get_winner() == symbol)
				estimations[hash_val] = 1.0;
			else if (state.get_winner() == 0)
				estimations[hash_val] = 0.5;
			else
				estimations[hash_val] = 0;
		}
		else
			estimations[hash_val] = 0.5;
	}
}

void playerType::backup()
{
	double td_error; // 相邻状态间的差值
	stateType state;
	for (int i = states.size()-1; i > 0; i--)
	{
		state = states[i - 1];
		td_error = estimations[states[i].hash()] - estimations[state.hash()];
		td_error *= greedy[i - 1];
		estimations[state.hash()] += step_size * td_error;
	}
}

double playerType::random_proba()
{
	double p;
	mt19937 rng;
	rng.seed(random_device()());
	uniform_real_distribution<double> distribution(0, 1);
	p = distribution(rng);
	return p;
}

pair<int, int> playerType::action()
{
	int i = states.size();
	pair<int, int> act;
	stateType state = states[i - 1];
	vector<stateType> next_states;
	vector<pair<int, int> > next_positions;
	for (int j = 0; j < BOARD_ROWS; j++)
		for (int k = 0; k < BOARD_COLS; k++)
		{
			if (state.data[j][k] == 0)
			{
				next_positions.push_back(make_pair(j, k));
				next_states.push_back(state.next_state(j, k, symbol));
			}
		}
	if (random_proba() < epsilon)
	{
		int I;
		mt19937 rng;
		rng.seed(random_device()());
		uniform_int_distribution<mt19937::result_type> dist(0, next_positions.size() - 1);
		I = dist(rng);
		act = next_positions[I];
		// change greedy last element
		auto& val = greedy.back();
		val = 0;
		return act;
	}
	vector<double> values;
	for (unsigned int l = 0; l < next_states.size(); l++)
		values.push_back(estimations[next_states[l].hash()]);
	vector<double>::iterator biggest = max_element(begin(values), end(values));
	act = next_positions[distance(begin(values), biggest)];  // values vector maxval index
	return act;
}

void playerType::save_policy(string path)
{
	fstream f(path, ios::out);
	map<int, double>::iterator iter;
	for (iter = estimations.begin(); iter != estimations.end(); iter++)
	{
		f << iter->first << ',' << iter->second << "\n";
	}
	f.close();
}

void playerType::load_policy(string path)
{
	map<int, double> estimations_;
	ifstream rfile;
	rfile.open(path.c_str());
	assert(rfile.is_open());
	string line_str;
	while (getline(rfile, line_str))
	{
		stringstream ss(line_str);
		vector<double> temp_vec;
		string temp;
		while (getline(ss, temp, ','))
			// .c_str字符串转换为字符数组
			// atof,字符数组转换为浮点数
			temp_vec.push_back(atof(temp.c_str()));
		estimations[int(temp_vec[0])] = temp_vec[1];
	}
	rfile.close();
	estimations = estimations_;
} 

#endif
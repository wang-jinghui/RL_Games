#ifndef JUDGERTYPE_H
#define JUDGERTYPE_H
#include<iostream>
#include"playerType.h"

using namespace std;

class judgerType
{
public:
	playerType p1, p2;
	vector<stateType> states;

	judgerType(playerType p1, playerType p2);
	void reset();
	// p1.reset(), p2.reset()
	int play(bool is_print_state);
    // true: print_state and return winner
	vector<stateType> get_states();
	// return states
	void clean_states();
};

judgerType::judgerType(playerType p_1, playerType p_2)
{
	p1 = p_1;
	p2 = p_2;
}

void judgerType::reset()
{
	p1.reset();
	p2.reset();
}

int judgerType::play(bool is_print_state)
{
	reset();
	stateType current_state;
	p1.record_state(current_state);
	p2.record_state(current_state);
	if (is_print_state)
		current_state.print_state();
	pair<int, int> act1, act2;
	while (true)
	{
		act1 = p1.action();
		current_state = current_state.next_state(act1.first, act1.second, p1.symbol);
		if (is_print_state)
			current_state.print_state();
		states.push_back(current_state);
		p1.states.push_back(current_state);
		p2.states.push_back(current_state);
		if (current_state.is_end())
			return current_state.get_winner();
		act2 = p2.action();
		current_state = current_state.next_state(act2.first, act2.second, p2.symbol);
		if (is_print_state)
			current_state.print_state();
		states.push_back(current_state);
		p1.states.push_back(current_state);
		p2.states.push_back(current_state);
		if (current_state.is_end())
			return current_state.get_winner();
	}
}

vector<stateType>judgerType::get_states()
{
	return states;
}

void judgerType::clean_states()
{
	states.clear();
}

#endif
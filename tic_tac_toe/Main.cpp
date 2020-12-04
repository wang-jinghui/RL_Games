#include<iostream>
#include<map>
#include<time.h>
#include<iomanip>
#include "humanType.h"
#include "judgerType.h"

using namespace std;

typedef map<int, stateType>  stateDict;

void get_all_states_impl(stateType current_state, int current_symbol, stateDict& all_states)
{
	stateType new_state;
	int new_hash;
	bool is_end;
	for(int i=0; i< BOARD_ROWS; i++)
		for (int j = 0; j < BOARD_COLS; j++)
		{
			if (current_state.data[i][j] == 0)
			{
				new_state = current_state.next_state(i, j, current_symbol);
				new_hash = new_state.hash();
				// all_states中的key值是部重复的,count=0,表示不存在
				if (all_states.count(new_hash) == 0)
				{
					is_end = new_state.is_end();
					all_states[new_hash] = new_state;
					if (is_end == false)
						current_symbol = current_symbol * (-1);
						get_all_states_impl(new_state, current_symbol, all_states);
				}
			}
		}
}

void play(humanType p1, playerType p2)
{
	stateType  current_state;
	current_state.print_state();
	pair<int, int> act1, act2;
	while (true)
	{
		act1 = p1.action();
		current_state = current_state.next_state(act1.first, act1.second, p1.symbol);
		p2.record_state(current_state);
		if (current_state.is_end())
		{
			cout << "winner is :" << current_state.get_winner() << endl;
			current_state.print_state();
			break;
		}
		act2 = p2.action();
		current_state = current_state.next_state(act2.first, act2.second, p2.symbol);
		current_state.print_state();
		p2.record_state(current_state);
		if (current_state.is_end())
		{
			cout << "winner is :" << current_state.get_winner() << endl;
			break;
		}
	}
}

int main()
{
	stateType current_state;
	stateDict all_states;
	get_all_states_impl(current_state, 1, all_states);
	playerType p1(0.1, 0.1, -1, all_states);
	playerType p2(0.1, 0.1,  1, all_states);
	int winner;
	map<int, double> scoreboard;
	scoreboard[-1] = 0;
	scoreboard[1] = 0;
	judgerType judger(p1, p2);
	for (int i = 0; i < 50000; i++)
	{
		winner = judger.play(false);
		judger.clean_states();
		scoreboard[winner] += 1;
		if (((i % 1000) == 0)and(i>0))
			cout << "Epoch  :" << i << "    , p1 winrate :  " <<setprecision(3)<< scoreboard[p1.symbol] / i<< "  p2 winrate : " <<setprecision(3)<< scoreboard[p2.symbol] / i << endl;
		p1.backup();
		p2.backup();
	}
	p1.save_policy("X:\\rl_policy\\p1_policy.txt");
	p2.save_policy("X:\\rl_policy\\p2_policy.txt");
    // human vs p1
	humanType wjh(1);  // symbol = 1
	play(wjh, p1);
}

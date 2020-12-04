#ifndef STATETYPE_H
#define STATETYPE_H
#include<iostream>
#include<vector>
#include<map>
using namespace std;

const int BOARD_ROWS = 3;
const int BOARD_COLS = 3;
const int BOARD_SIZE = BOARD_COLS * BOARD_ROWS;

class stateType
{
private:
	int winner;
	int hash_val;
	bool end;

public:
	int data[BOARD_ROWS][BOARD_COLS];
	stateType();
	// initial data = zeros(BOARD_ROWS, BOARD_COLS)
	// winner = 0, hash_val = 0, end = 0;
	int hash();
	// calculate data's hash value and return
	bool is_end();
	//  Check  the game state
	// over or not over
	stateType next_state(int x, int y, int symbol);
	// x, y : symbol's position (state(data))
	// return new_date
	void print_state();
	// print state
	int* get_state();
	// return state array (data)
	int get_winner();
	// return winner
};

stateType::stateType()
{
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS; j++)
		{
			data[i][j] = 0;
		}
	}
	winner = 0;
	hash_val = 0;
	end = false;
}

int stateType::hash()
{
	for (int i = 0; i < BOARD_COLS; i++)
	{
		for (int j = 0; j < BOARD_COLS; j++)
		{
			hash_val = hash_val * 3 + data[i][j] + 1;
		}
	}
	return hash_val;
}

bool stateType::is_end()
{
	vector<int> results;
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		int sum = 0;
		for (int j = 0; j < BOARD_COLS; j++)
			sum += data[i][j];
		results.push_back(sum);
	}
	for (int i = 0; i < BOARD_COLS; i++)
	{
		int sum = 0;
		for (int j = 0; j < BOARD_ROWS; j++)
			sum += data[j][i];
		results.push_back(sum);
	}

	int trace = 0;
	int reverse_trace = 0;
	for (int i = 0; i < BOARD_COLS; i++)
		trace += data[i][i];
	results.push_back(trace);

	for (int i = 0; i < BOARD_COLS; i++)
		reverse_trace += data[i][BOARD_COLS - i - 1];
	results.push_back(reverse_trace);

	for (unsigned int i = 0; i < results.size(); i++)
	{
		if (results[i] == 3)
		{
			winner = 1;
			end = true;
			return end;
		}
		if (results[i] == -3)
		{
			winner = -1;
			end = true;
			return end;
		}
	}
	// ps
	int sum_values = 0;
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS; j++)
			sum_values += abs(data[i][j]);
	}
	if (sum_values == BOARD_SIZE)
	{
		winner = 0;
		end = true;
		return end;
	}
	end = false;
	return end;
}

stateType stateType::next_state(int r, int c, int sym)
{
	stateType new_state;
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		for (int j = 0; j < BOARD_COLS; j++)
		{
			new_state.data[i][j] = data[i][j];
		}
	}
	new_state.data[r][c] = sym;
	return new_state;
}

void stateType::print_state()
{
	for (int i = 0; i < BOARD_ROWS; i++)
	{
		cout << "-------------" << endl;
		string out = "| ";
		string token;
		for (int j = 0; j < BOARD_COLS; j++)
		{
			if (data[i][j] == 1)
				token = "O";
			else if (data[i][j] == -1)
				token = "X";
			else
				token = " ";
			out += token + " | ";
		}
		cout << out << endl;
	}
	cout << "-------------" << endl;
}

int * stateType::get_state()
{
	return *data;
}

int stateType::get_winner()
{
	return winner;
}

#endif
#ifndef HUMANTYPE_H
#define HUMANTYPE_H
#include<iostream>
#include<map>
#include"playerType.h"
using namespace std;

class humanType
{
public:
	int symbol;
	map<char, pair<int, int> > action_dict;

	humanType(int sym);
	pair<int, int> action();
	// return action
};

humanType::humanType(int sym)
{
	symbol = sym;
	action_dict['q'] = make_pair(0, 0);
	action_dict['w'] = make_pair(0, 1);
	action_dict['e'] = make_pair(0, 2);
	action_dict['a'] = make_pair(1, 0);
	action_dict['s'] = make_pair(1, 1);
	action_dict['d'] = make_pair(1, 2);
	action_dict['z'] = make_pair(2, 0);
	action_dict['x'] = make_pair(2, 1);
	action_dict['c'] = make_pair(2, 2);
}

pair<int, int> humanType::action()
{
	char key = getchar();
	rewind(stdin); // ��������
	// �����enter�ᱻ����������������
	// ִ�е�һ��������,����ȵڶ�������,����ִ�л������еĵڶ�������
	// ���ڵڶ�������ʱ'\n',action_dict�в鲻��,Ĭ�Ϸ��ص�һ������
	pair<int, int> act = action_dict[key];
	return act;
}

#endif
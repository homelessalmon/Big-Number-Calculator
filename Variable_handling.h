#pragma once
#include<vector>
#include<string>
#include"NumberObject.h"

using namespace std;

class Variable_list
{
public:
	//variable
	vector<string> variable_name_I;
	vector<Integer> Number_I;
	vector<string> variable_name_D;
	vector<Decimal> Number_D;
	//function
	void push_pack(string name,NumberObject number);
	int find(string name);//return index
};
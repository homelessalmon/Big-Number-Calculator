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
	void push_pack(string name, Integer number);
	void push_pack(string name, Decimal number);
	int find(string name);//return index ,index for int 0~100 ,decimal 101~200
	void del_var(string name);//delete variable
};

#pragma once
#include<vector>
#include<string>
#include"NumberObject.h"
#include"Variable_handling.h"

using namespace std;

class Big_tree_calculator
{
public:

	//variable
	Variable_list list;
	//function
	void exe();
};
NumberObject string_process(string input);
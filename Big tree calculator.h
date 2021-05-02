#pragma once
#include<vector>
#include<string>
#include"NumberObject.h"
#include"Variable_handling.h"

using namespace std;

class Big_tree_calculator {
public:

	//variable
	Variable_list variableList;
	//function
	void exe();
	void string_process(string);
	NumberObject value_process(string input);
	friend void string_segmentation(string, vector<string>&, string, char);
	friend int order_of(const string&, char, int);
	friend int formula_factorial(string& formula, vector<Integer>& intlist, vector<Decimal>& declist);
	friend int formula_power(string&, vector<Integer>&, vector<Decimal>&);
	friend int formula_sign(string&, vector<Integer>&, vector<Decimal>&);
	friend int formula_muldiv(string&, vector<Integer>&, vector<Decimal>&);
	friend int formula_addsub(string&, vector<Integer>&, vector<Decimal>&);
	friend int positivity(string);
};

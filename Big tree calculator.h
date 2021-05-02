#pragma once
#include<vector>
#include<string>
#include"NumberObject.h"
#include"Variable_handling.h"
#define TEST1 1

using namespace std;

class Big_tree_calculator
{
public:

	//variable
	Variable_list variableList;
	//function
	void exe()
	{
		string input;
		getline(cin, input);
		string_process(input);
	}
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

//剛剛把下面這堆移到這邊才能過
#if TEST1
int order_of(const string& formula, char type, int pos) {
	int order = 0;
	for (int i = 0; i < pos; i++) { //這是第幾個n
		if (formula[i] == type) {
			order++;
		}
	}
	return order;
}

int formula_factorial(string& formula, vector<Integer>& intlist, vector<Decimal>& declist) {
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '!') {
			if (formula[i - 1] == 'i') {
				int order = order_of(formula, 'i', i - 1);
				intlist[order] = factorial(intlist[order]);
				formula.erase(i, 1); //把運算完的運算子清除
				i--;
			}
			else if (formula[i - 1] == 'd') {
				int order = order_of(formula, 'd', i - 1);
				declist[order] = factorial(declist[order]);
				formula.erase(i, 1); //把運算完的運算子清除
				i--;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}


int formula_power(string& formula, vector<Integer>& intlist, vector<Decimal>& declist) {
	for (int i = formula.size() - 1; i >= 0; i--) {
		if (formula[i] == '^') {
			if (formula[i - 1] == 'i') {
				int order = order_of(formula, 'i', i - 1);
				if (formula[i + 1] == 'i') {
					intlist[order] = power(intlist[order], intlist[order + 1]); //power(n, m) = n^m;
					intlist.erase(intlist.begin() + order + 1);
				}
				else if (formula[i + 1] == 'd') {
					int orderd = order_of(formula, 'd', i + 1);
					declist[orderd] = power(intlist[order], declist[orderd]); //power(n, m) = n^m;
					intlist.erase(intlist.begin() + order);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else if (formula[i - 1] == 'd') {
				int order = order_of(formula, 'd', i - 1);
				if (formula[i + 1] == 'd') {
					declist[order] = power(declist[order], declist[order + 1]); //power(n, m) = n^m;
					declist.erase(declist.begin() + order + 1);
				}
				else if (formula[i + 1] == 'i') {
					int orderi = order_of(formula, 'i', i + 1);
					declist[order] = power(declist[order], intlist[orderi]); //power(n, m) = n^m;
					intlist.erase(intlist.begin() + orderi);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

int positivity(string sign) {
	int positivity = 1;
	for (int i = 0; i < sign.size(); i++) {
		if (sign[i] == '+') {
			continue;
		}
		else if (sign[i] == '-') {
			positivity *= -1;
		}
		else {
			return 0;
		}
	}
	return positivity;
}

int formula_sign(string& formula, vector<Integer>& intlist, vector<Decimal>& declist) {
	if (formula[0] == '+' || formula[0] == '-') { //如--++-+n = -n
		int i = 0;
		while (formula[i] != 'd' && formula[i] != 'i') {
			i++;
		}
		i--;
		if (positivity(formula.substr(0, i)) == 0) {
			return 1;
		}
		else {
			if (formula[i + 1] == 'i') {
				intlist[0].positive = intlist[0].positive * positivity(formula.substr(0, i));
			}
			else if (formula[i + 1] == 'd') {
				declist[0].positive = declist[0].positive * positivity(formula.substr(0, i));
			}
		}
		formula.erase(0, i);
	}

	for (int i = formula.size() - 1; i >= 1; i--) {
		if (formula[i] == '+' || formula[i] == '-') { //d+--+++i = d+i
			if (formula[i + 1] != 'd' && formula[i + 1] != 'i') {
				return 1;
			}
			int j = i;
			while (j > 0 && (formula[j - 1] == '+' || formula[j - 1] == '-')) {
				j--;
			}
			int length;
			if (formula[j - 1] == '*' || formula[j - 1] == '/') {
				j--; // d/-----d j = 2
			}
			length = i - j;

			if (length > 0) {
				if (formula[i + 1] == 'i') {
					int order = order_of(formula, 'i', i + 1);
					if (positivity(formula.substr(j + 1, length)) == 0) {
						return 1;
					}
					else {
						intlist[order].positive = intlist[order].positive * positivity(formula.substr(j + 1, length));
					}
					formula.erase(j + 1, length);
					i = j - 1;
				}
				else if (formula[i + 1] == 'd') {
					int order = order_of(formula, 'd', i + 1);
					if (positivity(formula.substr(j + 1, length)) == 0) {
						return 1;
					}
					else {
						declist[order].positive = declist[order].positive * positivity(formula.substr(j + 1, length));
					}
					formula.erase(j + 1, length);
					i = j - 1;
				}
				else {
					return 1;
				}
			}
		}
	}
	return 0;
}

int formula_muldiv(string& formula, vector<Integer>& intlist, vector<Decimal>& declist) {
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '*') {
			if (formula[i - 1] == 'i') {
				int order = order_of(formula, 'i', i - 1);
				if (formula[i + 1] == 'i') {
					intlist[order] = intlist[order] * intlist[order + 1];
					intlist.erase(intlist.begin() + order + 1);
				}
				else if (formula[i - 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					declist[orderd] = intlist[order] * declist[orderd];
					intlist.erase(intlist.begin() + order);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else if (formula[i - 1] == 'd') {
				int order = order_of(formula, 'd', i - 1);
				if (formula[i + 1] == 'd') {
					declist[order] = declist[order] * declist[order + 1];
					declist.erase(declist.begin() + order + 1);
				}
				else if (formula[i + 1] == 'i') {
					int orderi = order_of(formula, 'i', i + 1);
					declist[order] = declist[order] * intlist[orderi];
					intlist.erase(intlist.begin() + orderi);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;

			}
			else {
				return 1;
			}
		}
		else if (formula[i] == '/') {
			if (formula[i - 1] == 'i') {
				int order = order_of(formula, 'i', i - 1);
				if (formula[i + 1] == 'i') {
					intlist[order] = intlist[order] / intlist[order + 1];
					intlist.erase(intlist.begin() + order + 1);
				}
				else if (formula[i - 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					declist[orderd] = intlist[order] / declist[orderd];
					intlist.erase(intlist.begin() + order);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else if (formula[i - 1] == 'd') {
				int order = order_of(formula, 'd', i - 1);
				if (formula[i + 1] == 'd') {
					declist[order] = declist[order] / declist[order + 1];
					declist.erase(declist.begin() + order + 1);
				}
				else if (formula[i + 1] == 'i') {
					int orderi = order_of(formula, 'i', i + 1);
					declist[order] = declist[order] / intlist[orderi];
					intlist.erase(intlist.begin() + orderi);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

int formula_addsub(string& formula, vector<Integer>& intlist, vector<Decimal>& declist) {
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '+') {
			if (formula[i - 1] == 'i') {
				int order = order_of(formula, 'i', i - 1);
				if (formula[i + 1] == 'i') {
					intlist[order] = intlist[order] + intlist[order + 1];
					intlist.erase(intlist.begin() + order + 1);
				}
				else if (formula[i - 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					declist[orderd] = intlist[order] + declist[orderd];
					intlist.erase(intlist.begin() + order);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else if (formula[i - 1] == 'd') {
				int order = order_of(formula, 'd', i - 1);
				if (formula[i + 1] == 'd') {
					declist[order] = declist[order] + declist[order + 1];
					declist.erase(declist.begin() + order + 1);
				}
				else if (formula[i + 1] == 'i') {
					int orderi = order_of(formula, 'i', i + 1);
					declist[order] = declist[order] + intlist[orderi];
					intlist.erase(intlist.begin() + orderi);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;

			}
			else {
				return 1;
			}
		}
		else if (formula[i] == '-') {
			if (formula[i - 1] == 'i') {
				int order = order_of(formula, 'i', i - 1);
				if (formula[i + 1] == 'i') {
					intlist[order] = intlist[order] - intlist[order + 1];
					intlist.erase(intlist.begin() + order + 1);
				}
				else if (formula[i - 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					declist[orderd] = intlist[order] - declist[orderd];
					intlist.erase(intlist.begin() + order);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else if (formula[i - 1] == 'd') {
				int order = order_of(formula, 'd', i - 1);
				if (formula[i + 1] == 'd') {
					declist[order] = declist[order] - declist[order + 1];
					declist.erase(declist.begin() + order + 1);
				}
				else if (formula[i + 1] == 'i') {
					int orderi = order_of(formula, 'i', i + 1);
					declist[order] = declist[order] - intlist[orderi];
					intlist.erase(intlist.begin() + orderi);
				}
				else {
					return 1;
				}
				formula.erase(i, 2);
				i -= 2;
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}
#endif

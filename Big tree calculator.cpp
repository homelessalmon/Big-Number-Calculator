#include<vector>
#include<string>
#include "Big tree calculator.h"

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
		int pn = positivity(formula.substr(0, i));
		if (pn == 0) {
			return 1;
		}
		else if (pn == -1) {
			if (formula[i] == 'i') {
				intlist[0] = -intlist[0];
			}
			else if (formula[i] == 'd') {
				declist[0] = -declist[0];
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
					int pn = positivity(formula.substr(j + 1, length));
					if (pn == 0) {
						return 1;
					}
					else if (pn == -1) {
						intlist[order] = -intlist[order];
					}
					formula.erase(j + 1, length);
					i = j - 1;
				}
				else if (formula[i + 1] == 'd') {
					int order = order_of(formula, 'd', i + 1);
					int pn = positivity(formula.substr(j + 1, length));
					if (pn == 0) {
						return 1;
					}
					else if (pn == -1) {
						declist[order] = -declist[order];
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
					formula.erase(i, 2);
				}
				else if (formula[i + 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					declist[orderd] = intlist[order] * declist[orderd];
					intlist.erase(intlist.begin() + order);
					formula.erase(i - 1, 2);
				}
				else {
					return 1;
				}
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
					if (intlist[order + 1].number == "0") {
						return 2;
					}
					intlist[order] = intlist[order] / intlist[order + 1];
					intlist.erase(intlist.begin() + order + 1);
					formula.erase(i, 2);
				}
				else if (formula[i + 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					if (declist[orderd].numerator.number == "00" || declist[orderd].numerator.number == "0") {
						return 2;
					}
					declist[orderd] = intlist[order] / declist[orderd];
					intlist.erase(intlist.begin() + order);
					formula.erase(i - 1, 2);
				}
				else {
					return 1;
				}
				i -= 2;
			}
			else if (formula[i - 1] == 'd') {
				int order = order_of(formula, 'd', i - 1);
				if (formula[i + 1] == 'd') {
					if (declist[order + 1].numerator.number == "00" || declist[order + 1].numerator.number == "0") {
						return 2;
					}
					declist[order] = declist[order] / declist[order + 1];
					declist.erase(declist.begin() + order + 1);
				}
				else if (formula[i + 1] == 'i') {
					int orderi = order_of(formula, 'i', i + 1);
					if (intlist[orderi].number == "0") {
						return 2;
					}
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
					formula.erase(i, 2);
				}
				else if (formula[i + 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					declist[orderd] = intlist[order] + declist[orderd];
					intlist.erase(intlist.begin() + order);
					formula.erase(i - 1, 2);
				}
				else {
					return 1;
				}
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
					formula.erase(i, 2);
				}
				else if (formula[i + 1] == 'd') {
					int orderd = order_of(formula, 'd', i - 1);
					declist[orderd] = intlist[order] - declist[orderd];
					intlist.erase(intlist.begin() + order);
					formula.erase(i - 1, 2);
				}
				else {
					return 1;
				}
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

void string_segmentation(string input, vector<string>& seg, string segflag, char packflag) {
	int cur = 0, nextpack = 0, nextseg = 0;
	while ((nextpack != string::npos || nextseg != string::npos) && cur >= 0) {
		nextseg = input.find_first_of(segflag, cur);
		nextpack = input.find_first_of(packflag, cur);
		if (nextpack == string::npos || nextseg < nextpack) {
			if (nextseg == string::npos) {
				seg.push_back(input.substr(cur));
				break;
			}
			seg.push_back(input.substr(cur, nextseg - cur));
			cur = nextseg + 1;
		}
		else if (nextseg == string::npos || nextseg > nextpack) {
			int packend = input.find_first_of(packflag, nextpack + 1);
			if (nextpack != cur) {
				seg.push_back(input.substr(cur, nextpack - cur));
			}
			seg.push_back(input.substr(nextpack + 1, packend - nextpack - 1));
			cur = input.find_first_not_of(segflag + packflag, packend);
		}
	}
}

void Big_tree_calculator::exe() {
	string input;
	while (getline(cin, input)) {
		string_process(input);
	}
	return;
}

void Big_tree_calculator::string_process(string input) {
	if (input == "") {
		return;
	}
	vector<string> input_seg;
	string_segmentation(input, input_seg, " ", '\"');
	if (input_seg[0] == "Integer" || input_seg[0] == "integer" || input_seg[0] == "Int" || input_seg[0] == "int") {
		if (variableList.find(input_seg[1]) != -1) {
			variableList.del_var(input_seg[1]);
		}
		if (input_seg.size() == 2) {
			Integer integer;
			integer.number = "0";
			variableList.push_pack(input_seg[1], integer);
		}
		else {
			Decimal temp = value_process(input_seg[3]);
			Integer integer;
			integer = (Integer)temp;
			variableList.push_pack(input_seg[1], integer);
		}
	}
	else if (input_seg[0] == "Decimal" || input_seg[0] == "decimal" || input_seg[0] == "Dec" || input_seg[0] == "dec") {
		if (input_seg.size() == 2) {
			Decimal decimal;
			decimal.denominator.number = "1";
			decimal.numerator.number = "0";
			variableList.push_pack(input_seg[1], decimal);
		}
		else {
			Decimal temp = value_process(input_seg[3]);
			if (temp.point_index == 0) {
				temp.point_index = 1;
				variableList.push_pack(input_seg[1], temp);
			}
			else {
				variableList.push_pack(input_seg[1], temp);
			}
		}
	}
	else if (input_seg.size() > 1 && input_seg[1] == "=") {
		Decimal temp = value_process(input_seg[2]);
		int v = variableList.find(input_seg[0]);
		if (v >= 0 && v < 100) {
			if (temp.point_index == 0) {
				variableList.Number_I[v] = temp;
			}
			else {
				Integer integer;
				integer = (Integer)temp;
				variableList.Number_I[v] = integer;
			}
		}
		else if (v >= 100) {
			if (temp.point_index != 0) {
				variableList.Number_D[v - 100] = temp;
			}
			else {
				temp.point_index = 1;
				variableList.Number_D[v - 100] = temp;
			}
		}
		else {
			cout << "errorcode:10" << endl;
			return;
		}
		//將input_seg[0]的變數賦值為input_seg[2]
	}
	else {
		Decimal os = value_process(input_seg[0]);
		if (os.point_index == 0) {
			Integer osi = (Decimal)os;
			cout << osi << endl;
		}
		else {
			cout << os << endl;
		}
	}
	return;
}

Decimal Big_tree_calculator::value_process(string input) {
	vector<Integer> num_int;
	vector<Decimal> num_dec;
	vector<char> op;
	string formula = "";
	int cur = 0;
	Decimal error;
	while (1) {
		//如果讀到數字就將其暫存為一個變數
		if ((input[cur] <= '9' && input[cur] >= '0')) {
			int begin = cur, end, is_Decimal = 0;
			while ((input[cur] <= '9' && input[cur] >= '0') || (input[cur] == '.')) {
				if ((input[cur] == '.')) {
					is_Decimal++;
				}
				cur++;
			}
			end = cur;
			int length = end - begin;
			string temp_string;
			switch (is_Decimal) {
			case 0: {
				temp_string = input.substr(begin, length);
				reverse(temp_string.begin(), temp_string.end());
				Integer temp;
				temp.number = temp_string;
				num_int.push_back(temp);
				formula = formula + 'i';
				break;
			}
			case 1: {
				temp_string = input.substr(begin, length);
				reverse(temp_string.begin(), temp_string.end());
				char point_pos;
				for (point_pos = 0; point_pos < temp_string.size(); point_pos++) {
					if (temp_string[point_pos] == '.') {
						temp_string.erase(point_pos, 1);
						break;
					}
				}
				
				while (temp_string[temp_string.length() - 1] == '0' && temp_string.length() > 1) {
					temp_string.pop_back();
					point_pos--;
				}
				
				Integer numerator;
				numerator.number = temp_string;
				Integer denominator;
				denominator.number = "1";
				for (point_pos; point_pos > 0; point_pos--) {
					denominator.number = denominator.number + "0";
				}
				reverse(denominator.number.begin(), denominator.number.end());
				Decimal temp;
				temp.numerator = numerator;
				temp.denominator = denominator;
				num_dec.push_back(temp);
				formula = formula + 'd';
				break;
			}
			default:
				error.positive = 11;
				return error;
				break;
			}
		}

		//讀到括號就遞迴，將括號內的結果作為變數暫存
		else if (input[cur] == '(') {
			int begin = cur + 1, end;
			int parenthese_deepth = 0;
			while (true) {
				if (input[cur] == '(') {
					parenthese_deepth++;
				}
				else if (input[cur] == ')') {
					parenthese_deepth--;
				}
				if (parenthese_deepth == 0) {
					end = cur;
					cur++;
					break;
				}
				cur++;
				if (cur == input.size()) {
					//如果parenthese_deepth合理的話可以做防呆？
					error.positive = 20;
					return error;
				}
			}
			int length = end - begin;
			Decimal parenthese = value_process(input.substr(begin, length));
			if (parenthese.point_index == 0) {
				Integer temp;
				temp = (Integer)parenthese;
				num_int.push_back(temp);
				formula = formula + 'i';
			}
			else {
				Decimal temp;
				temp = parenthese;
				num_dec.push_back(temp);
				formula = formula + 'd';
			}
		}
		else if (input[cur] == ')') {
			error.positive = 21;
			return error;
		}

		//如果是變數名就尋找該變數並將值存入暫存變數欄
		else if ((input[cur] >= 'a' && input[cur] <= 'z') || (input[cur] >= 'A' && input[cur] <= 'Z')) {
			int begin = cur, end;
			while ((input[cur] >= '0' && input[cur] <= '9') || (input[cur] >= 'a' && input[cur] <= 'z') || (input[cur] >= 'A' && input[cur] <= 'Z')) {
				cur++;
			}
			end = cur;
			int length = end - begin;
			int v = variableList.find(input.substr(begin, length));
			if (v >= 0 && v < 100) {
				num_int.push_back(variableList.Number_I[v]);
				formula = formula + 'i';
			}
			else if (v >= 100) {
				num_dec.push_back(variableList.Number_D[v - 100]);
				formula = formula + 'd';
			}
			else if (v == -1) {
				error.positive = 10;
				return error;
			}
		}
		else if (input[cur] == '+' || input[cur] == '-' || input[cur] == '*' || input[cur] == '/' || input[cur] == '^' || input[cur] == '!') {
			op.push_back(input[cur]);
			formula = formula + input[cur];
			cur++;
		}
		//讀到結尾就結束
		else if (input[cur] == '\0') {
			break;
		}

		//讀到空格就不管
		else {
			cur++;
		}
	}
	if (formula == "d") {
		formula = "d-d";
		Decimal temp;
		temp.numerator.number = "0";
		temp.denominator.number = "1";
		num_dec.push_back(temp);
	}

	//! :要確保前面只能是數
	//^ :要確保前後都是數，後面可以是+-
	//*/:要確保前後都是數，後面可以是+-
	//+-:要確保前後只能是+-與數
	//確保兩個數中間一定有運算子
	//有問題就回傳輸入錯誤
	if (formula[0] == '!' || formula[0] == '^' || formula[0] == '*' || formula[0] == '/') {
		error.positive = 30;
		return error;
	}
	if (formula[formula.size()] == '^' || formula[formula.size()] == '*' || formula[formula.size()] == '/' || formula[formula.size()] == '+' || formula[formula.size()] == '-') {
		error.positive = 31;
		return error;
	}
	for (int i = 1; i < formula.size() - 1; i++) {
		switch (formula[i]) {
		case '!':
			if ((formula[i - 1] != '!' && formula[i - 1] != 'i' && formula[i - 1] != 'd')) {
				error.positive = 32;
				return error;
			}
			break;
		case '^':
		case '*':
		case '/':
			if (formula[i + 1] != 'd' && formula[i + 1] != 'i' && formula[i + 1] != '+' && formula[i + 1] != '-') {
				error.positive = 33;
				return error;
			}
			break;
		case '+':
		case '-':
			if (formula[i + 1] != '+' && formula[i + 1] != '-' && formula[i + 1] != 'd' && formula[i + 1] != 'i') {
				error.positive = 34;
				return error;
			}
			break;
		case 'd':
		case 'i':
			if (formula[i - 1] == 'd' || formula[i + 1] == 'd' || formula[i - 1] == 'i' || formula[i + 1] == 'i') {
				error.positive = 35;
				return error;
			}
			break;
		default:
			error.positive = 36;
			return error;
			break;
		}
	}
	// n+n*n--n!
	for (int i = 0; i < num_int.size(); i++) {
		if (num_int[i].positive != 1 && num_int[i].positive != -1) {
			return num_int[i];
		}
	}
	for (int i = 0; i < num_dec.size(); i++) {
		if (num_dec[i].positive != 1 && num_dec[i].positive != -1) {
			return num_dec[i];
		}
	}

	if (formula_factorial(formula, num_int, num_dec) != 0) {
		error.positive = 40;
		return error;
	}

	if (formula_power(formula, num_int, num_dec) != 0) {
		error.positive = 41;
		return error;
	}

	if (formula_sign(formula, num_int, num_dec) != 0) {
		error.positive = 42;
		return error;
	}
	int code = formula_muldiv(formula, num_int, num_dec);
	if (code == 1) {
		error.positive = 43;
		return error;
	}
	else if (code == 2) {
		error.positive = 4;
		return error;
	}

	if (formula_addsub(formula, num_int, num_dec) != 0) {
		error.positive = 44;
		return error;
	}

	if (num_int.size() + num_dec.size() != 1) {
		error.positive = 50;
		return error;
	}

	if (num_int.size() == 1) {
		Decimal temp;
		temp = (Decimal)num_int[0];
		temp.point_index = 0;
		return temp;
	}
	else if (num_dec.size() == 1) {
		return num_dec[0];
	}
}

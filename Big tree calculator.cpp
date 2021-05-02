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
		else {
			if (formula[i] == 'i') {
				intlist[0].positive = intlist[0].positive * pn;
			}
			else if (formula[i] == 'd') {
				declist[0].positive = declist[0].positive * pn;
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

void string_segmentation(string input, vector<string>& seg, string segflag, char packflag) {
	int cur = 0, nextpack = 0, nextseg = 0;
	while (nextpack != string::npos || nextseg != string::npos) {
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
	if (input_seg[0] == "Integer") {
		if (variableList.find(input_seg[1]) != -1) {
			variableList.del_var(input_seg[1]);
		}
		if (input_seg.size() == 2) {
			Integer integer;
			integer.number = "0";
			variableList.push_pack(input_seg[1], integer);
		}
		else {
			NumberObject temp = value_process(input_seg[3]);
			if (temp.point_index == 0) {
				Integer integer;
				integer = temp;
				variableList.push_pack(input_seg[1], integer);
			}
			else {
				Decimal decimal;
				decimal = temp;
				Integer integer;
				integer = decimal;
				variableList.push_pack(input_seg[1], integer);
			}
		}
	}
	else if (input_seg[0] == "Decimal") {
		if (input_seg.size() == 2) {
			Decimal decimal;
			decimal.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
			variableList.push_pack(input_seg[1], decimal);
		}
		else {
			NumberObject temp = value_process(input_seg[3]);
			if (temp.point_index == 0) {
				Integer integer;
				integer = temp;
				Decimal decimal;
				decimal = integer;
				variableList.push_pack(input_seg[1], integer);
			}
			else {
				Decimal decimal;
				decimal = temp;
				variableList.push_pack(input_seg[1], decimal);
			}
		}
	}
	else if (input_seg.size() > 1 && input_seg[1] == "=") {
		NumberObject temp = value_process(input_seg[2]);
		int v = variableList.find(input_seg[0]);
		if (v <= 100) {
			if (temp.point_index == 0) {
				variableList.Number_I[v] = temp;
			}
			else {
				Decimal decimal;
				decimal = temp;
				Integer integer;
				integer = decimal;
				variableList.Number_I[v] = integer;
			}
		}
		else {
			if (temp.point_index != 0) {
				variableList.Number_D[v - 100] = temp;
			}
			else {
				Integer integer;
				integer = temp;
				Decimal decimal;
				decimal = integer;
				variableList.Number_D[v - 100] = decimal;
			}
		}
		//將input_seg[0]的變數賦值為input_seg[2]
	}
	else {
		cout << value_process(input_seg[0]) << endl;
	}
	return;
}

NumberObject Big_tree_calculator::value_process(string input) {
	vector<Integer> num_int;
	vector<Decimal> num_dec;
	vector<char> op;
	vector<int> op_pos;
	vector<int> int_pos;
	vector<int> dec_pos;
	int cur = 0;
	NumberObject error;
	while (1) {
		//如果讀到數字就將其暫存為一個變數
		if ((input[cur] <= '9' && input[cur] >= '0')) {
			int begin = cur, end, is_Decimal = 0;
			while ((input[cur] <= '9' && input[cur] >= '0') || (input[cur] == '.')) {
				if ((input[cur] == '.')) {
					is_Decimal = 1;
				}
				cur++;
			}
			end = cur;
			int length = end - begin;
			string tempS;
			switch (is_Decimal) {
			case 0: {
				Integer temp;
				tempS = input.substr(begin, length);
				reverse(tempS.begin(), tempS.end());
				temp.number = tempS;
				num_int.push_back(temp);
				int_pos.push_back(begin);
				break;
			}
			case 1: {
				Decimal temp;
				temp.number = input.substr(begin, length);
				num_dec.push_back(temp);
				dec_pos.push_back(begin);
				break;
			}
			default:
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
			NumberObject P = value_process(input.substr(begin, length));
			if (P.point_index == 0) {
				Integer temp;
				temp = P;
				num_int.push_back(temp);
				int_pos.push_back(begin);
			}
			else {
				Decimal temp;
				temp = P;
				num_dec.push_back(temp);
				dec_pos.push_back(begin);
			}
		}
		else if (input[cur] == ')') {
			error.positive = 21;
			return error;
		}

		//如果是變數名就尋找該變數並將值存入暫存變數欄
		else if ((input[cur] >= 'a' && input[cur] <= 'z') || (input[cur] >= 'A' && input[cur] <= 'Z')) {
			int begin = cur, end;
			while ((input[cur] >= '9' && input[cur] <= '0') || (input[cur] >= 'a' && input[cur] <= 'z') || (input[cur] >= 'A' && input[cur] <= 'Z')) {
				cur++;
			}
			end = cur;
			int length = end - begin;
			int v = variableList.find(input.substr(begin, length));
			if (v <= 100) {
				num_int.push_back(variableList.Number_I[v]);
				int_pos.push_back(begin);
			}
			else if (v > 100) {
				num_dec.push_back(variableList.Number_D[v - 100]);
				dec_pos.push_back(begin);
			}
			else if (v == -1) {
				error.positive = 10;
				return error;
			}
		}
		else if (input[cur] == '+' || input[cur] == '-' || input[cur] == '*' || input[cur] == '/' || input[cur] == '^' || input[cur] == '!') {
			op.push_back(input[cur]);
			op_pos.push_back(cur);
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


	//用merge還原算式，並且變數以i、d儲存
	int_pos.push_back(65536);
	dec_pos.push_back(65536);
	string num;
	vector<int> numpos;
	int int_pos_check = 0, dec_pos_check = 0;
	while (1) {
		if (int_pos[int_pos_check] < dec_pos[dec_pos_check]) {
			num = num + 'i';
			numpos.push_back(int_pos[int_pos_check]);
			int_pos_check++;
		}
		else {
			num = num + 'd';
			numpos.push_back(dec_pos[dec_pos_check]);
			dec_pos_check++;
		}
		if (int_pos[int_pos_check] == 65536 && dec_pos[dec_pos_check] == 65536) {
			break;
		}
	}
	int_pos.pop_back();
	dec_pos.pop_back();

	string formula;
	op_pos.push_back(65536);
	numpos.push_back(65536);
	int num_pos_check = 0, op_pos_check = 0;
	while (1) {
		if (numpos[num_pos_check] < op_pos[op_pos_check]) {
			formula = formula + num[num_pos_check];
			num_pos_check++;
		}
		else {
			formula = formula + op[op_pos_check];
			op_pos_check++;
		}
		if (numpos[num_pos_check] == 65536 && op_pos[op_pos_check] == 65536) {
			break;
		}
	}
	numpos.pop_back();
	op_pos.pop_back();

	//這塊應該有更好的寫法但我一時間想不到 先這樣
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
			if ((formula[i - 1] != '!' && formula[i - 1] != 'i')) {
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

	if (formula_muldiv(formula, num_int, num_dec) != 0) {
		error.positive = 43;
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
		return num_int[0];
	}
	else if (num_dec.size() == 1) {
		return num_dec[0];
	}
}

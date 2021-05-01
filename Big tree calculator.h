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

NumberObject find_veriable(string input) {
	//todo list
	//Big_tree_calculator.list.find(input);
	//return integer;
}

void string_segmentation(string input, vector<string>& seg, string segflag) {
	int cur = 0, next = 0;
	while (next != string::npos) {
		next = input.find_first_of(segflag, cur);
		if (next == string::npos) {
			seg.push_back(input.substr(cur));
			break;
		}
		seg.push_back(input.substr(cur, next - cur));
		cur = next + 1;
	}
}

void string_process(string input) {
	vector<string> input_seg;
	string_segmentation(input, input_seg, " ");
	if (input_seg[0] == "Integer" || input_seg[0] == "Decimal") {
		//建立以input_seg[1]為名的變數
	}
	else if (input_seg[1] == "=") {
		//將input_seg[0]的變數賦值為input_seg[2]
	}
	else {
		//input_seg[0]就是運算式
	}
}

NumberObject value_process(string input) {
	vector<NumberObject> num;
	vector<int> num_pos;
	int cur = 0;
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
			switch (is_Decimal) {
			case 1: {
				Integer temp(input.substr(begin, length));
				num.push_back(temp);
				num_pos.push_back(begin);
				break;
			}
			case 0: {
				Decimal temp(input.substr(begin, length));
				num.push_back(temp);
				num_pos.push_back(begin);
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
					break;
				}
				cur++;
				if (cur == input.size()) {
					//如果parenthese_deepth合理的話可以做防呆？
					//想辦法報錯，原因是無法找到對應的前後括號
					//return ?
				}
			}
			int length = end - begin;
			num.push_back(value_process(input.substr(begin, length)));
			num_pos.push_back(begin);
		}
		else if (input[cur] == ')') {
			//代表遇到沒有成對的後括號
		}

		//如果是變數名就尋找該變數並將值存入暫存變數欄
		else if ((input[cur] <= 'a' && input[cur] >= 'z')||(input[cur] <= 'A' && input[cur] >= 'Z')) {
			int begin = cur, end;
			while ((input[cur] <= '9' && input[cur] >= '0') || (input[cur] <= 'a' && input[cur] >= 'z')||(input[cur] <= 'A' && input[cur] >= 'Z')) {
				cur++;
			}
			end = cur;
			int length = end - begin;
			num.push_back(find_veriable(input.substr(begin, length)));
			num_pos.push_back(begin);
		}

		//讀到結尾就結束
		else if (input[cur] == '\0') {
			break;
		}

		//讀到運算子或是空格就不管
		else {
			cur++;
		}
	}

	//存入運算子
	vector<char> op;
	vector<int> op_pos;
	for (int i = 0; i < input.size(); i++) {
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '^' || input[i] == '!') {
			op.push_back(input[i]);
			op_pos.push_back(i);
		}
	}

	
	//用merge還原算式，並且變數以n儲存
	string formula;
	num_pos.push_back(65536);
	op_pos.push_back(65536);
	int num_pos_check = 0, op_pos_check = 0;
	while (1) {
		if (num_pos[num_pos_check] < op_pos[op_pos_check] ) {
			formula = formula + 'n';
            num_pos_check++;
        }
        else {
            formula = formula + op[op_pos_check];
            op_pos_check++;
        }
		if (num_pos[num_pos_check] == 65536 && op_pos[op_pos_check] == 65536) {
			break;
		}
    }
	num_pos.pop_back();
	op_pos.pop_back();

	//這塊應該有更好的寫法但我一時間想不到 先這樣
	//! :要確保前面只能是數
	//^ :要確保前後都是數，後面可以是+-
	//*/:要確保前後都是數，後面可以是+-
	//+-:要確保前後只能是+-與數
	//確保兩個數中間一定有運算子
	//有問題就回傳輸入錯誤
	if (formula[0] == '!' || formula[0] == '^' || formula[0] == '*' || formula[0] == '/') {
		//輸出錯誤狀況
	}
	if (formula[formula.size()] == '^' || formula[formula.size()] == '*' || formula[formula.size()] == '/' || formula[formula.size()] == '+' || formula[formula.size()] == '-') {
		//輸出錯誤狀況
	}
	for (int i = 1; i < formula.size() - 1; i++) {
		switch (formula[i]) {
		case '!':
			if ((formula[i - 1] != '!' && formula[i - 1] != 'n')) {
				//輸出錯誤狀況
			}
			break;
		case '^':
		case '*':
		case '/':
			if (formula[i - 1] != 'n' || (formula[i + 1] != 'n' && formula[i + 1] != '+' && formula[i + 1] != '-')) {
				//輸出錯誤狀況
			}
			break;
		case '+':
		case '-':
			if ((formula[i - 1] != '+' && formula[i - 1] != '-' && formula[i - 1] != 'n') || (formula[i + 1] != '+' && formula[i + 1] != '-' && formula[i + 1] != 'n')) {
				//輸出錯誤狀況
			}
			break;
		case 'n' :
			if (formula[i - 1] == 'n' || formula[i + 1] == 'n') {
				//輸出錯誤狀況
			}
			break;
		default:
			//輸出錯誤狀況
			break;
		}
	}
	// n+n*n--n!

	if (formula_facrorial(formula, num) != 0) {
		//return算式錯誤 
	}

	if (formula_power(formula, num) != 0) {
		//return算式錯誤
	}

	for (int i = 0; i < num.size(); i++) {
		if (num[i].positive != 1 && num[i].positive != -1) {
			return num[i];
		}
	}

	if (formula_sign(formula, num) != 0) {
		//return算式錯誤
	}

	if (formula_muldiv(formula, num) != 0) {
		//return算式錯誤
	}

	if (formula_addsub(formula, num) != 0) {
		//return算式錯誤
	}

	if (num.size() > 0) {
		//return算式錯誤
	}
	return num[0];
}

int order_of_n(const string& formula, int pos) {
	int order = 0;
	for (int i = 0; i < pos; i++) { //這是第幾個n
		if (formula[i] == 'n') {
			order++;
		}
	}
	return order;
}

int formula_facrorial(string& formula, vector<NumberObject>& numlist) {
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '!') {
			if (formula[i - 1] == 'n') {
				int order = order_of_n(formula, i - 1);
				numlist[order] = facrorial(numlist[order]);
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

int formula_power(string& formula, vector<NumberObject>& numlist) {
	for (int i = formula.size() - 1; i >= 0; i++) {
		if (formula[i] == '^') {
			if (formula[i - 1] == 'n') {
				int order = order_of_n(formula, i - 1);
				numlist[order] = power(numlist[order], numlist[order + 1]); //power(n, m) = n^m;
				formula.erase(i, 2);
				i -= 2;
				numlist.erase(numlist.begin() + order + 1);
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}
//01234567
//n++++++n
//-----n
int posibility(string sign) {
	int posibility = 1;
	for (int i = 0; i < sign.size(); i++) {
		if (sign[i] == '+') {
			continue;
		}
		else if (sign[i] == '-') {
			posibility *= -1;
		}
		else {
			return 0;
		}
	}
	return posibility;
}

int formula_sign(string& formula, vector<NumberObject>& numlist) {
	if (formula[0] == '+' || formula[0] == '-') { //如--++-+n = -n
		int i = 0;
		while (formula[i] != 'n') {
			i++;
		}
		i--;
		numlist[0].positive = numlist[0].positive * posibility(formula.substr(0, i));
		formula.erase(0, i);
	}
	for (int i = formula.size() - 1; i >= 1; i++) {
		if (formula[i] == '+' || formula[i] == '-') { //n+--+++n = n+n
			if (formula[i + 1] != 'n') {
				return 1;
			}
			int j = i;
			while (j != 0 && formula[j - 1] == '+' || formula[j - 1] == '-') {
				j--;
			}
			int length = i - j; 
			if (length > 0) {
				int order = order_of_n(formula, i + 1);
				numlist[order].positive = numlist[order].positive * posibility(formula.substr(j + 1, length));
				formula.erase(j + 1, length);
				i = j - 1;
			}
		}
	}
	return 0;
}

int formula_muldiv(string& formula, vector<NumberObject>& numlist) {
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '*') {
			if (formula[i - 1] == 'n') {
				int order = order_of_n(formula, i - 1);
				numlist[order] = mul(numlist[order], numlist[order + 1]);
				formula.erase(i, 2);
				i -= 2;
				numlist.erase(numlist.begin() + order + 1);
			}
			else {
				return 1;
			}
		}
		if (formula[i] == '/') {
			if (formula[i - 1] == 'n') {
				int order = order_of_n(formula, i - 1);
				numlist[order] = div(numlist[order], numlist[order + 1]);
				formula.erase(i, 2);
				i -= 2;
				numlist.erase(numlist.begin() + order + 1);
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

int formula_addsub(string& formula, vector<NumberObject>& numlist) {
	for (int i = 0; i < formula.size(); i++) {
		if (formula[i] == '+') {
			if (formula[i - 1] == 'n') {
				int order = order_of_n(formula, i - 1);
				numlist[order] = add(numlist[order], numlist[order + 1]);
				formula.erase(i, 2);
				i -= 2;
				numlist.erase(numlist.begin() + order + 1);
			}
			else {
				return 1;
			}
		}
		if (formula[i] == '-') {
			if (formula[i - 1] == 'n') {
				int order = order_of_n(formula, i - 1);
				numlist[order] = sub(numlist[order], numlist[order + 1]);
				formula.erase(i, 2);
				i -= 2;
				numlist.erase(numlist.begin() + order + 1);
			}
			else {
				return 1;
			}
		}
	}
	return 0;
}

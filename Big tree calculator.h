#pragma once
#include<vector>
#include<string>
#include"NumberObject.h"
#include"Variable_handling.h"

using namespace std;

class Big_tree_calculator {
public:

	//variable
	Variable_list list;
	//function
	void exe();
};

NumberObject find_veriable(string input) {
	//todo list
	Integer integer(0);
	return integer;
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
	char* formula;
	int formula_size = num.size() + op.size();
	formula = new char[formula_size];
	num_pos.push_back(65536);
	op_pos.push_back(65536);
	int num_pos_check = 0, op_pos_check = 0;
	for (int i = 0; i < formula_size; i++) {
		if (num_pos[num_pos_check] < op_pos[op_pos_check] ) {
			formula[i] = 'n';
            num_pos_check++;
        }
        else {
            formula[i] = op[op_pos_check];
            op_pos_check++;
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
	if (formula[formula_size] == '^' || formula[formula_size] == '*' || formula[formula_size] == '/' || formula[formula_size] == '+' || formula[formula_size] == '-' || ) {
		//輸出錯誤狀況
	}
	for (int i = 1; i < formula_size - 1; i++) {
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
			if (formula[i - 1] == n || formula[i + 1] == n) {
				//輸出錯誤狀況
			}
			break;
		default:
			//輸出錯誤狀況
			break;
		}
	}

	//todo: 底下架構會再改
	//做階乘
	for (int i = 0; i < op.size(); i++) {
		int factorial_pos;
		if (op[i] == '!') {
			factorial_pos = op_pos[i];
		}
		for (int j = 0; j < num.size(); j++) {
			if (num_pos[j] > factorial_pos) {
				num[j - 1] = factorial(num[j - 1]); //當輸入小數、負數時應報錯
				op.erase(op.begin() + i);
				op_pos.erase(op_pos.begin() + i);
			}
		}
	}

	//做次方
	for (int i = op.size() - 1; i >= 0; i--) {
		int power_pos;
		if (op[i] == '^') {
			power_pos = op_pos[i];
		}
		for (int j = 0; j < num.size(); j++) {
			if (num_pos[j] > power_pos) {
				num[j - 1] = power(num[j - 1], num[j]); //power(a,b) => a^b
				
				op.erase(op.begin() + i);
				op_pos.erase(op_pos.begin() + i);

				num.erase(num.begin() + j);
				num_pos.erase(num_pos.begin() + j);
			}
		}
	}
	return num[0];
}

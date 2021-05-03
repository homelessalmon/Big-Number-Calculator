#include"NumberObject.h"

using namespace std;

//NumberObject

void reduct_fraction(Integer& numerator, Integer& denominator) {
	Integer A = gcd(numerator, denominator);
	numerator = numerator / A;
	denominator = denominator / A;
}

Decimal sub(const Decimal& n1, const Decimal& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Decimal n3 = n1 + n2;
		n3 = -n3;
		return n3;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Decimal n3 = n1 + n2;
		return n3;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		return n2 - n1;
	}
	Decimal a;
	string num1, num2;
	vector<int> ans;
	num1 = n1.number;
	num2 = n2.number;
	//check if the answer is positive
	if (num1.length() > num2.length()) {}
	else if (num2.length() > num1.length()) {
		swap(num1, num2);
		a.positive = -1;
	}
	else {
		for (int i = num1.length() - 1; i >= 0; i--) {
			if (num1[i] > num2[i]) {
				break;
			}
			if (num1[i] < num2[i]) {
				swap(num1, num2);
				a.positive = -1;
				break;
			}
		}
	}
	//substraction
	int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
	for (int i = 0; i < num1_len; i++) {
		if (i < num2_len) {
			int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
		else {
			int t = (num1[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
	}
	//clear redundant zeros ex.1000 - 999 = 0001 -> 1
	for (int i = ans.size() - 1; i > 0; i--) {
		if (ans[i] != 0)
			break;
		ans.pop_back();
	}
	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}
	while (temp.length() < 101) {
		temp.append(1, '0');
	}
	a.number = temp;
	return a;
}

ostream& operator<<(ostream& io, NumberObject num) {
	if (num.positive != 1 && num.positive != -1) {
		io << "error code:" << num.positive;
		return io;
	}
	if (num.point_index == 0) {
		if (num.positive == 1) {
			string temp = num.number;
			reverse(temp.begin(), temp.end());
			io << temp;
			return io;
		}
		else {
			if (num.positive == -1) {
				string temp = num.number;
				reverse(temp.begin(), temp.end());
				io << "-" << temp;
				return io;
			}
		}
	}
	else {
		if (num.positive == 1) {
			string temp = num.number;
			reverse(temp.begin(), temp.end());
			for (int i = 0; i < temp.length(); i++) {
				if (temp.length() - i == 100) {
					cout << '.';
				}
				io << temp[i];
			}
			return io;
		}
		else if (num.positive == -1) {
			string temp = num.number;
			int c = temp.length();
			reverse(temp.begin(), temp.end());
			io << "-";
			for (int i = 0; i < temp.length(); i++) {
				if (temp.length() - i == 100) {
					cout << '.';
				}
				io << temp[i];
			}
			return io;
		}
	}
}

//NumberObject::operator Integer()
//{
//    Integer tmp;
//    tmp.number = this->number;
//    tmp.positive = this->positive;
//    return tmp;
//}
//
//NumberObject::operator Decimal()
//{
//    Decimal tmp;
//    tmp.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + number;
//    tmp.positive = 1;
//    return tmp;
//}

//int

Integer::Integer() {
	point_index = 0;
	positive = 1;
}

Integer::Integer(const Integer& reference) {
	number = reference.number;
	point_index = reference.point_index;
	positive = reference.positive;
}

Integer operator+(const Integer& n1, const Integer& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Integer n3 = n1;
		n3 = -n3;
		return n2 - n3;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Integer n3 = n2;
		n3 = -n3;
		return n1 - n3;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Integer n3 = n1;
		Integer n4 = n2;
		n3 = -n3;
		n4 = -n4;
		Integer n5 = n3 + n4;
		return -n5;
	}

	string num1 = n1.number, num2 = n2.number;
	vector<int>ans;

	int num1_len = num1.length(), num2_len = num2.length();
	if (num1_len > num2_len) {
		swap(num1, num2);
		swap(num1_len, num2_len);
	}

	int carry = 0;
	for (int i = 0; i < num2_len; i++) {
		if (i < num1_len) {
			int t = (num1[i] - '0') + (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
		else {
			int t = (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
	}
	if (carry == 1) ans.push_back(1);

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	Integer a;
	a.number = temp;
	a.positive = 1;
	return a;
}

Integer operator-(const Integer& n1, const Integer& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Integer n3 = n1;
		n3 = -n3;
		Integer n4 = n3 + n2;
		return -n4;
	}
	else if (n2.positive == -1 && n1.positive == 1) {
		Integer n3 = n2;
		n3 = -n3;
		Integer n4 = n3 + n1;
		return n4;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Integer n3 = n1;
		Integer n4 = n2;
		n3 = -n3;
		n4 = -n4;
		return n4 - n3;
	}

	Integer a;
	string num1, num2;
	vector<int> ans;
	num1 = n1.number;
	num2 = n2.number;

	//check if the answer is positive
	if (num1.length() > num2.length()) {}
	else if (num2.length() > num1.length()) {
		swap(num1, num2);
		a.positive = -1;
	}
	else {
		for (int i = num1.length() - 1; i >= 0; i--) {
			if (num1[i] > num2[i]) {
				break;
			}
			if (num1[i] < num2[i]) {
				swap(num1, num2);
				a.positive = -1;
				break;
			}
		}
	}

	//substraction
	int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
	for (int i = 0; i < num1_len; i++) {
		if (i < num2_len) {
			int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
		else {
			int t = (num1[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
	}

	//clear redundant zeros ex.1000 - 999 = 0001 -> 1
	for (int i = ans.size() - 1; i > 0; i--) {
		if (ans[i] != 0)
			break;
		ans.pop_back();
	}

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	a.number = temp;
	return a;
}

Integer operator*(const Integer& num1, const Integer& num2) {
	if (num1.number == "0" || num2.number == "0") {
		Integer A;
		A.number = "0";
		A.positive = 1;
		return A;
	}
	vector<Integer> list_to_plus;
	for (int i = 0; i < num2.number.length(); i++) {
		int q = 0;
		string temp = num1.number;
		for (int j = 0; j < num1.number.length(); j++) {
			int c = ((temp[j] - '0') * (num2.number[i] - '0') + q) % 10;
			q = ((temp[j] - '0') * (num2.number[i] - '0') + q) / 10;
			temp[j] = c + '0';
			if (j == num1.number.length() - 1 && q > 0) {
				temp.append(1, q + '0');
			}
		}
		Integer A;
		A.number = temp;
		list_to_plus.push_back(A);
	}
	for (int i = 0; i < list_to_plus.size(); i++) {
		string x = "";
		for (int j = 0; j < i; j++) {
			x.append(1, '0');
		}
		list_to_plus[i].number = x + list_to_plus[i].number;
	}
	Integer re;
	re.number = "0";
	for (int i = 0; i < list_to_plus.size(); i++) {
		re = re + list_to_plus[i];
	}
	re.positive = num1.positive * num2.positive;
	return re;
}

Integer operator/(const Integer& num1, const Integer& num2) {
	if (num2.number == "0") {
		Decimal error;
		error.positive = 4;
		return error;
	}
	Decimal n1, n2;
	n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + num1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + num2.number;
	n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n2.number;
	string t = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	if (n1.number == "0") {
		Integer X;
		X.number = "0";
		return X;
	}
	else {
		if (n2.number == "0") {
			Integer X;
			X.positive = 3;
			return X;
		}
	}
	if (num2.positive == 3) {
		Integer X;
		X.number = "0";
		return X;
	}
	while (n1.number.length() > n2.number.length()) {
		t = "0" + t;
		n2.number = "0" + n2.number;
	}

	if (n1.number[n1.number.length() - 1] == '0') { n1.number.pop_back(); }
	if (n2.number[n2.number.length() - 1] == '0') { n2.number.pop_back(); }

	for (int i = t.length() - 1; i > -1; i--) {
		int m = 0;
		while (1) {
			Decimal A;
			A = sub(n1, n2);
			if (A.positive < 0) { break; }
			n1 = sub(n1, n2);
			m++;
		}
		t[i] = m + '0';
		m = 0;
		n2.number.erase(n2.number.begin());
		if (n2.number.length() < 101) { n2.number.append(1, '0'); }
	}
	while (t[t.length() - 1] == '0') {
		t.pop_back();
	}

	while (t.length() < 101) {
		t.append(1, '0');
	}
	Integer temp;
	temp.number = t.substr(100);
	temp.positive = num1.positive * num2.positive;
	return temp;
}

Integer factorial(const Integer& num) {
	if (num.positive != -1 && num.positive != 1) { Integer X; X.positive = 2; return X; }
	Integer one; one.number = "1";
	Integer s = one, now = num;
	if (num.number == "0") {
		return one;
	}
	while (now.number != one.number) {
		s = s * now;
		now = now - one;
	}
	return s;
}

Integer power(const Integer& base, const Integer& exp) {
	if ((base.positive != 1 && base.positive != -1) || (exp.positive != 1 && exp.positive != -1)) { Integer X; X.positive = 3; return X; }
	Integer s = base, temp = exp, one; one.number = "1";
	if (exp.number == "0" || exp.positive == -1) { Integer tmp; tmp.number = "1"; return tmp; }
	while (temp.number != "1") { s = s * base; temp = temp - one; }
	return s;
}

Integer power(const Integer& base, const Decimal& exp) {
	if ((base.positive != 1 && base.positive != -1) || (exp.positive != 1 && exp.positive != -1)) { Decimal X; X.positive = 3; return X; }
	Decimal b, e = exp, one, two, zero; e.positive = 1; b.numerator.number = base.number; b.number = divide(b.numerator, b.denominator);
	zero.number.insert(0, 101, '0'); one.number.insert(0, 100, '0'); one.number.append(1, '1'); one.numerator.number = "1"; two = one + one;
	if (exp.numerator.number == "0") { return one; }
	if (b.numerator.number == "0") { return zero; }
	reduct_fraction(b.numerator, b.denominator);
	reduct_fraction(e.numerator, e.denominator);

	if (e.denominator.number == "2") {
		if (base.positive == -1) { Decimal X; X.positive = 3; return X; }
		e = e * two;

		Decimal re = b;
		while (e.number != one.number) {
			re = re * base;
			e = e - one;
		}
		Decimal next, now = re / two; next.number = "0";

		while (next.number != now.number) {
			next = wali(tashi(kake(now, now), re), kake(two, now));
			swap(next, now);
			if (now.positive != 1 && now.positive != -1) { Decimal X; X.positive = 4; return X; }
		}
		if (exp.positive == -1) {
			Decimal a;
			a.numerator.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
			a.denominator.number = now.number;
			while (a.denominator.number[a.denominator.number.length() - 1] == '0' && a.denominator.number.length() > 1)
			{
				a.denominator.number.pop_back();
				a.numerator.number = "0" + a.numerator.number;
			}
			reduct_fraction(a.numerator, a.denominator);
			a.number = divide(a.numerator, a.denominator);
			return a;
		}
		else {
			if (exp.positive == 1) {
				Decimal a;
				a.denominator.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
				a.numerator.number = now.number;
				while (a.numerator.number[a.numerator.number.length() - 1] == '0' && a.numerator.number.length() > 1)
				{
					a.numerator.number.pop_back();
					a.denominator.number = "0" + a.denominator.number;
				}
				reduct_fraction(a.numerator, a.denominator);
				a.number = divide(a.numerator, a.denominator);
				return a;
			}
		}
	}
	else {
		Decimal re = b;
		while (e.number != one.number) {
			re = re * base;
			e = e - one;
		}
		if (exp.positive == -1) {
			return one / re;
		}
		else {
			if (exp.positive == 1) {
				return re;
			}
		}
	}
}

bool operator >(const Integer& num1, const Integer& num2) {
	if (num2.positive > num1.positive) { return false; }
	if (num1.number == num2.number) { return false; }
	else if (num2.number.length() > num1.number.length()) { return false; }
	else {
		if (num1.number.length() > num2.number.length()) { return true; }
		else {
			for (int i = num1.number.length()-1; i > -1; i--) {
				if (num1.number[i] > num2.number[i]) { return true; }
				else
				{
					if (num2.number[i] > num1.number[i]) { return false; }
				}
			}
		}
	}
}

bool operator >=(const Integer& num1, const Integer& num2) {
	if (num2.positive > num1.positive) { return false; }
	if (num1.number == num2.number) { return true; }

	if (num2.number.length() > num1.number.length()) { return false; }
	else {
		if (num1.number.length() > num2.number.length()) { return true; }
		else {
			for (int i = num1.number.length() - 1; i > -1; i--) {
				if (num1.number[i] > num2.number[i]) { return true; }
				else
				{
					if (num2.number[i] > num1.number[i]) { return false; }
				}
			}
		}
	}
	return true;
}

Integer operator%(const Integer& num1, const Integer& num2) {
	Integer n1 = num1;
	if (num2 > num1) { return num1; }
	while (n1 >= num2) { n1 = n1 - num2; }
	return n1;
}

Integer gcd(const Integer& num1, const Integer& num2) {
	Integer n1 = num1, n2 = num2;
	if (n2.number == "0") {
		return n1;
	}
	else {
		return gcd(n2, n1 % n2);
	}
}

Integer lcm(const Integer& num1, const Integer& num2) {
	Integer re = num1 * num2;
	re = re / gcd(num1, num2);
	return re;
}

/*void Integer::operator=(const NumberObject& input) {
	number = input.number;
	positive = input.positive;
	point_index = input.point_index;
}*/

Integer Integer::operator-() {
	if (this->number != "0") {
		this->positive *= -1;
	}
	return *this;
}

Integer::operator Decimal() {
	Decimal temp;
	temp.numerator = *this;
	temp.denominator.positive = 1;
	temp.denominator.number = "1";
	temp.positive = this->positive;
	temp.number = divide(temp.numerator, temp.denominator);
	return temp;
}

//-------------------------------------------------------------------------
//Decimal

Decimal::Decimal() {
	numerator.number = "0";
	denominator.number = "1";
	point_index = 1;
	positive = 1;
}

Decimal::Decimal(const Decimal& reference) {
	numerator = reference.numerator;
	denominator = reference.denominator;
	number = reference.number;
	point_index = reference.point_index;
	positive = reference.positive;
}



Decimal operator+(const Decimal& n1, const Integer& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Decimal n3 = n1;
		n3 = -n3;
		return n2 - n3;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Integer n3 = n2;
		n3 = -n3;
		return n1 - n3;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Decimal n3 = n1;
		Integer n4 = n2;
		n3 = -n3;
		n4 = -n4;
		Decimal n5 = n3 + n4;
		return -n5;
	}

	Integer num = n1.denominator * n2;
	string num1 = n1.numerator.number, num2 = num.number;
	vector<int>ans;

	int num1_len = num1.length(), num2_len = num2.length();
	if (num1_len > num2_len) {
		swap(num1, num2);
		swap(num1_len, num2_len);
	}

	int carry = 0;
	for (int i = 0; i < num2_len; i++) {
		if (i < num1_len) {
			int t = (num1[i] - '0') + (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
		else {
			int t = (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
	}
	if (carry == 1) ans.push_back(1);

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	Decimal a;
	a.numerator.number = temp;
	a.denominator = n1.denominator;

	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	a.positive = a.numerator.positive;

	return a;
}

Decimal operator-(const Decimal& n1, const Integer& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Decimal n3 = n1;
		n3 = -n3;
		Decimal n4 = n3 + n2;
		return -n4;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Integer n3 = n2;
		n3 = -n3;
		Decimal n4 = n3 + n1;
		return n4;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Decimal n3 = n1;
		Integer n4 = n2;
		n3 = -n3;
		n4 = -n4;
		return n4 - n3;
	}

	Decimal a;
	Integer num = n1.denominator * n2;
	vector<int> ans;
	string num1 = n1.numerator.number, num2 = num.number;

	//check if the answer is positive
	if (num1.length() > num2.length()) {}
	else if (num2.length() > num1.length()) {
		swap(num1, num2);
		a.positive = -1;
	}
	else {
		for (int i = num1.length() - 1; i >= 0; i--) {
			if (num1[i] > num2[i]) {
				break;
			}
			if (num1[i] < num2[i]) {
				swap(num1, num2);
				a.positive = -1;
				break;
			}
		}
	}

	//substraction
	int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
	for (int i = 0; i < num1_len; i++) {
		if (i < num2_len) {
			int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
		else {
			int t = (num1[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
	}

	//clear redundant zeros ex.1000 - 999 = 0001 -> 1
	for (int i = ans.size() - 1; i > 0; i--) {
		if (ans[i] != 0)
			break;
		ans.pop_back();
	}

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	a.numerator.number = temp;
	a.denominator = n1.denominator;
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	return a;
}

Decimal operator*(const Decimal& num1, const Integer& num2) {
	if (num1.positive == -1 && num2.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Integer n3 = num2; n3 = -n3;
		return n2 * n3;
	}
	else if (num1.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Decimal n3 = n2 * num2;
		return -n3;
	}
	else if (num2.positive == -1) {
		Integer n2 = num2; n2 = -n2;
		Decimal n3 = num1 * n2;
		return -n3;
	}

	Decimal a;
	a.numerator = num1.numerator * num2;
	a.denominator = num1.denominator;
	a.positive = num1.positive * num2.positive;
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	return a;
}

Decimal operator/(const Decimal& num1, const Integer& num2) {
	if (num2.number == "0") {
		Decimal error;
		error.positive = 4;
		return error;
	}
	if (num1.positive == -1 && num2.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Integer n3 = num2; n3 = -n3;
		return n2 / n3;
	}
	else if (num1.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Decimal n3 = n2 / num2;
		return -n3;
	}
	else if (num2.positive == -1) {
		Integer n2 = num2; n2 = -n2;
		Decimal n3 = num1 / n2;
		return -n3;
	}

	Decimal a;
	a.numerator = num1.numerator;
	a.denominator = num1.denominator * num2;
	a.positive = num1.positive * num2.positive;
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	return a;
}

Decimal operator+(const Integer& n1, const Decimal& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Integer n3 = n1;
		n3 = -n3;
		return n2 - n3;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Decimal n3 = n2;
		n3 = -n3;
		return n1 - n3;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Integer n3 = n1;
		Decimal n4 = n2;
		n3 = -n3;
		n4 = -n4;
		Decimal n5 = n3 + n4;
		return -n5;
	}

	Integer num = n2.denominator * n1;
	string num1 = num.number, num2 = n2.numerator.number;
	vector<int>ans;

	int num1_len = num1.length(), num2_len = num2.length();
	if (num1_len > num2_len) {
		swap(num1, num2);
		swap(num1_len, num2_len);
	}

	int carry = 0;
	for (int i = 0; i < num2_len; i++) {
		if (i < num1_len) {
			int t = (num1[i] - '0') + (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
		else {
			int t = (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
	}
	if (carry == 1) ans.push_back(1);

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	Decimal a;
	a.numerator.number = temp;
	a.denominator = n2.denominator;

	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	a.positive = a.numerator.positive;
	return a;
}

Decimal operator-(const Integer& n1, const Decimal& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Integer n3 = n1;
		n3 = -n3;
		Decimal n4 = n3 + n2;
		return -n4;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Decimal n3 = n2;
		n3 = -n3;
		Decimal n4 = n3 + n1;
		return n4;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Integer n3 = n1;
		Decimal n4 = n2;
		n3 = -n3;
		n4 = -n4;
		return n4 - n3;
	}

	Decimal a;
	Integer num = n2.denominator * n1;
	vector<int> ans;
	string num1 = num.number, num2 = n2.numerator.number;

	//check if the answer is positive
	if (num1.length() > num2.length()) {}
	else if (num2.length() > num1.length()) {
		swap(num1, num2);
		a.positive = -1;
	}
	else {
		for (int i = num1.length() - 1; i >= 0; i--) {
			if (num1[i] > num2[i]) {
				break;
			}
			if (num1[i] < num2[i]) {
				swap(num1, num2);
				a.positive = -1;
				break;
			}
		}
	}

	//substraction
	int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
	for (int i = 0; i < num1_len; i++) {
		if (i < num2_len) {
			int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
		else {
			int t = (num1[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
	}

	//clear redundant zeros ex.1000 - 999 = 0001 -> 1
	for (int i = ans.size() - 1; i > 0; i--) {
		if (ans[i] != 0)
			break;
		ans.pop_back();
	}

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	a.numerator.number = temp;
	a.denominator = n2.denominator;

	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	a.positive = a.numerator.positive;
	return a;
}

Decimal operator*(const Integer& num1, const Decimal& num2) {
	if (num1.positive == -1 && num2.positive == -1) {
		Integer n2 = num1; n2 = -n2;
		Decimal n3 = num2; n3 = -n3;
		return n2 * n3;
	}
	else if (num1.positive == -1) {
		Integer n2 = num1; n2 = -n2;
		Decimal n3 = n2 * num2;
		return -n3;
	}
	else if (num2.positive == -1) {
		Decimal n2 = num2; n2 = -n2;
		Decimal n3 = num1 * n2;
		return -n3;
	}

	Decimal a;
	a.numerator = num1 * num2.numerator;
	a.denominator = num2.denominator;
	a.positive = num1.positive * num2.positive;
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	return a;
}

Decimal operator/(const Integer& num1, const Decimal& num2) {
	if (num2.numerator.number == "0") {
		Decimal error;
		error.positive = 4;
		return error;
	}
	if (num1.positive == -1 && num2.positive == -1) {
		Integer n2 = num1; n2 = -n2;
		Decimal n3 = num2; n3 = -n3;
		return n2 / n3;
	}
	else if (num1.positive == -1) {
		Integer n2 = num1; n2 = -n2;
		Decimal n3 = n2 / num2;
		return -n3;
	}
	else if (num2.positive == -1) {
		Decimal n2 = num2; n2 = -n2;
		Decimal n3 = num1 / n2;
		return -n3;
	}

	Decimal a;
	a.numerator = num1 * num2.denominator;
	a.denominator = num2.numerator;
	a.positive = num1.positive * num2.positive;
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	return a;
}

Decimal operator+(const Decimal& n1, const Decimal& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Decimal n3 = n1;
		n3 = -n3;
		return n2 - n3;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Decimal n3 = n2;
		n3 = -n3;
		return n1 - n3;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Decimal n3 = n1;
		Decimal n4 = n2;
		n3 = -n3;
		n4 = -n4;
		Decimal n5 = n3 + n4;
		return -n5;
	}

	Integer nn1 = n1.numerator * lcm(n1.denominator, n2.denominator) / n1.denominator, nn2 = n2.numerator * lcm(n1.denominator, n2.denominator) / n2.denominator;
	string num1 = nn1.number, num2 = nn2.number;
	vector<int>ans;

	int num1_len = num1.length(), num2_len = num2.length();
	if (num1_len > num2_len) {
		swap(num1, num2);
		swap(num1_len, num2_len);
	}

	int carry = 0;
	for (int i = 0; i < num2_len; i++) {
		if (i < num1_len) {
			int t = (num1[i] - '0') + (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
		else {
			int t = (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
	}
	if (carry == 1) ans.push_back(1);

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	Decimal a;
	a.numerator.number = temp;
	a.denominator = lcm(n1.denominator, n2.denominator);
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	a.positive = a.numerator.positive;
	return a;
}

Decimal operator-(const Decimal& n1, const Decimal& n2) {
	if (n1.positive == -1 && n2.positive == 1) {
		Decimal n3 = n1;
		n3 = -n3;
		Decimal n4 = n3 + n2;
		return -n4;
	}
	else if (n1.positive == 1 && n2.positive == -1) {
		Decimal n3 = n2;
		n3 = -n3;
		Decimal n4 = n3 + n1;
		return n4;
	}
	else if (n1.positive == -1 && n2.positive == -1) {
		Decimal n3 = n1;
		Decimal n4 = n2;
		n3 = -n3;
		n4 = -n4;
		return n4 - n3;
	}

	Decimal a;
	Integer nn1 = n1.numerator * lcm(n1.denominator, n2.denominator) / n1.denominator, nn2 = n2.numerator * lcm(n1.denominator, n2.denominator) / n2.denominator;
	string num1, num2;
	vector<int> ans;
	num1 = nn1.number;
	num2 = nn2.number;

	//check if the answer is positive
	if (num1.length() > num2.length()) {}
	else if (num2.length() > num1.length()) {
		swap(num1, num2);
		a.positive = -1;
	}
	else {
		for (int i = num1.length() - 1; i >= 0; i--) {
			if (num1[i] > num2[i]) {
				break;
			}
			if (num1[i] < num2[i]) {
				swap(num1, num2);
				a.positive = -1;
				break;
			}
		}
	}

	//substraction
	int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
	for (int i = 0; i < num1_len; i++) {
		if (i < num2_len) {
			int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
		else {
			int t = (num1[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
	}

	//clear redundant zeros ex.1000 - 999 = 0001 -> 1
	for (int i = ans.size() - 1; i > 0; i--) {
		if (ans[i] != 0)
			break;
		ans.pop_back();
	}

	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}

	a.numerator.number = temp;
	a.denominator = lcm(n1.denominator, n2.denominator);
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	a.positive = a.numerator.positive;
	return a;
}

Decimal operator*(const Decimal& num1, const Decimal& num2) {
	if (num1.positive == -1 && num2.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Decimal n3 = num2; n3 = -n3;
		return n2 * n3;
	}
	else if (num1.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Decimal n3 = n2 * num2;
		return -n3;
	}
	else if (num2.positive == -1) {
		Decimal n2 = num2; n2 = -n2;
		Decimal n3 = num1 * n2;
		return -n3;
	}

	Decimal a;
	a.numerator = num1.numerator * num2.numerator;
	a.denominator = num1.denominator * num2.denominator;
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	a.positive = num1.positive * num2.positive;
	return a;
}

Decimal operator/(const Decimal& num1, const Decimal& num2) {
	if (num2.numerator.number == "0") {
		Decimal error;
		error.positive = 4;
		return error;
	}
	if (num1.positive == -1 && num2.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Decimal n3 = num2; n3 = -n3;
		return n2 / n3;
	}
	else if (num1.positive == -1) {
		Decimal n2 = num1; n2 = -n2;
		Decimal n3 = n2 / num2;
		return -n3;
	}
	else if (num2.positive == -1) {
		Decimal n2 = num2; n2 = -n2;
		Decimal n3 = num1 / n2;
		return -n3;
	}

	Decimal a;
	a.numerator = num1.numerator * num2.denominator;
	a.denominator = num1.denominator * num2.numerator;
	reduct_fraction(a.numerator, a.denominator);
	a.number = divide(a.numerator, a.denominator);
	a.positive = num1.positive * num2.positive;
	return a;
}

Decimal factorial(const Decimal& num) {
	if (num.positive != -1 && num.positive != 1) { Decimal X; X.positive = 2; return X; }
	Decimal tmp = num;
	reduct_fraction(tmp.numerator, tmp.denominator);
	tmp.number = divide(tmp.numerator, tmp.denominator);
	if (tmp.denominator.number != "1") { Decimal X; X.positive = 2; return X; }

	Decimal one; one.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"; one.numerator.number = "1"; one.denominator.number = "1";
	Decimal now = tmp;
	Integer s;
	if (num.numerator.number == "0")
	{
		return one;
	}
	s = factorial((Integer)now);
	return (Decimal)s;
}

Decimal power(const Decimal& base, const Integer& exp) {
	if ((base.positive != 1 && base.positive != -1) || (exp.positive != 1 && exp.positive != -1)) { Decimal X; X.positive = 3; return X; }
	Integer one_i; one_i.number = "1";
	Decimal zero, one; zero.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"; one.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"; one.numerator.number = "1";
	Decimal b = base;
	reduct_fraction(b.numerator, b.denominator);
	if (b.numerator.number == "1" && base.denominator.number == "1") { return one; }
	if (exp.number == "0") { return one; }
	if (base.numerator.number == "0") { return zero; }
	Decimal re = base; Integer tmp = exp; tmp.positive=1;
	while (tmp.number != "1") 
	{ 
		re = re * base; 
		tmp = tmp - one_i; 
	}
	re.number = divide(re.numerator, re.denominator);
	if (exp.positive == 1) {
		return re;
	}
	else {
		if (exp.positive == -1) {
			return one / re;
		}
	}
}

Decimal power(const Decimal& base, const Decimal& exp) 
{
	if ((base.positive != 1 && base.positive != -1) || (exp.positive != 1 && exp.positive != -1)) { Decimal X; X.positive = 3; return X; }
	Decimal b = base, e = exp, one, two, zero; e.positive = 1;
	zero.number.insert(0, 101, '0'); one.number.insert(0, 100, '0'); one.number.append(1, '1'); one.numerator.number = "1"; two = one + one;
	if (exp.numerator.number == "0") { return one; }
	if (base.numerator.number == "0") { return zero; }
	if (base.numerator.number == "1" && base.denominator.number == "1") { return one; }
	reduct_fraction(b.numerator, b.denominator);
	reduct_fraction(e.numerator, e.denominator);

	if (e.denominator.number=="2") {
		if (base.positive == -1) { Decimal X; X.positive = 3; return X; }
		e = e * two;

		Decimal re = base;
		while (e.number != one.number) {
			re = re * base;
			e = e - one;
		}
		Decimal next, now = re / two; next.number = "0";

		while (next.number != now.number) {
			next = tashi(wali(now,two),wali(re,kake(two,now)));
			swap(next, now);
			if (now.positive != 1 && now.positive != -1) { Decimal X; X.positive = 4; return X; }
		}
		if (exp.positive == -1) {
			Decimal a;
			a.numerator.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
			a.denominator.number = now.number;
			while (a.denominator.number[a.denominator.number.length() - 1] == '0' && a.denominator.number.length() > 1)
			{
				a.denominator.number.pop_back();
				a.numerator.number = "0" + a.numerator.number;
			}
			reduct_fraction(a.numerator, a.denominator);
			a.number = divide(a.numerator, a.denominator);
			return a;
		}
		else {
			if (exp.positive == 1) {
				Decimal a;
				a.denominator.number = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
				a.numerator.number = now.number;
				while (a.numerator.number[a.numerator.number.length() - 1] == '0' && a.numerator.number.length() > 1)
				{
					a.numerator.number.pop_back();
					a.denominator.number = "0" + a.denominator.number;
				}
				reduct_fraction(a.numerator, a.denominator);
				a.number = divide(a.numerator, a.denominator);
				return a;
			}
		}
	}
	else {
		Decimal re = base;
		while (e.number != one.number) {
			re = re * base;
			e = e - one;
		}
		if (exp.positive == -1) {
			return one / re;
		}
		else {
			if (exp.positive == 1) {
				return re;
			}
		}
	}
}

Decimal tashi(const Decimal& n1, const Decimal& n2)
{
	if ((n1.positive != 1 && n1.positive != -1) || (n2.positive != 1 && n2.positive != -1)) { Decimal X; X.positive = 4; return X; }
	string num1 = n1.number, num2 = n2.number;
	vector<int>ans;
	int num1_len = num1.length(), num2_len = num2.length();
	if (num1_len > num2_len) {
		swap(num1, num2);
		swap(num1_len, num2_len);
	}
	int carry = 0;
	for (int i = 0; i < num2_len; i++) {
		if (i < num1_len) {
			int t = (num1[i] - '0') + (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
		else {
			int t = (num2[i] - '0') + carry;
			if (t >= 10) {
				carry = 1;
				t -= 10;
			}
			else carry = 0;
			ans.push_back(t);
		}
	}
	if (carry == 1) ans.push_back(1);
	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}
	Decimal a;
	a.number = temp;
	a.positive = 1;
	return a;
}

Decimal hiki(const Decimal& n1, const Decimal& n2)
{
	if ((n1.positive != 1 && n1.positive != -1) || (n2.positive != 1 && n2.positive != -1)) { Decimal X; X.positive = 4; return X; }
	Decimal a;
	string num1, num2;
	vector<int> ans;
	num1 = n1.number;
	num2 = n2.number;
	//check if the answer is positive
	if (num1.length() > num2.length()) {}
	else if (num2.length() > num1.length()) {
		swap(num1, num2);
		a.positive = -1;
	}
	else {
		for (int i = num1.length() - 1; i >= 0; i--) {
			if (num1[i] > num2[i]) {
				break;
			}
			if (num1[i] < num2[i]) {
				swap(num1, num2);
				a.positive = -1;
				break;
			}
		}
	}
	//substraction
	int borrow = 0, num1_len = num1.length(), num2_len = num2.length();
	for (int i = 0; i < num1_len; i++) {
		if (i < num2_len) {
			int t = (num1[i] - '0') - (num2[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
		else {
			int t = (num1[i] - '0') + borrow;
			if (t < 0) {
				borrow = -1;
				t += 10;
			}
			else borrow = 0;
			ans.push_back(t);
		}
	}
	//clear redundant zeros ex.1000 - 999 = 0001 -> 1
	for (int i = ans.size() - 1; i > 0; i--) {
		if (ans[i] != 0)
			break;
		ans.pop_back();
	}
	string temp;
	for (int i = 0; i < ans.size(); i++) {
		temp.append(1, (char)(ans[i] + '0'));
	}
	while (temp.length() < 101)
	{
		temp.append(1, '0');
	}
	a.number = temp;
	return a;
}

Decimal kake(const Decimal& num1, const Decimal& num2)
{
	if ((num1.positive != 1 && num1.positive != -1) || (num2.positive != 1 && num2.positive != -1)) { Decimal X; X.positive = 4; return X; }
	string zero = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	if (num1.number == zero || num2.number == zero) {
		Decimal A;
		A.number = zero;
		A.positive = 1;
		return A;
	}
	vector<Integer> list_to_plus;
	for (int i = 0; i < num2.number.length(); i++)
	{
		int q = 0;
		string temp = num1.number;
		for (int j = 0; j < num1.number.length(); j++)
		{
			int c = ((temp[j] - '0') * (num2.number[i] - '0') + q) % 10;
			q = ((temp[j] - '0') * (num2.number[i] - '0') + q) / 10;
			temp[j] = c + '0';
			if (j == num1.number.length() - 1 && q > 0)
			{
				temp.append(1, q + '0');
			}
		}
		Integer A;
		A.number = temp;
		list_to_plus.push_back(A);
	}
	for (int i = 0; i < list_to_plus.size(); i++)
	{
		string x = "";
		for (int j = 0; j < i; j++)
		{
			x.append(1, '0');
		}
		list_to_plus[i].number = x + list_to_plus[i].number;
	}
	vector<Decimal> list;
	for (int i = 0; i < list_to_plus.size(); i++)
	{
		Decimal tmp;
		tmp.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + list_to_plus[i].number;
		list.push_back(tmp);
	}
	Decimal re;
	re.number = "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	for (int i = 0; i < list.size(); i++)
	{
		re = tashi(re,list[i]);
	}
	
	re.number = re.number.substr(200);
	re.positive = num1.positive * num2.positive;
	
	return re;
}

Decimal wali(const Decimal& num1, const Decimal& num2)
{
	if ((num1.positive != 1 && num1.positive != -1) || (num2.positive != 1 && num2.positive != -1)) { Decimal X; X.positive = 4; return X; }
	Decimal n1 = num1, n2 = num2;
	n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n1.number; n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n2.number;
	string t = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	if (num1.number == t)
	{
		Decimal X;
		X.number = t;
		return X;
	}
	else
	{
		if (num2.number == t)
		{
			Decimal X;
			X.positive == 4;
			return X;
		}
	}
	while (n1.number[n1.number.length() - 1] == '0')
	{
		n1.number.pop_back();
		n1.number = "0" + n1.number;
		n2.number = "0" + n2.number;
	}
	while (n2.number[n2.number.length() - 1] == '0')
	{
		n2.number.pop_back();
		n2.number = "0" + n2.number;
		n1.number = "0" + n1.number;
	}
	while (n1.number.length() > n2.number.length())
	{
		t = "0" + t;
		n2.number = "0" + n2.number;
	}
	for (int i = t.length() - 1; i > -1; i--)
	{
		int m = 0;
		while (1)
		{
			Decimal A;
			A = hiki(n1,n2);
			if (A.positive < 0) { break; }
			n1 = hiki(n1,n2);
			m++;
		}
		t[i] = m + '0';
		m = 0;
		n2.number.erase(n2.number.begin());
		if (n2.number.length() < 101) { n2.number.append(1, '0'); }
	}
	while (t[t.length() - 1] == '0')
	{
		t.pop_back();
	}
	while (t.length() < 101)
	{
		t.append(1, '0');
	}
	Decimal temp;
	temp.number = t;
	temp.positive = num1.positive * num2.positive;
	return temp;
}

/*void Decimal::operator=(const NumberObject& input) {
	number = input.number;
	positive = input.positive;
	point_index = input.point_index;
}*/

Decimal Decimal::operator-() {
	if (this->number != "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000") {
		this->positive *= -1;
	}
	return *this;
}

Decimal::operator Integer() {
	//Integer tmp;
	//this->number = divide(numerator, denominator);
	//string str = this->number;
	//if (str.back() == '0')
	//	tmp.positive = 1;
	//else
	//	tmp.positive = this->positive;
	//tmp.number = str.substr(100);
	//return tmp;
	Integer tmp;
	tmp = numerator / denominator;
	return tmp;
}

NumberObject::NumberObject() {
	positive = -128;
	number = "";
	point_index = 0;
}

string divide(const Integer& num1, const Integer& num2) {
	Integer n1 = num1, n2 = num2;
	n1.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n1.number;
	n2.number = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" + n2.number;
	string t = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	if (num1.number == "0")
	{
		return t;
	}
	if (num1.number == t) {
		return t;
	}

	while (n1.number.length() > n2.number.length()) {
		t = "0" + t;
		n2.number = "0" + n2.number;
	}

	for (int i = t.length() - 1; i > -1; i--) {
		int m = 0;
		while (1) {
			Integer A;
			A = n1 - n2;
			// cout << A << endl;
			if (A.positive < 0) { break; }
			n1 = n1 - n2;
			m++;
		}
		t[i] = m + '0';
		m = 0;
		n2.number.erase(n2.number.begin());
	}
	while (t[t.length() - 1] == '0' && t.length() > 101) {
		t.pop_back();
	}

	return t;
}

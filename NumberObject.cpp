#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<iterator>
#include"NumberObject.h"

using namespace std;

//NumberObject
ostream& operator<<(ostream& io, NumberObject& num)
{
    if (num.point_index == 0)
    {
        if (num.positive > 0)
        {
            string temp = num.number;
            reverse(temp.begin(), temp.end());
            io << temp << endl;
            return io;
        }
        else
        {
            string temp = num.number;
            reverse(temp.begin(), temp.end());
            io << "-" << temp << endl;
            return io;
        }
    }
    else
    {
        if (num.positive > 0)
        {
            string temp = num.number;
            reverse(temp.begin(), temp.end());
            for (int i = 0; i < temp.length(); i++)
            {
                if (temp.length() - i == 100)
                {
                    cout << '.';
                }
                io << temp[i];
            }
            io << endl;
            return io;
        }
        else
        {
            string temp = num.number;
            int c = temp.length();
            reverse(temp.begin(), temp.end());
            io << "-" << temp << endl;
            for (int i = 0; i < temp.length(); i++)
            {
                if (temp.length() - i == 100)
                {
                    cout << '.';
                }
                io << temp[i];
            }
            io << endl;
            return io;
        }
    }
}

//int
Integer::Integer()
{
	point_index = 0;
	positive = 1;
}

Integer::Integer(const Integer& reference)
{
	number = reference.number;
	point_index = reference.point_index;
	positive = reference.positive;
}

Integer operator+(const Integer& n1, const Integer& n2)
{
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

Integer operator-(const Integer& n1, const Integer& n2)
{
    Integer a;
    string num1, num2;
    vector<int> ans;
    num1 = n1.number;
    num2 = n2.number;

    //check if the answer is positive
    if (num1.length() > num2.length()){}
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

Integer operator*(const Integer &num1, const Integer &num2)
{
    if (num1.number == "0" || num2.number == "0")
    {
        Integer A;
        A.number = "0";
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
    Integer re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.positive = num1.positive * num2.positive;
    return re;
}

Decimal::Decimal() 
{ 
    point_index = 1; positive = 1;
}

Decimal::Decimal(const Decimal& reference)
{
    number = reference.number;
    point_index = reference.point_index;
    positive = reference.positive;
}

Decimal operator+(const Decimal& n1, const Integer& n2)
{
    string num1 = n1.number, num2 = n2.number;
    num2.insert(0, 100, '0');
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

Decimal operator-(const Decimal& n1, const Integer& n2)
{
    Decimal a;
    string num1, num2;
    vector<int> ans;
    num1 = n1.number;
    num2 = n2.number;
    num2.insert(0, 100, '0');

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

Decimal operator*(const Decimal& num1, const Integer& num2)
{
    string zero = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == zero || num2.number == "0") {
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
    Decimal re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.positive = num1.positive * num2.positive;
    re.number = re.number.substr(100);
    return re;
}

Decimal operator+(const Integer& n1, const Decimal& n2)
{
    string num1 = n1.number, num2 = n2.number;
    num1.insert(0, 100, '0');
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

Decimal operator-(const Integer& n1, const Decimal& n2)
{
    Decimal a;
    string num1, num2;
    vector<int> ans;
    num1 = n1.number;
    num2 = n2.number;
    num1.insert(0, 100, '0');

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

Decimal operator*(const Integer& num1, const Decimal& num2)
{
    string zero = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (num1.number == "0" || num2.number == zero) {
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
    Decimal re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.positive = num1.positive * num2.positive;
    re.number = re.number.substr(100);
    return re;
}

Decimal operator+(const Decimal& n1, const Decimal& n2)
{
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

Decimal operator-(const Decimal& n1, const Decimal& n2)
{
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

    a.number = temp;
    return a;
}

Decimal operator*(const Decimal& num1, const Decimal& num2)
{
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
    Decimal re;
    re.number = "0";
    for (int i = 0; i < list_to_plus.size(); i++)
    {
        re = re + list_to_plus[i];
    }
    re.number = re.number.substr(200);
    re.positive = num1.positive * num2.positive;
    return re;
}

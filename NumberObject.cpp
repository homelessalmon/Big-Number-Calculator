#include<vector>
#include<string>
#include<iostream>
#include"NumberObject.h"

using namespace std;

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
Integer operator*(const Integer &A, const Integer &B)
{
	vector<Integer> list_to_plus;
	for (int i = 0; i < B.number.length(); i++)
	{
		for (int j = 0; j < A.number.length(); j++)
		{

		}
	}
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
    
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

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
    for(int i=0;i<ans.size();i++) {
        temp.append(1,(char)(ans[i]+'0'));
    }

    Integer a;
    a.number = temp;
    return a;
}

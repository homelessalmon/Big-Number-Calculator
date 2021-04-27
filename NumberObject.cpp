#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<iterator>
#include"NumberObject.h"

using namespace std;
//NumberObject
iostream& operator<<(iostream &io, NumberObject &num)
{
	if(num.point_index == 0)
	{
		if(num.positive > 0)
		{
			string temp=num.number;
			reverse(temp.begin(),temp.end());
			io<<temp<<endl;
			return io;
		}
		else
		{
			string temp=num.number;
			reverse(temp.begin(),temp.end());
			io<<"-"<<temp<<endl;
			return io;
		}
	}
	else
	{
		if(num.positive > 0)
		{
			int c=
			string temp=num.number;
			reverse(temp.begin(),temp.end());
			for_each(temp.begin(),temp.end(),[](
			return io;
		}
		else
		{
			string temp=num.number;
			reverse(temp.begin(),temp.end());
			io<<"-"<<temp<<endl;
			return io;
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

Integer operator*(const Integer &num1, const Integer &num2)
{
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
    for(int i=0;i<ans.size();i++) {
        temp.append(1,(char)(ans[i]+'0'));
    }

    Integer a;
    a.number = temp;
    return a;
}

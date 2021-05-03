#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<algorithm>
typedef class Decimal Decimal;

using namespace std;


class NumberObject
{
public:
	//variable
	string number;
	int positive;//positive 1,negative -1;
	//未定義 = -128
	/* positive等於這些數字時表示：
	2 = 階乘定義域外，3 = 冪次定義域外，4 = 除法定義域外
	10 = 不存在的變數
	20 = 前括號太多，21 = 後括號太多
	30 = 算式第一字元是非法運算子，31 = 算式最後字元是非法運算子
	32 = !的前後出現非數，33 = ^ * /的前出現非數或後出現非+-數
	34 = + -的後出現非+-數 35 = 數與數接在一起
	36 = 算式merge出現問題
	40 = 階乘有問題，41 = 冪次有問題，42 = 正負號有問題，43 = 乘除有問題，44 = 加減有問題
	50 = 算式最後還剩下一個以上的數
	*/
	NumberObject();
	int point_index;//index of the point,0 if create by default constructor
	//function
	friend ostream& operator>>(iostream&, NumberObject&);
	friend ostream& operator<<(ostream&, NumberObject);
	//operator Integer();//亂用可能會有危險
	//operator Decimal();//亂用可能會有危險
};

class Integer : public NumberObject
{
public:
	//variable
	//function
	Integer();
	Integer(const Integer& reference);
	Integer(const string a_string);//example: BigNumber A="3*1+2";
	//Integer& operator=(const Decimal&);
	friend Integer operator+(const Integer&, const Integer&);
	friend Integer operator-(const Integer&, const Integer&);
	friend Integer operator*(const Integer&, const Integer&);
	friend Integer operator/(const Integer&, const Integer&);
	friend Integer factorial(const Integer&);
	friend Integer power(const Integer& base, const Integer& exp);
	
	friend bool operator >(const Integer&, const Integer&);
	friend bool operator >=(const Integer&, const Integer&);
	friend Integer operator%(const Integer&, const Integer&);
	friend Integer gcd(const Integer&, const Integer&);
	friend Integer lcm(const Integer&, const Integer&);
	//void operator=(const NumberObject&);
	Integer operator-();
	operator Decimal();
};

class Decimal : public NumberObject
{
public:
	//variable
	//function
	Integer numerator;
	Integer denominator;
	Decimal();
	Decimal(const Decimal& reference);
	Decimal(const string a_string);//example: BigNumber A="3*1+2.5";
	//Decimal& operator=(const Decimal&);
	friend Decimal operator+(const Decimal&, const Integer&);
	friend Decimal operator-(const Decimal&, const Integer&);
	friend Decimal operator*(const Decimal&, const Integer&);
	friend Decimal operator/(const Decimal&, const Integer&);
	friend Decimal operator+(const Integer&, const Decimal&);
	friend Decimal operator-(const Integer&, const Decimal&);
	friend Decimal operator*(const Integer&, const Decimal&);
	friend Decimal operator/(const Integer&, const Decimal&);
	friend Decimal operator+(const Decimal&, const Decimal&);
	friend Decimal operator-(const Decimal&, const Decimal&);
	friend Decimal operator*(const Decimal&, const Decimal&);
	friend Decimal operator/(const Decimal&, const Decimal&);
	friend Decimal factorial(const Decimal&);
	friend Decimal power(const Decimal& base, const Integer& exp);
	friend Decimal power(const Decimal& base, const Decimal& exp);
	friend D power(const Integer& base, const Decimal& exp);
	friend void reduct_fraction(Integer&, Integer&);
	friend Decimal kake(const Decimal&, const Decimal&);
	friend Decimal hiki(const Decimal&, const Decimal&);
	friend Decimal tashi(const Decimal&, const Decimal&);
	friend Decimal wali(const Decimal&, const Decimal&);
	//void operator=(const NumberObject&);
	Decimal operator-();
	operator Integer();
};

string divide(const Integer&, const Integer&);

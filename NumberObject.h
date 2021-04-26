#pragma once
#include<string>
#include<vector>
//
using namespace std;
//
class NumberObject
{
public:
	//variable
	string number;
	int point_index;//index of the point,0 if create by default constructor
	//function
	friend iostream& operator>>(iostream&, Integer&);
	friend iostream& operator<<(iostream&, Integer&);
};

class Integer : public NumberObject
{
public:
	//variable
	//function
	Integer();
	Integer(const string a_string);//example: BigNumber A="3*1+2";
	friend iostream& operator>>(iostream&, Integer&);
	friend iostream& operator<<(iostream&, Integer&);
	Integer& operator=(const Integer&);
	Integer& operator=(const Decimal&);
	friend Integer operator+(const Integer&, const Integer&);
	friend Integer operator-(const Integer&, const Integer&);
	friend Integer operator*(const Integer&, const Integer&);
	friend Integer operator/(const Integer&, const Integer&);
	operator Decimal();
};

class Decimal : public NumberObject
{
public:
	//variable
	//function
	Decimal();
	Decimal(const string a_string);//example: BigNumber A="3*1+2.5";
	friend iostream& operator>>(iostream&, Decimal&);
	friend iostream& operator<<(iostream&, Decimal&);
	Decimal& operator=(const Integer&);
	Decimal& operator=(const Decimal&);
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
	operator Integer();
};
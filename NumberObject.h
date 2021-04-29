#pragma once
#include<string>
#include<vector>
#define TEST 1
//
using namespace std;
//
class NumberObject
{
public:
	//variable
	string number;
	int positive;//positive 1,negative -1;
	int point_index;//index of the point,0 if create by default constructor
	//function
	friend ostream& operator<<(ostream&, NumberObject&);
#if TEST == 0
	friend istream& operator>>(istream&, NumberObject&)
#endif
};

class Integer : public NumberObject
{
public:
	//variable
	//function
	Integer();
	Integer(const Integer& reference);
	Integer(const string a_string);//example: BigNumber A="3*1+2";
	//Integer& operator=(const Integer&);
	friend Integer operator+(const Integer&, const Integer&);
	friend Integer operator-(const Integer&, const Integer&);
	friend Integer operator*(const Integer&, const Integer&);
	friend Integer operator/(const Integer&, const Integer&);
	Integer operator+();
	Integer operator-();
	//operator Decimal();
	//Decimal calc_inverse();
};

class Decimal : public NumberObject
{
public:
	//variable
	//function
	Decimal(){ point_index = 1; positive = 1; }
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
	Decimal operator+();
	Decimal operator-();
	//operator Integer();
	//Decimal calc_inverse();
};

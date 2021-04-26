#include<vector>
#include<string>
#include<iostream>
#include"NumberObject.h"

using namespace std;

//int
Integer::Integer()
{
	point_index = 0;
}
Integer::Integer(const Integer& reference)
{
	number = reference.number;
	point_index = reference.point_index;
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
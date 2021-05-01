#include<vector>
#include<string>
#include"Variable_handling.h"
#include"NumberObject.h"

using namespace std;

void Variable_list::push_pack(string name, Integer number)
{
	variable_name_I.push_back(name);
	Number_I.push_back(number);
}

void Variable_list::push_pack(string name, Decimal number)
{
	variable_name_D.push_back(name);
	Number_D.push_back(number);
}

int Variable_list::find(string name)
{
	for (int i = 0; i < variable_name_I.size(); i++)
	{
		if (name == variable_name_I[i])
		{
			return i;
		}
	}
	for (int i = 0; i < variable_name_D.size(); i++)
	{
		if (name == variable_name_D[i])
		{
			return_ptr = &Number_D[i];
			return i + 100;
		}
	}
}

void Variable_list::del_var(string name)
{
	for (int i = 0; i < variable_name_I.size(); i++)
	{
		if (name == variable_name_I[i])
		{
			variable_name_I.erase(variable_name_I.begin() + i);
			Number_I.erase(Number_I.begin() + i);
		}
	}
	for (int i = 0; i < variable_name_D.size(); i++)
	{
		if (name == variable_name_D[i])
		{
			variable_name_D.erase(variable_name_D.begin() + i);
			Number_D.erase(Number_D.begin() + i);
		}
	}
}

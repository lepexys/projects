#include "pch.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
#include <vector>
#include <list>

using namespace std;
class vstack
{
public:
	vector <char> stack;
	void push(char&);
	bool pop();
	bool is_full();
	bool is_empty();
	char top();
};
void vstack::push(char& val)
{
	stack.push_back(val);
}

bool vstack::pop()
{
	if (stack.size())
	{
		stack.erase(stack.begin() + 0);
		return true;
	}
	return false;
}

bool vstack::is_full()
{
	if (stack[stack.capacity()-1])
		return true;
	return false;
}
bool vstack::is_empty()
{
	if (stack[0])
		return true;
	return false;
}
char vstack::top()
{
	return stack[0];
}
int main(char* arg)
{
	vstack loaded_stack;
	char f_name[14];
	setlocale(LC_ALL, "rus");
	cout << "Enter file_name\n";
	cin >> f_name;
	ifstream in_file(f_name);
	int cur, u = 1;
	char buff[256] = { 0 };
	while (in_file.get(buff, 256))
	{
		for (int i = 255; i >= 0; i--)
		{
			if (buff[i])
				loaded_stack.push(buff[i]);
		}
		cur = loaded_stack.stack.size();
		for (int i = 0; i < cur; i++)
		{
			cout << loaded_stack.top();
			loaded_stack.pop();
		}
		cout << endl;
		memset(buff, 0, 256);
	}
	in_file.close();
}

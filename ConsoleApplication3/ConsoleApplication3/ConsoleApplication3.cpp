// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{
	int num;
	int numbers[9];

	for (int i = 0; i < 9; i++)
		numbers[i] = 0;

	cin >> num;
	int a, b, c, d, e;
	for (int i = 1; (int)(num/10^i) != 0; i++)
	{
		c = num % (10 ^ (i - 1));
		b = num % (10 ^ i);
		d = (b - c) / 10 ^ i;
		cout << c << "\n" << b << "\n" << d;
	}

	for (int i = 0; i < 9; i++) 
	{
		if (numbers[i] > 0)
		cout << "Number: " << i << " Entrance " << numbers[i] << " times" << endl;
	
	}
    return 0;
}


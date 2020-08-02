#include "pch.h"
#include <iostream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
using namespace std;
const int n = 4;

int main()
{
	setlocale(LC_ALL, "rus");
	int a[n][n] = { {0, 0, 8, 3}, {9, 0, 0, 2}, {5, 2, 0, 6}, {3, 6, 8, 0} };
	int max[n] = { 0 };
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (a[i][k] && a[k][j] && i != j)
					if (a[i][k] + a[k][j] < a[i][j] || a[i][j] == 0)
						a[i][j] = a[i][k] + a[k][j];
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
			cout << a[k][i]<<" ";
		cout << endl;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (max[i] < a[j][i])
				max[i] = a[j][i];
	for (int i = 0; i < n; i++)
		cout << max[i] << " ";
	cout << endl;
	int num = 0, kol = INT_MAX;
	for (int i=0; i < n; i++)
		if (max[i] < kol)
		{
			kol = max[i];
			num = i+1;
		}
	printf("Центр орграфа - точка № %d", num);
}

#include "stdafx.h"
#include <iostream>
#include <ctime>

using namespace std;

template <class X>
void CreateRand(X* a, int n)
{
	srand(time(0));
	for (X *i = a; i < a+n; i++)
	{
		*i = (X)(rand()%100);
		cout << *i << " ";
	}
	cout << endl;
}
template <class X>
void Create(X* a, int n)
{
	for (X *i = a; i < a + n; i++)
	{
		cin >> *i;
	}
}
void Create(char* a, int n)
{
	char b;
	for (char *i = a; i < a + n; i++)
	{
		cin >> b;
		while (isdigit((int)b))
		{
			cout << "Ввести не цифру" << endl;
			cin >> b;
		}
		cout <<"^"<< (int)b<<endl;
		*i = b;
	}
}
template <class X>
int* Lover(X* a, int n)
{
	cout << "Give me digit ";
	X k;
	int h=0,j=0;
	int* ret = (int*)calloc(n,sizeof(int));
	cin >> k;
	for (X *i = a; i < a + n; i++)
	{
		if (*i <= k)
		{
			*(ret + j) = h;
			j++;
		}
		h++;
	}
	ret = (int*)realloc(ret, j * sizeof(int));
	return ret;
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	int* gg;
	cout << "Give me number ";
	cin >> n;
	char* arch = new char[n];
	Create(arch, n);
	gg = Lover(arch, n);
	if (gg!=nullptr)
	while (*gg >= 0)
	{
		cout << *gg << " ";
		gg++;
	}
	cout <<endl<< "Give me number ";
	cin >> n;
	double* arr = new double[n];
	CreateRand(arr, n);
	gg = Lover(arr,n);
	while (*gg >= 0)
	{
		cout << *gg<<" ";
		gg++;
	}
	system("pause");
    return 0;
}
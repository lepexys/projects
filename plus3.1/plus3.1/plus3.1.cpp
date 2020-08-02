#include "pch.h"
#include <iostream>
#include <fstream>
#include <clocale>
#include <time.h>
#include <iomanip>
using namespace std;

struct Sort
{
	long Simple(int* m,int s)
	{
		int temp = NULL, pos = NULL;
		long count = 0;
		for (int i = 1; i < s; i++)
		{
			temp = m[i];
			count++;
			pos = i-1;
			while (pos >= 0)
			{
				if (m[pos] <= temp)
				{
					m[pos + 1] = temp;
					count++;
					break;
				}
				else
				{
					m[pos + 1] = m[pos];
					count++;
					if (pos == 0)
					{
						m[0] = temp;
						count++;
					}
				}
				pos--;
			}
		}
		return count;
	}
	long Bubble(int* m, int s)
	{
		int temp = NULL;
		long count = 0;
		for (int i = 0; i < s; i++)
			for (int j = 0; j < s - i-1; j++)
			{
				if (m[j] > m[j + 1])
				{
					temp = m[j];
					m[j] = m[j + 1];
					m[j + 1] = temp;
					count += 3;
				}
			}
		return count;
	}
	long Choise(int* m, int s)
	{
		int min,temp;
		long count = 0;
		for (int i = 0; i < s - 1; i++)
		{
			min = i;
			count++;
			for (int j = i + 1; j < s; j++)
				if (m[j] < m[min]) { min = j; count++; }
			if (min != i)
			{
				temp = m[min];
				m[min] = m[i];
				m[i] = temp;
				count += 3;
			}
		}
		return count;
	}
	long Pyramid(int* m, int s)
	{
		long count = 0;
		int size = s-1,temp;
		for (int i = (s-1) / 2; i >= 0; i--)
			count+=pushdown(i, m, s);
		for (int i = s-1; i > 0; i--)
		{
			temp = m[0];
			m[0] = m[i];
			m[i] = temp;
			count += 3;
			size--;
			count += pushdown(0, m, size);
		}
		return count;
	}
	private : long pushdown(int i, int* m,int s)
	{
		int temp=m[i];
		long count = 0;
		while (true)
		{
			if ((i + 1) * 2 <= s)
			{
				if (m[(i+1) * 2-1] < m[(i+1) * 2])
				{
					if (m[(i + 1) * 2] > temp)
					{
						m[i] = m[(i + 1) * 2];
						count++;
						i = (i + 1) * 2;
					}
					else
					{
						m[i] = temp;
						count++;
						break;
					}
				}
				else
					if (m[(i + 1) * 2 - 1] > temp)
					{
						m[i] = m[(i + 1) * 2 - 1];
						count++;
						i = (i + 1) * 2 - 1;
					}
					else
					{
						m[i] = temp;
						count++;
						break;
					}
			}
			else
				if ((i + 1) * 2 - 1 <= s)
				{
					if (temp < m[(i + 1) * 2-1])
					{
						m[i] = m[(i + 1) * 2-1];
						count++;
						i = (i + 1) * 2-1;
					}
					else
					{
						m[i] = temp;
						count++;
						break;
					}
				}
				else
				{
					m[i] = temp;
					count++;
					break;
				}
		}
		return count;
	}
};
int main()
{
	srand(time(0));
	int t;
	const int n1 = 1000, n2 = 5000, n3 = 10000, n4 = 15000;
	setlocale(LC_ALL, "Russian");
	Sort s;
	int a1[n1],a11[n1],a12[n1],a13[n1],a14[n1], a2[n2], a21[n2], a22[n2], a23[n2], a24[n2], a3[n3], a31[n3], a32[n3], a33[n3], a34[n3], a4[n4], a41[n4], a42[n4], a43[n4], a44[n4], test[10] = { 3,1,5,2,7,4,8,10,6,1};
	for (int i = 0; i < n1; i++)
		a1[i] = rand() % n1;
	for (int i = 0; i < n1; i++)
		a11[i] = a1[i];
	for (int i = 0; i < n1; i++)
		a12[i] = a1[i];
	for (int i = 0; i < n1; i++)
		a13[i] = a1[i];
	for (int i = 0; i < n1; i++)
		a14[i] = a1[i];
	cout << "Кол-во присваиваний пирамида, тест: " << s.Pyramid(test, 10) << endl;
	cout << "Кол-во присваиваний пирамида, несортированный: " << s.Pyramid(a11, n1) << endl;
	cout << "Кол-во присваиваний пирамида, сортированный: " << s.Pyramid(a11, n1) << endl;
	for (int i = 0; i < n1 / 2; i++)
	{
		t = a11[i];
		a11[i] = a11[n1 - i-1];
		a11[n1 - i - 1] = t;
	}
	cout << "Кол-во присваиваний пирамида, обратный: " << s.Pyramid(a11, n1) << endl;
	cout << "Кол-во присваиваний вставки, несортированный: " << s.Simple(a12, n1) << endl;
	cout << "Кол-во присваиваний вставки, сортированный: " << s.Simple(a12, n1) << endl;
	for (int i = 0; i < n1 / 2; i++)
	{
		t = a12[i];
		a12[i] = a12[n1 - i - 1];
		a12[n1 - i - 1] = t;
	}
	cout << "Кол-во присваиваний вставки, обратный: " << s.Simple(a12, n1) << endl;
	cout << "Кол-во присваиваний пузырёк, несортированный: " << s.Bubble(a13, n1) << endl;
	cout << "Кол-во присваиваний пузырёк, сортированный: " << s.Bubble(a13, n1) << endl;
	for (int i = 0; i < n1 / 2; i++)
	{
		t = a13[i];
		a13[i] = a13[n1 - i - 1];
		a13[n1 - i - 1] = t;
	}
	cout << "Кол-во присваиваний пузырёк, обратный: " << s.Bubble(a13, n1) << endl;
	cout << "Кол-во присваиваний выбором, несортированный: " << s.Choise(a14, n1) << endl;
	cout << "Кол-во присваиваний выбором, сортированный: " << s.Choise(a14, n1) << endl;
	for (int i = 0; i < n1 / 2; i++)
	{
		a14[i] = a14[n1 - i - 1];
	}
	cout << "Кол-во присваиваний выбором, обратный: " << s.Choise(a14, n1) << endl;
	for (int i = 0; i < n2; i++)
		a2[i] = rand() % n2;
	for (int i = 0; i < n1; i++)
		a21[i] = a2[i];
	for (int i = 0; i < n1; i++)
		a22[i] = a2[i];
	for (int i = 0; i < n1; i++)
		a23[i] = a2[i];
	for (int i = 0; i < n1; i++)
		a24[i] = a2[i];
	cout << "Кол-во присваиваний пирамида, несортированный: " << s.Pyramid(a2, n2) << endl;
	cout << "Кол-во присваиваний пирамида, сортированный: " << s.Pyramid(a21, n2) << endl;
	for (int i = 0; i < n2 / 2; i++)
	{
		a21[i] = a21[n2 - i - 1];
	}
	cout << "Кол-во присваиваний пирамида, обратный: " << s.Pyramid(a21, n2) << endl;
	cout << "Кол-во присваиваний вставки, несортированный: " << s.Simple(a22, n2) << endl;
	cout << "Кол-во присваиваний вставки, сортированный: " << s.Simple(a22, n2) << endl;
	for (int i = 0; i < n2 / 2; i++)
	{
		a22[i] = a22[n2 - i - 1];
	}
	cout << "Кол-во присваиваний вставки, обратный: " << s.Simple(a22, n2) << endl;
	cout << "Кол-во присваиваний пузырёк, несортированный: " << s.Bubble(a23, n2) << endl;
	cout << "Кол-во присваиваний пузырёк, сортированный: " << s.Bubble(a23, n2) << endl;
	for (int i = 0; i < n2 / 2; i++)
	{
		a23[i] = a23[n2 - i - 1];
	}
	cout << "Кол-во присваиваний пузырёк, обратный: " << s.Bubble(a23, n1) << endl;
	cout << "Кол-во присваиваний выбором, несортированный: " << s.Choise(a24, n2) << endl;
	cout << "Кол-во присваиваний выбором, сортированный: " << s.Choise(a24, n2) << endl;
	for (int i = 0; i < n2 / 2; i++)
	{
		a24[i] = a24[n2 - i - 1];
	}
	cout << "Кол-во присваиваний выбором, обратный: " << s.Choise(a24, n2) << endl;
	for (int i = 0; i < n3; i++)
		a3[i] = rand() % n3;
	for (int i = 0; i < n1; i++)
		a31[i] = a3[i];
	for (int i = 0; i < n1; i++)
		a32[i] = a3[i];
	for (int i = 0; i < n1; i++)
		a33[i] = a3[i];
	for (int i = 0; i < n1; i++)
		a34[i] = a3[i];
	cout << "Кол-во присваиваний пирамида, несортированный: " << s.Pyramid(a3, n3) << endl;
	cout << "Кол-во присваиваний пирамида, сортированный: " << s.Pyramid(a31, n3) << endl;
	for (int i = 0; i < n3 / 2; i++)
	{

		a31[i] = a31[n3 - i - 1];
	}
	cout << "Кол-во присваиваний пирамида, обратный: " << s.Pyramid(a31, n3) << endl;
	cout << "Кол-во присваиваний вставки, несортированный: " << s.Simple(a32, n3) << endl;
	cout << "Кол-во присваиваний вставки, сортированный: " << s.Simple(a32, n3) << endl;
	for (int i = 0; i < n3 / 2; i++)
	{
		a32[i] = a32[n3 - i - 1];
	}
	cout << "Кол-во присваиваний вставки, обратный: " << s.Simple(a32, n3) << endl;
	cout << "Кол-во присваиваний пузырёк, несортированный: " << s.Bubble(a33, n3) << endl;
	cout << "Кол-во присваиваний пузырёк, сортированный: " << s.Bubble(a33, n3) << endl;
	for (int i = 0; i < n3 / 2; i++)
	{
		a33[i] = a33[n3 - i - 1];
	}
	cout << "Кол-во присваиваний пузырёк, обратный: " << s.Bubble(a33, n3) << endl;
	cout << "Кол-во присваиваний выбором, несортированный: " << s.Choise(a34, n3) << endl;
	cout << "Кол-во присваиваний выбором, сортированный: " << s.Choise(a34, n3) << endl;
	for (int i = 0; i < n3 / 2; i++)
	{
		a34[i] = a34[n3 - i - 1];
	}
	cout << "Кол-во присваиваний выбором, обратный: " << s.Choise(a34, n3) << endl;
	for (int i = 0; i < n4; i++)
		a4[i] = rand() % n4;
	for (int i = 0; i < n1; i++)
		a41[i] = a4[i];
	for (int i = 0; i < n1; i++)
		a42[i] = a4[i];
	for (int i = 0; i < n1; i++)
		a43[i] = a4[i];
	for (int i = 0; i < n1; i++)
		a44[i] = a4[i];
	cout << "Кол-во присваиваний пирамида, несортированный: " << s.Pyramid(a41, n4) << endl;
	cout << "Кол-во присваиваний пирамида, сортированный: " << s.Pyramid(a41, n4) << endl;
	for (int i = 0; i < n4 / 2; i++)
	{
		t = a41[i];
		a41[i] = a41[n4 - i - 1];
		a41[n4 - i - 1] = t;
	}
	cout << "Кол-во присваиваний пирамида, обратный: " << s.Pyramid(a41, n4) << endl;
	cout << "Кол-во присваиваний вставки, несортированный: " << s.Simple(a42, n4) << endl;
	cout << "Кол-во присваиваний вставки, сортированный: " << s.Simple(a42, n4) << endl;
	for (int i = 0; i < n4 / 2; i++)
	{
		a42[i] = a42[n4 - i - 1];
	}
	cout << "Кол-во присваиваний вставки, обратный: " << s.Simple(a42, n4) << endl;
	cout << "Кол-во присваиваний пузырёк, несортированный: " << s.Bubble(a43, n4) << endl;
	cout << "Кол-во присваиваний пузырёк, сортированный: " << s.Bubble(a43, n4) << endl;
	for (int i = 0; i < n4 / 2; i++)
	{
		a43[i] = a43[n4 - i - 1];
	}
	cout << "Кол-во присваиваний пузырёк, обратный: " << s.Bubble(a43, n4) << endl;
	cout << "Кол-во присваиваний выбором, несортированный: " << s.Choise(a44, n4) << endl;
	cout << "Кол-во присваиваний выбором, сортированный: " << s.Choise(a44, n4) << endl;
	for (int i = 0; i < n4 / 2; i++)
	{
		t = a44[i];
		a44[i] = a44[n4 - i - 1];
		a44[n4 - i - 1] = t;
	}
	cout << "Кол-во присваиваний выбором, обратный: " << s.Choise(a44, n4) << endl;
}
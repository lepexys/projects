#include "pch.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
using namespace std;

struct Shower
{
	bool* u,*s,*ls;
	int n;

	Shower(unsigned v,int num)
	{
		n = num;
		u = new bool[n];
		for (int i = 0; i < n; i++)
		{
			u[i] = true;
			if (i == v)
				u[i] = false;
		}
		s = new bool[n];
		ls = new bool[n];
		for (int i = 0; i < n; i++)
		{
			ls[i] = false;
			s[i] = false;
			if (i == v)
			{
				s[i] = true;
			}
		}
	}
	bool Copy()
	{
		bool k = false;
		for (int i = 0; i < n; i++)
		{
			if (s[i])
				k = true;
			ls[i] = s[i];
			s[i] = false;
		}
		return k;
	}
	void Show(int **mat,int v)
	{
		for (int j = 0; j < n; j++)
		{
			if (mat[v][j] == 1)
				if (u[j])
				{
					cout << j;
					u[j] = false;
					s[j] = true;
				}
		}
	}
	void Check(int **mat)
	{
		if(Copy())
		{
			for (int i = 0; i < n; i++)
			{
				if (ls[i])
				{
					Show(mat, i);
				}
			}
			Check(mat);
		}
	}
	void Show(int *mat, int v, int c)
	{
		for (int j = 0; j < c; j+=2)
		{
			if ((mat[j] == v))
				if (u[mat[j + 1]])
				{
					cout << mat[j+1];
					u[mat[j+1]] = false;
					s[mat[j+1]] = true;
				}
			if (mat[j + 1] == v)
				if (u[mat[j]])
				{
					cout << mat[j];
					u[mat[j]] = false;
					s[mat[j]] = true;
				}
		}
	}
	void Check(int *mat, int c)
	{
		if (Copy())
		{
			for (int i = 0; i < c; i+=2)
			{
				if (ls[mat[i]])
				{
					Show(mat, mat[i], c);
				}
			}
			Check(mat,c);
		}
	}
};

int main()
{
	int **mat = nullptr, **ormat = nullptr, *list = nullptr;
	int n = 0;
	bool k = true;
	setlocale(LC_ALL, "rus");
	while (k)
	{
		unsigned t = NULL;
		cout << "Матрица(\"1\") или список (\"2\")" << endl;
		cin >> t;
		if (!t)
		{
			cout << "Неправильное значение";
			break;
		}
		if (t == 1)
		{
			k = false;
			cout << "Матрица задаётся следующим образом:" << endl;
			cout << "Сначале в файле пишется степень матрицы, затем через пробел её элементы" << endl;
			cout << "(Если элементов нехватает, матрица дополняется нулями, используются только 0 и 1)" << endl;
			ifstream file;
			char buff[20];
			file.open("matrix.txt");
			if (file.is_open())
				cout << "file is open"<<endl;
			else
			{
				cout << "file is not open" << endl;
				break;
			}
			file >> n;
			mat = new int*[n];
			ormat = new int*[n];
			for (int i = 0; i < n; i++)
			{
				mat[i] = new int[n];
				ormat[i] = new int[n];
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (!file.eof())
						file >> ormat[i][j];
					else
						ormat[i][j] = 0;
					if (mat[i][j] != 1)
						mat[i][j] = ormat[i][j];
					if (mat[i][j] == 1)
						mat[j][i] = 1;
				}
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					cout<<mat[i][j];
				}
				cout << endl;
			}
			unsigned v;
			do {
				cout << "Введите номер вершины, из которой происходит обход...";
				cin >> v;
			} while (v >= n);
			cout << "Очерёдность обхода :";
			Shower* sh = new Shower(v,n);
			sh->Check(mat);
			cout << endl;
			int count = 0;
			cout << "   ";
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (i != j)
					{
						if (ormat[i][j] == 1)
						{
							count++;
							cout << i << "->" << j << " ";
						}
					}
				}
			}
			cout << endl;
			int **incmat;
			incmat = new int*[n];
			for (int i = 0; i < n; i++)
			{
				incmat[i] = new int[count];
				for (int j = 0; j < count; j++)
					incmat[i][j] = 0;
			}
			int p = 0;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (i != j)
					{
						if (ormat[i][j] == 1)
						{
							incmat[i][p] = -1;
							incmat[j][p] = 1;
							p++;
						}
					}
				}
			}
			for (int i = 0; i < n; i++)
			{
				printf("%2d", i);
				for (int j = 0; j < count; j++)
					printf("%4d ", incmat[i][j]);
				cout << endl;
			}
		}
		else if (t == 2)
		{
			k = false;
			cout << "Матрица задаётся следующим образом:" << endl;
			cout << "Сначале в файле пишется степень матрицы, затем через пробел её элементы" << endl;
			cout << "(Если элементов нехватает, матрица дополняется нулями, используются только 0 и 1)" << endl;
			ifstream file;
			char buff[20];
			file.open("matrix.txt", ifstream::in);
			if (file.is_open())
				cout << "file is open" << endl;
			else
			{
				cout << "file is not open" << endl;
				break;
			}
			file >> n;
			int cnt = 0;
			mat = new int*[n];
			ormat = new int*[n];
			for (int i = 0; i < n; i++)
			{
				mat[i] = new int[n];
				ormat[i] = new int[n];
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (!file.eof())
					{
						file >> ormat[i][j];
						if ((ormat[i][j] == 1) && (i != j))
							cnt += 2;
					}
					else
						ormat[i][j] = 0;
					if (mat[i][j] != 1)
						mat[i][j] = ormat[i][j];
					if (mat[i][j] == 1)
						mat[j][i] = 1;
				}
			}
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					cout << mat[i][j];
				}
				cout << endl;
			}
			list = new int[cnt];
			int d = 0;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if ((ormat[i][j] == 1) && (i != j))
					{
						list[d] = i;
						list[d + 1] = j;
						d += 2;
					}
				}
			}
			unsigned v;
			do {
				cout << "Введите номер вершины, из которой происходит обход...";
				cin >> v;
			} while (v >= n);
			cout << "Очерёдность обхода :";
			Shower* sh = new Shower(v, n);
			sh->Check(list, cnt);
			cout << endl;
			cout << "   ";
			for (int i = 0; i < cnt; i+=2)
			{
				cout << list[i] << "->" << list[i+1] << " ";
			}
			cout << endl;
			int **incmat;
			incmat = new int*[n];
			for (int i = 0; i < n; i++)
			{
				incmat[i] = new int[cnt/2];
				for (int j = 0; j < cnt/2; j++)
					incmat[i][j] = 0;
			}
			int p = 0;
			for (int i = 0; i < cnt; i+=2)
			{
				incmat[list[i]][p] = -1;
				incmat[list[i+1]][p] = 1;
				p++;
			}
			for (int i = 0; i < n; i++)
			{
				printf("%2d", i);
				for (int j = 0; j < cnt/2; j++)
					printf("%4d ", incmat[i][j]);
				cout << endl;
			}
		}
		
	}
	return NULL;
}
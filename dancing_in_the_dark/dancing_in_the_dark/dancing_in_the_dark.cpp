#include "pch.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
#include <list>
using namespace std;

struct point
{
	int number;
	bool max;
	list<point*> sons;
	point* dad;
	point(int n,point *d,bool m)
	{
		number = n;
		dad = d;
		max = m;
	}
	void Addp(point *p)
	{
		sons.push_back(p);
	}
	void Change(point *p)
	{
		p->max = !p->max;
		for (auto i = p->sons.begin(); i != p->sons.end(); ++i)
		{
			Change(*i);
		}
	}
};
int MinMax(point *p)
{
	if (p->max)
	{
		int max = 0;
		if (!p->sons.empty())
		{
			for (auto i = p->sons.begin(); i != p->sons.end(); ++i)
			{
				max = (MinMax(*i) > max) ? MinMax(*i) : max;
			}
			p->number = max;
			return max;
		}
		else
			return p->number;
	}
	else
	{
		int min = INT_MAX;
		if (!p->sons.empty())
		{
			for (auto i = p->sons.begin(); i != p->sons.end(); ++i)
			{
				min = (MinMax(*i) < min) ? MinMax(*i) : min;
			}
			p->number = min;
			return min;
		}
		else
			return p->number;
	}
}
int AlphaBeta(point *p)
{
	point *d = p->dad;
	if (p->max)
	{
		int min = INT_MAX;
		while (d != nullptr)
		{
			if (d->max != p->max)
			{
				for (auto i = d->sons.begin(); i != d->sons.end(); ++i)
				{
					if ((*i) != p)
						if ((*i)->number < min)
							min = (((*i)->number != -1)&&((*i)->number != 0)) ? (*i)->number : min;
				}
			}
			d = d->dad;
		}
		int max = 0;
		if (!p->sons.empty())
		{
			bool k = false;
			int buff;
			for (auto i = p->sons.begin(); i != p->sons.end(); ++i)
			{
				if (k)
					(*i)->number = -1;
				else
				{
					buff = AlphaBeta(*i);
					max = (buff > max) ? buff : max;
					if (buff > min)
						k = true;
				}
			}
			p->number = max;
			return max;
		}
		else
			return p->number;
	}
	else
	{
		int max = 0;
		while (d != nullptr)
		{
			if (d->max != p->max)
			{
				for (auto i = d->sons.begin(); i != d->sons.end(); ++i)
				{
					if ((*i) != p)
						if ((*i)->number > max)
							max = ((*i)->number != -1) && ((*i)->number != 0) ? (*i)->number : max;
				}
			}
			d = d->dad;
		}
		int min = INT_MAX;
		if (!p->sons.empty())
		{
			bool k = false;
			int buff;
			for (auto i = p->sons.begin(); i != p->sons.end(); ++i)
			{
				if (k)
					(*i)->number = -1;
				else
				{
					buff = AlphaBeta(*i);
					min = (buff < min) ? buff : min;
					if (buff < max)
						k = true;
				}
			}
			p->number = min;
			return min;
		}
		else
			return p->number;
	}
}
void print(list<point*>p)
{
	bool k = true;
	list<point*>np;
	if (!p.empty())
	{
		point *d = (*p.begin())->dad;
		cout << (((*p.begin())->max) ? "Max " : "Min ");
		for (auto i = p.begin(); i != p.end(); ++i)
		{
			if (k)
			{
				cout << "[";
				k = !k;
			}
			else
				if (d != (*i)->dad)
				{
					cout << "] [";
				}
			d = (*i)->dad;
			cout << "(";
			if ((*i)->number != -1)
				cout << (*i)->number;
			else
				if ((*i)->max)
					cout << "alpha";
				else
					cout << "beta";
			cout << ") ";
			if ((*i)->number != -1)
			for (auto j = (*i)->sons.begin(); j != (*i)->sons.end(); ++j)
			{
				np.push_back(*j);
			}
		}
		cout << "]"<<endl<<endl;
		print(np);
	}
	else
		return;
}
point *build(point* p,int lvl, int root)
{
	if (lvl == 1)
	{
		point* p1 = new point(0, p, (lvl % 2 == 0) ? true : false);
		point* p2 = new point(0, p, (lvl % 2 == 0) ? true : false);
		point* p3 = new point(0, p, (lvl % 2 == 0) ? true : false);
		p1 = build(p1, lvl + 1,root*2%67);
		p2 = build(p2, lvl + 1,root*3%57);
		p3 = build(p3, lvl + 1,root*4%47);
		p->sons.push_back(p1);
		p->sons.push_back(p2);
		p->sons.push_back(p3);
		return p;
	}
	if (lvl > 1 && lvl < 5)
	{
		point* p1 = new point(0, p, (lvl % 2 == 0) ? true : false);
		point* p2 = new point(0, p, (lvl % 2 == 0) ? true : false);
		p1 = build(p1, lvl + 1,root*2%37);
		p2 = build(p2, lvl + 1,root*3%47);
		p->sons.push_back(p1);
		p->sons.push_back(p2);
		return p;
	}
	if (lvl == 5)
	{
		p->number = root % 10+1;
		return p;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	point*root = new point(0,nullptr,true);
	root = build(root,1,97);
	cout << "(" << root->number << ")" << endl << endl;
	print(root->sons);
	root->number = MinMax(root);
	cout << "MinMax proceeding..."<<endl;
	cout << "Result: "<< root->number << endl << endl;
	print(root->sons);
	root = new point(0, nullptr, true);
	root = build(root, 1, 97);
	root->number = AlphaBeta(root);
	cout << "AlphaBeta proceeding..." << endl;
	cout << "Result: " << root->number << endl << endl;
	print(root->sons);
	return NULL;
}

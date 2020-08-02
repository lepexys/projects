#include "pch.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
#include <vector>

using namespace std;


struct elem
{
	elem* left,*right,*papa;
	int number;
	unsigned char height;
	elem()
	{
		left = NULL;
		right = NULL;
		papa = NULL;
		height = 1;
	}
	elem(elem* l,elem* r,elem* p, int n)
	{
		left = l;
		right = r;
		papa = p;
		number = n;
	}
};
struct tree
{
	elem* root;
	tree()
	{
		root = NULL;
	}
	void Show(elem* temp)
	{
		if(temp->left)
		Show(temp->left);
		cout << temp->number << " ";
		if (temp->right)
		Show(temp->right);
	}
	void fixheight(elem* p)
	{
		unsigned char hl = 0, hr = 0;
		if (p->left!=NULL && p->right!=NULL)
		{
			hl = height(p->left); hr = height(p->right);
		}
		else 
		{
			if (p->left != NULL)
				hl = height(p->left);
			if (p->right != NULL)
				hr = height(p->right);
		}
		p->height = (hl > hr ? hl : hr) + 1;
	}
	unsigned char height(elem* p)
	{
		return p ? p->height : 0;
	}
	int bfactor(elem* p)
	{
		if (p->right && p->left)
			return height(p->right) - height(p->left);
		if (p->left)
			return 0-height(p->left);
		if (p->right)
			return height(p->right);
		return 0;
	}
	elem* rotateright(elem* p)
	{
		elem* q = p->left, *t = p->papa;
		p->left = q->right;
		q->right = p;
		if(t)
		t->left = p;
		q->papa = t;
		p->papa = q;
		fixheight(p);
		fixheight(q);
		return q;
	}
	elem* rotateleft(elem* q) 
	{
		elem* p = q->right, *t = q->papa;
		q->right = p->left;
		p->left = q;
		if(t)
		t->right = p;
		p->papa = t;
		q->papa = p;
		fixheight(q);
		fixheight(p);
		return p;
	}
	elem* balance(elem* p)
	{
		fixheight(p);
		if (bfactor(p) == 2)
		{
			if (bfactor(p->right) < 0)
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if (bfactor(p) == -2)
		{
			if (bfactor(p->left) > 0)
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	}
	elem* Build()
	{
		int x=1;
		/*ifstream file;
		char buff[20];
		cout << "Введите название файла: ";
		cin >> buff;
		file.open(buff,ifstream::in);*/
		elem *now,*comp;
		cin >> x;
		while (x!=0)
		{
			now = new(elem);
			(*now).number = x;
			cin >> x;
			if(root == NULL)
			{
				root = now;
			}
			else
			{
				comp = root;
				while (true)
				{
					if (now->number > comp->number)
					{
						if (!comp->right)
						{
							comp->right = now;
							now->papa = comp;
							comp = balance(comp);
							while (comp->papa)
							{
								comp = comp->papa;
								comp = balance(comp);
							}
							root = comp;
							break;
						}
						else
							comp = comp->right;
					}
					else
					{
						if (!comp->left)
						{
							comp->left = now;
							now->papa = comp;
							comp = balance(comp);
							while (comp->papa)
							{
								comp = comp->papa;
								comp = balance(comp);
							}
							root = comp;
							break;
						}
						else
							comp = comp->left;
					}
				}
			}
		}
		Show(root);
		return root;
	}
};
int main()
{
	setlocale(LC_ALL, "rus");
	tree one = tree();
	one.Build();
	return NULL;
}
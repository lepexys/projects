#include "pch.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
#include <vector>

using namespace std;
struct hotel
{
	char* country;
	char* region;
	char* city;
	char* name;
	int hotclass;
	int onedaypay;
	int tripcost;
	hotel()
	{}
	hotel(char* country1, char* region1, char* city1, char* name1, int hotclass1, int onedaypay1, int tripcost1)
	{
		country = (char*)calloc(strlen(country1) + 1, sizeof(char));
		strcpy_s(country, strlen(country1) + 1, country1);
		region = (char*)calloc(strlen(region1) + 1, sizeof(char));
		strcpy_s(region, strlen(region1) + 1, region1);
		city = (char*)calloc(strlen(city1) + 1, sizeof(char));
		strcpy_s(city, strlen(city1) + 1, city1);
		name = (char*)calloc(strlen(name1) + 1, sizeof(char));
		strcpy_s(name, strlen(name1) + 1, name1);
		hotclass = hotclass1;
		onedaypay = onedaypay1;
		tripcost = tripcost1;
	}
	void print()
	{
			cout << setw(10) << left << country << setw(10) << left << region << setw(10) << left << city << setw(10) << left << name << setw(10) << left << hotclass << setw(10) << left << onedaypay << setw(10) << left << tripcost << endl;
	}
};
struct elem
{
	elem* next;
	hotel data;
	elem()
	{
		next = NULL;
	}
	elem(elem* n, hotel d)
	{
		next = n;
		data = d;
	}
};
struct twinlist
{
	char* fnam;
	elem* tail;
	int count;
	twinlist()
	{
		tail = NULL;
		count = 0;
	}
	void end(char* file)
	{
		ofstream f = ofstream();
		f.open(file);
		elem* x = tail;
		while (x->next!=NULL)
		{
			f << setw(10) << left << x->data.country << setw(10) << left << x->data.region << setw(10) << left << x->data.city << setw(10) << left << x->data.name << setw(10) << left << x->data.hotclass << setw(10) << left << x->data.onedaypay << setw(10) << left << x->data.tripcost << endl;
			x = x->next;
		}
		f.close();
	}
	void start(char* file)
	{
		if (file)
		{
			ifstream f = ifstream();
			f.open(file);
			char buff[10];
			while (!f.eof())
			{
				char buff[10];
				char* cou,* reg,* cit,* nam;
				int day, tri, cla;
				f >> buff;
				cou = (char*)calloc(strlen(buff) + 1, sizeof(char));
				strcpy_s(cou, strlen(buff) + 1, buff);
				f >> buff;
				reg = (char*)calloc(strlen(buff) + 1, sizeof(char));
				strcpy_s(reg, strlen(buff) + 1, buff);
				f >> buff;
				cit = (char*)calloc(strlen(buff) + 1, sizeof(char));
				strcpy_s(cit, strlen(buff) + 1, buff);
				f >> buff;
				nam = (char*)calloc(strlen(buff) + 1, sizeof(char));
				strcpy_s(nam, strlen(buff) + 1, buff);
				f >> cla;
				f >> day;
				f >> tri;
				hotel a = hotel(cou, reg, cit, nam, cla, day, tri);
				add(a);
				f >> buff;
			}
		}
	}
	void add(hotel x)
	{
			elem* temp = (elem*)malloc(sizeof(elem));
			temp->data = x;
			if (tail)
				temp->next = tail;
			else
				temp->next = NULL;
			tail = temp;
			count++;
	}
	elem* find(int n)
	{
		elem* x = tail;
		int i = 0;
		while (x && i < n)
		{
			x = x->next;
			i++;
		}
		return x;
	}
	void del(int n)
	{
		elem* x = tail;
		int i = 0;
		while (x && i<n)
		{
			x = x->next;
			i++;
		}
		
		delete x;
	}
	void lowprice(int clas)
	{
		elem* x = tail;
		int i;
		if (tail)
			i = tail->data.onedaypay;
		else
		{
			printf("Empty list\n");
			return;
		}
		while (x)
		{
			if (x->data.hotclass == clas && i > x->data.onedaypay)
				i = x->data.onedaypay;
			x = x->next;
		}
		elem* y = tail;
		bool k = true;
		while (y)
		{
			if (y->data.hotclass == clas && i == y->data.onedaypay)
			{
				if (k)
				{
					for (int i = 0; i < 70; i++)
						cout << "-";
					cout << endl;
					k = false;
				}
				y->data.print();
			}
			y = y->next;
		}
		if (!k)
			for (int i = 0; i < 70; i++)
				cout << "-";
		cout << endl;
	}
	double avarage(int clas)
	{
		elem* x = tail;
		double ret;
		if (tail)
			ret = tail->data.onedaypay * 7 + tail->data.tripcost;
		else
		{
			printf("Empty list\n");
			return NULL;
		}
		while (x)
		{
			if (x->data.hotclass == clas)
				ret = (ret + x->data.onedaypay * 7 + x->data.tripcost) / 2;
			x = x->next;
		}
		return ret;
	}
};
int main(int argc,char* arg[])
{
	setlocale(LC_ALL, "rus");
	twinlist one;
	char buff[20];
	if (argc > 1)
	{
		one.start(arg[1]);
		strcpy_s(buff, arg[1]);
	}
	else
	{
		cout << "Введите название файла: ";
		cin >> buff;
		one.start(buff);
	}
	int cont = 1;
	do {
		int choose;
		cout << "Выберите действие:\n" << "1. Печать всех элементов базы \n" << "2. Добавить новый отель \n" << "3. Удалить отель \n" << "4. Минимальная стоимость для класса отеля\n" << "5. Средняя стоимость для отелей класса... \n" << "6. Выход (с сохранением данных) \n" << endl;
		cout << "Ваш выбор: ";
		cin >> choose;
		while (cin.fail())
		{
			cin.clear();
			cout << "Неверное значение, введите ещё раз:";
			cin >> choose;
		};
		cout << "Количество отелей в базе: ";
		cout << one.count << endl;
		switch (choose)
		{
		case 1: {
			elem* x = one.tail;
			for (int i = 0; i < 70; i++)
				cout << "-";
			cout << endl;
			while (x)
			{
				x->data.print();
				x = x->next;
			}
			for (int i = 0; i < 70; i++)
				cout << "-";
			cout << endl;
			break;
		};

		case 2: {
			char cou[10], reg[10], cit[10], nam[10];
			int day, tri, cla;
			cout << "Введите страну: ";
			cin >> cou;
			cout << "Введите регион: ";
			cin >> reg;
			cout << "Введите город: ";
			cin >> cit;
			cout << "Введите название: ";
			cin >> nam;
			cout << "Введите класс: ";
			cin >> cla;
			cout << "Введите плату за день: ";
			cin >> day;
			cout << "Введите плату за дорогу: ";
			cin >> tri;
			hotel a = hotel(cou, reg, cit,nam,cla,day,tri);
			one.add(a);
			cout << endl << endl;
			break;
		};
		case 3: {
			int input;
			cout << "Введите номер: ";
			cin >> input;
			one.del(input);
			break;
		};
		case 4: {
			int p;
			cout << "Введите класс:";
			cin >> p;
			one.lowprice(p);
			break;
		};
		case 5: {
			int p;
			cout << "Введите класс:";
			cin >> p;
			cout << "Ответ: " << one.avarage(p) << endl;
			break;
		};
		case 6: {
			if (argc > 1)
				one.end(arg[1]);
			else
				one.end(buff);
			break;
		};
		default: cout << "Нет такого действия " << endl;
		};
		cout << "Хотите продолжить? (ДА - 1; НЕТ - 0) ";
		cin >> cont;
	} while (cont == 1);
	return 0;
}



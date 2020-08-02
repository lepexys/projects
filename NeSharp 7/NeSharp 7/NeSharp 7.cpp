#include "pch.h"
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
#include <vector>


using namespace std;

static class Product* t;
enum type { loaf, bisquit, cake };
static int rang = 0;

template <class Data>
Data* Find(Data*mas, int n, const Data& key)
{
	for (int i = 0; i < n; i++)
		if (*(mas + i) == key)
			return mas + i;
	return 0;
}
class Exeption
{
public:
	char* message;
	Exeption(const char* mess)
	{
		message = (char*)calloc(strlen(mess) + 1, sizeof(char));
		strcpy_s(message, strlen(mess) + 1, mess);
	}
};
class Coding
{
	char* code;
public:
	Coding()
	{
		code = new char[30];
	}
public:
	Coding(char* c)
	{
		code = (char*)calloc(strlen(c) + 1, sizeof(char));
		strcpy_s(code, strlen(c) + 1, c);
	}
public:
	char* getcode()
	{
		return code;
	}
public:
	void setcode(char* buff)
	{
		code = (char*)calloc(strlen(buff) + 1, sizeof(char));
		strcpy_s(code, strlen(buff) + 1, buff);
	}
public:
	~Coding()
	{
		delete code;
	}
};
class  CalcuProd :public Coding
{
	char* sourse; //Сырьё
	double n; // Колличество сырья
public:
	char* getsourse()
	{
		return sourse;
	}
public:
	double getn()
	{
		return n;
	}
public:
	CalcuProd(char* cd, char* s, double cu) :Coding(cd)
	{
		sourse = (char*)calloc(strlen(s) + 1, sizeof(char));
		strcpy_s(sourse, strlen(s) + 1, s);
		n = cu;
	}
public:
	CalcuProd() :Coding()
	{
		sourse = new char[30];
		n = NULL;
	}
public:
	void AddCalcu(CalcuProd & a, char* c, char* s, double d)
	{
		a.setcode(c);
		a.sourse = (char*)calloc(strlen(s) + 1, sizeof(char));
		strcpy_s(a.sourse, strlen(s) + 1, s);
		a.n = d;
	}
public:
	~CalcuProd()
	{
		delete sourse;
	}
public:
	void Print()
	{
		cout << setw(18) << left << getcode() << setw(18) << left << sourse << setw(18) << left << n << endl;
	}
};
class Product : public Coding
{
	char* name; // Название продукта
	int pastery; // Тип выпечки (pastery)
	int colcal; // Колличество калькуляций
	vector<CalcuProd> kalkul; //Массив калькуляций
	friend class CalcuProd;
public:
	Product(char* c, char* nam, type p, int r) : Coding(c)
	{
		name = (char*)calloc(strlen(nam) + 1, sizeof(char));
		memcpy(name, nam, strlen(nam));
		pastery = p;
		colcal = 0;
		rang = r;
	}
public:
	Product() : Coding()
	{
		name = new char[30];
		colcal = 0;
		pastery = -1;
	}

public:
	int getrang()
	{
		return rang;
	}
public:
	~Product()
	{
		delete name;
		kalkul.clear();
	}
public:
	void InitProd()
	{
		ifstream f("Products.txt");
		double weight;
		CalcuProd w;
		char buff[30];
		f >> buff >> buff;
		f >> rang;
		if (f.fail())
			return;
		f >> buff >> buff >> buff >> buff;
		t = (class Product*)realloc(t, rang * sizeof(class Product));
		for (int i = 0; i < rang; i++)
		{
			f >> buff;
			t[i].setcode(buff);
			f >> buff;
			t[i].name = (char*)calloc(strlen(buff) + 1, sizeof(char));
			strcpy_s(t[i].name, strlen(buff) + 1, buff);
			f >> buff;
			if (strcmp(buff, "loaf") == 0)
				t[i].pastery = loaf;
			if (strcmp(buff, "bisquit") == 0)
				t[i].pastery = bisquit;
			if (strcmp(buff, "cake") == 0)
				t[i].pastery = cake;
			if (t[i].pastery == -1)
				throw new Exeption("Ошибка типа изделия в файле");
			f >> buff >> buff;
			t[i].colcal = 0;
			while (!strcmp(buff, "*") == 0)
			{
				f >> weight;
				w = CalcuProd(t[i].getcode(), buff, weight);
				t[i].kalkul.push_back(w);
				f >> buff;
				t[i].colcal++;
			}
		}
		f.close();
	}
public:
	//Добавить калькуляцию
	void AddCalculation(int u)
	{
		char* sor = new char[30];
		double weight;
		CalcuProd w;
		int k = 1;
		while (k == 1)
		{
			cout << "Введите тип сырья: ";
			cin >> sor;
			cout << "Введите колличество сырья: ";
			cin >> weight;
			w = CalcuProd(t[u].getcode(), sor, weight);
			t[u].kalkul.push_back(w);
			t[u].colcal++;
			cout << "Ещё по одной? (0 - <нет> , 1 - <да>): ";
			cin >> k;
		}
	}
public:
	const char* ToString(type a)
	{
		switch (a)
		{
		case loaf:
			return"loaf";
		case bisquit:
			return"bisquit";
		case cake:
			return "cake";
		}
	}
public:
	//печать того, что находится в файле
	void printbase()
	{
		for (int j = 0; j < rang; j++)
		{
			cout << "Код          Название			Тип изделия\n\n";
			for (int i = 0; i < 50; i++)
				cout << "-";
			cout << endl;
			cout << setw(18) << left << t[j].getcode() << setw(18) << left << t[j].name << setw(18) << left << ToString((type)t[j].pastery) << endl;
			for (int i = 0; i < 50; i++)
				cout << "=";
			cout << endl;
			cout << "Код          Тип сырья			Колличество\n\n";
			for (int i = 0; i < t[j].colcal; i++)
				t[j].kalkul[i].Print();
			for (int i = 0; i < 50; i++)
				cout << "=";
			cout << endl;
		}
	}
public:
	//запрос и создание нового элемента
	int add()
	{
		char bcode[30];
		char bname[30];
		char bpastery[30];
		t = (Product*)realloc(t, (1 * sizeof(class Product)));
		cout << "Введите код: ";
		cin >> bcode;
		t[rang].setcode(bcode);
		cout << "Введите назввание: ";
		cin >> bname;
		t[rang].name = (char*)calloc(strlen(bname) + 1, sizeof(char));
		strcpy_s(t[rang].name, strlen(bname) + 1, bname);
		cout << "Введите тип изделия(loaf,bisquit,cake): ";
		cin >> bpastery;
		if (strcmp(bpastery, "loaf") == 0)
			t[rang].pastery = loaf;
		if (strcmp(bpastery, "bisquit") == 0)
			t[rang].pastery = bisquit;
		if (strcmp(bpastery, "cake") == 0)
			t[rang].pastery = cake;
		if (t[rang].pastery == -1)
			throw Exeption("Нет такого типа");
		t[rang].colcal = 0;
		rang++;
		return rang;
	}
public:
	//Завершение с закрытием
	void end()
	{
		ofstream f("Products.txt");
		f << "Количество продуктов: " << rang << endl << "Код\tНазвание\tТип изделия" << endl;
		for (int i = 0; i < rang; i++)
		{
			f << setw(18) << left << t[i].getcode() << setw(18) << left << t[i].name << setw(18) << left << t[i].pastery << endl;
			f << "*\n";
			for (int j = 0; j < t[i].colcal; j++)
				t[i].kalkul[j].Print();
			f << "*\n";
		}
		f.close();
		free(t);
	}
	friend class Order;
};
class CountOrder
{
	char* sourse;
	double amount;
public:
	void AddCoOrder(CountOrder &co, char* c, double d)
	{
		co.sourse = c;
		co.amount = d;
	}
public:
	CountOrder(char* s, double a)
	{
		sourse = (char*)calloc(strlen(s) + 1, sizeof(char));
		strcpy_s(sourse, strlen(s) + 1, s);
		amount = a;
	}
public:
	CountOrder()
	{
		sourse = new char[30];
		amount = 0;
	}
public:
	char* getsourse()
	{
		return sourse;
	}
	double getamount()
	{
		return amount;
	}
public:
	void setCountOrder(double a)
	{
		amount = a;
	}
};
class TypeOrder : public Coding
{
	int count;
public:
	void TypeAdd(TypeOrder &a, char* c, int k)
	{
		a.setcode(c);
		a.count = k;
	}
public:
	int getcount()
	{
		return count;
	}
public:
	TypeOrder() : Coding()
	{
		count = NULL;
	}
public:
	TypeOrder(char* c, int k) : Coding(c)
	{
		count = k;
	}
};
class Order
{
	friend class Product;
	int amount; // Колличество строк в заказе
	long number; // Номер заказа
	int countamount; // Колличество строк в рассчёте заказа
	CountOrder* SSCHET; // Массив рассчёта заказа
	TypeOrder* ordertype; //Массив запросов заказа
	int getamount()
	{
		return amount;
	}
	long getnumber()
	{
		return number;
	}
public:
	Order()
	{
		amount = 0;
		number = 0;
		countamount = 0;
	}
public:
	void AddOrder(int n)
	{
		int k, y = 1;
		bool v = false;
		char* c = new char[30];
		number = n;
		ordertype = (TypeOrder*)malloc(1 * sizeof(TypeOrder));
		while (y == 1)
		{
			ordertype = (TypeOrder*)realloc(ordertype, 1 * sizeof(TypeOrder));
			cout << "Введите код продукта:";
			cin >> c;
			for (int i = 0; i < rang; i++)
				if (strcmp(t[i].getcode(), c) == 0)
					v = true;
			if (v == false)
				throw new Exeption("Нет такого изделия");
			v = false;
			cout << "Введите колличество продуктов:";
			cin >> k;
			TypeOrder obj;
			obj.TypeAdd(ordertype[amount], c, k);
			cout << "1 - для продолжения, 0 - завершить заказ :";
			amount++;
			while (true)
			{
				cin >> y;
				if (y == 1 || y == 0)
					break;
				cout << "Введите 0 или 1";
			}
		}
	}
public:
	void Count()
	{
		bool w;
		for (int i = 0; i < amount; i++)
		{
			for (int j = 0; j < rang; j++)
				if (strcmp(t[j].getcode(), ordertype[i].getcode()) == 0)
				{
					for (int o = 0; o < t[j].colcal; o++)
					{
						w = false;
						for (int l = 0; l < countamount; l++)
							if (strcmp(t[j].kalkul[o].getsourse(), SSCHET[l].getsourse()) == 0)
							{
								w = true;
								if (t[j].pastery == 0 || t[j].pastery == 1)
									SSCHET[l].setCountOrder(SSCHET[l].getamount() + (t[j].kalkul[o].getn()*ordertype[i].getcount() / 100));
								else
									SSCHET[l].setCountOrder(SSCHET[l].getamount() + (t[j].kalkul[o].getn()*ordertype[i].getcount() / 10));
								break;
							}
						if (!w)
						{
							CountOrder cor;
							SSCHET = (CountOrder*)realloc(SSCHET, sizeof(CountOrder));
							if (t[j].pastery == 0 || t[j].pastery == 1)
							{
								cor.AddCoOrder(SSCHET[countamount], t[j].kalkul[o].getsourse(), t[j].kalkul[o].getn()*ordertype[i].getcount() / 100);
							}
							else
							{
								cor.AddCoOrder(SSCHET[countamount], t[j].kalkul[o].getsourse(), t[j].kalkul[o].getn()*ordertype[i].getcount() / 10);
							}
							countamount++;
						}
					}
					break;
				}
		}
		Esketit(countamount);
	}
	void Esketit(int ccc)
	{
		cout << "Рассчёт заказа:" << endl;
		for (int i = 0; i < 50; i++)
			cout << "*";
		cout << endl;
		for (int i = 0; i < ccc; i++)
		{
			cout << SSCHET[i].getsourse() << ": " << SSCHET[i].getamount() << " кг" << endl;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	Product obj;
	Order ord;
	int k = 0;
	obj.InitProd();
	int cont = 1;
	do {
		int choose;
		cout << "Выберите действие:\n" << "1. Печать всех элементов базы \n" << "2. Добавить новый продукт \n" << "3. Добавить новую калькуляцию \n" << "4. Сделать заказ\n" << "5. Рассчитать заказ \n" << "6. Выход (с сохранением данных) \n" << endl;
		cout << "Ваш выбор: ";
		cin >> choose;
		while (cin.fail())
		{
			cin.clear();
			char c[30];
			cin >> c;
			cout << "Неверное значение, введите ещё раз:";
			cin >> choose;
		};
		cout << "Количество студентов в базе: ";
		cout << rang << endl;
		switch (choose)
		{
		case 1: {
			obj.printbase();
			cout << endl << endl;
			break;
		};

		case 2: {
			obj.add();
			cout << endl << endl;
			break;
		};
		case 3: {
			int g = 0;
			char* input = new char[30];
			cout << "Введите код продукта: ";
			cin >> input;
			for (int i = 0; i < obj.getrang(); i++)
			{
				if (strcmp(t[i].getcode(), input) == 0)
				{
					t[i].AddCalculation(i);
					g = 1;
				}
			}
			if (g = 0)
				cout << "Нет такого кода";
			break;
		};
		case 4: {
			int p;
			cout << "Введите номер заказа:";
			cin >> p;
			ord.AddOrder(p);
			break;
		};
		case 5: {
			ord.Count();
			break;
		};
		case 6: obj.end();
			break;
		default: cout << "Нет такого действия " << endl;
		};
		cout << "Хотите продолжить? (ДА - 1; НЕТ - 0) ";
		cin >> cont;
	} while (cont == 1);
	system("pause");
	return 0;
}
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>

using namespace std;


static class student *t;
class man;
class prepod;
class student;
class man
{
public:
	char* fam; //фамилия
	char* name;  //имя
	man() {
		fam = new char[30];
		strcpy_s(fam, 30, " ");
		name = new char[30];
		strcpy_s(name, 30, " ");
	}
	~man()
	{
		delete fam;
		delete name;
	}
};
	class student
	{
	public:
		man guy; 		//Мужчина
		char* faculty;		// факультет
		static int count;
		int group;			// номер группы
		student(char* fam1, char* name1, char* fac1, int count1, int group1)
		{
			guy.fam = fam1;
			guy.name = name1;
			faculty = fac1;
			count = count1;
			group = group1;
		}
		student()
		{
			man();
			faculty = new char[30];
			count = 0;
			group = NULL;
		}
		~student()
		{
			delete faculty;
		}
		student(student& cop)
		{
			guy.fam = cop.guy.fam;
			guy.name = cop.guy.name;
			faculty = cop.faculty;
			count = cop.count;
			group = cop.group;
		}
		student& operator = (const student& r)
		{
			guy.fam = r.guy.fam;
			guy.name = r.guy.name;
			faculty = r.faculty;
			count = r.count;
			group = r.group;
			return *this;
		}
		void operator >> (student& inp)
		{
			cin >> inp.guy.fam >> inp.guy.name >> inp.faculty >> inp.count >> inp.group;
		}
		bool operator == (student& com)
		{
			if (this->guy.fam == com.guy.fam)
				if (this->guy.name == com.guy.name)
					if (this->faculty == com.faculty)
						if (this->count == com.count)
							if (this->group == com.group)
								return true;
			return false;
		}
		friend student operator ++ (student& r);
		//функция считывания базы из файла
		int start(void)
		{
			ifstream f("file.txt");
			char buff[30];
			f >> buff >> buff;
			f >> count;
			if (f.fail()) return 0;
			f >> buff >> buff >> buff >> buff >> buff >> buff;
			t = (class student*)realloc(t, count * sizeof(class student));
			for (int i = 0; i < count; i++)
			{
				f >> buff;
				t[i].guy.fam = (char*)calloc(strlen(buff) + 1, sizeof(char));
				memcpy(t[i].guy.fam, buff, strlen(buff));
				f >> buff;
				t[i].guy.name = (char*)calloc(strlen(buff) + 1, sizeof(char));
				memcpy(t[i].guy.name, buff, strlen(buff));
				f >> buff;
				t[i].faculty = (char*)calloc(strlen(buff) + 1, sizeof(char));
				memcpy(t[i].faculty, buff, strlen(buff));
				f >> t[i].group;
			}
			f.close();
			return count;
		}

		//печать того, что находится в файле
		void printbase()
		{
			cout << "Фамилия           Имя          Факультет        Номер группы\n\n";
			for (int i = 0; i < 60; i++)
				cout << "-";
			cout << endl;
			for (int i = 0; i < count; i++)
				cout << setw(18) << left << t[i].guy.fam << setw(18) << left << t[i].guy.name << setw(18) << left << t[i].faculty << setw(18) << left << t[i].group << endl;
		}

		//проверка на ввод числа
		double num(void)
		{
			double buff;
			cin >> buff;
			while (cin.fail())
			{
				cin.clear();
				char c[30];
				cin >> c;
				cout << "Неверное значение, введите ещё раз:";
				cin >> buff;
			}
			return buff;
		}

		//создание новой строчки
		void addnew(man &guy, char* faculty, int group)
		{
			static int c = 10;//расширение сруктуры для десятка новых строчек
			if (c == 10)//если этот десяток закончился, то добавим
			{
				t = (student*)realloc(t, (count + 10) * sizeof(class student));
				c = 0;
			}
			c++;
			t[count].guy.fam = (char*)calloc(strlen(guy.fam) + 1, sizeof(char));
			strcpy_s(t[count].guy.fam, strlen(guy.fam) + 1, guy.fam);
			t[count].guy.name = (char*)calloc(strlen(guy.name) + 1, sizeof(char));
			strcpy_s(t[count].guy.name, strlen(guy.name) + 1, guy.name);
			t[count].faculty = (char*)calloc(strlen(faculty) + 1, sizeof(char));
			strcpy_s(t[count].faculty, strlen(faculty) + 1, faculty);
			t[count].group = group;
		}

		//запрос и создание нового элемента
		int add()
		{
			student s();
			man bguy = man::man();
			char bfaculty[30];
			int bgroup;
			cout << "Введите фамилию: ";
			cin >> bguy.fam;
			cout << "Введите имя: ";
			cin >> bguy.name;
			cout << "Введите факультет: ";
			cin >> bfaculty;
			cout << "Введите группу: ";
			cin >> bgroup;
			addnew(bguy, bfaculty, bgroup); //создание нового элемента
			count++;
			return count;
		}
		//поиск по фамилии
		friend char search_fam(char *);
		char search_group(int group)
		{
			int k = 0; //для единождого вывода шапки таблицы
			int cn = 0;//для проверки на наличие владельца в базе
			for (int i = 0; i < count; ++i)
			{
				int flag;
				int p_tek; // текущий указатель
				p_tek = t[i].group;
				flag = (group == p_tek);
				if (flag == 1)
				{
					while (k == 0)
					{
						cout << "Фамилия           Имя          Факультет        Номер группы\n\n";
						for (int i = 0; i < 60; i++)
							cout << "-";
						cout << endl;
						k++;
					};
					cout << setw(18) << left << t[i].guy.fam << setw(18) << left << t[i].guy.name << setw(18) << left << t[i].faculty << setw(18) << left << t[i].group << endl;
					k++;
					cn++;
				}
			}
			if (cn == 0) cout << "Студентов в группе нет" << endl;
			return 0;
		}
		friend void sortir();
		//записывание данных в файл, очищeние памяти
		void end()
		{
			ofstream f("file.txt");
			f << "Количество студентов: " << student::count << endl << "Фамилия\tИмя\tФакультет\tНомер группы" << endl;
			for (int i = 0; i < student::count; i++)
				f << setw(18) << left << t[i].guy.fam << setw(18) << left << t[i].guy.name << setw(18) << left << t[i].faculty << setw(18) << left << t[i].group << endl;
			f.close();
			free(t);
		}
	};
	char search_fam(char *fam)
	{
		int kok = 0;
		bool k = 0; //для единождого вывода шапки таблицы
		for (int i = 0; i < student::count; ++i)
		{
			int flag1;
			char *p1_tek; // текущий указатель
			p1_tek = t[i].guy.fam;
			flag1 = strcmp(fam, p1_tek);
			if (flag1 == 0)
			{
				while (k == 0)
				{
					cout << "Фамилия           Имя          Факультет        Номер группы\n\n";
					for (int i = 0; i < 60; i++)
						cout << "-";
					cout << endl;
					k = 1;
				};
				cout << setw(18) << left << t[i].guy.fam << setw(18) << left << t[i].guy.name << setw(18) << left << t[i].faculty << setw(18) << left << t[i].group << endl;
				k = 1;
				kok++;
			}
		}
		if (kok == 0)
		{
			cout << "Такого студента нет\n";
			t->add();
		}
		return 0;
	}
	void sortir()
	{
		for (int j = 0; j < student::count - 1; j++)
			for (int i = 0; i < student::count - j - 1; i++)
			{
				int flag;
				char *p1, *p2, *p;
				p1 = t[i].guy.name;
				p2 = t[i + 1].guy.name;
				flag = strcmp(p1, p2);
				if (flag > 0)
				{
					p = p1;
					p1 = p2;
					p2 = p;
				}
				if (i == student::count - 2)
					cout << "Сортировка завершена\n";
			}
	}
	student operator ++ (student& rap)
	{
		student::count++;
		int k = student::count;
		t = (student*)realloc(t, (1 * sizeof(class student)));
		t[k].guy.fam = (char*)calloc(strlen(rap.guy.fam) + 1, sizeof(char));
		strcpy_s(t[k].guy.fam, strlen(rap.guy.fam) + 1, rap.guy.fam);
		t[k].guy.name = (char*)calloc(strlen(rap.guy.name) + 1, sizeof(char));
		strcpy_s(t[k].guy.name, strlen(rap.guy.name) + 1, rap.guy.name);
		t[k].faculty = (char*)calloc(strlen(rap.faculty) + 1, sizeof(char));
		strcpy_s(t[k].faculty, strlen(rap.faculty) + 1, rap.faculty);
		t[k].group = rap.group;
	}
	class prepod : public student
	{
		man guy;
		char* depart;
		char* course;
		prepod(char* fam1, char* name1, char* dep, char* cor)
		{
			guy.fam = fam1;
			guy.name = name1;
			depart = dep;
			course = cor;
		}
		prepod()
		{
			guy.fam = new char[30];
			guy.name = new char[30];
			depart = new char[30];
			course = new char[30];
		}
		~prepod()
		{
			delete depart;
			delete course;
		}
	};
	int student::count = 0;
int main()
{
	setlocale(LC_ALL, "Russian");
	student kol; //экземпляр класса
	kol.start(); //считывание из файла
	bool cont = 0;
	do {
		int choose;
		cout << "Выберите действие:\n" << "1. Печать всех элементов базы \n" << "2. Добавить новый элемент \n" << "3. Поиск студента по фамилии \n" << "4. Фильтр по номеру группы  \n" << "5. Сортировать по алфавиту \n" << "6. Выход (с сохранением данных) \n" << endl;
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
		cout << kol.count << endl;
		switch (choose)
		{
		case 1: {
			kol.printbase();//печать базы
			cout << endl << endl;
			break;
		};

		case 2: {
			kol.add();
			cout << endl << endl;
			break;
		};
		case 3: {
			char fam[30];
			cout << "Введите фамилию: ";
			cin >> fam;
			search_fam(fam); cout << endl << endl;
			break;
		};
		case 4: {
			int group;
			cout << "Введите группу: ";
			cin >> group;
			kol.search_group(group); cout << endl << endl;
			break;
		};
		case 5: {
			sortir();
			cout << endl << endl;
			break;
		};
		case 6: kol.end();
			break;
		default: cout << "Нет такого действия " << endl;
		};
		cout << "Хотите продолжить? (ДА - 1; НЕТ - 0) ";
		cin >> cont;
	} while (cont == 1);
	system("pause");
	return 0;
}
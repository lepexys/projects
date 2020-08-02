#include "pch.h"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <clocale>
#define filename "file.txt"
char limiters[] = { '{','}','(',')','[',']',';',','};

using namespace std;

struct Lexem
{
	int type, code;
	char* word;
	Lexem()
	{
		word = nullptr;
	}
	Lexem(int t, const char* w, int c)
	{
		type = t;
		word = (char*)calloc(strlen(w) + 1, sizeof(char));
		strcpy_s(word, strlen(w) + 1, w);
		code = c;
	}
	Lexem(int t, char* w, int c)
	{
		type = t;
		word = (char*)calloc(strlen(w) + 1, sizeof(char));
		strcpy_s(word, strlen(w) + 1, w);
		code = c;
	}
};
struct Lex_analis
{
	Lexem* lstream;
	short type, pos;
	char buff[40] = { 0 };
	int state = 0;
	ifstream file;
	Lex_analis()
	{
		pos = 0;
		lstream = NULL;
		file.open(filename);
		if (!file)
		{
			cout << "Error";
			exit(1);
		}
	}
	void zero_check(char cur)
	{
		int asc = (int) cur;
		for (int i = 0; i < 8; i++)
		{
			if (cur == limiters[i])
			{
				type = 4;
				buff[0] = cur;
				Result(buff);
			}
		}
		if ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95)))
		{
			switch (cur)
			{
			case 'i':
			{
				type = 1;
				buff[0] = cur;
				state = 4;
				break;
			}
			case 'e':
			{
				type = 1;
				buff[0] = cur;
				state = 2;
				break;
			}
			case 'b':
			{
				type = 1;
				buff[0] = cur;
				state = 7;
				break;
			}
			default:
			{
				type = 1;
				buff[0] = cur;
				state = 8;
				break;
			}
			}
		}
		if (((asc >= 48) && (asc <= 57)) || (asc == 46))
		{
			type = 3;
			buff[0] = cur;
			state = 1;
		}
		if (cur == '+' || cur == '-' || cur == '=' || cur == '*' || cur == '%')
		{
			type = 5;
			buff[0] = cur;
			Result(buff);
		}
		if (cur == '/')
		{
			type = 6;
			buff[0] = cur;
			state = 5;
		}
	}
	void else_check(char cur)
	{
		for (int i = 0; i < 8; i++)
		{
			if (cur == limiters[i])
			{
				Result(buff);
				type = 4;
				buff[0] = cur;
				Result(buff);
				state = 0;
			}
		}
		if (cur == ' ' || cur == '/n')
		{
			Result(buff);
			state = 0;
		}
		if (cur == '+' || cur == '-' || cur == '=' || cur == '*' || cur == '%')
		{
			Result(buff);
			type = 5;
			buff[0] = cur;
			Result(buff);
			state = 0;
		}
		if (cur == '/')
		{
			Result(buff);
			type = 6;
			buff[0] = cur;
			state = 5;
		}
	}
	Lexem* Analys()
	{
		char cur;
		int asc;
		if (file.eof())
		{
			file.close();
			return NULL;
		}
		else
			while (!file.eof())
			{
				cur = file.get();
				asc = (int)cur;
				switch (state)
				{
				case 0:
				{
					zero_check(cur);
					break;
				}
				case 1:
				{
					if (((asc >= 48) && (asc <= 57)) || (asc == 46))
					{
						buff[++pos] = cur;
					}
					if ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95)))
					{
						type = 7;
						state = 21;
					}
					else_check(cur);
					break;
				}
				case 2:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 'l')
						{
							buff[++pos] = cur;
							state = 15;
						}
						else
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
						else_check(cur);
					break;
				}
				case 4:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 'f')
						{
							buff[++pos] = cur;
							state = 14;
						}
						else
							if (cur == 'n')
							{
								buff[++pos] = cur;
								state = 12;
							}
							else
							{
								type = 1;
								buff[++pos] = cur;
								state = 8;
							}
					else
						else_check(cur);
					break;
				}
				case 5:
				{
					if (cur == '*')
					{
						buff[++pos] = cur;
						state = 9;
					}
					else
					{
						type = 5;
						Result(buff);
						state = 0;
						zero_check(cur);
					}
					break;
				}
				case 7:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 'o')
						{
							buff[++pos] = cur;
							state = 18;
						}
						else
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
						else_check(cur);
					break;
				}
				case 8:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
					{
						buff[++pos] = cur;
					}
					else
						else_check(cur);
					break;
				}
				case 9:
				{
					if (cur = '*')
					{
						buff[++pos] = cur;
						state = 10;
					}
					else
					{
						buff[++pos] = cur;
					}
					break;
				}
				case 10:
				{
					if (cur = '/')
					{
						buff[++pos] = cur;
						Result(buff);
						state = 0;
					}
					else
					{
						buff[++pos] = cur;
						state = 9;
					}
					break;
				}
				case 12:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 't')
						{
							buff[++pos] = cur;
							state = 13;
						}
						else
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
						else_check(cur);
					break;
				}
				case 13:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
					{
						type = 2;
						else_check(cur);
					}
					break;
				}
				case 14:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
					{
						buff[++pos] = cur;
						state = 8;
					}
					else
					{
						type = 2;
						else_check(cur);
					}
					break;
				}
				case 15:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 's')
						{
							buff[++pos] = cur;
							state = 16;
						}
						else
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
						else_check(cur);
					break;
				}
				case 16:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 'e')
						{
							buff[++pos] = cur;
							state = 17;
						}
						else
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
						else_check(cur);
					break;
				}
				case 17:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
					{
						buff[++pos] = cur;
						state = 8;
					}
					else
					{
						type = 2;
						else_check(cur);
					}
					break;
				}
				case 18:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 'o')
						{
							buff[++pos] = cur;
							state = 19;
						}
						else
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
						else_check(cur);
					break;
				}
				case 19:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
						if (cur == 'l')
						{
							buff[++pos] = cur;
							state = 20;
						}
						else
						{
							buff[++pos] = cur;
							state = 8;
						}
					else
						else_check(cur);
					break;
				}
				case 20:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
					{
						buff[++pos] = cur;
						state = 8;
					}
					else
					{
						else_check(cur);
					}
					break;
				}
				case 21:
				{
					if ((((asc >= 48) && (asc <= 57)) || (asc == 46)) || ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95))))
					{
						buff[++pos] = cur;
					}
					else
						else_check(cur);
					break;
				}
				}
			}
		file.close();
		return NULL;
	}
	Lexem* Result(char* word)
	{
		switch (type)
		{
		case 1:
			cout << "Идентификатор " << buff << endl; // Идентификаторы
			lstream = new Lexem(1, buff, NULL);
			pos = 0;
			memset(buff, NULL, sizeof(buff));
			return lstream;
		case 2:
			cout << "Служебное слово " << buff << endl; //Служебные слова
			lstream = new Lexem(2, buff, NULL);
			pos = 0;
			memset(buff, NULL, sizeof(buff));
			return lstream;
		case 3:
			cout << "Константа " << buff << endl; // Константы
			lstream = new Lexem(3, buff, NULL);
			pos = 0;
			memset(buff, NULL, sizeof(buff));
			return lstream;
		case 4:
			cout << "Разделитель " << buff << endl; //Разделители
			lstream = new Lexem(4, buff, NULL);
			pos = 0;
			memset(buff, NULL, sizeof(buff));
			return lstream;
		case 5:
			cout << "Оператор " << buff << endl; //Разделители
			lstream = new Lexem(5, buff, NULL);
			pos = 0;
			memset(buff, NULL, sizeof(buff));
			return lstream;
		case 6:
			cout << "Комментарий " << buff << endl; //Разделители
			lstream = new Lexem(6, buff, NULL);
			pos = 0;
			memset(buff, NULL, sizeof(buff));
			return lstream;
		case 7:
			cout << "Неверная лексема " << buff << endl;
			pos = 0;
			memset(buff, NULL, sizeof(buff));
			break;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "rus");
	Lex_analis* l = new Lex_analis();
	l->Analys();
}
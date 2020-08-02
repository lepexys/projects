#include "pch.h"
#include <iostream>
#include <cstdio>
#include <stack>
#include <fstream>
#include <clocale>
#define filename "file.txt"

using namespace std;
static char limiters[] = {'=', ',', '.', '(', ')', '[', ']', ':', ';', '+', '-', '*', '/', '<', '>', '@' };
static char hashlim[][3] = { "=", ",", ".", "(", ")", "[", "]", ":", ";", "+", "-", "*", "/", "<", ">", "@","<>","=>","<=",">=",":="};
static char reservedWords[][10] = { "procedure", "begin","if", "is", "new", "then", "end", "else", "elseif","declare","function","array","type","loop","Put_Line","Put","Get","New_Line","Sqrt","return","Integer","Float","exit","when","while" };
static int Hash(char* w)
{
	int i;
	for (i = 0; i < 21; i++)
		if (strcmp(w, hashlim[i]) == 0)
			return i + 1;
	int j=i;
	for (i; i < j + 25; i++)
	{
		if (strcmp(w, reservedWords[i - j]) == 0)
			return i + 1;
	}
	return NULL;
}
static int Hash(const char* w)
{
	int i;
	for (i = 0; i < 21; i++)
		if (strcmp(w, hashlim[i]) == 0)
			return i + 1;
	int j = i;
	for (i; i < j + 25; i++)
	{
		if (strcmp(w, reservedWords[i - j]) == 0)
			return i + 1;
	}
	return NULL;
}
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
struct Lexical_analis
{
	Lexem* lstream;
	short type, pos;
	char buff[40] = {0};
	ifstream file;
	Lexical_analis()
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
	while(!file.eof())
	{
		cur = file.get();
		asc = (int)cur;
		if (cur == (char)'/"')
		{
			if (type == 6)
			{
				buff[pos++] = '\'';
				type = 3;
				return Result(buff);
			}
			if (buff[0] != NULL)
			{
				Result(buff);
				buff[pos++] = '\'';
				type = 6;
				return lstream;
			}
			else
			{
				type = 6;
				buff[pos++] = '\'';
			}
			continue;
		}
		if (type == 6)
		{
			buff[pos++] = cur;
			continue;
		}
		if ((cur == ' ' || cur == '/n') && buff[0] != NULL)
		{
			Result(buff);
			return lstream;
		}
		for (int i = 0; i < 16; i++)
		{
			if (cur == limiters[i])
			{
				if (buff[0] != NULL && (type == 1 || type == 3))
				{
					Result(buff);
					type = 4;
					buff[0] = cur;
					return lstream;
				}
				if(buff[0]==NULL)
				type = 4;
				if (buff[0] != NULL)
				{
					if ((buff[0] == ':' && cur == '=') || (buff[0] == '=' && cur == '>') || ((buff[0] == '<') && (cur == '>' || cur == '=')) || (buff[0] == '>'&&cur == '='))
					{
						buff[1] = cur;
						Result(buff);
						return lstream;
					}
					else
					{
						Result(buff);
						buff[0] = cur;
						return lstream;
					}
				}
				else
				{
					buff[0] = cur;
					break;
				}
			}
		}
		if ((((asc >= 65) && (asc <= 90)) || ((asc >= 97) && (asc <= 122)) || (asc == 95)))
		{
			if (type == 4 && buff[0] != NULL)
			{
				Result(buff);
				type = 1;
				buff[pos++] = cur;
				return lstream;
			}
			if (buff[0] == NULL)
				type = 1;
			if (type == 3 && buff[0] != NULL)
				type = 5;
			buff[pos++] = asc;
			continue;
		}
		if (((asc >= 48) && (asc <= 57)) || (asc == 46))
		{
			if (type == 4 && buff[0] != NULL)
			{
				Result(buff);
				type = 3;
				buff[pos++] = cur;
				return lstream;
			}
			if (asc == 46)
			{
				continue;
			}
			if (buff[0] == NULL)
				type = 3;
			buff[pos++] = asc;
			continue;
		}
	}
	file.close();
	return NULL;
	}
	Lexem* Result(char* word)
	{
		for (int i = 0; i < 25; i++)
		{
			if (strcmp(word, reservedWords[i]) == 0)
			{
				type = 2;
				break;
			}
		}
			switch(type)
			{
			case 1:
				cout << "1 " << buff<<endl; // Идентификаторы
				lstream = new Lexem(1, buff,NULL);
				pos = 0;
				memset(buff, NULL, sizeof(buff));
				return lstream;
			case 2:
				cout << "2 " << buff << " " << Hash(buff) << endl; //Служебные слова
				lstream = new Lexem(2, buff, Hash(buff));
				pos = 0;
				memset(buff, NULL, sizeof(buff));
				return lstream;
			case 3:
				cout << "3 " << buff << endl; // Константы
				lstream = new Lexem(3, buff, NULL);
				pos = 0;
				memset(buff, NULL, sizeof(buff));
				return lstream;
			case 4:
				cout << "4 " << buff << " " << Hash(buff) << endl; //Разделители
				lstream = new Lexem(4, buff, Hash(buff));
				pos = 0;
				memset(buff, NULL, sizeof(buff));
				return lstream;
			case 5:
				cout << "Error " << buff << endl;
				pos = 0;
				memset(buff, NULL, sizeof(buff));
				break;
			}
	}
};
struct Func
{
	int amount;
	char* name;
	Lexem* arg;
	Lexem* ret;
	Func()
	{
		amount = NULL;
		name = nullptr;
		arg = nullptr;
		ret = nullptr;
	}
	Func(int a, char* n, Lexem* t,Lexem *r)
	{
		amount = a;
		name = n;
		arg = t;
		ret = r;
	}
};
struct Ident
{
	char* name;
	Lexem* type;
	Ident(char* n, Lexem* t)
	{
		name = (char*)calloc(strlen(n) + 1, sizeof(char)); strcpy_s(name, strlen(n) + 1, n); type = t;
	}
	Ident(const char* n, Lexem* t)
	{
		name = (char*)calloc(strlen(n) + 1, sizeof(char)); strcpy_s(name, strlen(n) + 1, n); type = t;
	}
};
struct Typ
{
	int amount;
	char* type;
	char* name;
	Typ(char* n, char* t, int a)
	{
		type = t;
		amount = a;
		name = n;
	}
	Typ(const char* n, char* t, int a)
	{
		type = t;
		amount = a;
		name = (char*)calloc(strlen(n) + 1, sizeof(char)); 
		strcpy_s(name, strlen(n) + 1, n);
	}
};
struct Code_Generator
{
	ofstream file,file1;
	int bi;
	char text[40];
	Code_Generator(const char* name)
	{
		file.open(name, ios::beg);
		file1.open("data.txt");
		bi = 1;
		sprintf(text, ".386\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, ".model flat,stdcall\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, ".stack 100h\n");
		file << text;
		memset(text, NULL, 40); 
		sprintf(text, "option casemap : none\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, "include \\masm32\\include\\kernel32.inc\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, " include \\masm32\\include\\msvcrt.inc\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, "includelib \\masm32\\lib\\kernel32.lib\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, "includelib \\masm32\\lib\\msvcrt.lib\n\n"); 
		file << text;
		memset(text, NULL, 40);
		sprintf(text, ".code\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, ".data\n");
		file1 << text;
		memset(text, NULL, 40);
	}
	void Loc(Ident l, bool f)
	{
		if (f)
		{
			file1 << ", :dword";
			sprintf(text, ", %s:dword", l.name);
			file << text;
			memset(text, NULL, 40);
		}
		else
		{
			file1 << " :dword\n";
			sprintf(text, " %s:dword\n", l.name);
			file << text;
			memset(text, NULL, 40);
		}
	}
	void put(char *w)
	{
		sprintf(text, "%s\n", w);
		file << text;
		memset(text, NULL, 40);
	}
	void ENDL()
	{
		file1 << "\n";
		file << "\n";
	}
	void BEGIN()
	{
		sprintf(text, "Begin: \n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, "finit \n");
		file << text;
		memset(text, NULL, 40);
	}
	void Get(char* w)
	{
		sprintf(text, "invoke _scanf, fmd, %s\n", w);
		file << text;
		memset(text, NULL, 40);
	}
	void ELSE()
	{
		sprintf(text, ".ELSE\n");
		file << text;
		memset(text, NULL, 40);
	}
	void PROC(char* name)
	{
		sprintf(text, "%s PROC ", name);
		file << text;
		memset(text, NULL, 40);
		sprintf(text, "%s PROTO  STDCALL ", name);
		file1 << text;
		memset(text, NULL, 40);
	}
	void INIT_MAS(char* w)
	{
		sprintf(text, "%s DD ", w);
		file1 << text;
		memset(text, NULL, 40);
	}
	void PUT_N(char* n,bool f)
	{
		if (f)
		{
			sprintf(text, "%s, ", n);
			file1 << text;
			memset(text, NULL, 40);
		}
		else
		{
			sprintf(text, "%s \n", n);
			file1 << text;
			memset(text, NULL, 40);
		}
	}
	void RET(char* w)
	{
		if (strcmp(w, "eax") != 0)
		{
			sprintf(text, "mov eax, %s\n", w);
			file << text;
			memset(text, NULL, 40);
		}
		file << "RET\n";
	}
	void MOV(char* name, char* qwerty)
	{
		if (strcmp(qwerty, "eax") == 0)
		{
			sprintf(text, "MOV %s, %s\n", name, qwerty);
			file << text;
			memset(text, NULL, 40);
		}
		else
		{
			sprintf(text, "MOV ebx, %s\n",qwerty);
			file << text;
			memset(text, NULL, 40);
			sprintf(text, "MOV %s, ebx\n", name);
			file << text;
			memset(text, NULL, 40);
		}
	}
	void MOV(char* name, const char* qwerty)
	{
		if (strcmp(qwerty, "eax") == 0)
		{
			sprintf(text, "MOV %s, %s\n", name, qwerty);
			file << text;
			memset(text, NULL, 40);
		}
		else
		{
			sprintf(text, "MOV ebx, %s\n", qwerty);
			file << text;
			memset(text, NULL, 40);
			sprintf(text, "MOV %s, ebx\n", name);
			file << text;
			memset(text, NULL, 40);
		}
	}
	void MOV(const char* name, char* qwerty)
	{
		if (strcmp(qwerty, "eax") == 0)
		{
			sprintf(text, "MOV %s, %s\n", name, qwerty);
			file << text;
			memset(text, NULL, 40);
		}
		else
		{
			sprintf(text, "MOV ebx, %s\n", qwerty);
			file << text;
			memset(text, NULL, 40);
			sprintf(text, "MOV %s, ebx\n", name);
			file << text;
			memset(text, NULL, 40);
		}
	}
	void I_Put(char* name,int n)
	{
		if (n == 4)
			sprintf(text, "%s DW ?\n", name);
		if (n == 8)
			sprintf(text, "%s DD ?\n", name);
		file << text;
		memset(text, NULL, 40);
	}
	void OUTL(char *b)
	{
		if (b[0] == '\'')
		{
			sprintf(text, "b%d db %s,10,0\n", bi, b);
			file1 << text;
			memset(text, NULL, 40);
			sprintf(text, "invoke crt_printf, addr fmt, addr b%d\n", bi);
			file << text;
			memset(text, NULL, 40);
			bi++;
		}
		else
		{
			sprintf(text, "invoke crt_printf, addr fmd, %s\n", b);
			file << text;
			memset(text, NULL, 40);
		}
	}
	void OUT(char *b)
	{
		if (b[0] == '\'')
		{
			sprintf(text, "b%d db %s,0\n", bi, b);
			file1 << text;
			memset(text, NULL, 40);
			sprintf(text, "invoke crt_printf, addr fmt, addr b%d\n", bi);
			file << text;
			memset(text, NULL, 40);
			bi++;
		}
		else
		{
			sprintf(text, "invoke crt_printf, addr fmd, %s\n", b);
			file << text;
			memset(text, NULL, 40);
		}
	}
	void END(Lexem* l)
	{
		switch (l->type)
		{
		case 1:
		{
			sprintf(text, "%s ENDP\n", l->word);
			file << text;
			memset(text, NULL, 40);
			break;
		}
		case 2:
		{
			switch (l->code)
			{
			case 24: //if
			{
				sprintf(text, ".ENDIF\n");
				file << text;
				memset(text, NULL, 40);
				break;
			}
			}
		}
		case 4:
		{
			if (l->code == 9)
			{
				sprintf(text, "END Begin\n");
				file << text;
				memset(text, NULL, 40);
				break;
			}
		}
		}
	}
	void WHEN(stack <Lexem> s)
	{
		sprintf(text, ".IF ");
		file << text;
		memset(text, NULL, 40);
		L_Put(s);
		file << endl;
		sprintf(text, "invoke ExitProcess,0\n");
		file << text;
		memset(text, NULL, 40);
		sprintf(text, ".ENDIF\n");
		file << text;
		memset(text, NULL, 40);
	}
	void If(stack <Lexem> s)
	{
		sprintf(text, ".IF ");
		file << text;
		memset(text, NULL, 40);
		L_Put(s);
		file << endl;
	}
	void While(stack <Lexem> s)
	{
		sprintf(text, ".WHILE ");
		file << text;
		memset(text, NULL, 40);
		L_Put(s);
		file << endl;
	}
	void ENDWhile()
	{
		sprintf(text, ".ENDW\n");
		file << text;
		memset(text, NULL, 40);
	}
	void LOOP(int c)
	{
		sprintf(text, "lp%d: \n", c);
		file << text;
		memset(text, NULL, 40);
	}
	void ENDLOOP(int c)
	{
		sprintf(text, "jmp lp%d \n", c);
		file << text;
		memset(text, NULL, 40);
	}
	void PUSH(char *x)
	{
		sprintf(text, "push %s\n", x);
		file << text;
		memset(text, NULL, 40);
	}
	void POP()
	{
		sprintf(text, "pop eax\n");
		file << text;
		memset(text, NULL, 40);
	}
	void L_Put(stack <Lexem> s)
	{
		while (!s.empty())
		{
			switch (s.top().type)
			{
			case 1:
			{
				sprintf(text, "%s", s.top().word);
				file << text;
				memset(text, NULL, 40);
				s.pop();
				break;
			}
			case 2:
			{
				s.pop();
				break;
			}
			case 3:
			{
				sprintf(text, "%s", s.top().word);
				file << text;
				memset(text, NULL, 40);
				s.pop();
				break;
			}
			case 4:
			{
				switch (s.top().code)
				{
				case 1: // =
				{
					sprintf(text, " == ");
					file << text;
					memset(text, NULL, 40);
					s.pop();
					break;
				}
				case 14: // <
				{
					sprintf(text, " < ");
					file << text;
					memset(text, NULL, 40);
					s.pop();
					break;
				}
				case 15: // >
				{
					sprintf(text, " > ");
					file << text;
					memset(text, NULL, 40);
					s.pop();
					break;
				}
				case 19: // <=
				{
					sprintf(text, " <= ");
					file << text;
					memset(text, NULL, 40);
					s.pop();
					break;
				}
				case 20: // <=
				{
					sprintf(text, " <= ");
					file << text;
					memset(text, NULL, 40);
					s.pop();
					break;
				}
				case 4: // (
				{
					s.pop();
					break;
				}
				case 5: // )
				{
					s.pop();
					return;
				}
				s.pop();
				}
				break;
			}
			break;
			}
		}
	}
	stack <Lexem> A_Put(stack <Lexem> s)
	{
		stack <Lexem> st;
		while (!s.empty())
		{
			switch (s.top().type)
			{
			case 1:
			{
				st.push(s.top());
				s.pop();
				break;
			}
			case 2:
			{
				s.pop();
				break;
			}
			case 3:
			{
				st.push(s.top());
				s.pop();
				break;
			}
			case 4:
			{
				switch (s.top().code)
				{
				case 4: // (
				{
					s.pop();
					if (s.top().type == 2 && s.top().code == 40)
					{
						s = A_Put(s);
						sprintf(text, "fld ax\n");
						file << text;
						memset(text, NULL, 40);
						sprintf(text, "fsqrt\n");
						file << text;
						memset(text, NULL, 40);
						sprintf(text, "fstp %s\n", s.top().word);
						file << text;
						memset(text, NULL, 40);
						st.pop();
					}
					else
					{
						sprintf(text, "invoke %s,%s\n", s.top().word, st.top().word);
						file << text;
						memset(text, NULL, 40);
						st.pop();
					}
					s.pop();
					break;
				}
				case 5: // )
				{
					s.pop();
					return s;
				}
				case 10: //+
				{
					sprintf(text, "add %s", st.top().word);
					file << text;
					memset(text, NULL, 40);
					sprintf(text, ", %s\n", st.top().word);
					s.pop();
					break;
				}
				case 11: //-
				{
					sprintf(text, "sub %s", st.top().word);
					file << text;
					memset(text, NULL, 40);
					sprintf(text, ", %s\n", st.top().word);
					s.pop();
					break;
				}
				case 12: //*
				{
					sprintf(text, "mul %s", st.top().word);
					file << text;
					memset(text, NULL, 40);
					sprintf(text, ", %s\n", st.top().word);
					s.pop();
					break;
				}
				case 13: // /
				{
					sprintf(text, "div %s", st.top().word);
					file << text;
					memset(text, NULL, 40);
					sprintf(text, ", %s\n", st.top().word);
					s.pop();
					break;
				}
				s.pop();
				}
				break;
			}
			break;
			}
		}
		return s;
	}
	void write_data(Ident* mi,int icnt)
	{
		sprintf(text, "bf dd 0\n");
		file1 << text;
		memset(text, NULL, 40);
		sprintf(text, "fmd db \'%%d\',0\n");
		file1 << text;
		memset(text, NULL, 40);
		sprintf(text, "fmt db \'%%s\',0\n");
		file1 << text;
		memset(text, NULL, 40);
		sprintf(text, ".data\?\n");
		file1 << text;
		memset(text, NULL, 40);
		for (int i = 0; i < icnt; i++)
		{
			if (mi[i].type != nullptr)
			{
				if (strcmp(mi[i].type->word, "Integer") == 0)
					sprintf(text, "%s DD ?\n", mi[i].name);
				if (strcmp(mi[i].type->word, "Float") == 0)
					sprintf(text, "%s DD ?\n", mi[i].name);
				file1 << text;
				memset(text, NULL, 40);
			}
		}
	}
};
struct Syntax_analis
{
	Lexem *cur;
	stack <Lexem> stk;
	Lexical_analis *stream;
	Code_Generator *cogen;
	Ident *Mas_Ident;
	Typ *Mas_Types;
	Func *Mas_Func;
	int icnt,tcnt,fcnt,dns,lc;
	Syntax_analis()
	{
		cur = NULL;
		stream = new Lexical_analis();
		Mas_Ident = NULL;
		Mas_Types = NULL;
		Mas_Func = NULL;
		icnt = 0;
		tcnt = 0;
		fcnt = 0;
		dns = 0;
		lc = 0;
		cogen = new Code_Generator("a.asm");
	}
	void Add(Typ i)
	{
		Mas_Types = (Typ*)realloc(Mas_Types, ((tcnt+1) * sizeof(struct Typ)));
		Mas_Types[tcnt] = i;
		tcnt++;
		cout << "Added new type " << i.name << endl;
	}
	void Add(char *name, Lexem* type)
	{
		Mas_Ident = (Ident*)realloc(Mas_Ident, (icnt * sizeof(struct Ident)));
		Mas_Ident[icnt - 1].name = (char*)calloc(strlen(name) + 1, sizeof(char));
		strcpy_s(Mas_Ident[icnt - 1].name, strlen(name) + 1, name);
		if (type != nullptr)
		{
			Mas_Ident[icnt - 1].type = type;
		}
		else
			Mas_Ident[icnt - 1].type = nullptr;
		cout << "Added new Identificator " << name<< endl;
	}
	void Add(Func i)
	{
		Mas_Func = (Func*)realloc(Mas_Func, ((fcnt + 1) * sizeof(struct Func)));
		Mas_Func[fcnt] = i;
		fcnt++;
		cout << "Added new Function " << i.name << endl;
	}
	int Find_F(Lexem *f)
	{
		for (int i = 0; i < fcnt; i++)
			if (strcmp(Mas_Func[i].name, f->word) == 0)
			{
				return i;
			}
		return -1;
	}
	int Find_I(Lexem* l)
	{
		for (int i = 0; i < icnt; i++)
			if (strcmp(Mas_Ident[i].name, l->word) == 0)
			{
				return i;
			}
		return -1;
	}
	int Find_T(Lexem* t)
	{
		for (int i = 0; i < tcnt; i++)
			if (strcmp(Mas_Types[i].name, t->word) == 0)
			{
				return i;
			}
		return -1;
	}
	bool I_Skan(Lexem *i)
	{
		bool k = false;
		cur = stream->Analys();
		if (cur == nullptr)
			return false;
		if (cur->code == Hash("("))
		{
			char* g = A_Put(A_Skan(Hash(")"))), m[20];
			cur = stream->Analys();
			sprintf(m, "%s[(%s*4]", i->word, g);
			char *s = A_Put(A_Skan(Hash(";")));
			cogen->MOV(m, s);
			return true;
		}
		if (cur->code == Hash(":"))
		{
			cur = stream->Analys();
			Mas_Ident[i->code].type = cur;
			cur = stream->Analys();
			k = true;
		}
		if (cur == nullptr)
			return false;
		if (cur->code == Hash(":="))
		{
			if (Find_T(Mas_Ident[Find_I(i)].type) != -1)
			{
				cur = stream->Analys();
				if (cur->code == Hash("("))
				{
					char s[20] = { 0 };
					cogen->INIT_MAS(i->word);
					for (int j = 0; j < Mas_Types[Find_T(Mas_Ident[Find_I(i)].type)].amount - 1; j++)
					{
						sprintf(s, A_Put(A_Skan(Hash(","))));
						cogen->PUT_N(s, true);
						memset(s, NULL, 20);
					}
					sprintf(s, A_Put(A_Skan(Hash(")"))));
					cogen->PUT_N(s, false);
					memset(s, NULL, 20);
					cur = stream->Analys();
				}
				else
				{
					stack <Lexem> ttr,rtt;
					Lexem fnc = *cur;
					cur = stream->Analys();
					ttr.push(*cur);
					rtt = A_Skan(Hash(")"));
					while (!rtt.empty())
					{
						ttr.push(rtt.top());
						rtt.pop();
					}
					ttr.push(*cur);
					ttr.push(fnc);
					while (!ttr.empty())
					{
						rtt.push(ttr.top());
						ttr.pop();
					}
					char *s = A_Put(rtt);
					cogen->MOV(i->word, s);
				}
			}
			else
			{
				char *s = A_Put(A_Skan(Hash(";")));
				cogen->MOV(i->word, s);
			}
			k = true;
		}
		if (cur == nullptr)
			return false;
		if (cur->code == Hash(","))
		{
			Lexem* tp = IC_Skan();
			if (tp != nullptr)
				Mas_Ident[i->code].type = tp;
			else
				Mas_Ident[i->code].type = nullptr;
		}
		return k;
	}
	Lexem* IC_Skan()
	{
		Lexem* l = stream->Analys();
		bool k = true;
		if (Find_I(l)!=-1)
		{
			l->code = Find_I(l);
			k = false;
		}
		if (k)
		{
			l->code = icnt++;
			Add(l->word,NULL);
		}
		cur = stream->Analys();
		if (cur->code == Hash(":"))
		{
			cur = stream->Analys();
			Mas_Ident[l->code].type = cur;
			return cur;
		}
		if (cur->code == Hash(":="))
		{
			char *s = A_Put(A_Skan(Hash(";")));
			cogen->MOV(l->word, s);
			return nullptr;
		}
		if (cur->code == Hash(","))
		{
			Lexem* tp = IC_Skan();
			if (tp != nullptr)
			{
				Mas_Ident[l->code].type = tp;
			}
			return tp;
		}
	}
	int popcheck(int c)
	{
		if (c == Hash("*") || c == Hash("/"))
			return 2;
		if (c == Hash("+") || c == Hash("-"))
			return 1;
		if (c == Hash(")")|| c == Hash("Sqrt"))
			return 0;
		if (c == Hash("("))
			return -1;
	}
	stack <Lexem> A_Skan(int c)
	{
		int o = 0;
		stack <Lexem> oper, ret;
		do
		{
		cur = stream->Analys();
		if ((cur->code == c || cur == nullptr) && o == 0)
		{
			while (!oper.empty())
			{
				ret.push(oper.top());
				oper.pop();
			}
			while (!ret.empty())
			{
				oper.push(ret.top());
				ret.pop();
			}
			return oper;
		}
		switch (cur->type)
		{
		case 1:
		{
			bool k = false;
			if(Find_F(cur) != -1)
			{
				cur->code = Find_F(cur);
				Lexem fnc = *cur;
				cur = stream->Analys();
				if (cur->code == Hash("("))
				{
					ret.push(*cur);
					for (int i = 0; i < Mas_Func[fnc.code].amount - 1; i++)
					{
						stack <Lexem> p = A_Skan(Hash(",")),np;
						while (!p.empty())
						{
							ret.push(p.top());
							p.pop();
						}
						ret.push(*cur);
					}
					stack <Lexem> p = A_Skan(Hash(")")), np;
					while (!p.empty())
					{
						ret.push(p.top());
						p.pop();
					}
					ret.push(*cur);
					ret.push(fnc);
				}
				k = true;
			}
			if (k)
				break;
			if (Find_I(cur) != -1)
			{
				if (Find_T(Mas_Ident[Find_I(cur)].type) != -1)
				{
					Lexem fnc = *cur;
					cur = stream->Analys();
					if (cur->code == Hash("("))
					{
						ret.push(*cur);
						stack <Lexem> p = A_Skan(Hash(")"));
						while (!p.empty())
						{
							ret.push(p.top());
							p.pop();
						}
						ret.push(*cur);
						ret.push(fnc);
					}
					else
					{
						ret.push(fnc);
						return ret;
					}
				}
				else
				{
				cur->code = Find_I(cur);
				ret.push(*cur);
				}
				k = true;
			}
			if (k)
				break;
			cur->code = icnt++;
			Add(cur->word, NULL);
			ret.push(*cur);
			break;
		}
		case 2:
		{
			if (cur->code == Hash("Sqrt"))
			{
				Lexem fnc = *cur;
				cur = stream->Analys();
				if (cur->code == Hash("("))
				{
					ret.push(*cur);
					stack <Lexem> p = A_Skan(Hash(")"));
					while (!p.empty())
					{
						ret.push(p.top());
						p.pop();
					}
					ret.push(*cur);
					ret.push(fnc);
				}
			}
			break;
		}
		case 3:
		{
			ret.push(*cur);
			break;
		}
		case 4:
		{
			switch (cur->code)
			{
			case 2: //,
			{
				ret.push(*cur);
				break;
			}
			case 4: // (
			{
				o++;
				oper.push(*cur);
				break;
			}
			case 5: // )
			{
				o--;
				if (!oper.empty())
				{
					while (popcheck(oper.top().code) != -1)
					{
						ret.push(oper.top());
						oper.pop();
					}
					oper.pop();
				}
				break;
			}
			case 10: //+
			{
				if (!oper.empty())
					while (popcheck(oper.top().code) >= popcheck(cur->code))
					{
						ret.push(oper.top());
						oper.pop();
						if (oper.empty())
							break;
					}
				oper.push(*cur);
				break;
			}
			case 11: //-
			{
				if (!oper.empty())
					while (popcheck(oper.top().code) >= popcheck(cur->code))
					{
						ret.push(oper.top());
						oper.pop();
						if (oper.empty())
							break;
					}
				oper.push(*cur);
				break;
			}
			case 12: //*
			{
				oper.push(*cur);
				break;
			}
			case 13: // /
			{
				oper.push(*cur);
				break;
			}
			}
			break;
		}
		break;
		}
		} while (true);
	}
	char* A_Put(stack <Lexem> s)
	{
		char top[20] = { 0 };
		stack <Lexem> ls;
		char text[40] = { 0 };
		stk = s;
		if (stk.top().word[0] == '\'')
		{
			return stk.top().word;
		}
		if (!stk.empty())
		{
			Lexem a = stk.top();
			if (stk.size() == 1)
			{
				return a.word;
			}
		}
		else
		{
			return nullptr;
		}
		while (!stk.empty())
		{
			switch (stk.top().type)
			{
			case 1:
			{
				ls.push(stk.top());
				stk.pop();
				break;
			}
			case 2:
			{
				stk.pop();
				break;
			}
			case 3:
			{
				ls.push(stk.top());
				stk.pop();
				break;
			}
			case 4:
			{
				switch (stk.top().code)
				{
				case 2: //,
				{
					char* txt = (char*)malloc(strlen(ls.top().word) * sizeof(char));
					txt = strcpy(txt, ls.top().word);
					return txt;
				}
				case 4: // (
				{
					stk.pop();
					char* ret = A_Put(stk);
					if (stk.top().code == Hash(","))
					{
						stk.pop();
						sprintf(text, "%s, %s", ret, A_Put(stk));
						char tmp[30];
						sprintf(tmp, "invoke %s, %s", stk.top().word,text);
						cogen->put(tmp);
						memset(text, NULL, 40);
						Lexem u = Lexem(1, "eax", 0);
						ls.push(u);
						stk.pop();
						break;
					}
					if (Find_F(&stk.top()) != -1)
					{
						sprintf(text, "invoke %s, %s", stk.top().word, ret);
						cogen->put(text);
						memset(text, NULL, 40);
						Lexem u = Lexem(1,"eax",0);
						ls.push(u);
						stk.pop();
						break;
					}
					if (stk.top().type == 2 && stk.top().code == Hash("Sqrt"))
					{
						sprintf(text, "fild %s", ret);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "fsqrt");
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "fistp bf");
						cogen->put(text);
						memset(text, NULL, 40);
						Lexem u = Lexem(1, "bf", 0);
						ls.push(u);
						stk.pop();
						break;
					}
					if (Find_T(Mas_Ident[Find_I(&stk.top())].type) != -1)
					{
						sprintf(text, "%s[%s*4]",stk.top().word,ret);
						Lexem u = Lexem(1, text, 0);
						ls.push(u);
						memset(text, NULL, 40);
						stk.pop();
						break;
					}
				}
				case 5: // )
				{
					stk.pop();
					char* txt = (char*)malloc(strlen(ls.top().word) * sizeof(char));
					txt = strcpy(txt, ls.top().word);
					return txt;
				}
				case 10: //+
				{
					sprintf(top, "%s", ls.top().word);
					ls.pop();
					if (strcmp(top, "eax") == 0)
					{
						sprintf(text, "add eax, %s", ls.top().word);
						cogen->put(text);
						memset(text, NULL, 40);
					}
					else
					if (strcmp(ls.top().word, "eax") == 0)
					{
						sprintf(text, "add eax, %s", top);
						cogen->put(text);
						memset(text, NULL, 40);
					}
					else
					{
						sprintf(text, "mov eax, %s", ls.top().word);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "add eax, %s",top);
						cogen->put(text);
						memset(text, NULL, 40);
					}
					ls.pop();
					Lexem u = Lexem(1, "eax", 0);
					ls.push(u);
					memset(top, NULL, 20);
					stk.pop();
					break;
				}
				case 11: //-
				{
					sprintf(top, "%s", ls.top().word);
					ls.pop();
					if (ls.empty())
					{
						if (strcmp(top, "eax") != 0)
						{
							sprintf(text, "mov eax, %s", top);
							cogen->put(text);
							memset(text, NULL, 40);
						}
						sprintf(text, "neg eax");
						cogen->put(text);
						memset(text, NULL, 40);
					}
					else
					{
						if (strcmp(top, "eax") == 0)
						{
							sprintf(text, "mov ebx, %s", top);
							cogen->put(text);
							memset(text, NULL, 40);
							sprintf(text, "mov eax, %s", ls.top().word);
							cogen->put(text);
							memset(text, NULL, 40);
							sprintf(text, "sub eax, ebx");
							cogen->put(text);
							memset(text, NULL, 40);
						}
						else
						if (strcmp(ls.top().word, "eax") == 0)
						{
							sprintf(text, "sub eax, %s", top);
							cogen->put(text);
							memset(text, NULL, 40);
						}
						else
						{
							sprintf(text, "mov eax, %s", ls.top().word);
							cogen->put(text);
							memset(text, NULL, 40);
							sprintf(text, "sub eax, %s", top);
							cogen->put(text);
							memset(text, NULL, 40);
						}
						ls.pop();
					}
					Lexem u = Lexem(1, "eax", 0);
					ls.push(u);
					memset(top, NULL, 20);
					stk.pop();
					break;
				}
				case 12: //*
				{
					sprintf(top, "%s", ls.top().word);
					ls.pop();
					if (strcmp(top, "eax") == 0 || isalpha(top[0]) == 0)
					{
						sprintf(text, "mov ebx, %s", top);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "mov eax, %s", ls.top().word);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "mul ebx");
						cogen->put(text);
						memset(text, NULL, 40);
					}
					else
					if (strcmp(ls.top().word, "eax") == 0)
					{
						sprintf(text, "mul %s", top);
						cogen->put(text);
						memset(text, NULL, 40);
					}
					else
					{
						sprintf(text, "mov eax, %s", ls.top().word);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "mul %s", top);
						cogen->put(text);
						memset(text, NULL, 40);
					}
					ls.pop();
					Lexem u = Lexem(1, "eax", 0);
					ls.push(u);
					memset(top, NULL, 20);
					stk.pop();
					break;
				}
				case 13: // /
				{
					sprintf(top, "%s", ls.top().word);
					ls.pop();
					if (strcmp(top, "eax") == 0 || isalpha(top[0]) == 0)
					{
						sprintf(text, "mov ebx, %s", top);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "mov eax, %s", ls.top().word);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "div ebx");
						cogen->put(text);
						memset(text, NULL, 40);
					}
					else
					if (strcmp(ls.top().word, "eax") == 0)
					{
						sprintf(text, "div %s", top);
						cogen->put(text);
						memset(text, NULL, 40);
					}
					else
					{
						sprintf(text, "mov eax, %s", ls.top().word);
						cogen->put(text);
						memset(text, NULL, 40);
						sprintf(text, "div %s", top);
						cogen->put(text);
						memset(text, NULL, 40);
					}
					ls.pop();
					Lexem u = Lexem(1, "eax", 0);
					ls.push(u);
					memset(top, NULL, 20);
					stk.pop();
					break;
				}
				stk.pop();
				}
				break;
				}
			}
		}
		char* txt = (char*)malloc(strlen(ls.top().word) * sizeof(char));
		txt = strcpy(txt, ls.top().word);
		return txt;
	}
	stack <Lexem> L_Skan(int c)
	{
		stack <Lexem> oper, ret;
		do
		{
			cur = stream->Analys();
			if (cur->code == c || cur==nullptr)
			{
				while (!oper.empty())
				{
					ret.push(oper.top());
					oper.pop();
				}
				while (!ret.empty())
				{
					oper.push(ret.top());
					ret.pop();
				}
				return oper;
			}
			switch (cur->type)
			{
			case 1:
			{
				bool k = false;
				if (fcnt > 0)
				{
					for (int i = 0; i < fcnt; i++)
						if (strcmp(Mas_Func[i].name, cur->word) == 0)
						{
							cur->code = i;
							Lexem* fnc = cur;
							cur = stream->Analys();
							if (cur->code == Hash("("))
							{
								ret.push(*cur);
								for (int i = 0; i < Mas_Func[i].amount - 1; i++)
								{
									stack <Lexem> p = A_Skan(Hash(","));
									while (!p.empty())
									{
										ret.push(p.top());
										p.pop();
									}
									ret.push(*cur);
								}
								stack <Lexem> p = A_Skan(Hash(")"));
								while (!p.empty())
								{
									ret.push(p.top());
									p.pop();
								}
								ret.push(*cur);
								ret.push(*fnc);
							}
							k = true;
							break;
						}
				}
				if (Find_T(Mas_Ident[Find_I(cur)].type) != -1)
				{
					Lexem *h = cur;
					char text[20];
					cur = stream->Analys();
					char *r = A_Put(A_Skan(Hash(")")));
					sprintf(text, "%s[%s*4]", h->word, r);
					Lexem u = Lexem(1, text, 0);
					ret.push(u);
					k = true;
				}
				if (k)
					break;
				if (icnt > 0)
				{
					for (int i = 0; i < icnt; i++)
						if (strcmp(Mas_Ident[i].name, cur->word) == 0)
						{
							cur->code = i;
							ret.push(*cur);
							k = true;
							break;
						}
				}
				if (k)
					break;
				cur->code = icnt++;
				Add(cur->word, NULL);
				ret.push(*cur);
				break;
			}
			case 3:
			{
				ret.push(*cur);
				break;
			}
			case 4:
			{
				switch (cur->code)
				{
				case 4: // (
				{
					break;
				}
				case 1:// =
				{
					ret.push(*cur);
					break;
				}
				case 19: //<=
				{
					ret.push(*cur);
					break;
				}
				case 20: //>=
				{
					ret.push(*cur);
					break;
				}
				case 15: //>
				{
					ret.push(*cur);
					break;
				}
				case 14: //<
				{
					ret.push(*cur);
					break;
				}
				}
				break;
			}
			break;
			}
		} while (true);
	}
	void Return(bool f)
	{
		if (f)
		{
			char *s = A_Put(A_Skan(Hash(";")));
			cogen->RET(s);
		}
		else
		{
			char o[30] = { 0 };
			sprintf(o, "invoke ExitProcess,0\n");
			cogen->put(o);
		}
	}
	bool Put_Line()
	{
		cur = stream->Analys();
		if (cur->code == Hash("("))
		{
			A_Skan(Hash(")"));
			if (cur->code == Hash(";"))
				return true;
		}
		return false;
	}
	bool Put()
	{
		cur = stream->Analys();
		if (cur->code == Hash("("))
		{
			char* b = A_Put(A_Skan(Hash(")")));
			cogen->OUT(b);
			if (cur->code == Hash(";"))
				return true;
		}
		return false;
	}
	bool Get()
	{
		cur = stream->Analys();
		if (cur->code == Hash("("))
		{
			cur = stream->Analys();
			cogen->Get(cur->word);
			cur = stream->Analys();
			if (cur->code == Hash(")"))
			{
				cur = stream->Analys();
				if (cur->code == Hash(";"))
				return true;
			}
		}
		return false;
	}
	bool New_Line()
	{
		cur = stream->Analys();
		if (cur->code == Hash(";"))
			return true;
		return false;
	}
	void Typed(char* name)
	{
		int a, b;
		cur = stream->Analys();
		if(cur->code == Hash("is"))
		{
			cur = stream->Analys();
			if (cur->code == Hash("array"))
			{
				cur = stream->Analys();
				if (cur->code == Hash("("))
				{
					cur = stream->Analys();
					string s = string(cur->word);
					a = atoi(s.c_str());
					cur = stream->Analys();
					cur = stream->Analys();
					cur = stream->Analys();
					s = string(cur->word);
					b = atoi(s.c_str());
					cur = stream->Analys();
					cur = stream->Analys();
					cur = stream->Analys();
					Typ t = Typ(name, cur->word, b - a + 1);
					Add(t);
				}
			}
		}
	}
	bool Operations(char* name)
	{
		while (true)
		{
			cur = stream->Analys();
			if (cur == nullptr)
				break;
			switch (cur->type)
			{
			case 1:
			{
				bool k = true;
				if (Find_I(cur) != -1)
				{
					cur->code = Find_I(cur);
					k = false;
				}
				if (k)
				{
					cur->code = icnt++;
					Add(cur->word, NULL);
				}
				I_Skan(cur);
				break;
			}
			case 2:
			{
				switch (cur->code)
				{
				case 23: //begin
				{
					if (dns == 1)
					{
						cogen->BEGIN();
						Operations(";");
						return true;
					}
					break;
				}
				case 24: //if
				{
					cogen->If(L_Skan(Hash("then")));
					Operations("if");
					break;
				}
				case 28: //end
				{
					cur = stream->Analys();
					if (strcmp(cur->word, name) == 0)
					{
						if (strcmp(cur->word, "loop") == 0)
						{
							cogen->ENDLOOP(lc);
							return true;
						}
						else
						{
							cogen->END(cur);
							return true;
						}
					}
					else
					{
						if (strcmp(cur->word, "loop") == 0 && strcmp(name, "while") == 0)
						{
							cogen->ENDWhile();
							return true;
						}
					}
					break;
				}
				case 29: //else
				{
					cogen->ELSE();
					break;
				}
				case 31: // declare
				{
					cur = stream->Analys();
					if (cur->code == Hash("function"))
					{
						cur = stream->Analys();
						Function(cur->word);
					}
					break;
				}
				case 34: // type
				{
					cur = stream->Analys();
					Typed(cur->word);
					break;
				}
				case 35: // loop
				{
					lc++;
					cogen->LOOP(lc);
					Operations("loop");
					break;
				}
				case 36: //Put_Line
				{
					Put_Line();
					break;
				}
				case 37: //Put
				{
					Put();
					break;
				}
				case 38: //Get
				{
					Get();
					break;
				}
				case 39: //New_Line
				{
					New_Line();
					break;
				}
				case 41: //return
				{
					if (dns <= 1)
						Return(false);
					else
						Return(true);
					break;
				}
				case 44: //exit
				{
					cur = stream->Analys();
					if (cur->code == 45) //when
					{
						cogen->WHEN(L_Skan(Hash(";")));
					}
					break;
				}
				case 46: //while
				{
					cogen->While(L_Skan(Hash("loop")));
					Operations("while");
					break;
				}
				}
				break;
			}
			}
		}
	}
	bool Operations(const char* name)
	{
		while (true)
		{
			cur = stream->Analys();
			if (cur == nullptr)
				break;
			switch (cur->type)
			{
			case 1:
			{
				bool k = true;
				if (Find_I(cur) != -1)
				{
					cur->code = Find_I(cur);
					k = false;
				}
				if (k)
				{
					cur->code = icnt++;
					Add(cur->word, NULL);
				}
				I_Skan(cur);
				break;
			}
			case 2:
			{
				switch (cur->code)
				{
				case 23: //begin
				{
					if (dns == 1)
					{
						cogen->BEGIN();
						Operations(";");
						return true;
					}
					break;
				}
				case 24: //if
				{
					cogen->If(L_Skan(Hash("then")));
					Operations("if");
					break;
				}
				case 28: //end
				{
					cur = stream->Analys();
					if (strcmp(cur->word, name) == 0)
					{
						if (strcmp(cur->word, "loop") == 0)
						{
							cogen->ENDLOOP(lc);
							return true;
						}
						else
						{
							cogen->END(cur);
							return true;
						}
					}
					else
					{
						if (strcmp(cur->word, "loop") == 0 && strcmp(name, "while") == 0)
						{
							cogen->ENDWhile();
							return true;
						}
					}
				}
				case 29: //else
				{
					cogen->ELSE();
					break;
				}
				case 31: // declare
				{
					cur = stream->Analys();
					if (cur->code == Hash("function"))
					{
						cur = stream->Analys();
						Function(cur->word);
					}
					break;
				}
				case 34: // type
				{
					cur = stream->Analys();
					Typed(cur->word);
					break;
				}
				case 35: // loop
				{
					lc++;
					cogen->LOOP(lc);
					Operations("loop");
					break;
				}
				case 36: //Put_Line
				{
					Put_Line();
					break;
				}
				case 37: //Put
				{
					Put();
					break;
				}
				case 38: //Get
				{
					Get();
					break;
				}
				case 39: //New_Line
				{
					New_Line();
					break;
				}
				case 41: //return
				{
					if (dns <= 1)
						Return(false);
					else
						Return(true);
					break;
				}
				case 44: //exit
				{
					cur = stream->Analys();
					if (cur->code == 45) //when
					{
						cogen->WHEN(L_Skan(Hash(";")));
					}
					break;
				}
				case 46: //while
				{
					cogen->While(L_Skan(Hash("loop")));
					Operations("while");
					break;
				}
				}
				break;
			}
			}
		}
	}
	bool Function(char* name)
	{
		cogen->PROC(name);
		cur = stream->Analys();
		if (cur->code == Hash("("))
		{
			Func f = Arg(name);
			cur = stream->Analys();
			if (cur->code == Hash("return"))
			{
				cur = stream->Analys();
				f.ret = cur;
				Add(f);
				cur = stream->Analys();
				if (cur->code == Hash("is"))
				{
					dns++;
					if (Operations(name))
					{
						dns--;
						return true;
					}
				}
			}
		}
		return false;
	}
	Func Arg(char* name)
	{
		int a = 0;
		Func f;
		Lexem* lexem = nullptr;
		while(true)
		{
			cur = stream->Analys();
			if (cur->code == Hash(")"))
			{
				cogen->ENDL();
				break;
			}
			if (cur->code == Hash(","))
			{
				cur = stream->Analys();
				cur->code = icnt++;
				Add(cur->word, NULL);
				cur = stream->Analys();
				if (cur->code == Hash(":"))
				{
					cur = stream->Analys();
					Mas_Ident[icnt - 1].type = cur;
					cogen->Loc(Mas_Ident[icnt - 1],true);
					lexem = (Lexem*)realloc(lexem, (a + 1) * sizeof(struct Lexem));
					lexem[a] = *cur;
					a++;
				}
			}
			else
			{
				cur->code = icnt++;
				Add(cur->word, NULL);
				cur = stream->Analys();
				if (cur->code == Hash(":"))
				{
					cur = stream->Analys();
					Mas_Ident[icnt-1].type = cur;
					cogen->Loc(Mas_Ident[icnt - 1], false);
					lexem = (Lexem*)realloc(lexem, (a + 1) * sizeof(struct Lexem));
					lexem[a] = *cur;
					a++;
				}
			}
		}
		f.amount = a;
		f.arg = lexem;
		f.name = name;
		return f;
	}
	bool Procedure(char* name)
	{
		cur = stream->Analys();
		if (cur->code == Hash("is"))
		{
			dns++;
			if (Operations(name))
			{
				dns--;
				return true;
			}
		}
		return false;
	}
	void Analysis()
	{
		bool k = true;
		while (k)
		{
			cur = stream->Analys();
			if (cur == nullptr)
				break;
			if (cur->type==2)
			{
				if (cur->code==22) //procedure
				{
					k = Procedure(stream->Analys()->word);
				}
			}
		}
	}
};
int main()
{
	setlocale(LC_ALL, "rus");
	Syntax_analis p = Syntax_analis();
	p.Analysis();
	p.cogen->write_data(p.Mas_Ident, p.icnt);
	p.cogen->file.close();
	p.cogen->file1.close();
}
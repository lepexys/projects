#include "pch.h"
#include <iostream>
#include <fstream>
#include <clocale>
#include <time.h>
#include <iomanip>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int n=100;// Колличество чисел в исходном файле 
	srand(time(0));
	ofstream ofiles[8] = {ofstream("1.txt", ios::binary|ios::out),ofstream("2.txt", ios::binary|ios::out),ofstream("3.txt", ios::binary|ios::out),ofstream("4.txt", ios::binary|ios::out),ofstream("1.1.txt", ios::binary|ios::out),ofstream("1.2.txt", ios::binary|ios::out),ofstream("1.3.txt", ios::binary|ios::out),ofstream("1.4.txt", ios::binary|ios::out) };
	ifstream ifiles[8] = { ifstream("1.txt", ios::binary|ios::in),ifstream("2.txt", ios::binary|ios::in),ifstream("3.txt", ios::binary|ios::in),ifstream("4.txt", ios::binary|ios::in),ifstream("1.1.txt", ios::binary|ios::in),ifstream("1.2.txt", ios::binary|ios::in),ifstream("1.3.txt", ios::binary|ios::in),ifstream("1.4.txt", ios::binary|ios::in) };
	double rd[4] = {0.0,0.0,0.0,0.0};
	double buff;
	ofstream ofile("file.txt", ios::binary | ios::out);
	for (int i = 0; i < n; i++)
	{
		buff = (double)(rand() % 100) / (double)100 + (double)(rand() % 100);
		ofile.write((char*)&buff,sizeof (buff));
	}
	ofile.close();
	double last,max=NULL;
	int j=4;
	ifstream ifile("file.txt", ios::binary | ios::in);
	short counter = 0;
	ifile.read((char*)&buff, sizeof buff);
	ofiles[0].write((char*)&buff, sizeof buff);
	last = buff;
	while (!ifile.eof())
	{
		ifile.read((char*)&buff,sizeof buff);
		cout << buff<<" ";
		if (last > buff)
		{
			ofiles[counter].write((char*)&buff,sizeof buff);
			last = buff;
		}
		else
		{
			counter++;
			if (counter == 4)
				counter = 0;
			ofiles[counter].write((char*)&buff, sizeof buff);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		ofiles[i].close();
		ifiles[i].close();
	}
	ifiles[0].open("1.txt", ios::binary | ios::in);
	ifiles[1].open("2.txt", ios::binary | ios::in);
	ifiles[2].open("3.txt", ios::binary | ios::in);
	ifiles[3].open("4.txt", ios::binary | ios::in);
	bool go=false;
	bool side = 0;
	counter = 0;
	while (true)
	{
		for (int i = 0; i < 4; i++)
			if (!ifiles[i + 4 * side].eof())
			{
				ifiles[i + 4 * side].read((char*)&buff,sizeof buff);
				rd[i] = buff;
				if (rd[i] > max)
				{
					max = rd[i];
					j = i;
					last = max;
				}
			}
		while (true)
		{
			buff = rd[j];
			ofiles[counter + 4 * !side].write((char*)&buff, sizeof buff);
			if (!ifiles[j + 4 * side].eof())
			{
				ifiles[j + 4 * side].read((char*)&buff,sizeof buff);
				rd[j] = buff;
			}
			else
				rd[j] = 0;
			max = NULL;
			j = 4;
			for(int i = 0;i<4;i++)
				if (max < rd[i])
				{
					max = rd[i];
					j = i;
				}
			if (max > last)
			{
				counter++;
				if(counter==4)
				{
					counter = 0;
					go = true;
				}
				last = max;
			}
			else
			{
				last = max;
			}
			if (j == 4)
				break;
		}
		if (counter == 0 && go == false)
		{
			for (int i = 0; i < 4; i++)
			{
				ifiles[i + side * 4].close();
				ifiles[i + !side * 4].close();
				ofiles[i + !side * 4].close();
				ofiles[i + side * 4].close();
			}
			if (side)
			{
				ifiles[0] =ifstream("1.txt", ios::binary | ios::in);
				ifiles[1] = ifstream("2.txt", ios::binary | ios::in);
				ifiles[2] = ifstream("3.txt", ios::binary | ios::in);
				ifiles[3] = ifstream("4.txt", ios::binary | ios::in);
				ofiles[4] = ofstream("1.1.txt", ios::binary | ios::out);
				ofiles[5] = ofstream("1.2.txt", ios::binary | ios::out);
				ofiles[6] = ofstream("1.3.txt", ios::binary | ios::out);
				ofiles[7] = ofstream("1.4.txt", ios::binary | ios::out);
			}
			else
			{
				ofiles[0] = ofstream("1.txt", ios::binary | ios::out);
				ofiles[1] = ofstream("2.txt", ios::binary | ios::out);
				ofiles[2] = ofstream("3.txt", ios::binary | ios::out);
				ofiles[3] = ofstream("4.txt", ios::binary | ios::out);
				ifiles[4] = ifstream("1.1.txt", ios::binary | ios::in);
				ifiles[5] = ifstream("1.2.txt", ios::binary | ios::in);
				ifiles[6] = ifstream("1.3.txt", ios::binary | ios::in);
				ifiles[7] = ifstream("1.4.txt", ios::binary | ios::in);
			}
			side = !side;
			break;
		}
		for (int i = 0; i < 4; i++)
		{
			ifiles[i + side * 4].close();
			ofiles[i + !side * 4].close();
			ofiles[i + !side * 4].close();
			ofiles[i + side * 4].close();
		}
		if (side)
		{
			ifiles[0] = ifstream("1.txt", ios::binary | ios::in);
			ifiles[1] = ifstream("2.txt", ios::binary | ios::in);
			ifiles[2] = ifstream("3.txt", ios::binary | ios::in);
			ifiles[3] = ifstream("4.txt", ios::binary | ios::in);
			ofiles[4] = ofstream("1.1.txt", ios::binary | ios::out);
			ofiles[5] = ofstream("1.2.txt", ios::binary | ios::out);
			ofiles[6] = ofstream("1.3.txt", ios::binary | ios::out);
			ofiles[7] = ofstream("1.4.txt", ios::binary | ios::out);
		}
		else
		{
			ofiles[0] = ofstream("1.txt", ios::binary | ios::out);
			ofiles[1] = ofstream("2.txt", ios::binary | ios::out);
			ofiles[2] = ofstream("3.txt", ios::binary | ios::out);
			ofiles[3] = ofstream("4.txt", ios::binary | ios::out);
			ifiles[4] = ifstream("1.1.txt", ios::binary | ios::in);
			ifiles[5] = ifstream("1.2.txt", ios::binary | ios::in);
			ifiles[6] = ifstream("1.3.txt", ios::binary | ios::in);
			ifiles[7] = ifstream("1.4.txt", ios::binary | ios::in);
		}
		side = !side;
		counter = 0;
		go = false;
		memset(rd, 0.0, 4*sizeof(double));
	}
	ifile.close();
	ofstream ofile1("fin.txt");
	while (!ifiles[4 * side].eof())
	{
		ifiles[4 * side].read((char*)&buff, sizeof buff);
		ofile1<<buff<<" ";
	}
	ofile1.close();
}

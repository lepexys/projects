#include "pch.h"

#include <cstdio>
#include <iostream>
#include <cstdlib>

#include <cmath>
#include <limits>
#include <climits>
#include <time.h>

using namespace std;


class ACO {
public:
	ACO(int nAnts, int nCities,
		double alpha, double beta, double q, double ro, double taumax,
		int initCity, int endcity);
	virtual ~ACO();

	void init();

	void connectCITIES(int cityi, int cityj);
	void setCITYPOSITION(int city, double x, double y);

	void printPHEROMONES();
	void printGRAPH();
	void printRESULTS();

	void optimize(int ITERATIONS);

private:
	double distance(int cityi, int cityj); //расстояние между узлами
	bool exists(int cityi, int cityc); //проверка наличия пути
	bool vizited(int antk, int c);	//посещён ли узел
	double PHI(int cityi, int cityj, int antk); //вероятность перехода муравья

	double length(int antk); //длина маршрута муравья

	int city(); 
	void route(int antk);
	int valid(int antk, int iteration);

	void updatePHEROMONES();


	int NUMBEROFANTS, NUMBEROFCITIES, INITIALCITY,DESTCITY;
	double ALPHA, BETA, Q, RO, TAUMAX;

	double BESTLENGTH;
	int* BESTROUTE;

	int** GRAPH, ** ROUTES;
	double** CITIES, ** PHEROMONES, ** DELTAPHEROMONES, ** PROBS;
	double randoms;
};
//Конструктор класса
ACO::ACO(int nAnts, int nCities,
	double alpha, double beta, double q, double ro, double taumax,
	int initCity,int endcity) 
{
	NUMBEROFANTS = nAnts;
	NUMBEROFCITIES = nCities;
	ALPHA = alpha;
	BETA = beta;
	Q = q;
	RO = ro;
	TAUMAX = taumax;
	INITIALCITY = initCity;
	DESTCITY = endcity;
	srand(time(0));
	randoms = rand()%21;
}
ACO::~ACO() {
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		delete[] GRAPH[i];
		delete[] CITIES[i];
		delete[] PHEROMONES[i];
		delete[] DELTAPHEROMONES[i];
		if (i < NUMBEROFCITIES - 1) {
			delete[] PROBS[i];
		}
	}
	delete[] GRAPH;
	delete[] CITIES;
	delete[] PHEROMONES;
	delete[] DELTAPHEROMONES;
	delete[] PROBS;
}

void ACO::init() {
	GRAPH = new int*[NUMBEROFCITIES];
	CITIES = new double*[NUMBEROFCITIES];
	PHEROMONES = new double*[NUMBEROFCITIES];
	DELTAPHEROMONES = new double*[NUMBEROFCITIES];
	PROBS = new double*[NUMBEROFCITIES - 1];
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		GRAPH[i] = new int[NUMBEROFCITIES];
		CITIES[i] = new double[2];
		PHEROMONES[i] = new double[NUMBEROFCITIES];
		DELTAPHEROMONES[i] = new double[NUMBEROFCITIES];
		PROBS[i] = new double[2];
		for (int j = 0; j < 2; j++) {
			CITIES[i][j] = -1.0;
			PROBS[i][j] = -1.0;
		}
		for (int j = 0; j < NUMBEROFCITIES; j++) {
			GRAPH[i][j] = 0;
			PHEROMONES[i][j] = 0.0;
			DELTAPHEROMONES[i][j] = 0.0;
		}
	}

	ROUTES = new int*[NUMBEROFANTS];
	for (int i = 0; i < NUMBEROFANTS; i++) {
		ROUTES[i] = new int[NUMBEROFCITIES];
		for (int j = 0; j < NUMBEROFCITIES; j++) {
			ROUTES[i][j] = -1;
		}
	}

	BESTLENGTH = (double)INT_MAX;
	BESTROUTE = new int[NUMBEROFCITIES];
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		BESTROUTE[i] = -1;
	}
}


void ACO::connectCITIES(int cityi, int cityj) {
	GRAPH[cityi][cityj] = 1;
	PHEROMONES[cityi][cityj] = (randoms/21) * TAUMAX;
	GRAPH[cityj][cityi] = 1;
	PHEROMONES[cityj][cityi] = PHEROMONES[cityi][cityj];
}
void ACO::setCITYPOSITION(int city, double x, double y) {
	CITIES[city][0] = x;
	CITIES[city][1] = y;
}
void ACO::printPHEROMONES() {
	cout << " feromoni: " << endl;
	cout << "  | ";
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		printf("%5d   ", i);
	}
	cout << endl << "- | ";
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		cout << "--------";
	}
	cout << endl;
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		cout << i << " | ";
		for (int j = 0; j < NUMBEROFCITIES; j++) {
			if (i == j) {
				printf("%5s   ", "x");
				continue;
			}
			if (exists(i, j)) {
				printf("%7.3f ", PHEROMONES[i][j]);
			}
			else {
				if (PHEROMONES[i][j] == 0.0) {
					printf("%5.0f   ", PHEROMONES[i][j]);
				}
				else {
					printf("%7.3f ", PHEROMONES[i][j]);
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

// Расстояние между вершинами
double ACO::distance(int cityi, int cityj) { 
	return (double)
		(abs(10 - cityi - cityj) + 0.5);
		/*sqrt(pow(CITIES[cityi][0] - CITIES[cityj][0], 2) +
			pow(CITIES[cityi][1] - CITIES[cityj][1], 2));*/
}
// Существует ли дорога между вершинами
bool ACO::exists(int cityi, int cityc) { 
	return (GRAPH[cityi][cityc] == 1);
}
//Посещена ли вершина данным муравьём
bool ACO::vizited(int antk, int c) { 
	for (int l = 0; l < NUMBEROFCITIES; l++) {
		if (ROUTES[antk][l] == -1) {
			break;
		}
		if (ROUTES[antk][l] == c) {
			return true;
		}
	}
	return false;
}
//Вероятность пойти по ребру
double ACO::PHI(int cityi, int cityj, int antk) { 
	double ETAij = (double)pow(1 / distance(cityi, cityj), BETA);
	double TAUij = (double)pow(PHEROMONES[cityi][cityj], ALPHA);

	double sum = 0.0;
	for (int c = 0; c < NUMBEROFCITIES; c++) {
		if (exists(cityi, c)) {
			if (!vizited(antk, c)) {
				double ETA = (double)pow(1 / distance(cityi, c), BETA);
				double TAU = (double)pow(PHEROMONES[cityi][c], ALPHA);
				sum += ETA * TAU;
			}
		}
	}
	return (ETAij * TAUij) / sum;
}
//Пройденный путь
double ACO::length(int antk) { 
	double sum = 0.0;
	for (int j = 0; j < NUMBEROFCITIES - 1; j++) {
		if(ROUTES[antk][j + 1]!=-1)
		sum += distance(ROUTES[antk][j], ROUTES[antk][j + 1]);
	}
	return sum;
}
//Выбор следующей вершины
int ACO::city() { 
	double xi = (double)(rand() % 21)/21;
	int i = 0; 
	double sum = PROBS[i][0];
	while (sum < xi && i < NUMBEROFCITIES - 1) {
		i++;
		sum += (PROBS[i][0] >= 0 ? PROBS[i][0] : 0);
	}
	return (int)PROBS[i][1];
}
//Нахождение пути
void ACO::route(int antk) { 
	ROUTES[antk][0] = INITIALCITY;
	for (int i = 0; i < NUMBEROFCITIES - 1; i++) 
	{
		int cityi = ROUTES[antk][i];
		int count = 0;
		for (int c = 0; c < NUMBEROFCITIES; c++) 
		{
			if (cityi == c) {
				continue;
			}
			if (exists(cityi, c)) {
				if (!vizited(antk, c)) {
					PROBS[count][0] = PHI(cityi, c, antk);
					PROBS[count][1] = (double)c;
					count++;
				}

			}
		}
		if (0 == count) {
			return;
		}
		ROUTES[antk][i + 1] = city();
		if (ROUTES[antk][i + 1] == DESTCITY)
			break;
	}
}
//Проверка на валидность пути
int ACO::valid(int antk, int iteration) { 
	for (int i = 0; i < NUMBEROFCITIES - 1; i++) {
		int cityi = ROUTES[antk][i];
		int cityj = ROUTES[antk][i + 1];
		if(cityi >=0 && cityj >= 0)
			if (!exists(cityi, cityj))
			{
				return -2;
			}
		if (cityi >= 0 && cityj < 0) 
		{
			if (cityi == DESTCITY)
				return 0;
			else
				return -1;
		}
		if (cityi < 0 && cityj < 0)
			return -3;
	}
	return 0;
}

void ACO::printGRAPH() {
	cout << " GRAPH: " << endl;
	cout << "  | ";
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		cout << i << " ";
	}
	cout << endl << "- | ";
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		cout << "- ";
	}
	cout << endl;
	int count = 0;
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		cout << i << " | ";
		for (int j = 0; j < NUMBEROFCITIES; j++) {
			if (i == j) {
				cout << "x ";
			}
			else {
				cout << GRAPH[i][j] << " ";
			}
			if (GRAPH[i][j] == 1) {
				count++;
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "Number of connections: " << count << endl << endl;
	cout << "Initial point № " << INITIALCITY << endl;
	cout << "Destination point № " << DESTCITY << endl;
}
void ACO::printRESULTS() {
	cout << " BEST ROUTE:" << endl;
	for (int i = 0; i < NUMBEROFCITIES; i++) 
	{
		if (BESTROUTE[i] != -1)
			cout << BESTROUTE[i] << " ";
	}
	cout << endl << "length: " << BESTLENGTH << endl;
}
//Обновить феромоны
void ACO::updatePHEROMONES() {
	for (int k = 0; k < NUMBEROFANTS; k++) {
		double rlength = length(k);
		for (int r = 0; r < NUMBEROFCITIES - 1; r++) {
			if (ROUTES[k][r] >= 0 && ROUTES[k][r + 1] >= 0)
			{
				int cityi = ROUTES[k][r];
				int cityj = ROUTES[k][r + 1];
				DELTAPHEROMONES[cityi][cityj] += Q / rlength;
				DELTAPHEROMONES[cityj][cityi] += Q / rlength;
			}
		}
	}
	for (int i = 0; i < NUMBEROFCITIES; i++) {
		for (int j = 0; j < NUMBEROFCITIES; j++) {
			PHEROMONES[i][j] = (1 - RO) * PHEROMONES[i][j] + DELTAPHEROMONES[i][j];
			DELTAPHEROMONES[i][j] = 0.0;
		}
	}
}


void ACO::optimize(int ITERATIONS) {
	for (int iterations = 1; iterations <= ITERATIONS; iterations++) {
		cout << flush;
		cout << "ITERATION " << iterations << " HAS STARTED!" << endl << endl;

		for (int k = 0; k < NUMBEROFANTS; k++) 
		{
			cout << " : ant " << k << " has been released!" << endl;
			while (0 != valid(k, iterations)) {
				cout << "  :: releasing ant " << k << " again!" << endl;
				for (int i = 0; i < NUMBEROFCITIES; i++) {
					ROUTES[k][i] = -1;
				}
				route(k);
			}

			for (int i = 0; i < NUMBEROFCITIES; i++) {
				if(ROUTES[k][i]!=-1)
				cout << ROUTES[k][i] << " ";
			}
			cout << endl;

			cout << "  :: route done" << endl;
			double rlength = length(k);

			if (rlength < BESTLENGTH) {
				BESTLENGTH = rlength;
				for (int i = 0; i < NUMBEROFCITIES; i++) {
					BESTROUTE[i] = ROUTES[k][i];
				}
			}
			cout << " : ant " << k << " has ended!" << endl;
		}

		cout << endl << "updating PHEROMONES . . .";
		updatePHEROMONES();
		cout << " done!" << endl << endl;
		printPHEROMONES();

		for (int i = 0; i < NUMBEROFANTS; i++) {
			for (int j = 0; j < NUMBEROFCITIES; j++) {
				ROUTES[i][j] = -1;
			}
		}

		cout << endl << "ITERATION " << iterations << " HAS ENDED!" << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	ACO* a = new ACO(10, 10, 0.5, 0.8, 3.5, 0.2, 3, 5, 7);
	a->init();
	a->setCITYPOSITION(0, 0, 4);
	a->setCITYPOSITION(1, -2, 3);
	a->setCITYPOSITION(2, 2, 3);
	a->setCITYPOSITION(3, -3, 1);
	a->setCITYPOSITION(4, 3, 1);
	a->setCITYPOSITION(5, -3, -1);
	a->setCITYPOSITION(6, 3, -1);
	a->setCITYPOSITION(7, -2, -3);
	a->setCITYPOSITION(8, 2, -3);
	a->setCITYPOSITION(9, 0, -4);
	a->connectCITIES(0, 1);
	a->connectCITIES(0, 2);
	a->connectCITIES(0, 7);
	a->connectCITIES(0, 8);
	a->connectCITIES(1, 6);
	a->connectCITIES(1, 9);
	a->connectCITIES(2, 5);
	a->connectCITIES(2, 9);
	a->connectCITIES(3, 4);
	a->connectCITIES(3, 5);
	a->connectCITIES(3, 8);
	a->connectCITIES(4, 6);
	a->connectCITIES(4, 7);
	a->connectCITIES(5, 6);
	a->connectCITIES(7, 9);
	a->connectCITIES(8, 9);
	a->printGRAPH();
	a->printPHEROMONES();
	a->optimize(3);
	a->printRESULTS();
	return 0;
}
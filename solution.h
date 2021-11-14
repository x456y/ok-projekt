#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>

#include "types.h"

using namespace std;

//Reprezentuje rozwiązanie problemu (niekonieczne optymalne)
class Solution
{
	//W tej tablicy w każdej komorce jest przechowywana lista zadan
	//przydzielonych do jednego procesora
	//w/z czasami rozpoczecia i zakonczenia
	vector<computing_period> *schedule;

	//Mapa indeksowana identyfikatorem zadania
	//Zawiera informacje o czasie rozpoczecia i zakonczenia zadania
	//Oraz liste przydzielonych procesorow
	map<int, job_assignment> job_assignments;

	//Tablica pomocnicza
	//Zawiera informacje o identyfikatorze procesora i czasie zakonczenia
	//wykonywania ostatniego zadania
	//Przydatne przy wyszukiwaniu procesora ktory jest zwolniony najwczesniej
	pair<int, int> *finish_times;
	int m;

public:
	Solution(int num_machines);

	~Solution();

	//wstawia zadanie naiwnie na dostepne procesory
	void insert_naively(Job &job);

	//wyswietla wynik w narzuconym formacie
	//patrz: https://www.cs.put.poznan.pl/mdrozdowski/dyd/ok/index.html
	void print_result();

	//oblicza funkcje celu
	int calculate_c_max();

	Solution *perturbate();
};

#endif
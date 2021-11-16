#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

#include "types.h"

//Funkcja pomocnicza do analizy skladni plikow .swf
vector<string> tokenize(string s, int max_token_count);

//analizuje plik wejsciowy i zwraca liste zadan do uszeregowania
//oraz liczbe dostepnych procesorow
Problem *parse_file(string filename, int max_jobs = 0);

//Porownoje zadania wg. czasu gotowosci, a nastepnie wg. rozmiaru
bool compare_jobs_1(const Job &j1, const Job &j2);

//Porownoje zadania wg. czasu rozmiaru, a nastepnie wg. czasu gotowosci
bool compare_jobs_2(const Job &j1, const Job &j2);

//Porownoje zadania wg. liczby wymaganych procesorow, a nastepnie wg. czasu gotowosci
bool compare_jobs_3(const Job &j1, const Job &j2);

//Porownuje pary wg. drugiego elementu
bool compare_pairs_by_second(pair<int, int> &p1, pair<int, int> &p2);

#endif
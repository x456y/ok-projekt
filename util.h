#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>

#include "types.h"

//Funkcja pomocnicza do analizy skladni plikow .swf
vector<string> tokenize(string s, int max_token_count);

//analizuje plik wejsciowy i zwraca liste zadan do uszeregowania
//oraz liczbe dostepnych procesorow
Problem *parse_file(string filename);

//Porownoje zadania wg. czasu gotowosci, a nastepnie wg. rozmiaru
bool compare_jobs_1(const Job &j1, const Job &j2);

//Porownuje pary wg. drugiego elementu
bool compare_pairs_by_second(pair<int, int> &p1, pair<int, int> &p2);

#endif
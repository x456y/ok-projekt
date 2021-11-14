#ifndef TYPES_H
#define TYPES_H

#include <vector>

using namespace std;

//reprezentuje pojedyncze zadanie
typedef struct
{
	int id;
	//dlugosc wykonywania zadania
	int p;
	//czas gotowosci zadania
	int r;
	//Liczba wymaganych procesorow
	int size;
} Job;

//Reprezentuje jeda instancje problemu
typedef struct
{
	vector<Job> jobs;
	//liczba procesorow
	int n;
	//liczba maszyn
	int m;
} Problem;

typedef struct
{
	vector<int> machines;
	int start_t;
	int end_t;
} job_assignment;

typedef struct
{
	int start_t;
	int end_t;
	int job;
} computing_period;

#endif
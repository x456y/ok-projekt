#include <time.h>
#include <random>
#include <math.h>
#include <limits>

#include "solution.h"
#include "util.h"

using namespace std;

//Sortuje zadania wg. czasu gotowości i wstawia je na dostępne procesory
Solution *generate_initial_solution(Problem *problem)
{
	int n = problem->n;
	int m = problem->m;
	Solution *solution = new Solution(m);

	sort(problem->jobs.begin(), problem->jobs.end(), compare_jobs_1);
	for (int i = 0; i < n; i++)
	{
		solution->insert_naively((problem->jobs.at(i)));
	}

	return solution;
}

//Realizuje metaheurystyke symulowanego wyzarzania (patrz: https://reader.elsevier.com/reader/sd/pii/S0736584502000133?token=942AA450ED4938BDD5762982DB5FCC7B3FA8488615254FA944F84298495B8191C05141EA63616BFB6E6AEB0F09B70AA6&originRegion=eu-west-1&originCreation=20211114144856)
Solution *simulated_annealing(Problem *problem, int initial_temp,
							  double cooling_coefficient, int time_limit = 300)
{
	Solution *solution = new Solution(problem->m);
	int start_time = time(NULL);
	int current_time = time(NULL);
	int temperature = initial_temp;
	do
	{
		Solution *candidate = solution->perturbate();
		int delta = candidate->calculate_c_max() - solution->calculate_c_max();
		if (delta > 0 || exp(-delta / temperature) > (double)rand() / (RAND_MAX))
		{
			delete solution;
			solution = candidate;
		}
		else
		{
			delete candidate;
		}
		temperature *= cooling_coefficient;
		current_time = time(NULL);
	} while (current_time - start_time < time_limit);

	return solution;
}

Solution *grasp(Problem *problem, int k, int time_limit = 300)
{
	int start_time = time(NULL);
	int current_time = time(NULL);
	int last_iteration_time = 0;
	unsigned long long best_c_max = numeric_limits<unsigned long long>::max();
	Solution *solution = NULL;

	random_device rd;
	default_random_engine rng(rd());
	do
	{
		int iteration_start_time = time(NULL);
		Solution *candidate = new Solution(problem->m);
		sort(problem->jobs.begin(), problem->jobs.end(), compare_jobs_1);
		for (int i = 0; i < problem->jobs.size(); i += k)
		{
			int j = min(i + k - 1, (int)problem->jobs.size() - 1);
			shuffle(problem->jobs.begin() + i, problem->jobs.begin() + j, rng);
			//cout << "i: " << i << " j: " << j << endl;
			for (int l = i; l <= j; l++)
			{
				candidate->insert_naively((problem->jobs.at(l)));
			}
		}
		unsigned long long current_c_max = candidate->calculate_c_max();
		if (current_c_max < best_c_max)
		{
			delete solution;
			solution = candidate;
			best_c_max = current_c_max;
		}
		else
		{
			delete candidate;
		}
		current_time = time(NULL);
		last_iteration_time = current_time - iteration_start_time;
	} while (current_time - start_time + last_iteration_time < time_limit);

	return solution;
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	//brak ograniczeina na liczbe wczytywanych zadan
	int max_jobs = 0;
	if (argc > 2)
	{
		max_jobs = stoi(argv[2]);
	}
	Problem *problem = parse_file(argv[1], max_jobs);

	Solution *solution = grasp(problem, 100, 300);
	cout << "C max: " << solution->calculate_c_max() << endl;
	//solution->print_result();

	delete problem;
	delete solution;
}

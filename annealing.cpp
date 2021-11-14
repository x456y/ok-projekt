#include <time.h>
#include <random>
#include <math.h>

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
							  double cooling_coefficient, int time_limit)
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
			solution = candidate;
		}
		temperature *= cooling_coefficient;
		current_time = time(NULL);
	} while (current_time - start_time < time_limit);

	return solution;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	Problem *problem = parse_file(argv[1]);

	simulated_annealing(problem, 1000, 0.6, 300);
}
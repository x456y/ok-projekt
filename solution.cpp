#include "solution.h"
#include "util.h"

using namespace std;

Solution::Solution(int num_machines)
{
	schedule = new vector<computing_period>[num_machines];
	finish_times = new pair<int, int>[num_machines];
	m = num_machines;
	for (int i = 0; i < m; i++)
	{
		finish_times[i].first = i;
		finish_times[i].second = 0;
	}
}

Solution::~Solution()
{
	delete[] schedule;
	delete[] finish_times;
}

void Solution::insert_naively(Job &job)
{
	sort(finish_times, finish_times + m, compare_pairs_by_second);
	int ready_time = finish_times[job.size - 1].second;
	int insert_time = ready_time < job.r ? job.r : ready_time;

	if (job_assignments.find(job.id) == job_assignments.end())
	{
		job_assignment empty_ja;
		job_assignments.insert(pair<int, job_assignment>(job.id, empty_ja));
		job_assignments.at(job.id).start_t = insert_time;
		job_assignments.at(job.id).end_t = insert_time + job.p;
	}

	for (int i = 0; i < job.size; i++)
	{
		int machine_number = finish_times[i].first;
		computing_period ma;
		ma.start_t = insert_time;
		ma.end_t = insert_time + job.p;
		ma.job = job.id;
		schedule[machine_number].push_back(ma);
		finish_times[machine_number].second = ma.end_t;

		job_assignments.at(job.id).machines.insert(machine_number);
	}
}

void Solution::print_result()
{
	for (pair<int, job_assignment> p : job_assignments)
	{
		cout << p.first << " " << p.second.start_t << " " << p.second.end_t;
		for (auto &m : p.second.machines)
		{
			cout << " " << m;
		}
		cout << endl;
	}
}

unsigned long long Solution::calculate_c_max()
{
	unsigned long long c_max = 0;
	for (auto entry : job_assignments)
	{
		c_max += entry.second.end_t;
	}

	return c_max;
}

Solution *Solution::perturbate()
{
	return this;
}
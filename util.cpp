#include <fstream>
#include <iostream>

#include "util.h"

using namespace std;

vector<string> tokenize(string s, int max_token_count)
{
	vector<string> tokens;
	int i = 0, j = 0;
	while (i < s.size() && tokens.size() < max_token_count)
	{
		while (s[i] == ' ')
		{
			i++;
		}
		j = s.find(" ", i);
		string token = s.substr(i, j - i);
		tokens.push_back(token);
		i = j;
	}
	return tokens;
}

Problem *parse_file(string filename, int max_jobs)
{
	ifstream input;
	Problem *problem = new Problem;
	problem->m = 0;
	problem->n = 0;
	input.open(filename);
	if (!input.good())
	{
		input.close();
		return problem;
	}

	string line;
	while (!input.eof())
	{
		getline(input, line);
		if (line.find("MaxProcs: ") != string::npos)
		{
			problem->m = stoi(line.substr(line.find(":")+2));
			problem->jobs.reserve(problem->m);
		}
		if (line == "" || line[0] == ';')
		{
			continue;
		}

		vector<string> tokens = tokenize(line, 5);
		Job a_job;
		a_job.id = stoi(tokens[0]);
		a_job.r = stoi(tokens[1]);
		a_job.p = stoi(tokens[3]);
		a_job.size = stoi(tokens[4]);
		if (a_job.r < 0 || a_job.p <= 0 || a_job.size <= 0)
		{
			continue;
		}
		problem->jobs.push_back(a_job);
		if (max_jobs >= 0 && problem->jobs.size() >= max_jobs)
		{
			break;
		}
	}

	problem->n = problem->jobs.size();
	input.close();
	return problem;
}

bool compare_jobs_1(const Job &j1, const Job &j2)
{
	if (j1.r < j2.r)
	{
		return true;
	}
	else if (j1.r > j2.r)
	{
		return false;
	}
	else
	{
		return j1.size * j1.p > j2.size * j2.p;
	}
}

bool compare_jobs_2(const Job &j1, const Job &j2)
{
	if (j1.size * j1.p > j2.size * j2.p)
	{
		return true;
	}
	else if (j1.size * j1.p < j2.size * j2.p)
	{
		return false;
	}
	else
	{
		return j1.r < j2.r;
	}
}

bool compare_jobs_3(const Job &j1, const Job &j2)
{
	if (j1.size > j2.size)
	{
		return true;
	}
	else if (j1.size < j2.size)
	{
		return false;
	}
	else
	{
		return j1.r < j2.r;
	}
}

bool compare_pairs_by_second(pair<int, int> &p1, pair<int, int> &p2)
{
	return p1.second < p2.second;
}
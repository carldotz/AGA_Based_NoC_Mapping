#include "ga.h"
#include <vector>
#include <algorithm>

GA::GA(ACG *a,NAG *n,size_t s,size_t mnig,double mi) :
	Algorithms(a,n),size(s),max_no_improved_generation(mnig),min_improved(mi) {
	while(individuals.size() < size)
	{
		individuals.push_back(Individual(nag->size()));
	}
}

void GA::selection()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<> u(0,individuals.size());
	std::vector<Individual> new_individuals;
	while(new_individuals.size() < individuals.size()) {
		int i = u(e);
		int j = u(e);
		new_individuals.push_back((individuals[i] > individuals[j]) ? individuals[i] :individuals[j]);
	}
	individuals = new_individuals;
}

void GA::crossover()
{
	for(unsigned int i=0;i<individuals.size();i+=2)
	{
		individuals[i].crossover(individuals[i+1]);
	}
}

void GA::mutation()
{
	for(unsigned int i=0;i<individuals.size();++i)
	{
		individuals[i].mutation();
	}
}

void GA::store_best()
{
	best = *(std::max_element(individuals.begin(),individuals.end()));
}

void GA::restore_best()
{
	*(std::min_element(individuals.begin(),individuals.end())) = best;
}

void GA::execute()
{
	while(no_improved_generation < max_no_improved_generation)
	{
		store_best();
		selection();
		crossover();
		mutation();
		restore_best();
	}
}

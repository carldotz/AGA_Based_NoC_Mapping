#include "ga.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using std::ofstream;

GA::GA(const ACG *a,const NAG *n,size_t s,size_t mnig,double mi) :
	Algorithms(a,n),size(s),max_no_improved_generation(mnig),min_improved(mi) {
	while(individuals.size() < size)
	{
		individuals.push_back(Individual(acg,nag));
	}
}

void GA::selection()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<> u(0,individuals.size()-1);
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

void GA::calc_fitness()
{
	for(auto &a:individuals)
	{
		a.calc_fitness();
	}
}

void GA::execute()
{
	std::cout << "+++++++++++++++++++++++Mapping++++++++++++++++++++++" << std::endl;

	calc_fitness();
	store_best();
	while(no_improved_generation < max_no_improved_generation)
	{
		selection();
		crossover();
		mutation();
		calc_fitness();
		restore_best();
		Individual best_temp =
				*(std::max_element(individuals.begin(),individuals.end()));
		if(best_temp.get_fitness() - best.get_fitness() < min_improved)
			++no_improved_generation;
		else {
			no_improved_generation = 0;
			store_best();
		}
		std::cout << "Generation=" << generation++;
		std::cout << "\tCost of Communication="
				  << best_temp.get_fitness() << std::endl;
	}
	std::cout << this->best.get_phenotype() << std::endl;
	ofstream out("data",ofstream::app);
	out << this->best.get_phenotype().get_com_cost() << std::endl;
}

#include "ga.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <memory>

using std::ofstream;
using std::make_shared;
using std::shared_ptr;

GA::GA(const ACG *a,const NAG *n,size_t s,size_t mnig,double mi):
		Algorithms(a,n),size(s),max_no_improved_generation(mnig),
		min_improved(mi) {
		add_individual();
}

GA::GA(const ACG *a,const NAG *n,size_t mnig,double mi):
	Algorithms(a,n),max_no_improved_generation(mnig),min_improved(mi){}

void GA::add_individual()
{
	while(individuals.size() < size)
	{
		individuals.push_back(make_shared<Individual>(acg,nag));
	}
}

void GA::selection()
{
	static std::default_random_engine e;
	std::uniform_int_distribution<> u(0,individuals.size()-1);
	std::vector<shared_ptr<Individual>> new_individuals;
//	//
//	Individual m0(**std::max_element(individuals.begin(),individuals.end(),
//					[](const shared_ptr<Individual> &a,
//						const shared_ptr<Individual> &b)
//						  {return *a < *b;}));
//	shared_ptr<Individual> max_i0 = make_shared<Individual>(m0);
//	new_individuals.push_back(max_i0);
//	//
	while(new_individuals.size() < individuals.size()) {
		int i = u(e);
		int j = u(e);
		shared_ptr<Individual> max_i =
				make_shared<Individual>(std::max(*individuals[i],*individuals[j]));
		new_individuals.push_back(max_i);
	}
	individuals = new_individuals;
}

void GA::crossover()
{
	for(unsigned int i=0;i<individuals.size();i+=2)
	{
		individuals[i]->crossover(*individuals[i+1]);
	}
}

void GA::mutation()
{
	for(unsigned int i=0;i<individuals.size();++i)
	{
		individuals[i]->mutation();
	}
}

void GA::store_best()
{
	best_individual = **(std::max_element(individuals.begin(),individuals.end(),
				[](const shared_ptr<Individual> &a,
					const shared_ptr<Individual> &b)
						{return *a < *b;}));
}

void GA::restore_best()
{
	**(std::min_element(individuals.begin(),individuals.end(),
		[] (const shared_ptr<Individual> &a,
			const shared_ptr<Individual> &b)
			{return *a < *b;})) = best_individual;
}

void GA::calc_fitness()
{
	for(auto a:individuals)
	{
		a->calc_fitness();
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
		Individual best_temp =
				**(std::max_element(individuals.begin(),individuals.end(),
								[](const shared_ptr<Individual> &a,
									const shared_ptr<Individual> &b)
										{return *a < *b;}));

		if(best_temp.get_fitness() < best_individual.get_fitness())
		{
			restore_best();
			++no_improved_generation;
		} else if(best_temp.get_fitness() - best_individual.get_fitness() < min_improved)
			++no_improved_generation;
		else {
			no_improved_generation = 0;
			store_best();
		}

		std::cout << "Generation=" << generation++;
		std::cout << "\tCost of Communication="
				  << best_individual.get_fitness() << std::endl;
	}
	std::cout << this->best_individual.get_phenotype() << std::endl;
	ofstream out("ga_data",ofstream::app);
	out << generation << "\t" << this->best_individual.get_phenotype().get_com_cost() << std::endl;
}

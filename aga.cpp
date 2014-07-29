#include "aga.h"
#include "aga_individual.h"
#include <memory>
#include <algorithm>
#include <fstream>

using std::shared_ptr;
using std::make_shared;
using std::ofstream;

void AGA::add_individual()
{
	while(individuals.size() < size)
	{
		individuals.push_back(make_shared<AGA_Individual>(acg,nag));
	}
}

void AGA::selection()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<> u(0,individuals.size()-1);
	std::vector<shared_ptr<Individual>> new_individuals;
	while(new_individuals.size() < individuals.size()) {
		int i = u(e);
		int j = u(e);
		AGA_Individual m(dynamic_cast<AGA_Individual &>(
					*std::max(individuals[i],individuals[j],
						[](const shared_ptr<Individual> &a,
							const shared_ptr<Individual> &b)
							  {return *a < *b;})));
		shared_ptr<AGA_Individual> max_i = make_shared<AGA_Individual>(m);
		new_individuals.push_back(max_i);
	}
	individuals = new_individuals;
}

double AGA::calc_max_fitness()
{
	return (**(std::max_element(individuals.begin(),individuals.end(),
				[](const shared_ptr<Individual> &a,
					const shared_ptr<Individual> &b)
						{return *a < *b;}))).get_fitness();
}

double AGA::calc_avg_fitness()
{
	double sum = 0;
	for(auto spi:individuals)
	{
		sum += spi->get_fitness();
	}
	return sum/individuals.size();
}

void AGA::update_individuals_paremeter()
{
	for(auto &spi:individuals)
	{
		std::dynamic_pointer_cast<AGA_Individual>(spi)->set_global_parameter(max_fitness,avg_fitness);
	}
}

void AGA::update_individuals_k_paremeter()
{
	for(auto &spi:individuals)
	{
		std::dynamic_pointer_cast<AGA_Individual>(spi)->set_k_parameter(k1,k3);
	}
}

void AGA::set_k(float _k1,float _k3)
{
	k1 = _k1;
	k3 = _k3;
}

void AGA::execute()
{
	std::cout << "+++++++++++++++++++++++Mapping++++++++++++++++++++++" << std::endl;

	calc_fitness();
	max_fitness = calc_max_fitness();
	avg_fitness = calc_avg_fitness();
	update_individuals_paremeter();
	while(no_improved_generation < max_no_improved_generation)
	{
		selection();
		crossover();
		mutation();
		calc_fitness();
		if(calc_max_fitness() - max_fitness < min_improved)
			++no_improved_generation;
		else {
			max_fitness = calc_max_fitness();
			no_improved_generation = 0;
		}
		avg_fitness = calc_avg_fitness();
		update_individuals_paremeter();
		std::cout << "Generation=" << generation++;
		std::cout << "\tCost of Communication="
				  << max_fitness << std::endl;
	}
	store_best();
	std::cout << this->best.get_phenotype() << std::endl;
	ofstream out("aga_data",ofstream::app);
	out << generation << "\t" <<best.get_phenotype().get_com_cost() << std::endl;
}

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
	std::uniform_int_distribution<> u(0,individuals.size()-1);
	std::vector<shared_ptr<Individual>> new_individuals;
//	//
//	AGA_Individual m0(dynamic_cast<AGA_Individual &>(
//				**std::max_element(individuals.begin(),individuals.end(),
//					[](const shared_ptr<Individual> &a,
//						const shared_ptr<Individual> &b)
//						  {return *a < *b;})));
//	shared_ptr<AGA_Individual> max_i0 = make_shared<AGA_Individual>(m0);
//	new_individuals.push_back(max_i0);
//	//
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

void AGA::store_best()
{
	best_aga_individual = dynamic_cast<AGA_Individual &>(
				**(std::max_element(individuals.begin(),individuals.end(),
				[](const shared_ptr<Individual> &a,
					const shared_ptr<Individual> &b)
						{return *a < *b;})));
}

void AGA::restore_best()
{
	*std::dynamic_pointer_cast<AGA_Individual>(*std::min_element(individuals.begin(),individuals.end(),
		[] (const shared_ptr<Individual> &a,
			const shared_ptr<Individual> &b)
			{return *a < *b;})) = best_aga_individual;
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
	calc_fitness();
	max_fitness = calc_max_fitness();
	avg_fitness = calc_avg_fitness();
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
	update_individuals_k_paremeter();
}

void AGA::execute()
{
	std::cout << "+++++++++++++++++++++++Mapping++++++++++++++++++++++" << std::endl;
	update_individuals_paremeter();
	store_best();
	while(no_improved_generation < max_no_improved_generation)
	{
		double max_fit = max_fitness;
		update_individuals_paremeter();
		selection();
		update_individuals_paremeter();

//		if(max_fit > max_fitness)
//		{
//			restore_best();
//			update_individuals_paremeter();
//		}

		crossover();
		update_individuals_paremeter();
		mutation();
		update_individuals_paremeter();

//		if(max_fit > max_fitness)
//			throw std::logic_error("logic");

		if(max_fit > max_fitness)
			restore_best();
			++no_improved_generation;
		if(calc_max_fitness() - max_fit < min_improved)
			++no_improved_generation;
		else {
			store_best();
			no_improved_generation = 0;
		}

//		if(calc_max_fitness() - max_fit < min_improved)
//			++no_improved_generation;
//		else {
//			store_best();
//			no_improved_generation = 0;
//		}
		update_individuals_paremeter();

		std::cout << "Generation=" << generation++;
		std::cout << "\tFitness="
				  << max_fitness << std::endl;
	}
	std::cout << "++++++++++++++++++++++++Best++++++++++++++++++++++++" << std::endl;
	std::cout << (1.0/max_fitness) << "\n"<< std::endl;
	ofstream out("aga_data",ofstream::app);
	out << generation << "\t" << (1.0/max_fitness) << std::endl;
}

#include "individual.h"
#include <algorithm>

Individual::genetic* Individual::code(Mapping_Result)
{
	//todo some thing
	return nullptr;
}

Mapping_Result Individual::decode(Individual::genetic*)
{
	//todo some thing
	return Mapping_Result();
}


void Individual::crossover(Individual &m)
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u(0,chromosome_size-1);
	static std::bernoulli_distribution b(p_crossover);
	if(b(e))
	{
		unsigned int l = u(e);
		genetic * temp = chromosome;
		std::copy(m.chromosome,m.chromosome+l,chromosome);
		std::copy(temp,temp+l,m.chromosome);
	}
}

void Individual::mutation()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u(0,chromosome_size-1);
	static std::bernoulli_distribution b(p_mutation);
	if(b(e))
	{
		unsigned int l = u(e);
		std::uniform_int_distribution<unsigned> uv(1,l+1);
		*(chromosome + l) = uv(e);
	}
}

void Individual::calc_fitness()
{
	phenotype = decode(chromosome);
	fitness = 1 / phenotype.get_com_cost();
	//todo some thing
}

Individual::Individual(const Individual &srouce):
	fitness(srouce.fitness),chromosome_size(srouce.chromosome_size),
	chromosome(new genetic[chromosome_size]),phenotype(srouce.phenotype)
{
	std::copy(srouce.chromosome,srouce.chromosome + chromosome_size,chromosome);
}

Individual & Individual::operator=(const Individual &srouce)
{
	fitness = srouce.fitness;
	chromosome_size = srouce.chromosome_size;
	delete chromosome;
	chromosome = new genetic[chromosome_size];
	phenotype = srouce.phenotype;
	std::copy(srouce.chromosome,srouce.chromosome + chromosome_size,chromosome);
	return *this;
}

bool Individual::operator<(const Individual &in) const
{
	return this->get_fitness() < in.get_fitness();
}

bool Individual::operator>(const Individual &in) const
{
	return this->get_fitness() > in.get_fitness();
}

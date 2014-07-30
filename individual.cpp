#include "individual.h"
#include <algorithm>

Individual::Individual(const ACG *a,const NAG *n):
	acg(a),nag(n),chromosome_size(nag->size()),
	real_genetic_size(acg->size())
{
	chromosome = new genetic[chromosome_size];
	static std::default_random_engine e;
	for(size_t i = 0;i<chromosome_size;++i)
	{
		std::uniform_int_distribution<unsigned> u(1,i+1);
		*(chromosome + i) = u(e);
	}
}

Individual::~Individual()
{
	delete []chromosome;
}

Mapping_Result Individual::decode(Individual::genetic*)
{
	genetic * temp = new genetic[chromosome_size];
	for(size_t i=0;i<chromosome_size;++i)
	{
		size_t location = *(chromosome + i) - 1;//min 0;
		for(size_t j=i;j>location;--j)
		{
			*(temp + j) = *(temp + j - 1);
		}
		*(temp + location) = i;
	}
	Mapping_Result result;
	for(size_t i=0;i<chromosome_size;++i)
	{
		if(*(temp+i)<real_genetic_size)
			result.result.insert({(*acg)[*(temp+i)],(*nag)[i]});
	}
	result.calc_com_cost();
	delete [] temp;
	return result;
}


void Individual::crossover(Individual &m)
{
	static std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u(0,chromosome_size-1);
	std::bernoulli_distribution b(p_crossover);
	std::bernoulli_distribution b_p(0.5);
	if(b(e))
	{
		genetic temp;
		for(size_t i=0;i<chromosome_size;++i)
		{
			if(b_p(e))
			{
				temp = *(m.chromosome + i);
				*(m.chromosome + i) = *(chromosome + i);
				*(chromosome + i) = temp;
			}
		};
	}
}

void Individual::mutation()
{
	static std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u(0,chromosome_size-1);
	std::bernoulli_distribution b(p_mutation);
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
}

Individual::Individual(const Individual &srouce):
	fitness(srouce.fitness),acg(srouce.acg),nag(srouce.nag),
	real_genetic_size(srouce.real_genetic_size),
	chromosome_size(srouce.chromosome_size),
	chromosome(new genetic[chromosome_size]),phenotype(srouce.phenotype)
{
	std::copy(srouce.chromosome,srouce.chromosome + chromosome_size,chromosome);
}

Individual & Individual::operator=(const Individual &srouce)
{
	fitness = srouce.fitness;
	acg = srouce.acg;
	nag = srouce.nag;
	real_genetic_size = srouce.real_genetic_size;
	chromosome_size = srouce.chromosome_size;
	delete []chromosome;
	chromosome = new genetic[chromosome_size];
	std::copy(srouce.chromosome,srouce.chromosome + chromosome_size,chromosome);
	phenotype = srouce.phenotype;
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

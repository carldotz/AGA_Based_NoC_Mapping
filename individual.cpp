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

//Individual::genetic* Individual::code(Mapping_Result)
//{
//	//to do something;
//	return nullptr;
//}

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
			result.result.insert({(*nag)[i],(*acg)[*(temp+i)]});
	}
	delete [] temp;
	return result;
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
}

Individual::Individual(const Individual &srouce):
	fitness(srouce.fitness),chromosome_size(srouce.chromosome_size),
	real_genetic_size(srouce.real_genetic_size),
	chromosome(new genetic[chromosome_size]),phenotype(srouce.phenotype)
{
	std::copy(srouce.chromosome,srouce.chromosome + chromosome_size,chromosome);
}

Individual & Individual::operator=(const Individual &srouce)
{
	fitness = srouce.fitness;
	chromosome_size = srouce.chromosome_size;
	real_genetic_size = srouce.real_genetic_size;
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

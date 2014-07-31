#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "mapping_result.h"
#include "acg.h"
#include "nag.h"
#include <random>

class Individual {
public:
	typedef std::size_t size_type;
	typedef unsigned int genetic;

	explicit Individual(const ACG *,const NAG *);
	Individual(const Individual &);
	Individual& operator=(const Individual &);
	virtual ~Individual();

	virtual Mapping_Result decode(genetic*);
	virtual void crossover(Individual &);
	virtual void mutation();
	virtual void calc_fitness();
	virtual Mapping_Result get_phenotype() const
	{
		return phenotype;
	}
	double get_fitness() const {
		return fitness;
	}

	bool operator<(const Individual &) const;
	bool operator>(const Individual &) const;

protected:
	double fitness;
	const ACG *acg;
	const NAG *nag;
	size_t real_genetic_size = 0;
	size_t chromosome_size = 0;
	genetic * chromosome;
	Mapping_Result phenotype;
	float p_crossover = 0.8;
	float p_mutation = 0.2;
	int seed = 1;
};

#endif // INDIVIDUAL_H

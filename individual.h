#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "mapping_result.h"
#include <random>

class Individual {
public:
	typedef std::size_t size_type;
	typedef unsigned int genetic;

	explicit Individual(size_t cs) : chromosome_size(cs) {}
	Individual(const Individual &);
	Individual& operator=(const Individual &);
	virtual ~Individual() {}

	virtual genetic* code(Mapping_Result);
	virtual Mapping_Result decode(genetic*);
	virtual void crossover(Individual &);
	virtual void mutation();
	virtual void calc_fitness();
	double get_fitness() const {
		return fitness;
	}

	bool operator<(const Individual &) const;
	bool operator>(const Individual &) const;

private:
	double fitness;
	genetic * chromosome;
	size_t chromosome_size;
	Mapping_Result phenotype;
	float p_crossover = 0.8;
	float p_mutation = 0.05;
};

#endif // INDIVIDUAL_H
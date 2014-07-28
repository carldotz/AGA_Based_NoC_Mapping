#ifndef GA_H
#define GA_H

#include "algorithms.h"
#include "individual.h"
#include <vector>
#include <random>

class GA : public Algorithms {
public:
	GA(ACG *a,NAG *n,size_t s,size_t mnig,double mi);
	virtual void execute() override;

protected:
	virtual void selection();
	virtual void crossover();
	virtual void mutation();
	virtual void store_best();
	virtual void restore_best();

	std::vector<Individual> individuals;
	Individual best = Individual(nag->size());
	unsigned int size = 200;
	unsigned int generation;
	unsigned int no_improved_generation;
	unsigned int max_no_improved_generation;
	double min_improved;
};

#endif // GA_H

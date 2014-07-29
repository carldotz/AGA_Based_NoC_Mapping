#ifndef GA_H
#define GA_H

#include "algorithms.h"
#include "individual.h"
#include <vector>
#include <random>

class GA : public Algorithms {
public:
	GA(const ACG *a,const NAG *n,size_t s,size_t mnig,double mi);
	virtual void execute() override;

protected:
	virtual void selection();
	virtual void crossover();
	virtual void mutation();
	virtual void store_best();
	virtual void restore_best();
	virtual void calc_fitness();

	std::vector<Individual> individuals;
	Individual best = Individual(acg,nag);
	unsigned int size = 200;
	unsigned int generation = 0;
	unsigned int no_improved_generation = 0;
	unsigned int max_no_improved_generation = 50;
	double min_improved = 1E-10;
};

#endif // GA_H

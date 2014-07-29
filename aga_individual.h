#ifndef AGA_INDIVIDUAL_H
#define AGA_INDIVIDUAL_H

#include "individual.h"

class AGA_Individual : public Individual
{
public:
	AGA_Individual(const ACG *a,const NAG *n) : Individual(a,n) {}
	virtual void calc_p_crossover(AGA_Individual &);
	virtual void calc_p_mutation();
	virtual ~AGA_Individual() {}
	virtual void crossover(AGA_Individual &);
	virtual void mutation();
protected:
	float k1_p_crossover = 0.8;
	float k2_p_crossover = 1.0;
	float k3_p_mutation = 0.4;
	float k4_p_mutation = 0.5;
};

#endif // AGA_INDIVIDUAL_H

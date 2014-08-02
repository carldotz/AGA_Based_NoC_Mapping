#ifndef AGA_INDIVIDUAL_H
#define AGA_INDIVIDUAL_H

#include "individual.h"

class AGA_Individual : public Individual
{
public:
	explicit AGA_Individual(const ACG *a,const NAG *n) : Individual(a,n) {}
	virtual void calc_p_crossover(AGA_Individual &);
	virtual void calc_p_mutation();

	virtual ~AGA_Individual() {}

	virtual void crossover(Individual &) override;
	virtual void mutation() override;

	virtual void set_global_parameter(double, double);

	virtual void set_k_parameter(float, float, float, float);

protected:
	float k1_p_crossover = 1.0;
	float k2_p_crossover = 1.0;
	float k3_p_mutation = 0.5;
	float k4_p_mutation = 0.5;
	double max_fitness = 0;
	double avg_fitness = 0;
};

#endif // AGA_INDIVIDUAL_H

#ifndef AGA_H
#define AGA_H

#include "ga.h"
#include "aga_individual.h"
class AGA : public GA
{
public:
	AGA(ACG *a,NAG *n,size_t s,size_t mnig,double mi) :
		GA(a,n,mnig,mi) {
		size = s;
		add_individual();
	}
	AGA(ACG *a,NAG *n,size_t mnig,double mi) :
		GA(a,n,mnig,mi) {}
	virtual double execute(double avg[]) override;
	void set_k(float,float,float,float);

protected:
	virtual void add_individual() override;
	virtual void selection() override;
	virtual double calc_max_fitness();
	virtual	double calc_avg_fitness();

	virtual void store_best() override;
	virtual void restore_best() override;

	virtual	void update_individuals_paremeter();
	virtual	void update_individuals_k_paremeter();

	double max_fitness = 0;
	double avg_fitness = 0;

	AGA_Individual best_aga_individual = AGA_Individual(acg,nag);

	float k1;
	float k2;
	float k3;
	float k4;
};

#endif // AGA_H

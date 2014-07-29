#ifndef AGA_H
#define AGA_H

#include "ga.h"
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
	virtual void execute() override;

	void set_k(float,float);

protected:
	virtual void add_individual() override;
	virtual void selection() override;
	virtual double calc_max_fitness();
	virtual	double calc_avg_fitness();

	virtual	void update_individuals_paremeter();
	virtual	void update_individuals_k_paremeter();

	double max_fitness = 0;
	double avg_fitness = 0;

	float k1;
	float k3;
};

#endif // AGA_H

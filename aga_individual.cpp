#include "aga_individual.h"
#include <cmath>
#include <memory>
#define _USE_MATH_DEFINES

void AGA_Individual::calc_p_crossover(AGA_Individual &ai)
{
//	double better_fitness = std::max(this->get_fitness(),ai.get_fitness());
//	if(better_fitness > avg_fitness)
//	{
//		p_crossover = k1_p_crossover *
//				std::sin(M_PI_2*(max_fitness - better_fitness)/(max_fitness - avg_fitness));
//	} else p_crossover = k2_p_crossover;
	double better_fitness = std::max(this->get_fitness(),ai.get_fitness());
	if(better_fitness > avg_fitness)
	{
		p_crossover = k1_p_crossover - (k1_p_crossover - k2_p_crossover)
				*(better_fitness - avg_fitness)/(max_fitness - avg_fitness);
	} else p_crossover = k1_p_crossover;
//	p_crossover += 0.4;
//	p_crossover = 0.8;
}

void AGA_Individual::calc_p_mutation()
{
//	if(fitness > avg_fitness)
//	{
//		p_mutation = k3_p_mutation *
//				std::sin(M_PI_2*(max_fitness - fitness)/(max_fitness - avg_fitness));
//	} else p_mutation = k4_p_mutation;
	if(fitness > avg_fitness)
	{
		p_mutation = k3_p_mutation - (k3_p_mutation - k4_p_mutation)
				*(fitness - avg_fitness)/(max_fitness - avg_fitness);
	} else p_mutation = k3_p_mutation;
//	p_mutation += 0.1;
//	p_mutation = 0.2;
}

void AGA_Individual::crossover(Individual &ai)
{
	calc_p_crossover(dynamic_cast<AGA_Individual &>(ai));
	Individual::crossover(ai);
}

void AGA_Individual::mutation()
{
	calc_p_mutation();
	Individual::mutation();
}

void AGA_Individual::set_global_parameter(double m, double a)
{
	max_fitness = m;
	avg_fitness = a;
}

void AGA_Individual::set_k_parameter(float k1, float k2, float k3, float k4)
{
	k1_p_crossover = k1;
	k2_p_crossover = k2;
	k3_p_mutation = k3;
	k4_p_mutation = k4;
}

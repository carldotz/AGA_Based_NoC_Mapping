#ifndef AGA_INDIVIDUAL_H
#define AGA_INDIVIDUAL_H

#include "individual.h"

class AGA_Individual : public Individual
{
public:
	AGA_Individual(const ACG *a,const NAG *n) : Individual(a,n) {}
};

#endif // AGA_INDIVIDUAL_H

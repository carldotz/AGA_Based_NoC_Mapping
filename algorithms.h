#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <iostream>
#include <map>
#include <memory>
#include "acg_node.h"
#include "nag_node.h"
#include "acg.h"
#include "nag.h"

class Algorithms {
public:
	Algorithms(const ACG *a,const NAG *n) : acg(a),nag(n){}
	virtual ~Algorithms() {}
	virtual double execute(double avg[]) = 0;
protected:
	const ACG *acg;
	const NAG *nag;
};

#endif // ALGORITHMS_H

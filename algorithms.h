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
	Algorithms(ACG *a,NAG *n) : acg(a),nag(n){}
	virtual ~Algorithms() {}
	virtual void execute() = 0;

	ACG *acg;
	NAG *nag;
};

#endif // ALGORITHMS_H

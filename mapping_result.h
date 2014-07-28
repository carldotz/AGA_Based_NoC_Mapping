#ifndef MAPPING_RESULT_H
#define MAPPING_RESULT_H

#include <map>
#include <memory>
#include "nag_node.h"
#include "acg_node.h"

class Mapping_Result
{
public:
	Mapping_Result() {}
	double get_com_cost() {
		return com_cost;
	}

	double calc_com_cost();

	double com_cost;
	std::map<std::shared_ptr<NAG_Node>,
		   std::shared_ptr<ACG_Node>> result;
};

std::ostream & operator<<(std::ostream&,const Mapping_Result &);

#endif // MAPPING_RESULT_H

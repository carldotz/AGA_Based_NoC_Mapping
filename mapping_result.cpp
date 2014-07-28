#include "mapping_result.h"
#include "acg_node.h"
#include "nag_node.h"

using std::endl;

void Mapping_Result::calc_com_cost()
{
	com_cost = 0;
	for(auto p:result) {
		auto p_acg_n = p.first;
		auto p_nag_n = p.second;
		for(auto an:p_acg_n->edge)
		{
//			size_t d = (*result[an.first])-(*p_nag_n);
//			com_cost = an.second * d;
			com_cost += an.second * ((*result[an.first])-(*p_nag_n));
		}
	}
}

std::ostream &
operator<<(std::ostream& os,const Mapping_Result & resu)
{
	os << "+++++++++++++++++++Mapping Solution+++++++++++++++++" << endl;
	for (auto p:resu.result) {
		os << "\t" << *p.first << "\t->\t" << *p.second << endl;
	}
	os << "++++++++++++++++++Communication Cost++++++++++++++++" << endl;
	os << resu.com_cost << endl;
	return os;
}

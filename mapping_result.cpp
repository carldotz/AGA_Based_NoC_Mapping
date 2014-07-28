#include "mapping_result.h"
#include "acg_node.h"
#include "nag_node.h"

using std::endl;

double Mapping_Result::calc_com_cost()
{
	for(auto p:result) {
		auto p_acg_n = p.first;
		auto p_nag_n = p.second;
		//to do some thing
	}
	return 0;
}

std::ostream &
operator<<(std::ostream& os,const Mapping_Result & resu)
{
	os << "+++++++++++++++++++Mapping Solution+++++++++++++++++" << endl;
	for (auto p:resu.result) {
		os << p.first << "/t<-/t" << p.second << endl;
	}
	os << "++++++++++++++++++Communication Cost++++++++++++++++" << endl;
	os << resu.com_cost << endl;
	return os;
}

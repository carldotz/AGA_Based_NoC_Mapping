#include "acg_node.h"
#include <iostream>

std::ostream & operator<<(std::ostream &os,const ACG_Node&an)
{
	os << "T" << an.get_no();
	return os;
}

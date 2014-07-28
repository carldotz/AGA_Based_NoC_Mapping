#include "nag_node.h"
#include <iostream>

std::ostream & operator<<(std::ostream &os,const NAG_Node&nn)
{
	auto p = nn.get_local();
	os << "(" << p.first << "," << p.second << ")";
	return os;
}

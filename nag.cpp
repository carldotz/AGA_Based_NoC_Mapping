#include "nag.h"
#include <memory>

using std::make_shared;
using std::shared_ptr;

void NAG::add_node(local x,local y)
{
	nodes.push_back(make_shared<NAG_Node>(y*lines_x + x,x,y));
}

NAG::NAG(const line lx, const line ly) :lines_x(lx),lines_y(ly)
{
	local x = 0,y = 0;
	while(y<ly)
	{
		x = 0;
		while(x<lx)
			add_node(x++,y);
		++y;
	}
}

shared_ptr<NAG_Node> NAG::operator[](std::size_t i) const
{
	return std::dynamic_pointer_cast<NAG_Node>(nodes[i]);
}

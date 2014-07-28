#include "nag.h"
#include <memory>

using std::make_shared;

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

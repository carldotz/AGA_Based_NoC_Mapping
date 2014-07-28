#ifndef NAG_NODE_H
#define NAG_NODE_H

#include "node.h"
#include <iostream>
#include <utility>

class NAG_Node : public Node {
public:
	typedef std::size_t local;
	NAG_Node(Node::no_type n,local _x,local _y) :
		Node(n),x(_x), y(_y) {}
	unsigned int operator-(const NAG_Node&s)
	{
		unsigned int dx = (x > s.x) ? (x - s.x) : (s.x - x);
		unsigned int dy = (y > s.y) ? (y - s.y) : (s.y - y);
		return dx + dy;
	}
	std::pair<local,local>
	get_local() const
	{
		return std::pair<local,local>(x,y);
	}

private:
	local x;
	local y;
};

std::ostream & operator<<(std::ostream &,const NAG_Node&);

#endif // NAG_NODE_H

#ifndef ACG_NODE_H
#define ACG_NODE_H

#include "node.h"
#include <map>
#include <memory>

class ACG_Node : public Node {
public:
	ACG_Node(no_type n) : Node(n){}
	void add_edge(std::shared_ptr<ACG_Node> target,float communication) {
		edge.insert({target,communication});
	}
	std::map<std::shared_ptr<ACG_Node>, float> edge;
};

std::ostream & operator<<(std::ostream &,const ACG_Node&);

#endif // ACG_NODE_H

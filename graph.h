#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include "node.h"

class Graph {
public:
	Graph() {}
	virtual ~Graph() {}
	size_t size() const {
		return nodes.size();
	}

protected:
	std::vector<std::shared_ptr<Node>> nodes;
};

#endif // GRAPH_H

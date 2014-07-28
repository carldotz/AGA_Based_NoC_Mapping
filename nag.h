#ifndef NAG_H
#define NAG_H

#include "graph.h"
#include "nag_node.h"

class NAG : public Graph {
public:
	typedef std::size_t line;
	typedef NAG_Node::local local;
	NAG() : Graph() {}
	NAG(const line, const line);
	std::shared_ptr<NAG_Node> operator[](std::size_t) const;
protected:
	void add_node(local,local);
private:
	line lines_x;
	line lines_y;
};

#endif // NAG_H

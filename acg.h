#ifndef ACG_H
#define ACG_H

#include <vector>
#include "graph.h"
#include "node.h"
#include "acg_node.h"
#include "tgff_manager.h"

class TGFF_Manager;
class ACG : public Graph {
public:
	ACG() : Graph(){}
	void add_from_tgff(TGFF_Manager &);
	void add_node(ACG_Node::no_type n);
	std::shared_ptr<ACG_Node> operator[](std::size_t);

private:
};

#endif // ACG_H

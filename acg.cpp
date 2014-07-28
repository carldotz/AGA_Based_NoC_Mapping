#include "acg.h"
#include <memory>

using std::make_shared;
using std::shared_ptr;

void ACG::add_from_tgff(TGFF_Manager &tm)
{
	tm.write_option();
	tm.run_tgff();
	tm.read_result();
	tm.clear_trash();
}

void ACG::add_node(ACG_Node::no_type n)
{
	nodes.push_back(make_shared<ACG_Node>(n));
}

shared_ptr<ACG_Node> ACG::operator[](std::size_t i) const
{
	return std::dynamic_pointer_cast<ACG_Node>(nodes[i]);
}

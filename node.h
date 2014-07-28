#ifndef NODE_H
#define NODE_H

class Node {
public:
	typedef unsigned int no_type;

	explicit Node(no_type n) : no(n) {}
	no_type get_no() const
	{
		return no;
	}

	virtual ~Node() {}
protected:
	no_type no;
};

#endif // NODE_H

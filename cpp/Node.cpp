#include "Node.h"
std::ostream&
operator<< (std::ostream& os, const Node& n)
{
    os << '(' << n._item.first << ", " << n._item.second << ')';
    return os;
}
Node::Node(pair <T,T1> item):_left(NULL), _right(NULL), _parent(NULL), _item(item){};

Node::Node(pair <T,T1> item,Node<T,T1>* l,Node<T,T1>* r,Node<T,T1>* p):_left(l), _right(r), _parent(p), _item(item){};

T1 Node::getValue(){
	return _item.second;
};

T Node::getKey(){
        return _item.first;
};

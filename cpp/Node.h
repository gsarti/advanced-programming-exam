#include <iostream>
#include <utility>
using namespace std;

template <class T,class T1>
class Node{
public:
	pair <T,T1> _item;
	Node* _right;
	Node* _left;
	Node* _parent;
	Node(pair <T,T1> item);
	Node(pair <T,T1> item,Node<T,T1>* l,Node<T,T1>* r,Node<T,T1>* p);
	T getValue();	
	T1 getKey();
};

std::ostream& operator<< (std::ostream&, const Node&);

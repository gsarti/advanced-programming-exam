/**
 * @file BinarySearchTreeSubclasses.hxx
 * @author Gabriele Sarti
 * @date 12 January 2019
 * @brief Header containing Node, Iterator and ConstIterator nested classes.
 */

#include "BinarySearchTree.h"

/**
 * @brief A node of the binary search tree with two children nodes and one parent node.
 */
template <class TKey,class TValue,class TCompare>
struct BinarySearchTree<TKey, TValue, TCompare>::Node
{
	/** Node's data in key-value format. */
	std::pair<TKey, TValue> data;
	/** Node's left child node (smaller key). */
	std::unique_ptr<Node> left;
	/** Node's right child node (bigger key). */
	std::unique_ptr<Node> right;
	/** Node's parent node. */
	Node * parent;
	/**
	 * @brief Default constructor of node
	 * This constructor is used only to create the pseudoRoot node in the DSW algorithm.
	 */
	Node() {}
	/**
	 * @brief Construct a new Node object without parent.
	 * @param d The data to be inserted into the node.
	 */
	Node(std::pair<TKey, TValue> d): data{d}, left{nullptr}, right{nullptr}, parent{nullptr} {}
	/**
	 * @brief Construct a new Node object with a parent.
	 * @param d The data to be inserted into the node.
	 * @param p The parent of the node to be constructed.
	 */
	Node(std::pair<TKey, TValue> d, Node* p) : data{d}, left{nullptr}, right{nullptr}, parent{p} {}
	/**
	 * @brief Copy constructor for Node class.
	 * @param n The node to be copied.
	 */
	Node(const Node& n) : data{n.data}, left{nullptr}, right{nullptr}, parent{n.parent} {}
};

/**
 * @brief An iterator for the binary search tree class.
 */
template <class TKey,class TValue,class TCompare>
class BinarySearchTree<TKey, TValue, TCompare>::Iterator
{
	/** Used to give access to getNode method */
	friend class BinarySearchTree;
	/** Alias to make names shorter and intuitive*/
	using Node = BinarySearchTree<TKey, TValue, TCompare>::Node;
private:
	/** The node to which the iterator is currently referring. */
	Node * currentNode;
	/**
	 * @brief Returns a pointer to the node pointed to by the iterator.
	 */
	Node * getNode() { return currentNode; }
public:
	/**
	 * @brief Construct an iterator on current node.
	 * @param n The node on which the iterator is constructed.
	 */
	Iterator(Node * n) : currentNode{n} {}
	/**
	 * @brief Operator it() for deferencing a binary search tree iterator.
	 * @return std::pair<TKey, TValue>& Reference to current node's data in key, value format.
	 */
	std::pair<TKey, TValue>& operator*() const { return currentNode->data; }
	/**
	 * @brief Operator ++it to advance iterator to the next node.
	 * @return Iterator& Reference to an iterator pointing on the next node.
	 */
	Iterator& operator++()
	{
		if (!currentNode)
		{
			return *this;
		}
		else if(currentNode->right)
		{
			currentNode = currentNode->right.get();
			while(currentNode->left)
			{
				currentNode = currentNode->left.get();
			}
		}
		else
		{
			Node * tempNode{currentNode->parent};
			while(tempNode && currentNode == tempNode->right.get())
			{
				currentNode = tempNode;
				tempNode = tempNode->parent;
			}
			currentNode = tempNode;
		}
		return *this;
	}
	/**
	 * @brief Operator it++ to advance iterator to the next node.
	 * @return Iterator Value of the current iterator before advancing it to the next node.
	 */
	Iterator operator++(int)
	{
		Iterator it{*this};
		++(*this);
		return it;
	}
	/**
	 * @brief Operator == to check for iterators equality.
	 * @param other The iterator to be compared with this one.
	 * @return True if iterators point to the same node, else false
	 */
	bool operator==(const Iterator& other) { return currentNode == other.currentNode; }
	/**
	 * @brief Operator != to check for iterators inequality.
	 * @param other The iterator to be compared with this one.
	 * @return False if iterators point to the same node, else true.
	 */
	bool operator!=(const Iterator& other) { return currentNode != other.currentNode; }
};

/**
 * @brief A constant iterator for the binary search tree class.
 * 
 * The only difference with a normal iterator from which it inherits is the 
 * constant pair returned by the deferencing operator.
 */
template <class TKey,class TValue,class TCompare>
class BinarySearchTree<TKey,TValue, TCompare>::ConstIterator : 
public BinarySearchTree<TKey,TValue, TCompare>::Iterator
{
	/** Used to give access to getNode method */
	friend class BinarySearchTree;
	/** Alias to make names shorter and intuitive*/
	using Iterator = BinarySearchTree<TKey, TValue, TCompare>::Iterator;
private:
	/**
	 * @brief Returns a constant pointer to the node pointed to by the iterator.
	 */
	const Node * getNode() const { return Iterator::getNode(); }
public:
	/** Uses the same method of the base class. */
	using Iterator::Iterator;
	/**
	 * @brief Operator it() for deferencing a binary search tree iterator.
	 * @return const std::pair<TKey, TValue>& Constant reference to current 
	 * node's data in key, value format.
	 */
	const std::pair<TKey, TValue>& operator*() const { return Iterator::operator*(); }
};

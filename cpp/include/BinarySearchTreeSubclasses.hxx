/**
 * @file BinarySearchTreeSubclasses.h
 * @author Gabriele Sarti
 * @date 12 January 2019
 * @brief Header containing Node, Iterator and ConstIterator nested classes.
 */

#include "BinarySearchTree.h"


template <class TKey,class TValue>
struct BinarySearchTree<TKey, TValue>::Node
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


template <class TKey,class TValue>
class BinarySearchTree<TKey, TValue>::Iterator
{
	/** Alias to make names shorter and intuitive*/
	using Node = BinarySearchTree<TKey, TValue>::Node;
private:
	/** The node to which the iterator is currently referring. */
	Node * currentNode;
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


template <class TKey,class TValue>
class BinarySearchTree<TKey,TValue>::ConstIterator : 
public BinarySearchTree<TKey,TValue>::Iterator
{
	/** Alias to make names shorter and intuitive*/
	using Iterator = BinarySearchTree<TKey, TValue>::Iterator;
public:
	/** Uses the same methods of the base class. */
	using Iterator::Iterator;
	/**
	 * @brief Operator it() for deferencing a binary search tree iterator.
	 * @return const std::pair<TKey, TValue>& Constant reference to current 
	 * node's data in key, value format.
	 */
	const std::pair<TKey, TValue>& operator*() const { return Iterator::operator*(); }
};

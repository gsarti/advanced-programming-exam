/**
 * @file BinarySearchTree.h
 * @author Gabriele Sarti
 * @date 9 January 2019
 * @brief Header containing variables and method names for the BinarySearchTree class.
 */

#include <iostream> // << operator
#include <memory> // unique pointers
#include <vector> // vector class

#ifndef BINARYSEARCHTREE_H__
#define BINARYSEARCHTREE_H__

/**
 * @brief Templated implementation of a binary search tree.
 * @tparam TKey Type of node keys, used for ordering.
 * @tparam TValue Type of node values.
 */
template <class TKey,class TValue>
class BinarySearchTree
{
private:
	/**
	 * @brief A node of the binary search tree with two children nodes and one parent node.
	 */
	struct Node;

public:
	/**
	 * @brief An iterator for the binary search tree class.
	 */
	class Iterator;
	/**
	 * @brief A constant iterator for the binary search tree class.
	 * 
	 * The only difference with a normal iterator from which it inherits is the 
	 * constant pair returned by the deferencing operator.
	 */
	class ConstIterator;

private:
	/** Root node of the binary search tree. */
	std::unique_ptr<Node> root;
	/**
	 * @brief Finds the nearest element to the element with a key inside the tree.
	 * @param key The key of the element to be found.
	 * @return Iterator An iterator to the closest found element.
	 * 
	 * If the tree is empty, it returns an iterator to nullptr -> end().
	 * If the element is present, it returns an iterator to the element.
	 * If the element is not present, it returns an iterator to the element
	 * which would be the parent of the element if it was present.
	 */
	Iterator findNearest(TKey key);
	/**
	 * @brief Recursive private method used to create a deep copy of a binary search tree.
	 * @param node The root node of the tree that should be copied.
	 */
	void copy(const std::unique_ptr<Node>& node);
	/**
	 * @brief Recursively rebuilds a balanced tree from an ordered list of pairs.
	 * @param nodes An orderer list of pairs in key,value format.
	 * @param firstId The id of the first element of the list, for recursion purposes.
	 * @param lastId The id of the last element of the list, for recursion purposes.
	 */
	void rebuildBalancedTree(std::vector<std::pair<TKey, TValue>>& nodes, int firstId, int lastId);
	/**
	 * @brief Utility function of printTree, prints the value of a node.
	 * @param node The node to be printed.
	 * @param os THe stream to which the value should be printed.
	 */
	void printNode(const std::unique_ptr<Node>& node, std::ostream& os) const;
	/**
	 * @brief Utility function of printTree, recursively prints the tree structure.
	 * @param node The value of the node to be printed next.
	 * @param os The stream to which the values should be printed.
	 * @param right If the branch is a right or a left one, for formatting purposes.
	 * @param indent Specifies the indent of the current branch.
	 */
	void printTreeStructure(const std::unique_ptr<Node>& node, std::ostream& os, bool right, std::string indent) const;

public:
	/**
	 * @brief Default constructor for binary search tree.
	 */
	BinarySearchTree() {}
	/**
	 * @brief Constructor for binary search tree with root node.
	 * @param d The key,value pair for root node.
	 */
	BinarySearchTree(std::pair<TKey, TValue> d): root{new Node{d}} {}
	/**
	 * @brief Copy constructor for binary search tree.
	 * @param bst The binary search tree to be copied into a new one.
	 * 
	 * The method performs a deep copy of the tree using the copy private method.
	 */
	BinarySearchTree(const BinarySearchTree& bst) { copy(bst.root); }
	/**
	 * @brief Move constructor for binary search tree.
	 * @param bst The binary search tree to be moved into a new one.
	 */
	BinarySearchTree(BinarySearchTree&& bst) : root{std::move(bst.root)} {}
	/**
	 * @brief Insert a new node in the binary search tree.
	 * @param d The key,value pair to be inserted.
	 * @return True if the insert operation is successful, else false.
	 *  
	 * If a node with the same key is already present inside the tree, the insert operation
	 * will simply return false without performing any action. This design choice has been
	 * taken in order to keep the implementation as simple as possible.
	 */
	bool insert(std::pair<TKey, TValue> d);
	/**
	 * @brief Clears all the elements of the tree
	 */
	void clear() { root.reset(); }
	/**
	 * @brief Prints nodes in ascending key order.
	 * @param os The stream to which nodes are sent.
	 */
	std::ostream& printOrderedList(std::ostream& os) const;
	/**
	 * @brief Prints the tree structure.
	 * @param os The stream to which the nodes are sent.
	 */
	std::ostream& printTree(std::ostream& os) const;
	/**
	 * @brief Used to find a node inside the tree.
	 * @param key The key of the node to be found.
	 * @return Iterator An iterator to the node if it's found, else to end().
	 */
	Iterator find(TKey key);
	/**
	 * @brief Balances the tree to preserve its performances.
	 * 
	 * The method is inspired from the Day algorithm, taking full
	 * advantage of the iterators and the methods we already created
	 * to make it as simple as possible.
	 */
	void balance();
	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return Iterator An iterator to the leftmost node of the tree. 
	 * aka the one with the lowest key value.
	 */
	Iterator begin();
	/**
	 * @brief Used to finish an iteration on the binary search tree.
	 * @return Iterator Returns an iterator to nullptr.
	 */
	Iterator end() { return Iterator{nullptr}; }
	/**
	 * @brief Used to begin an iteration on the binary search tree.
	 * @return ConstIterator A constant iterator to the leftmost node of the tree.
	 * aka the one with the lowest key value.
	 */
	ConstIterator cbegin() const;
	/**
	 * @brief Used to finish an iteration on the binary search tree.
	 * @return ConstIterator Returns a constant iterator to nullptr.
	 */
	ConstIterator cend() const { return ConstIterator{nullptr}; }
	/**
	 * @brief Copy assignment for binary search tree.
	 * @param bst The binary search tree to be copied into an existing one.
	 * @return BinarySearchTree& The modified existing tree.
	 */
	BinarySearchTree& operator=(const BinarySearchTree& bst);
	/**
	 * @brief Move assignment for binary search tree.
	 * @param bst The binary search tree to be moved into an existing one.
	 * @return BinarySearchTree& The modified existing tree.
	 */
	BinarySearchTree& operator=(BinarySearchTree&& bst);
	/**
	 * @brief Operator << to print the binary search tree in ascending key order.
	 * @param os The output stream to which the strings to be printed are appended.
	 * @param bst The binary search tree instance to be printed.
	 * @return std::ostream& The output stream to which strings have been appended.
	 */
	friend std::ostream& operator<<(std::ostream& os, BinarySearchTree const& bst)
	{
		#ifdef PTREE
		return bst.printTree(os);
		#else
		return bst.printOrderedList(os);
		#endif 
	}
};

#include "BinarySearchTreeSubclasses.hxx"
#include "BinarySearchTreeMethods.hxx"

#endif //BINARYSEARCHTREE_H__

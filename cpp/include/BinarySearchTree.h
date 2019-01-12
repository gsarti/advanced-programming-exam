/**
 * @file BinarySearchTree.h
 * @author Gabriele Sarti
 * @date 9 January 2019
 * @brief Header containing variables and method names for the BinarySearchTree class.
 */

#include <iostream>
#include <memory>

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
	/** Root node of the binary search tree. */
	std::unique_ptr<Node> root;
	/**
	 * @brief Recursive private insert method for the binary search tree.
	 * @param node A unique pointer to the node currently being validated for insertion.
	 * @param d The key,value pair to be inserted inside the binary search tree.
	 * @return True if the insert operation is successful, else false.
	 * 
	 * If a node with the same key is already present inside the tree, the insert operation
	 * will simply return false without performing any action. This design choice has been
	 * taken in order to keep the implementation as simple as possible.
	 */
	bool insert(std::unique_ptr<Node>& node, std::pair<TKey, TValue> d);
	/**
	 * @brief Recursive private method used to create a deep copy of a binary search tree.
	 * @param node The root node of the tree that should be copied.
	 */
	void copy(const std::unique_ptr<Node>& node);

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
	BinarySearchTree(BinarySearchTree&& bst) : root{ std::move(bst.root); }
	/**
	 * @brief Insert a new node in the binary search tree.
	 * @param d The key,value pair to be inserted.
	 * @return True if the insert operation is successful, else false.
	 */
	bool insert(std::pair<TKey, TValue> d) { return insert(root, d); }
	/**
	 * @brief Clears all the elements of the tree
	 */
	void clear() { root.reset(); }
	/**
	 * @brief Function used to stream nodes' contents in ascending key order.
	 * @param os The stream to which nodes are sent.
	 * 
	 * This function allows for iterators encapsulation, since we are accessing
	 * them through a binary search tree member function instead of making them 
	 * public for friend operator << below.
	 */
	std::ostream& stream(std::ostream& os) const;
	/**
	 * @brief Used to find a node inside the tree.
	 * @param key The key of the node to be found.
	 * @return Iterator An iterator to the node if it's found, to nullptr instead.
	 */
	Iterator find(TKey key);
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
	friend std::ostream& operator<<(std::ostream& os, BinarySearchTree const& bst) { return bst.stream(os); }
};

#include "BinarySearchTreeSubclasses.hxx"
#include "BinarySearchTreeMethods.hxx"

#endif //BINARYSEARCHTREE_H__

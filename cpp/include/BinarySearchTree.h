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
	struct Node
	{
		/** Node's data in key-value format. */
		std::pair<TKey, TValue> data;
		/** Node's parent node. */
		Node * parent;
		/** Node's left child node (smaller key). */
		std::unique_ptr<Node> left;
		/** Node's right child node (bigger key). */
		std::unique_ptr<Node> right;

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
	};

	/** Root node of the binary search tree. */
	std::unique_ptr<Node> root;

public:

};

#endif //BINARYSEARCHTREE_H__

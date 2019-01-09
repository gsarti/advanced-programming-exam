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

	/**
	 * @brief An iterator for the binary search tree class
	 */
	struct Iterator
	{
		/** The node to which the iterator is currently referring. */
		Node * current;
		/**
		 * @brief Construct an iterator on current node.
		 * @param n The node on which the iterator is constructed.
		 */
		Iterator(Node * n) : current{n} {}
		/**
		 * @brief Operator it() for deferencing a binary search tree iterator.
		 * @return std::pair<TKey, TValue>& Reference to current node's data in key, value format.
		 */
		std::pair<TKey, TValue>& operator*() const { return current->data; }
		/**
		 * @brief Operator ++it to advance iterator to the next node.
		 * @return Iterator& Reference to an iterator pointing on the next node.
		 */
		Iterator& operator++() 
		{
			// TODO
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
		bool operator==(const Iterator& other) { return current == other.current; }
		/**
		 * @brief Operator != to check for iterators inequality.
		 * @param other The iterator to be compared with this one.
		 * @return False if iterators point to the same node, else true.
		 */
		bool operator!=(const Iterator& other) { return current != other.current; }
	};

	/**
	 * @brief A constant iterator for the binary search tree class
	 */
	struct ConstIterator : public Iterator
	{
		using Iterator::Iterator
		const std::pair<TKey, TValue>& operator*() const { return Iterator::operator*(); }
		using Iterator::operator==;
		using Iterator::operator!=;
	}

public:

};

#endif //BINARYSEARCHTREE_H__

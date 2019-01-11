/**
 * @file BinarySearchTree.h
 * @author Gabriele Sarti
 * @date 9 January 2019
 * @brief Header containing variables and method names for the BinarySearchTree class.
 */

#include <iostream>
#include <memory>
#include <stack>

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
		/** Node's left child node (smaller key). */
		std::unique_ptr<Node> left;
		/** Node's right child node (bigger key). */
		std::unique_ptr<Node> right;
		/** Node's parent node. */
		Node * parent;

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

	/** Root node of the binary search tree. */
	std::unique_ptr<Node> root;
	/**
	 * @brief Recursive private insert method for the binary search tree.
	 * @param node The node which is currently being validated for insertion.
	 * @param d The key,value pair to be inserted inside the binary search tree.
	 * @return True if the insert operation is successful, else false.
	 */
	bool insert(std::unique_ptr<Node>& node, std::pair<TKey, TValue> d)
	{
		if (!node)
		{
			node.reset(new Node{d});
			return true;
		}
		if(d.first == node->data.first)
		{
			return false;
		}
		else if(d.first > node->data.first)
		{
			if (node->right)
			{
				insert(node->right, d);
			}
			else
			{
				node->right.reset(new Node{d, node.get()});
				return true;
			}
		}
		else if (d.first < node->data.first)
		{
			if (node->left)
			{
				insert(node->left, d);
			}
			else
			{
				node->left.reset(new Node{d, node.get()});
				return true;
			}
		}
		return false;
	}

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
	 * @brief Insert a new node in the binary search tree.
	 * @param d The key,value pair to be inserted.
	 * @return True if the insert operation is successful, else false.
	 */
	bool insert(std::pair<TKey, TValue> d)
	{
		return insert(root, d);
	}

	void print()
	{
		ConstIterator it{cbegin()};
		ConstIterator end{cend()};
		
		if(it == end)
		{
			std::cout << "Tree is empty" << std::endl;
		}
		
		for(; it != end; ++it)
		{
			std::cout << "(" << (*it).first << "," << (*it).second << ")" << std::endl;
		}
	}
	/**
	 * @brief An iterator for the binary search tree class
	 */
	class Iterator
	{
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
		Iterator& operator++() // TODO AGAIN
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
				Node * tempNode = currentNode->parent;
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
	 * @brief A constant iterator for the binary search tree class
	 */
	struct ConstIterator : public Iterator
	{
		using Iterator::Iterator;
		const std::pair<TKey, TValue>& operator*() const { return Iterator::operator*(); }
		using Iterator::operator==;
		using Iterator::operator!=;
	};

	Iterator begin()
	{
		if(!root)
		{
			return Iterator{nullptr};
		}
		Node * node = root.get();
		while(node->left)
		{
			node = node->left.get();
		}
		return Iterator{node};
	}	

	Iterator end() { return Iterator{nullptr}; }

	ConstIterator cbegin() const
	{
		if(!root)
		{
			return ConstIterator{nullptr};
		}
		Node * node = root.get();
		while(node->left)
		{
			node = node->left.get();
		}
		return ConstIterator{node};
	}	

	ConstIterator cend() { return ConstIterator{nullptr}; }
};

#endif //BINARYSEARCHTREE_H__

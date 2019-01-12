/**
 * @file BinarySearchTreeMethods.h
 * @author Gabriele Sarti
 * @date 12 January 2019
 * @brief Header containing method definitions for the BinarySearchTree class.
 */

#include "BinarySearchTree.h"

// Private Methods

template <class TKey,class TValue>
bool BinarySearchTree<TKey, TValue>::insert(std::unique_ptr<Node>& node, 
                                            std::pair<TKey, TValue> d)
{
    if (!node)
    {
        node.reset(new Node{d});
        return true;
    }
    else if(d.first > node->data.first)
    {
        if (!node->right)
        {
            node->right.reset(new Node{d, node.get()});
            return true;
        }
        insert(node->right, d);
    }
    else if (d.first < node->data.first)
    {
        if (!node->left)
        {
            node->left.reset(new Node{d, node.get()});
            return true;
        }
        insert(node->left, d);
    }
    return false;
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::copy(const std::unique_ptr<Node>& node)
{
    if(node)
    {
        insert(node->data);
        copy(node->left);
        copy(node->right);
    }
}

// Public methods

template <class TKey,class TValue>
std::ostream& BinarySearchTree<TKey, TValue>::stream(std::ostream& os) const
{
    ConstIterator it{cbegin()};
    ConstIterator end{cend()};
    if(it == end)
    {
        os << "Empty" << std::endl;
    }
    for(; it != end; ++it)
    {
        os << (*it).first << ": " << (*it).second << std::endl;
    }
    return os;
}

template <class TKey,class TValue>
typename BinarySearchTree<TKey, TValue>::Iterator BinarySearchTree<TKey, TValue>::begin()
{
    if(!root)
    {
        return Iterator{nullptr};
    }
    Node * node{root.get()};
    while(node->left)
    {
        node = node->left.get();
    }
    return Iterator{node};
}

template <class TKey,class TValue>
typename BinarySearchTree<TKey, TValue>::Iterator BinarySearchTree<TKey, TValue>::find(TKey key)
{
    Node * node{root.get()};
    while(node)
    {
        if(key > node->pair.first)
        {
            if(!node->right)
            {
                return Iterator{nullptr};
            }
            node = node->right.get();
        }
        else if (key < node->pair.first)
        {
            if(!node->left)
            {
                return Iterator{nullptr};
            }
            node = node->left.get();
        }
        else
        {
            return Iterator{node};
        }
    }
    return Iterator{nullptr};
}

template <class TKey,class TValue>
typename BinarySearchTree<TKey, TValue>::ConstIterator BinarySearchTree<TKey, TValue>::cbegin() const
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

template <class TKey,class TValue>
BinarySearchTree& BinarySearchTree<TKey, TValue>::operator=(const BinarySearchTree& bst)
{
    clear();
    copy(bst.root);
    return *this;
}

template <class TKey,class TValue>
BinarySearchTree& BinarySearchTree<TKey, TValue>::operator=(BinarySearchTree&& bst)
{
    root = std::move(bst.root);
    return *this;
}

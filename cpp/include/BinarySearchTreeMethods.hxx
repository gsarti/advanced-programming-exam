/**
 * @file BinarySearchTreeMethods.h
 * @author Gabriele Sarti
 * @date 12 January 2019
 * @brief Header containing method definitions for the BinarySearchTree class.
 */

#include "BinarySearchTree.h"

// Private Methods

template <class TKey,class TValue>
typename BinarySearchTree<TKey, TValue>::Iterator BinarySearchTree<TKey, TValue>::findNearest(TKey key)
{
    Node * node = root.get();
    while(node)
    {
        if(key > node->data.first)
        {
            if(!node->right) // Node was not found
            {
                return Iterator{node};
            }
            node = node->right.get();
        }
        else if (key < node->data.first)
        {
            if(!node->left) // Node was not found
            {
                return Iterator{node};
            }
            node = node->left.get();
        }
        else // Node was found
        {
            return Iterator{node};
        }
    }
    return end(); // Tree is empty
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

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::rebuildBalancedTree(std::vector<std::pair<TKey, TValue>>& nodes, int firstId, int lastId)
{
    if(firstId > lastId)
    {
        return;
    }
    int halfId = (firstId + lastId) / 2;
    insert(nodes[halfId]);
    rebuildBalancedTree(nodes, firstId, halfId - 1);
    rebuildBalancedTree(nodes, halfId + 1, lastId);
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::printNode(const std::unique_ptr<Node>& node, std::ostream& os) const
{
    os << node->data.first << ":" << node->data.second << std::endl;
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::printTreeStructure(const std::unique_ptr<Node>& node, std::ostream& os, bool right, std::string indent) const
{
    if (node->right) 
    {
        printTreeStructure(node->right, os, true, indent + (right ? "        " : " |      "));
    }
    os << indent << (right ? " /" : " \\") << "----- ";
    printNode(node, os);
    if (node->left) 
    {
        printTreeStructure(node->left, os, false, indent + (right ? " |      " : "        "));
    }
}

// Public methods

template <class TKey,class TValue>
bool BinarySearchTree<TKey, TValue>::insert(std::pair<TKey, TValue> d)
{
    Iterator nearest{this->findNearest(d.first)};
    if (nearest != end())
    {
        Node * node = nearest.getNode();
        if(d.first > (*nearest).first)
        {
            node->right.reset(new Node{d, node});
            return true;
        }
        else if (d.first < (*nearest).first)
        {
            node->left.reset(new Node{d, node});
            return true;
        }
        return false; // Node was already present, no action performed.
    }
    else // Tree is empty
    {
        root.reset(new Node{d});
        return true;
    }
}

template <class TKey,class TValue>
std::ostream& BinarySearchTree<TKey, TValue>::printOrderedList(std::ostream& os) const
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
std::ostream& BinarySearchTree<TKey, TValue>::printTree(std::ostream& os) const
{
    if (!root)
    {
        return os << "Empty";
    }
    if (root->right) 
    {
        printTreeStructure(root->right, os, true, "");
    }
    printNode(root, os);
    if (root->left)
    {
        printTreeStructure(root->left, os, false, "");
    }
    return os;
}

template <class TKey,class TValue>
typename BinarySearchTree<TKey, TValue>::Iterator BinarySearchTree<TKey, TValue>::find(TKey key)
{
    Iterator nearest{this->findNearest(key)};
    if (nearest != end())
    {
        return (*nearest).first == key ? nearest : end();
    }
    else
    {
        return end();
    }
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::balance()
{
    Iterator it{this->begin()};
    Iterator end{this->end()};
    std::vector<std::pair<TKey, TValue>> nodes;
    if(it == end)
    {
        return;
    }
    for(; it != end; ++it)
    {
        nodes.push_back(*it);
    }
    clear();
    rebuildBalancedTree(nodes, 0, nodes.size() - 1);
}

template <class TKey,class TValue>
typename BinarySearchTree<TKey, TValue>::Iterator BinarySearchTree<TKey, TValue>::begin()
{
    if(!root)
    {
        return end();
    }
    Node * node = root.get();
    while(node->left)
    {
        node = node->left.get();
    }
    return Iterator{node};
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
BinarySearchTree<TKey, TValue>& BinarySearchTree<TKey, TValue>::operator=(const BinarySearchTree& bst)
{
    clear();
    copy(bst.root);
    return *this;
}

template <class TKey,class TValue>
BinarySearchTree<TKey, TValue>& BinarySearchTree<TKey, TValue>::operator=(BinarySearchTree&& bst)
{
    root = std::move(bst.root);
    return *this;
}

/**
 * @file BinarySearchTreeMethods.hxx
 * @author Gabriele Sarti
 * @date 12 January 2019
 * @brief Header containing method definitions for the BinarySearchTree class.
 */

#include "BinarySearchTree.h"

// Private Methods

template <class TKey,class TValue,class TCompare>
typename BinarySearchTree<TKey, TValue, TCompare>::Iterator BinarySearchTree<TKey, TValue, TCompare>::findNearest(const TKey& key)
{
    Node * node = root.get();
    while(node)
    {
        if(compare(node->data.first, key))
        {
            if(!node->right) // Node was not found
            {
                return Iterator{node};
            }
            node = node->right.get();
        }
        else if (compare(key, node->data.first))
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

template <class TKey,class TValue,class TCompare>
void BinarySearchTree<TKey, TValue, TCompare>::copy(const std::unique_ptr<Node>& node)
{
    if(node)
    {
        insert(node->data);
        copy(node->left);
        copy(node->right);
    }
}

template <class TKey,class TValue,class TCompare>
void BinarySearchTree<TKey, TValue, TCompare>::rebuildBalancedTree(std::vector<std::pair<TKey, TValue>>& nodes, int firstId, int lastId)
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

template <class TKey,class TValue,class TCompare>
void BinarySearchTree<TKey, TValue, TCompare>::printNode(const std::unique_ptr<Node>& node, std::ostream& os) const
{
    os << node->data.first << ":" << node->data.second << std::endl;
}

template <class TKey,class TValue,class TCompare>
void BinarySearchTree<TKey, TValue, TCompare>::printTreeStructure(const std::unique_ptr<Node>& node, std::ostream& os, bool right, std::string indent) const
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

template <class TKey,class TValue,class TCompare>
bool BinarySearchTree<TKey, TValue, TCompare>::insert(std::pair<TKey, TValue> d)
{
    Iterator nearest{this->findNearest(d.first)};
    if (nearest != end())
    {
        Node * node = nearest.getNode();
        if(compare((*nearest).first,d.first))
        {
            node->right.reset(new Node{d, node});
            return true;
        }
        else if (compare(d.first,(*nearest).first))
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

template <class TKey,class TValue,class TCompare>
std::ostream& BinarySearchTree<TKey, TValue, TCompare>::printOrderedList(std::ostream& os) const
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

template <class TKey,class TValue,class TCompare>
std::ostream& BinarySearchTree<TKey, TValue, TCompare>::printTree(std::ostream& os) const
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

template <class TKey,class TValue,class TCompare>
typename BinarySearchTree<TKey, TValue, TCompare>::Iterator BinarySearchTree<TKey, TValue, TCompare>::find(TKey key)
{
    Iterator nearest{this->findNearest(key)};
    if (nearest != end())
    {
        return (*nearest).first == key ? nearest : end();
    }
    return end();

}

template <class TKey,class TValue,class TCompare>
void BinarySearchTree<TKey, TValue, TCompare>::balance()
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

template <class TKey,class TValue,class TCompare>
typename BinarySearchTree<TKey, TValue, TCompare>::Iterator BinarySearchTree<TKey, TValue, TCompare>::begin()
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

template <class TKey,class TValue,class TCompare>
typename BinarySearchTree<TKey, TValue, TCompare>::ConstIterator BinarySearchTree<TKey, TValue, TCompare>::cbegin() const
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

template <class TKey,class TValue,class TCompare>
BinarySearchTree<TKey, TValue, TCompare>& BinarySearchTree<TKey, TValue, TCompare>::operator=(const BinarySearchTree& bst)
{
    clear();
    copy(bst.root);
    return *this;
}

template <class TKey,class TValue,class TCompare>
BinarySearchTree<TKey, TValue, TCompare>& BinarySearchTree<TKey, TValue, TCompare>::operator=(BinarySearchTree&& bst)
{
    root = std::move(bst.root);
    return *this;
}

template <class TKey,class TValue,class TCompare>
TValue& BinarySearchTree<TKey, TValue, TCompare>::operator[](const TKey& key)
{
    std::pair<TKey, TValue> pair{key, TValue{}};
    insert(pair); // Does nothing if node is already present
    Iterator it{find(key)};
    return (*it).second;
}

template <class TKey,class TValue,class TCompare>
const TValue& BinarySearchTree<TKey, TValue, TCompare>::operator[](const TKey& key) const
{
    std::pair<TKey, TValue> pair{key, TValue{}};
    insert(pair); // Does nothing if node is already present
    ConstIterator it{find(key)};
    return (*it).second;
}

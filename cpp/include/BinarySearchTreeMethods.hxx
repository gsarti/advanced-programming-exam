/**
 * @file BinarySearchTreeMethods.h
 * @author Gabriele Sarti
 * @date 12 January 2019
 * @brief Header containing method definitions for the BinarySearchTree class.
 */

#include "BinarySearchTree.h"

// Private Methods

template <class TKey,class TValue>
bool BinarySearchTree<TKey, TValue>::insert(std::unique_ptr<Node>& node, std::pair<TKey, TValue> d)
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

// template <class TKey,class TValue>
// bool BinarySearchTree<TKey, TValue>::isBalanced(const std::unique_ptr<Node>& node, int * height)
// {
//     if(!node)
//     {
//         return true;
//     }
//     int leftHeight = 0;
//     int rightHeight = 0;
//     bool isLeftBalanced = isBalanced(node->left, &leftHeight);
//     bool isRightBalanced = isBalanced(node->right, &rightHeight);
//     *height = std::max(leftHeight, rightHeight) + 1;
//     if(abs(leftHeight - rightHeight) > 1)
//     {
//         return false;
//     }
//     else
//     {
//         return isLeftBalanced && isRightBalanced;
//     }
// }

template <class TKey,class TValue>
int BinarySearchTree<TKey, TValue>::treeToVine(const std::unique_ptr<Node>& root)
{
   Node * vineTail = root.get();
   Node * remain = vineTail->right.get();
   int size = 0;
   while(remain)
   {
      if(!remain->left)
      {  
        vineTail = remain;
        remain = remain->right.get();
        ++size;
      }
      else
      {  
        Node * tempPtr = remain->left.get();
        remain->left = std::move(tempPtr->right);
        tempPtr->right.reset(remain);
        remain = tempPtr;
        vineTail->right.reset(tempPtr);
      }
   }
   return size;
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::vineToTree(const std::unique_ptr<Node>& root, int size)
{
    // int fullCount = 1;
    // while(fullCount <= size)
    // {
    //     fullCount = fullCount + fullCount + 1;
    // }
    // fullCount /= 2;
    // compression(root, size - fullCount);
    // for(size = fullCount; size > 1; size /= 2)
    // {
    //     compression(root, size/2);
    // }
    int leafCount = size + 1 - pow(2, log(size + 1));
    compression(root, leafCount);
    size = size - leafCount;
    while(size > 1)
    {
        size /= 2;
        compression(root, size);
    }
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::compression(const std::unique_ptr<Node>& root, int count)
{
    Node * scanner = root.get();
    for(int i = 0; i < count; i++)
    {
        Node * child = scanner->right.get();
        scanner->right.reset(child->right.get());
        scanner = scanner->right.get();
        child->right.reset(scanner->left.get());
        scanner->left.reset(child);
    }
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::printNode(const std::unique_ptr<Node>& node, std::ostream& os) const
{
    if (!node) 
    {
        os << "<null>";
    } 
    else 
    {
        os << node->data.first << ":" << node->data.second << std::endl;
    }
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::printTree(const std::unique_ptr<Node>& node, std::ostream& os, bool right, std::string indent) const
{
    if (node->right) 
    {
        printTree(node->right, os, true, indent + (right ? "        " : " |      "));
    }
    os << indent;
    if (right) 
    {
        os << " /";
    } 
    else 
    {
        os << " \\";
    }
    os << "----- ";
    printNode(node, os);
    if (node->left) 
    {
        printTree(node->left, os, false, indent + (right ? " |      " : "        "));
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
typename BinarySearchTree<TKey, TValue>::Iterator BinarySearchTree<TKey, TValue>::find(TKey key)
{
    Node * node = root.get();
    while(node)
    {
        if(key > node->data.first)
        {
            if(!node->right)
            {
                return end();
            }
            node = node->right.get();
        }
        else if (key < node->data.first)
        {
            if(!node->left)
            {
                return end();
            }
            node = node->left.get();
        }
        else
        {
            return Iterator{node};
        }
    }
    return end();
}

template <class TKey,class TValue>
void BinarySearchTree<TKey, TValue>::balance()
{
    std::unique_ptr<Node> pseudoRoot(new Node());
    pseudoRoot->right.reset(root.get());
    int size = treeToVine(pseudoRoot);
    vineToTree(pseudoRoot, size);
    root.reset(pseudoRoot->right.get());
}

template <class TKey,class TValue>
std::ostream& BinarySearchTree<TKey, TValue>::print(std::ostream& os) const
{
    if (!root)
    {
        return os << "Empty";
    }
    if (root->right) 
    {
        printTree(root->right, os, true, "");
    }
    printNode(root, os);
    if (root->left)
    {
        printTree(root->left, os, false, "");
    }
    return os;
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

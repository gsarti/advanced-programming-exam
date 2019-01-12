/**
 * @file BinarySearchTreeTest.cpp
 * @author Gabriele Sarti
 * @date 9 January 2019
 * @brief Source file to perform various tests on the BinarySearchTree class.
 */
#include "BinarySearchTree.h"

int main()
{
    std::pair<int, int> pair{4,4};
    std::pair<int, int> pair2{2,2};
    std::pair<int, int> pair3{6,6};
    std::pair<int, int> pair4{1,1};
    std::pair<int, int> pair5{5,5};
    std::pair<int, int> pair6{3,3};
    std::pair<int, int> pair7{7,7};
    
    BinarySearchTree<int, int> bst;
    std::cout << bst << std::endl;
    bst.insert(pair);
    std::cout << bst << std::endl;
    bst.insert(pair2);
    bst.insert(pair3);
    bst.insert(pair4);
    std::cout << bst << std::endl;
    bst.insert(pair5);
    bst.insert(pair6);
    bst.insert(pair7);
    std::cout << bst << std::endl;
    BinarySearchTree<int, int> bst2{bst};
    std::cout << bst2 << std::endl;
}
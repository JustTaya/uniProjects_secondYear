#include <iostream>
#include "Tree.h"

void print(int key, int data) {
    std::cout << "Key: " << key << " Data: " << data << std::endl;
}

int main() {
/*
    MultiTree<int,int>* tree=new MultiTree<int,int>();
    tree->insert(1,1);
    MultiNode<int,int>* tmp= tree->insert(tree->getRoot(),2,2);
    tree->insert(tree->getRoot(),3,3);
    tree->insert(tmp,5,5);
    tree->deleteNode(2);
    tree->printLevelOrder(print);*/

/*  BinTree<int, int> *tree = new BinTree<int, int>();
    tree->insert(1,1);
    tree->insertleft(tree->getRoot(),2,2);
    BinNode<int,int>* tmp=tree->insertright(tree->getRoot(),3,3);
    tree->insertright(tmp,5,5);
    tree->deleteNode(3);
    tree->printLevelOrder(print);
    */
    BSTree<int, int> *tree = new BSTree<int, int>();
    tree->insert(1, 1);
    tree->insert(2, 2);
    tree->insert(3, 3);
    tree->insert(5, 5);
  //  tree->deleteNode(3);
    tree->printPostOrder(print);
    return 0;
}
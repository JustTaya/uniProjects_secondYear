#include <iostream>
#include "Tree.h"

void print(int key,int data)
{
    std::cout<<"Key: "<<key<<" Data: "<<data<<std::endl;
}

int main() {

    MultiTree<int,int>* tree=new MultiTree<int,int>();
    tree->insert(1,1);
    MultiNode<int,int>* tmp= tree->insert(tree->getRoot(),2,2);
    tree->insert(tree->getRoot(),3,3);
    tree->insert(tmp,5,5);
    tree->deleteNode(2);
    tree->printPreOrder(print);
    return 0;
}
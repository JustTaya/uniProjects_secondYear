#include <iostream>
#include "Tree.h"

int main() {

    BSTree<int, int> *tree = new BSTree<int, int>();
    tree->printPostOrder();
    return 0;
}
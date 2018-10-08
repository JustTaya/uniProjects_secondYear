//
// Created by taya on 10/8/18.
//

#ifndef LAB1_1_SAMPLES_H
#define LAB1_1_SAMPLES_H

#include "Tree.h"
#include "IPAddress.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>

void print(int key) {
    std::cout << "Key: " << key << std::endl;
}

void print(double key) {
    std::cout << "Key: " << key << std::endl;
}

void print(std::string key) {
    std::cout << "Key: " << key << std::endl;
}

void print(std::vector<int> *key) {
    std::cout << "Key: ";
    std::for_each(key->begin(), key->end(), [](int digit) {
        std::cout << digit;
    });
    std::cout << std::endl;
}

void print(IP *key) {
    std::cout << "Key: ";
    key->print();
    std::cout << std::endl;
}

void print(Subnet *key) {
    std::cout << "Key: ";
    key->print();
    std::cout << std::endl;
}

class Compare_vector {
    bool operator()(std::vector<int> *vector1, std::vector<int> *vector2) {
        if (vector1->size() < vector2->size())
            return true;
        else if (vector1->size() > vector2->size())
            return false;
        for (size_t i = 0; i < vector1->size(); i++) {
            if (vector1[i] < vector2[i])
                return true;
            else if (vector1[i] > vector2[i])
                return false;
        }
        return false;
    }
};

class CompareIP {
    bool operator()(IP *ip1, IP *ip2) {
        ip1->compare(ip2);
    }
};

class CompareSubnet {
    bool operator()(Subnet *net1, Subnet *net2) {
        net1->compare(net2);
    }
};
void multiTree_int()
{
    std::cout << "MultiTree<int>" << std::endl;
    MultiTree<int> *multiTree = new MultiTree<int>();
    multiTree->insert(rand() % 100);
    MultiNode<int> *tmp1 = multiTree->insert(multiTree->getRoot(), rand() % 100);
    multiTree->insert(multiTree->getRoot(), rand() % 100);
    multiTree->insert(tmp1, 5);
    multiTree->deleteNode(5);
    multiTree->printLevelOrder(print);
    delete multiTree;
    std::cout << std::endl;
}

void binTree_int()
{
    std::cout << "BinTree<int>" << std::endl;
    BinTree<int> *binTree = new BinTree<int>();
    binTree->insert(rand() % 100);
    binTree->insertleft(binTree->getRoot(), rand() % 100);
    BinNode<int> *tmp2 = binTree->insertright(binTree->getRoot(), rand() % 100);
    binTree->insertright(tmp2, 5);
    binTree->deleteNode(5);
    binTree->printLevelOrder(print);
    delete binTree;
    std::cout << std::endl;
}

void bsTree_int()
{
    std::cout << "BSTree<int>" << std::endl;
    BSTree<int> *bsTree = new BSTree<int>();
    bsTree->insert(8);
    for(size_t i=0; i<5;i++)
        bsTree->insert(rand()%100);
    bsTree->deleteNode(8);
    bsTree->printLevelOrder(print);
    delete bsTree;
    std::cout<<std::endl;
}

void int_sample() {
    //multi node tree
    multiTree_int();

    //bin tree
   binTree_int();

    //binary search tree
  // bsTree_int();
}


void double_sample() {
    MultiTree<double> *multiTree = new MultiTree<double>();
    multiTree->insert((rand() % 100) / 10);
    multiTree->insert((rand() % 100) / 10);
    MultiNode<double> *tmp1 = multiTree->insert(multiTree->getRoot(), (rand() % 100) / 10);
    multiTree->insert(multiTree->getRoot(), (rand() % 100) / 10);
    multiTree->insert(tmp1, 5.0);
    multiTree->deleteNode(5.0);
    multiTree->printLevelOrder(print);
    delete multiTree;

    //bin tree
    BinTree<double> *binTree = new BinTree<double>();
    binTree->insert(rand() % 100);
    binTree->insertleft(binTree->getRoot(), rand() % 100);
    BinNode<double> *tmp2 = binTree->insertright(binTree->getRoot(), rand() % 100);
    binTree->insertright(tmp2, 5);
    binTree->deleteNode(5);
    binTree->printLevelOrder(print);
    delete binTree;

    //binary search tree
    BSTree<double> *bsTree = new BSTree<double>();
    for (size_t i = 0; i < 5; i++)
        bsTree->insert(rand() % 100);
    bsTree->insert(5);
    for (size_t i = 0; i < 5; i++)
        bsTree->insert(rand() % 100);
    bsTree->deleteNode(5);
    bsTree->printLevelOrder(print);
    delete bsTree;
}
//TODO:
/*
void string_sample() {

}

void vector_sample() {

}

void ip_sample() {

}

void subnet_sample() {

}
*/

#endif //LAB1_1_SAMPLES_H

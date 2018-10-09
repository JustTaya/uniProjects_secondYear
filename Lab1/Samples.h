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

void print_int(int key) {
    std::cout << "Key: " << key << std::endl;
}

void print_double(double key) {
    std::cout << "Key: " << key << std::endl;
}

void print_string(std::string key) {
    std::cout << "Key: " << key << std::endl;
}

void print_vector(std::vector<int> *key) {
    std::cout << "Key: ";
    std::for_each(key->begin(), key->end(), [](int digit) {
        std::cout << digit;
    });
    std::cout << std::endl;
}

void print_ip(IP *key) {
    std::cout << "Key: ";
    key->print();
    std::cout << std::endl;
}

void print_subnet(Subnet *key) {
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

void multiTree_int() {
    std::cout << "MultiTree<int>" << std::endl;
    MultiTree<int> *multiTree = new MultiTree<int>();
    multiTree->insertRoot(rand() % 100);
    MultiNode<int> *tmp1 = multiTree->insert(multiTree->getRoot(), rand() % 100);
    multiTree->insert(multiTree->getRoot(), rand() % 100);
    multiTree->insert(tmp1, 5);
    multiTree->deleteNode(5);
    multiTree->printLevelOrder(print_int);
    delete multiTree;
    std::cout << std::endl;
}

void binTree_int() {
    std::cout << "BinTree<int>" << std::endl;
    BinTree<int> *binTree = new BinTree<int>();
    binTree->insertRoot(rand() % 100);
    binTree->insertleft(binTree->getRoot(), rand() % 100);
    BinNode<int> *tmp2 = binTree->insertright(binTree->getRoot(), rand() % 100);
    binTree->insertright(tmp2, 5);
    binTree->deleteNode(5);
    binTree->printLevelOrder(print_int);
    delete binTree;
    std::cout << std::endl;
}

void bsTree_int() {
    std::cout << "BSTree<int>" << std::endl;
    BSTree<int> *bsTree = new BSTree<int>();
    bsTree->insertRoot(8);
    for (size_t i = 0; i < 5; i++)
        bsTree->insertNode(rand() % 100);
    bsTree->deleteNode(8);
    bsTree->printLevelOrder(print_int);
    delete bsTree;
    std::cout << std::endl;
}

void int_sample() {
    //multi node tree
    multiTree_int();

    //bin tree
    binTree_int();

    //binary search tree
    bsTree_int();
}

void multiTree_double() {
    std::cout << "MultiTree<double>" << std::endl;
    MultiTree<double> *multiTree = new MultiTree<double>();
    multiTree->insertRoot((rand() % 100) / 10.0);
    MultiNode<double> *tmp1 = multiTree->insert(multiTree->getRoot(), (rand() % 100) / 10.0);
    multiTree->insert(multiTree->getRoot(), (rand() % 100) / 10.0);
    multiTree->insert(tmp1, 5.0);
    multiTree->deleteNode(5.0);
    multiTree->printLevelOrder(print_double);
    delete multiTree;
};

void binTree_double() {
    std::cout << "BinTree<double>" << std::endl;
    BinTree<double> *binTree = new BinTree<double>();
    binTree->insertRoot((rand() % 100)/10.0);
    binTree->insertleft(binTree->getRoot(), (rand() % 100)/10.0);
    BinNode<double> *tmp2 = binTree->insertright(binTree->getRoot(), (rand() % 100)/10.0);
    binTree->insertright(tmp2, 5.0);
    binTree->deleteNode(5.0);
    binTree->printLevelOrder(print_double);
    delete binTree;
}

void bsTree_double()
{
    std::cout << "BSTree<double>" << std::endl;
    BSTree<double> *bsTree = new BSTree<double>();
    bsTree->insertRoot(5.0);
    for (size_t i = 0; i < 5; i++)
        bsTree->insertNode((rand() % 100)/10.0);
   // bsTree->deleteNode(8.1);
    bsTree->printLevelOrder(print_double);
    delete bsTree;
    std::cout << std::endl;
}

void double_sample() {
    //multi node tree
    multiTree_double();

    //bin tree
    binTree_double();

    //binary search tree
    bsTree_double();

}

void multiTree_string() {
    std::cout << "MultiTree<double>" << std::endl;
    MultiTree<std::string> *multiTree = new MultiTree<std::string>();
    multiTree->insertRoot("xx");
    MultiNode<std::string> *tmp1 = multiTree->insert(multiTree->getRoot(), "xy");
    multiTree->insert(multiTree->getRoot(), "yx");
    multiTree->insert(tmp1, "yy");
    multiTree->deleteNode("yy");
    multiTree->printLevelOrder(print_string);
    delete multiTree;
};

void binTree_string() {
    std::cout << "BinTree<string>" << std::endl;
    BinTree<std::string> *binTree = new BinTree<std::string>();
    binTree->insertRoot("xx");
    binTree->insertleft(binTree->getRoot(), "xy");
    BinNode<std::string> *tmp2 = binTree->insertright(binTree->getRoot(), "yx");
    binTree->insertright(tmp2, "yy");
    binTree->deleteNode("yy");
    binTree->printLevelOrder(print_string);
    delete binTree;
}

void bsTree_string()
{
    std::cout << "BSTree<string>" << std::endl;
    BSTree<std::string> *bsTree = new BSTree<std::string>();
    bsTree->insertRoot("xx");
    bsTree->insertNode("xy");
    bsTree->insertNode("yx");
    bsTree->insertNode("yy");
     bsTree->deleteNode("xx");
    bsTree->printLevelOrder(print_string);
    delete bsTree;
    std::cout << std::endl;
}


void string_sample() {
    //multi node tree
    multiTree_string();

    //bin tree
    binTree_string();

    //binary search tree
    bsTree_string();
}

//TODO:
/*
void vector_sample() {

}

void ip_sample() {

}

void subnet_sample() {

}
*/

#endif //LAB1_1_SAMPLES_H

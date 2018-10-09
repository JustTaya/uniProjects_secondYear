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
        std::cout << digit << " ";
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
public:
    bool operator()(std::vector<int> *vector1, std::vector<int> *vector2) {
        if ((*vector1).size() < (*vector2).size())
            return true;
        else if ((*vector1).size() > (*vector2).size())
            return false;
        for (size_t i = 0; i < (*vector1).size(); i++) {
            if ((*vector1)[i] < (*vector2)[i])
                return true;
            else if ((*vector1)[i] > (*vector2)[i])
                return false;
        }
        return false;
    }
};

class CompareIP {
public:
    bool operator()(IP *ip1, IP *ip2) {
        ip1->compare(ip2);
    }
};

class CompareSubnet {
public:
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
    binTree->search(5);
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
    std::cout << std::endl;
};

void binTree_double() {
    std::cout << "BinTree<double>" << std::endl;
    BinTree<double> *binTree = new BinTree<double>();
    binTree->insertRoot((rand() % 100) / 10.0);
    binTree->insertleft(binTree->getRoot(), (rand() % 100) / 10.0);
    BinNode<double> *tmp2 = binTree->insertright(binTree->getRoot(), (rand() % 100) / 10.0);
    binTree->insertright(tmp2, 5.0);
    binTree->deleteNode(5.0);
    binTree->printLevelOrder(print_double);
    delete binTree;
    std::cout << std::endl;
}

void bsTree_double() {
    std::cout << "BSTree<double>" << std::endl;
    BSTree<double> *bsTree = new BSTree<double>();
    bsTree->insertRoot(5.0);
    for (size_t i = 0; i < 5; i++)
        bsTree->insertNode((rand() % 100) / 10.0);
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
    std::cout << std::endl;
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
    std::cout << std::endl;
}

void bsTree_string() {
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

void multiTree_vector(std::vector<std::vector<int> *> tmp) {
    std::cout << "MultiTree<vector>" << std::endl;
    MultiTree<std::vector<int> *> *multiTree = new MultiTree<std::vector<int> *>();
    multiTree->insertRoot(tmp[0]);
    MultiNode<std::vector<int> *> *tmp1 = multiTree->insert(multiTree->getRoot(), tmp[1]);
    multiTree->insert(multiTree->getRoot(), tmp[2]);
    multiTree->insert(tmp1, tmp[3]);
    multiTree->deleteNode(tmp[3]);
    multiTree->printLevelOrder(print_vector);
    delete multiTree;
    std::cout << std::endl;
};

void binTree_vector(std::vector<std::vector<int> *> tmp) {
    std::cout << "BinTree<vector>" << std::endl;
    BinTree<std::vector<int> *> *binTree = new BinTree<std::vector<int> *>();
    binTree->insertRoot(tmp[0]);
    binTree->insertleft(binTree->getRoot(), tmp[1]);
    BinNode<std::vector<int> *> *tmp2 = binTree->insertright(binTree->getRoot(), tmp[2]);
    binTree->insertright(tmp2, tmp[3]);
    binTree->deleteNode(tmp[3]);
    binTree->printLevelOrder(print_vector);
    delete binTree;
    std::cout << std::endl;
}

void bsTree_vector(std::vector<std::vector<int> *> tmp) {
    std::cout << "BSTree<vector>" << std::endl;
    BSTree<std::vector<int> *, Compare_vector> *bsTree = new BSTree<std::vector<int> *, Compare_vector>();
    bsTree->insertRoot(tmp[0]);
    bsTree->insertNode(tmp[1]);
    bsTree->insertNode(tmp[2]);
    bsTree->insertNode(tmp[3]);
    bsTree->deleteNode(tmp[3]);
    bsTree->printLevelOrder(print_vector);
    delete bsTree;
    std::cout << std::endl;
}

void vector_sample(std::vector<std::vector<int> *> tmp) {
//multi node tree
    multiTree_vector(tmp);

//bin tree
    binTree_vector(tmp);

//binary search tree
    bsTree_vector(tmp);

}


void multiTree_ip() {
    std::cout << "MultiTree<IP>" << std::endl;
    MultiTree<IP *> *multiTree = new MultiTree<IP *>();
    multiTree->insertRoot(new IP());
    MultiNode<IP *> *tmp1 = multiTree->insert(multiTree->getRoot(), new IP());
    multiTree->insert(multiTree->getRoot(), new IP());
    multiTree->insert(tmp1, new IP());
    // multiTree->deleteNode();
    multiTree->printLevelOrder(print_ip);
    delete multiTree;
    std::cout << std::endl;
};

void binTree_ip() {
    std::cout << "BinTree<IP>" << std::endl;
    BinTree<IP *> *binTree = new BinTree<IP *>();
    binTree->insertRoot(new IP());
    binTree->insertleft(binTree->getRoot(), new IP());
    BinNode<IP *> *tmp2 = binTree->insertright(binTree->getRoot(), new IP());
    binTree->insertright(tmp2, new IP());
    //binTree->deleteNode(new IP());
    binTree->printLevelOrder(print_ip);
    delete binTree;
    std::cout << std::endl;
}

void bsTree_ip() {
    std::cout << "BSTree<IP>" << std::endl;
    BSTree<IP *, CompareIP> *bsTree = new BSTree<IP *, CompareIP>();
    bsTree->insertRoot(new IP());
    bsTree->insertNode(new IP());
    bsTree->insertNode(new IP());
    bsTree->insertNode(new IP());
    //  bsTree->deleteNode(new IP());
    bsTree->printLevelOrder(print_ip);
    delete bsTree;
    std::cout << std::endl;
}

void ip_sample() {
//multi node tree
    multiTree_ip();

//bin tree
    binTree_ip();

//binary search tree
    bsTree_ip();
}

void multiTree_subnet() {
    std::cout << "MultiTree<subnet>" << std::endl;
    MultiTree<Subnet *> *multiTree = new MultiTree<Subnet *>();
    multiTree->insertRoot(new Subnet());
    MultiNode<Subnet *> *tmp1 = multiTree->insert(multiTree->getRoot(), new Subnet());
    multiTree->insert(multiTree->getRoot(), new Subnet());
    multiTree->insert(tmp1, new Subnet());
    // multiTree->deleteNode();
    multiTree->printLevelOrder(print_subnet);
    delete multiTree;
    std::cout << std::endl;
};

void binTree_subnet() {
    std::cout << "BinTree<subnet>" << std::endl;
    BinTree<Subnet *> *binTree = new BinTree<Subnet *>();
    binTree->insertRoot(new Subnet());
    binTree->insertleft(binTree->getRoot(), new Subnet());
    BinNode<Subnet *> *tmp2 = binTree->insertright(binTree->getRoot(), new Subnet());
    binTree->insertright(tmp2, new Subnet());
    binTree->printLevelOrder(print_subnet);
    delete binTree;
    std::cout << std::endl;
}

void bsTree_subnet() {
    std::cout << "BSTree<subnet>" << std::endl;
    BSTree<Subnet *, CompareSubnet> *bsTree = new BSTree<Subnet *, CompareSubnet>();
    bsTree->insertRoot(new Subnet());
    bsTree->insertNode(new Subnet());
    bsTree->insertNode(new Subnet());
    bsTree->insertNode(new Subnet());
    bsTree->printLevelOrder(print_subnet);
    delete bsTree;
    std::cout << std::endl;
}

void subnet_sample() {
//multi node tree
    multiTree_subnet();

//bin tree
    binTree_subnet();

//binary search tree
    bsTree_subnet();
}


#endif //LAB1_1_SAMPLES_H

//
// Created by taya on 02.10.18.
//

#ifndef LAB1_1_IPADRESS_H
#define LAB1_1_IPADRESS_H

#include "Convert.h"
#include <iostream>
#include <bitset>

enum IPversion {
    v4, v6
};

struct IP4 {
    explicit IP4(unsigned ip[4]);

    unsigned octet[4];  //4 decimal numbers from 0 to 255
    std::bitset<32> getBinary();   //IPv4 in binary form
};

struct IP6 {
    explicit IP6(std::string *ip);

    std::string octet[8];

    std::bitset<128> getBinary();

    void transform();    //add omitted zeros
    void compress();    //zeros can be omitted
};

#endif //LAB1_1_IPADRESS_H

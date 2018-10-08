//
// Created by taya on 02.10.18.
//

#ifndef LAB1_1_IPADRESS_H
#define LAB1_1_IPADRESS_H

#include <iostream>
#include <bitset>
#include <random>
#include <ctime>
#include <cmath>


enum IPversion {
    v4, v6
};

class IPv6 {
public:
    explicit IPv6(std::string *ip);

    std::bitset<128> getBinary();

    void print();

    friend class IP;

private:
    std::string octet[8];

    void compress();    //zeros can be omitted
    void transform();    //add omitted zeros
};

class IPv4 {
public:
    explicit IPv4(unsigned ip[4]);

    std::bitset<32> getBinary();   //IPv4 in binary form
    void print();

    IPv6 *converttoIPv6();

    friend class IP;

private:
    unsigned octet[4];  //4 decimal numbers from 0 to 255

};

class IP {
public:
    IP();

    explicit IP(unsigned ip[4]);

    explicit IP(std::string *ip);

    void print();

    bool compare(IP *right);  //return true if current IP is less
    friend class Subnet;

private:
    IPversion version;
    union {
        IPv4 *ipv4;
        IPv6 *ipv6;
    } address;

    void getRandom();

    void getRandomIPv4();

    void getRandomIPv6();
};

//subnet class in CIDR notation
class Subnet {
public:
    Subnet();

    Subnet(IP *ip, unsigned mask) : ip(ip), mask(mask) {};

    bool check(IP *checkIP);

    bool compare(Subnet *right);    //compare the number of hosts

    void print();

private:
    IP *ip;  //ip address
    unsigned mask;  //subnet mask
};

#endif //LAB1_1_IPADRESS_H

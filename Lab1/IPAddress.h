//
// Created by taya on 02.10.18.
//

#ifndef LAB1_1_IPADRESS_H
#define LAB1_1_IPADRESS_H

#include <iostream>
#include <bitset>
#include <map>
#include <ctime>
#include <random>

const char *hex_to_bin(char c);

std::string getBin(unsigned dec);

//flag to know which ip protocol version is used
enum IPVersion {
    v4, v6
};

struct IP4 {
    unsigned octet[4];  //4 decimal numbers
    std::bitset<32> &returnBinary();
};

struct IP6 {
    std::string octet[8];

    std::bitset<128> &returnBinary();
};


//class to represent IP address
struct IPAddress {
    explicit IPAddress() : ipv4(nullptr), ipv6(nullptr) { version = v4; };

    explicit IPAddress(const unsigned* v4_input[4]):ipv4();

    explicit IPAddress(const std::string* v6_input[8]):;

    explicit IPAddress(IP4* address):ipv4(address){version=v4;};

    explicit IPAddress(IP6* address):ipv6(address){version=v6};

    IPVersion version;
    IP4 *ipv4;
    IP6 *ipv6;

    void setRandomIP4();

    void setRandomIP6();

//  void converttoIP4();

    void converttoIP6();
};

//CIDR: {IPv4 or IPv6}/{subnet mask}
struct SubNet {
    explicit SubNet(IP4* address, unsigned mask) : address(IPAddress(address)), mask(mask) {};

    explicit SubNet(IP6* address, unsigned mask) : address(IPAddress(address)), mask(mask) {};
    IPAddress address;
    unsigned mask;  //subnet mask
    void converttoIP6();
};

#endif //LAB1_1_IPADRESS_H

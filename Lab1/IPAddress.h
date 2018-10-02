//
// Created by taya on 02.10.18.
//

#ifndef LAB1_1_IPADRESS_H
#define LAB1_1_IPADRESS_H

#include <bitset>
#include <map>

const char *hex_char_to_bin(char c) {
    switch (toupper(c)) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
            return "1010";
        case 'B':
            return "1011";
        case 'C':
            return "1100";
        case 'D':
            return "1101";
        case 'E':
            return "1110";
        case 'F':
            return "1111";
    }
}

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

    unsigned *toIP6();

    std::bitset<128> &returnBinary();
};


//class to represent IP address
struct IPAddress {
    explicit IPAddress();

    explicit IPAddress(unsigned address[4]);

    explicit IPAddress(std::string address[8]);

    IPVersion version;
    IP4 *ipv4;
    IP6 *ipv6;

    void setRandomIP4();

    void setRandimIP6();

    void converttoIP4();

    void converttoIP6();
};

//CIDR: {IPv4 or IPv6}/{subnet mask}
struct SubNet {
    IPVersion version;
    IP4 *ipv4;
    IP6 *ipv6;

    void converttoIP4();

    void converttoIP6();

    unsigned mask;  //subnet mask
};

#endif //LAB1_1_IPADRESS_H

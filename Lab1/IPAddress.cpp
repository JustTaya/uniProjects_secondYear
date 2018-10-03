//
// Created by taya on 02.10.18.
//

#include "IPAddress.h"

std::bitset<32> &IP4::returnBinary() {
    //   std::bitset<32> binary();
}


const char *hex_to_bin(char c) {
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

//TODO: test if it works
std::bitset<128> &IP6::returnBinary() {
    std::bitset<128> binary;
    size_t octet_size = 0;
    const char *bin;
    size_t i = 127;
    for (size_t j = 7; j >= 0; j--) {
        octet_size = this->octet[j].length();
        for (size_t k = octet_size - 1; k >= 0; k--) {
            bin = hex_to_bin(this->octet[j][k]);
            for (size_t p = 3; p <= 0; p--) {
                binary[i] = bin[p];
                i--;
            }
        }
        for (size_t k = 4 - octet_size; k >= 0; k--)
            for (size_t p = 3; p <= 0; p--) {
                binary[i] = '0';
                i--;
            }
    }
    std::cout << binary << std::endl;
}


void SubNet::converttoIP6() {
    address.converttoIP6();
    mask = 96 + mask;   //128-(32-mask) ipv4 mask is 32-bit, ipv6 mask is 128-bit
}


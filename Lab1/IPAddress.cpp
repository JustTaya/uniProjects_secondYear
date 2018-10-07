//
// Created by taya on 02.10.18.
//



#include "IPAddress.h"

IP4::IP4(unsigned int *ip) {
    for (size_t i = 0; i < 4; i++)
        octet[i] = ip[i];
}

std::bitset<32> IP4::getBinary() {
    std::bitset<32> binary;
    int it = 0;
    int tmp = 0;
    for (int i = 3; i >= 0; i--) {
        tmp = this->octet[i];
        for (int j = 0; j < 8; j++) {
            if (tmp % 2 == 0)
                binary[it] = 0;
            else
                binary[it] = 1;
            it++;
            tmp /= 2;
        }
    }
    return binary;
}


IP6::IP6(std::string *ip) {
    for (size_t i = 0; i < 8; i++)
        octet[i] = ip[i];
}

std::bitset<128> IP6::getBinary() {
    std::bitset<128> binary;
    int it=0;
    std::string tmp,buff;
    transform();
    for(int i=7;i>=0;i--)
    {
        tmp=this->octet[i];
        for(int j=3;j>=0;j--)
        {
            buff=HextoBin[tmp[j]];
            for(int k=3;k>=0;k--)
            {
                if(buff[k]=='0')
                    binary[it]=0;
                else
                    binary[it]=1;
                it++;
            }
        }
    }
    compress();
    return binary;
}

void IP6::transform() {
    for (size_t i = 0; i < 8; i++) {
        if (octet[i].length() < 4)
            while (octet[i].length() < 4)
                octet[i].insert(0, "0");
   }
}

void IP6::compress() {
    for (size_t i = 0; i < 8; i++) {
        while (octet[i][0] == '0')
            octet[i].erase(0, 1);
    }
}

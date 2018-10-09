//
// Created by taya on 02.10.18.
//



#include "IPAddress.h"
#include "Convert.h"

IPv4::IPv4(unsigned int *ip) {
    for (size_t i = 0; i < 4; i++)
        octet[i] = ip[i];
}

std::bitset<32> IPv4::getBinary() {
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

void IPv4::print() {
    std::cout << octet[0] << ":" << octet[1] << ":" << octet[2] << ":" << octet[3];
}

IPv6 *IPv4::converttoIPv6() {
    int n = 0, tmp = 0, it = 7;
    std::string *ip = new std::string[8], buff;
    buff.resize(8, '0');
    for (int i = 3; i >= 0; i--) {
        n = this->octet[i];
        while (n != 0) {
            tmp = n % 16;
            n /= 16;
            buff[it] = dectoHex[tmp];
            it--;
        }
    }
    ip[6].append(buff.substr(0, 4));
    ip[7].append(buff.substr(4, 4));
    IPv6 *ip6 = new IPv6(ip);
    return ip6;
}


IPv6::IPv6(std::string *ip) {
    for (size_t i = 0; i < 8; i++)
        octet[i] = ip[i];
    this->compress();
}

std::bitset<128> IPv6::getBinary() {
    std::bitset<128> binary;
    int it = 0;
    std::string tmp, buff;
    transform();
    for (int i = 7; i >= 0; i--) {
        tmp = this->octet[i];
        for (int j = 3; j >= 0; j--) {
            buff = hextoBin[tmp[j]];
            for (int k = 3; k >= 0; k--) {
                if (buff[k] == '0')
                    binary[it] = 0;
                else
                    binary[it] = 1;
                it++;
            }
        }
    }
    compress();
    return binary;
}

void IPv6::transform() {
    for (size_t i = 0; i < 8; i++) {
        if (octet[i].length() < 4)
            while (octet[i].length() < 4)
                octet[i].insert(0, "0");
    }
}

void IPv6::compress() {
    for (size_t i = 0; i < 8; i++) {
        while (octet[i][0] == '0')
            octet[i].erase(0, 1);
    }
}

void IPv6::print() {
    this->compress();
    std::cout << octet[0] << ":" << octet[1] << ":" << octet[2] << ":" << octet[3] << ":" <<
              octet[4] << ":" << octet[5] << ":" << octet[6] << ":" << octet[7];
}

IP::IP() {
    getRandom();
}

IP::IP(unsigned int *ip) {
    this->version = v4;
    this->address.ipv4 = new IPv4(ip);
}

IP::IP(std::string *ip) {
    this->version = v6;
    this->address.ipv6 = new IPv6(ip);
}

void IP::print() {
    if (this->version == v4)
        this->address.ipv4->print();
    else
        this->address.ipv6->print();
}

void IP::getRandom() {
    int type = rand() % 2;
    if (type == 0) {
        this->version = v4;
        this->getRandomIPv4();
    } else {
        this->version = v6;
        this->getRandomIPv6();
    }
}

void IP::getRandomIPv4() {
    unsigned ip[4];
    for (size_t i = 0; i < 4; i++) {
        ip[i] = rand() % 256;
    }
    this->address.ipv4 = new IPv4(ip);
}

void IP::getRandomIPv6() {
    std::string *ip = new std::string[8];
    int n = 0, tmp = 0;
    for (size_t i = 0; i < 8; i++) {
        tmp = rand() % 16;
        if (tmp < 10)
            ip[i].push_back(tmp + 48);
        else
            ip[i].push_back(tmp + 87);
    }
    this->address.ipv6 = new IPv6(ip);
}

bool IP::compare(IP *right) {
    if (this->version != right->version) {
        IPv6 *l, *r;     //left and right values for comparator
        if (this->version == v4) {
            l = this->address.ipv4->converttoIPv6();
            r = right->address.ipv6;
        } else {
            l = this->address.ipv6;
            r = right->address.ipv4->converttoIPv6();
        }
        for (size_t i = 0; i < 8; i++)
            if (l->octet[i] < r->octet[i])
                return true;
            else if (l->octet[i] > r->octet[i])
                return false;
    } else {
        if (this->version == v4) {
            for (size_t i = 0; i < 4; i++)
                if (this->address.ipv4->octet[i] < this->address.ipv4->octet[i])
                    return true;
                else if (this->address.ipv4->octet[i] > this->address.ipv4->octet[i])
                    return false;
        } else {
            for (size_t i = 0; i < 8; i++)
                if (this->address.ipv6->octet[i] < this->address.ipv6->octet[i])
                    return true;
                else if (this->address.ipv6->octet[i] > this->address.ipv6->octet[i])
                    return false;
        }
    }
    return false;
}

Subnet::Subnet() {
    this->ip = new IP();
    if (this->ip->version == v4)
        this->mask = rand() % 33;   //from 0 to 32
    else
        this->mask = rand() % 129;  //from 0 to 128
}

bool Subnet::check(IP *checkIP) {
    if (this->ip->version != checkIP->version) {
        IPv6 *tmp;
        std::bitset<128> subnet;    //bitset of subnet ip
        std::bitset<128> check;     //bitset of ip to check
        std::bitset<128> mask;
        if (this->ip->version == v6) {
            subnet = this->ip->address.ipv6->getBinary();
            tmp = checkIP->address.ipv4->converttoIPv6();
            check = tmp->getBinary();
            for (int i = 127; i >= (128 - this->mask); i--)
                mask[i] = 1;
        } else {
            tmp = this->ip->address.ipv4->converttoIPv6();
            subnet = tmp->getBinary();
            check = checkIP->address.ipv6->getBinary();
            for (int i = 127; i >= (96 + this->mask); i--)    //127-(32-this->mask)
                mask[i] = 1;
        }
        subnet = subnet & mask;
        check = check & mask;
        if (subnet == check)
            return true;
    } else {
        if (this->ip->version == v4) {
            std::bitset<32> subnet = this->ip->address.ipv4->getBinary();    //bitset of subnet ip
            std::bitset<32> check = checkIP->address.ipv4->getBinary();     //bitset of ip to check
            std::bitset<32> mask;
            for (int i = 31; i >= 32 - this->mask; i--)
                mask[i] = 1;
            subnet = subnet & mask;
            check = check & mask;
            if (subnet == check)
                return true;
        } else {

            std::bitset<128> subnet = this->ip->address.ipv6->getBinary();    //bitset of subnet ip
            std::bitset<128> check = checkIP->address.ipv6->getBinary();     //bitset of ip to check
            std::bitset<128> mask;
            for (int i = 127; i >= 128 - this->mask; i--)
                mask[i] = 1;
            subnet = subnet & mask;
            check = check & mask;
            if (subnet == check)
                return true;
        }
    }
    return false;
}

bool Subnet::compare(Subnet *right) {
    return (this->mask < right->mask);    //2^mask-2 is number of hosts in subnet, so compare masks
}

void Subnet::print() {
    this->ip->print();
    std::cout << "/" << this->mask;
}


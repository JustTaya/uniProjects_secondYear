#include "Samples.h"


int main() {
    srand(time(NULL));
    int_sample();
    double_sample();
    string_sample();
    std::vector<std::vector<int>*> tmp(4);
    tmp[0]=new std::vector<int>();
    tmp[0]->push_back(38);  tmp[0]->push_back( 1235); tmp[0]->push_back(3);
    tmp[1]=new std::vector<int>();
    tmp[1]->push_back(88);  tmp[1]->push_back(21);
    tmp[1]->push_back(21);  tmp[1]->push_back(0);
    tmp[2]=new std::vector<int>();
    tmp[2]->push_back(443); tmp[2]->push_back(1000);
    tmp[2]->push_back(1000);    tmp[2]->push_back(2);
    tmp[3]=new std::vector<int>();
    tmp[3]->push_back(1);   tmp[3]->push_back(1);
    tmp[3]->push_back(0);   tmp[3]->push_back(1);
    vector_sample(tmp);
    ip_sample();
    subnet_sample();
    return 0;
}


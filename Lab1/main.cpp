#include "Samples.h"


int main() {
    srand(time(NULL));
    int_sample();
    double_sample();
    string_sample();

    std::vector<std::vector<int> *> tmp(4);
    tmp[0]=new std::vector<int>({38,1235,3});
    tmp[1]=new std::vector<int>({88,21,21,0});
    tmp[2]=new std::vector<int>({443,1000,1000,2});
    tmp[3]=new std::vector<int>({1,1,0,1});

    vector_sample(tmp);
    ip_sample();
    subnet_sample();
    return 0;
}


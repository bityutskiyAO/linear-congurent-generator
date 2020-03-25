//
// Created by m1707760 on 17.03.2020.
//

#ifndef UNTITLED_LCG_H
#define UNTITLED_LCG_H

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

class LCG {
private:
    int64_t  m, a, b, currentXi, capacity , n = pow(2, 25);
    int d = 10;
public:
    LCG();
    double getPsevdoRandom();
    vector<int64_t> getElementFrequency(int64_t size);
    int64_t getConstant();
    int64_t getSize();
};


#endif //UNTITLED_LCG_H

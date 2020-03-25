//
// Created by m1707760 on 17.03.2020.
//

#include "LCG.h"

LCG::LCG()
    :m(pow(2, 31) - 1), a(132325724), b(0), currentXi(1) {

}

int64_t LCG::getConstant() {
    return d;
}

int64_t LCG::getSize() {
    return n;
}

double LCG::getPsevdoRandom() {
    if (capacity != m) {
        double doubleXi(currentXi / static_cast<double>(m));
        currentXi = (a * currentXi + b) % m;
        capacity++;
        return doubleXi;
    }
}

vector<int64_t> LCG::getElementFrequency(int64_t size) {
    vector<int64_t> vec(d, 0);
    for (int64_t i = 0; i < size; ++i) {
        vec[static_cast<int64_t>(d*getPsevdoRandom())] += 1;
    }
    return vec;
}

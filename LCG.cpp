#include "LCG.h"

LCG::LCG()
        :m(pow(2, 31) - 1), a(132325724), b(0), currentXi(1), currentXni(1), Xo(1) {

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

//Метод для модульного возведения числа a в степень n по модулю m
int64_t LCG::modPow(int64_t a, int64_t n, int64_t m) {
    int64_t result = 1;
    for (int i = 0; i < n; ++i) {
        result *= a;
        result = result % m;
    }
    return result;
}

//Процедура сдвига
void LCG::transitionProcedure() {
    currentXni = (modPow(a, n / 2, m) * Xo) % m;
}

//Проход по генератору начиная со сдвига.
double LCG::getTransitionPsevdoRandom() {
    if (currentXni == Xo) {
        transitionProcedure();
    }
    if (capacity != m) {
        double doubleXni(currentXni / static_cast<double>(m));
        currentXni = (a * currentXni + b) % m;
        capacity++;
        return doubleXni;
    }
}
//
// Created by m1707760 on 18.03.2020.
//

#include "GeneratorEvaluation.h"
#include <vector>
#include <set>
using namespace std;

GeneratorEvaluation::GeneratorEvaluation()
    : generator(new LCG()) {

}

GeneratorEvaluation::~GeneratorEvaluation() {
    delete generator;
    generator = nullptr;
}

double xiSquaredTest(const std::vector<int64_t>& v, const std::vector<double>& p, const int64_t n) {
    double result(0.0);
    for (int64_t i(0); i < v.size(); i += 1) {
        result += pow(v[i] - n * p[i], 2) / (n * p[i]);
    }
    return result;
}

double GeneratorEvaluation::theoreticalGoldshteinXiSquare(double freedom, double quantile) {
    quantile = 1 - quantile;
    vector<double> a = {1.0000886, 0.4713941, 0.0001348028, -0.008553069, 0.00312558, -0.0008426812, 0.00009780499};
    vector<double> b = {-0.2237368, 0.02607083, 0.01128186, -0.01153761, 0.005169654, 0.00253001, -0.001450117};
    vector<double> c = {-0.01513904, -0.008986007, 0.02277679, -0.01323293, -0.006950356, 0.001060438, 0.001565326};
    double d = 0.0;
    if(quantile >= 0.5 && quantile <= 0.999) {
        d = 2.0637*pow(log(1.0/(1-quantile) - 0.16), 0.4274) - 1.5774;
    } else if (quantile >= 0.001 && quantile < 0.5) {
        d = -2.0637*pow(log(1.0/(quantile) - 0.16), 0.4274) + 1.5774;
    }
    double expression = 0.0;
    for (int i = 0; i < 7; ++i) {
        expression += pow(freedom, -i/2.0)*pow(d, i)*(a[i] + b[i]/freedom + c[i]/pow(freedom, 2));
    }
    return freedom*pow(expression, 3);
}

int64_t stirlingNumbers(int64_t n, int64_t k) {
    if( n == 1 || k == 1 || k == n) {
        return 1;
    } else {
        return stirlingNumbers(n-1, k-1) + k*stirlingNumbers(n-1, k);
    }
}

int64_t factorial(int n) {
    if (n != 1) {
        return n * factorial(n - 1);
    }
}

/*----------------------------------------- Критерий частот ----------------------------------------------------*/
double GeneratorEvaluation::frequencyCriterionTest() {
    int64_t  n = generator->getSize();
    int d = generator->getConstant();
    double result = 0;
    vector<int64_t> frequencyVector = generator->getElementFrequency(n);
    std::vector<double> p(d, 1.0 / d);
    return xiSquaredTest(frequencyVector, p, n);
}

/*----------------------------------------- Критерий серий ----------------------------------------------------*/
double GeneratorEvaluation::serialCriterionTest() {
    int d = generator->getConstant();
    int64_t n = generator->getSize();
    vector<int64_t> counter(d * d, 0);
    for (int64_t i = 0; i < n; i++) {
        int64_t first(static_cast<int64_t>(d*generator->getPsevdoRandom()));
        int64_t second(static_cast<int64_t>(d*generator->getPsevdoRandom()));
        counter[d * first + second] += 1;
    }
    vector<double> p(d * d, 1.0 / (d * d));
    return xiSquaredTest(counter, p, n);
}
/*----------------------------------------- Интервальный критерий ----------------------------------------------------*/
double GeneratorEvaluation::intervalCriterionTest(const int64_t t) {
    int64_t d = generator->getConstant();
    int64_t n = generator->getSize();
    vector<int64_t> counter(t+1, 0);
    int64_t iterator(0);
    int64_t capacity(1);
    int64_t x = static_cast<int64_t>(d*generator->getPsevdoRandom());
    int64_t y = static_cast<int64_t>(d*generator->getPsevdoRandom());
    while(iterator < n) {
        if(x == y) {
            x = y;
            y = static_cast<int64_t>(d*generator->getPsevdoRandom());
            capacity++;
        } else {
            if(capacity > t) {
               counter[t]++;
            } else {
                counter[capacity-1]++;
            }
            capacity = 1;
        }
        iterator++;
    }
    vector<double> p(t+1, 0);
    double lastProbability = 0;
    for (int i = 0; i < p.size() - 1; ++i) {
        p[i] = (d-1)/static_cast<double>(pow(d, i + 1));
        lastProbability += p[i];
    }
    p[t] = 1 - lastProbability;
    return xiSquaredTest(counter, p, n);
}
/*---------------------------------------- Покер критерий ----------------------------------------------------*/
double GeneratorEvaluation::pokerCriterionTest() {
    int64_t d = generator->getConstant();
    int64_t n = generator->getSize();

    std::vector<int64_t> counter(5, 0);
    for (int64_t i = 0; i < n; i += 1) {
        std::set<int64_t> differentNumbers;
        for (ptrdiff_t j = 0; j < 5; j += 1) {
            differentNumbers.insert(static_cast<int64_t>(d * generator->getPsevdoRandom()));
        }
        counter[differentNumbers.size() - 1]++;
    }

    std::vector<double> p(5, 0);
    for (int64_t  k = 0; k < p.size(); ++k) {
        int64_t r(k + 1);
        p[k] = (stirlingNumbers(5, r) / pow(d, 5)) * factorial(d) / factorial(d - r);
    }
    return xiSquaredTest(counter, p, n);
}

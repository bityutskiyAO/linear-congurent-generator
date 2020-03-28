//
// Created by m1707760 on 18.03.2020.
//

#ifndef UNTITLED_GENERATOREVALUATION_H
#define UNTITLED_GENERATOREVALUATION_H


#include "LCG.h"

class GeneratorEvaluation {
    private:
        LCG* generator{ nullptr };
    public:
    GeneratorEvaluation();
    ~GeneratorEvaluation();
    double frequencyCriterionTest();
    double serialCriterionTest();
    double intervalCriterionTest(int64_t t);
    double pokerCriterionTest();
    double theoreticalGoldshteinXiSquare(double freedom, double quantile);

    /*Parallel methods*/
    double parallelFrequencyCriterionTest();
    double parallelSerialCriterionTest();
    double parallelIntervalCriterionTest(int64_t t);
    double parallelPokerCriterionTest();
    double parallelTheoreticalGoldshteinXiSquare(double freedom, double quantile);
};


#endif //UNTITLED_GENERATOREVALUATION_H

#include <iostream>
#include "GeneratorEvaluation.h"
#include <omp.h>

using namespace std;

int main() {
    GeneratorEvaluation generatorEvaluation1;
    LCG lcg;

    for (int i = 0; i < lcg.getSize(); ++i) {
        cout << lcg.getPsevdoRandom() << " ";
    }
    cout << endl;

    for (int i = 0; i < lcg.getSize()/2; ++i) {
        cout << lcg.getTransitionPsevdoRandom() << " ";
    }
    cout << endl;
    /*Frequency test checking*/
//    double firstTestStart = omp_get_wtime();
//    double frequencyTestResult = generatorEvaluation1.frequencyCriterionTest();
//    double firstTestEnd = omp_get_wtime();
//    cout << "Sequentially Frequency criterion test: " << frequencyTestResult << endl;
//    cout <<"Sequentially Frequency test duration: " << firstTestEnd - firstTestStart << endl ;
//    cout << endl;
//
//    GeneratorEvaluation parallelGeneratorEvaluation;
//    double parallelFirstTestStart = omp_get_wtime();
//    double parallelFrequencyTestResult = parallelGeneratorEvaluation.parallelFrequencyCriterionTest();
//    double parallelFirstTestEnd = omp_get_wtime();
//    cout << "Parallel Frequency criterion test: " << parallelFrequencyTestResult << endl;
//    cout <<"Parallel Frequency test duration: " << parallelFirstTestEnd - parallelFirstTestStart << endl ;
//    cout << endl;
    /*---------------------------------------------------------------------*/
    /*Serial test checking*/
    GeneratorEvaluation generatorEvaluation2;
    double secondTestStart = omp_get_wtime();
    double serialTestResult = generatorEvaluation2.serialCriterionTest();
    double secondTestEnd = omp_get_wtime();
    cout << "Sequentially Serial test result: " << serialTestResult << endl ;
    cout <<"Sequentially Serial test duration: " << secondTestEnd - secondTestStart << endl ;
    cout << endl;

    GeneratorEvaluation parallelGeneratorEvaluation2;
    double parallelSecondTestStart = omp_get_wtime();
    double parallelSerialTestResult = parallelGeneratorEvaluation2.parallelSerialCriterionTest();
    double parallelSecondTestEnd = omp_get_wtime();
    cout << "Parallel Serial criterion test: " << parallelSerialTestResult << endl;
    cout <<"Parallel Serial test duration: " << parallelSecondTestEnd - parallelSecondTestStart << endl ;
    cout << endl;
    /*---------------------------------------------------------------------*/
    /*Interval test checking*/
//    GeneratorEvaluation generatorEvaluation3;
//    double thirdTestStart = omp_get_wtime();
//    double intervalTestResult = generatorEvaluation3.intervalCriterionTest(6);
//    double thirdTestEnd = omp_get_wtime();
//    cout << "Interval test result: " << intervalTestResult << endl ;
//    cout <<"Interval test duration: " << thirdTestEnd - thirdTestStart << endl ;
//    cout << endl;
//    /*---------------------------------------------------------------------*/
//
//    GeneratorEvaluation generatorEvaluation4;
//    /*Poker test checking*/
//    double fourthTestStart = omp_get_wtime();
//    double pokerTestResult = generatorEvaluation4.pokerCriterionTest();
//    double fourthTestEnd = omp_get_wtime();
//    cout << "Poker test result: " << pokerTestResult << endl ;
//    cout <<"Poker test duration: " << fourthTestEnd - fourthTestStart << endl ;
//    cout << endl;
    /*---------------------------------------------------------------------*/
    return 0;
}
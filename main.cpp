#include <iostream>
#include "GeneratorEvaluation.h"

using namespace std;

vector<double> getXiSquareTheoretical(GeneratorEvaluation& generatorEvaluation, double freedom, vector<double> quantiles) {
    vector<double> xiSquareTest;
    for (int i = 0; i < quantiles.size() ; ++i) {
        xiSquareTest.push_back(generatorEvaluation.theoreticalGoldshteinXiSquare(freedom, quantiles[i]));
        cout << xiSquareTest[i] << " ";
    }
    cout << endl;
    return xiSquareTest;
}

int main() {
    GeneratorEvaluation generatorEvaluation;
    LCG lcg;
    double freedom = lcg.getConstant();
    /*Frequency test checking*/
    vector<double> quantiles = {0.01, 0.1, 0.9, 0.99};
    vector<double> xiSquareTest1 = getXiSquareTheoretical(generatorEvaluation, freedom - 1, quantiles);
    double frequencyTestResult = generatorEvaluation.frequencyCriterionTest();
    cout << "Frequency criterion test. V1 = " << frequencyTestResult << endl;
    cout << "Checking with theoretical xi-square: " << endl;
    if (frequencyTestResult > xiSquareTest1[0] || frequencyTestResult < xiSquareTest1[3]) {
        cout << "Test №1 failed" << endl;
    } else if ((frequencyTestResult < xiSquareTest1[0] && frequencyTestResult > xiSquareTest1[1]) || (frequencyTestResult < xiSquareTest1[2] && frequencyTestResult > xiSquareTest1[3])) {
        cout << "Result aproximately good" << endl;
    } else if (frequencyTestResult < xiSquareTest1[1] && frequencyTestResult > xiSquareTest1[2]) {
        cout << "Test passed" << endl;
    }
    /*---------------------------------------------------------------------*/
    /*Serial test checking*/
    vector<double> xiSquareTest2 = getXiSquareTheoretical(generatorEvaluation, freedom * freedom - 1, quantiles);
    double serialTestResult = generatorEvaluation.serialCriterionTest();
    cout << "Serial criterion test. V2 = " << serialTestResult << endl;
    cout << "Checking with theoretical xi-square: " << endl;
    if (serialTestResult > xiSquareTest2[0] || serialTestResult < xiSquareTest2[3]) {
        cout << "Test №2 failed" << endl;
    } else if ((serialTestResult < xiSquareTest2[0] && serialTestResult > xiSquareTest2[1]) || (serialTestResult < xiSquareTest2[2] && serialTestResult > xiSquareTest2[3])) {
        cout << "Result №2 aproximately good" << endl;
    } else if (serialTestResult < xiSquareTest2[1] && serialTestResult > xiSquareTest2[2]) {
        cout << "Test №2 passed" << endl;
    }
    /*---------------------------------------------------------------------*/

    /*Interval test checking*/
    vector<double> xiSquareTest3 = getXiSquareTheoretical(generatorEvaluation, 6, quantiles);
    double intervalTestResult = generatorEvaluation.intervalCriterionTest(6);
    cout << "Interval criterion test = " << intervalTestResult << endl;
    if (intervalTestResult > xiSquareTest3[0] || intervalTestResult < xiSquareTest3[3]) {
        cout << "Test №3 failed" << endl;
    } else if ((intervalTestResult < xiSquareTest3[0] && intervalTestResult > xiSquareTest3[1]) || (intervalTestResult < xiSquareTest3[2] && intervalTestResult > xiSquareTest3[3])) {
        cout << "Result №3 aproximately good" << endl;
    } else if (intervalTestResult < xiSquareTest3[1] && intervalTestResult > xiSquareTest3[2]) {
        cout << "Test №3 passed" << endl;
    }
    /*---------------------------------------------------------------------*/

    /*Poker test checking*/
    vector<double> xiSquareTest4 = getXiSquareTheoretical(generatorEvaluation, 4, quantiles);
    double pokerTestResult = generatorEvaluation.pokerCriterionTest();
    cout << "Poker criterion test = " << pokerTestResult << endl;
    if (pokerTestResult > xiSquareTest4[0] || pokerTestResult < xiSquareTest4[3]) {
        cout << "Test №3 failed" << endl;
    } else if ((pokerTestResult < xiSquareTest4[0] && pokerTestResult > xiSquareTest4[1]) || (pokerTestResult < xiSquareTest4[2] && pokerTestResult > xiSquareTest4[3])) {
        cout << "Result №3 aproximately good" << endl;
    } else if (pokerTestResult < xiSquareTest4[1] && pokerTestResult > xiSquareTest4[2]) {
        cout << "Test №3 passed" << endl;
    }
    /*---------------------------------------------------------------------*/
    return 0;
}
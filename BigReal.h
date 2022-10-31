//
// Created by Twins on 11/1/2022.
//

#ifndef BIGDECIMALINTCLASS_CPP_BIGREAL_H
#define BIGDECIMALINTCLASS_CPP_BIGREAL_H
#include<iostream>
#include <string>
#include "BigDecimalIntClass.h"
using namespace std;
class BigReal{
private:
    string Whole_number;
    string Int;
    string Float;
    char signNumber;
public:
    BigReal (double realNumber = 0.0); // Default constructor
    BigReal (string realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment


};


#endif //BIGDECIMALINTCLASS_CPP_BIGREAL_H

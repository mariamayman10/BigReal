#ifndef FINAL_BIGREAL_H
#define FINAL_BIGREAL_H

#include <iostream>
#include <string>
#include <deque>
#include <regex>
#include "BigDecimalInt.h"
using namespace std;


class BigReal
{
private:
    BigDecimalInt Before_point;
    BigDecimalInt After_point;
    int dot_pos;
    char signNumber;

public:
    BigReal();
    BigReal(string number);
    bool checkValidInput(string input);
    BigReal(double realNumber);
    BigReal(BigDecimalInt bigInteger);
    BigReal(const BigReal &other); // Copy constructor
    BigReal(BigReal &&other);          // Move constructor
    BigReal &operator=(BigReal other); // Assignment operator
    BigReal &operator=(BigReal &&other); // Move assignment
    BigReal operator+(BigReal anotherReal);
    BigReal operator-(BigReal anotherReal);
    friend ostream &operator<<(ostream &out, BigReal num);
    friend istream &operator>>(istream &in, BigReal &num);
    bool operator==(BigReal anotherReal);
    bool operator<(BigReal anotherReal);
    bool operator>(BigReal anotherReal);
    int size();
    int sign();
    string getRNumber();
};
int MenuSystem();
int options(int choice);



#endif //FINAL_BIGREAL_H

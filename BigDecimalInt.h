#ifndef FINAL_BIGDECIMALINT_H
#define FINAL_BIGDECIMALINT_H

#include <iostream>
#include <string>
#include <deque>
#include <regex>
using namespace std;
class BigDecimalInt
{
private:
    string number;
    char signNumber;

public:
    bool operator<(const BigDecimalInt &anotherDec);
    bool operator>(const BigDecimalInt &anotherDec);
    bool operator==(const BigDecimalInt anotherDec);
    BigDecimalInt &operator=(const BigDecimalInt& anotherDec);
    BigDecimalInt operator+(BigDecimalInt anotherDec);
    BigDecimalInt operator-(BigDecimalInt& anotherDec);
    unsigned long long size();
    int sign() const;
    void setNumber(string num);
    void setSign(char s);
    string getNumber();
    BigDecimalInt();
    BigDecimalInt(string num);
};


#endif //FINAL_BIGDECIMALINT_H

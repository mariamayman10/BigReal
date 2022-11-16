#include "BigDecimalInt.h"


void BigDecimalInt ::setNumber(string num)
{
    number = num;
    if (number[0] == '+')
    {
        number.erase(0, 1);
        signNumber = '+';
    }
    else if (number[0] == '-')
    {
        number.erase(0, 1);
        signNumber = '-';
    }
    else
    {
        signNumber = '+';
    }
}
BigDecimalInt::BigDecimalInt(string num)
{
    setNumber(num);
}
BigDecimalInt ::BigDecimalInt()
{
    number = "0";
    signNumber = '+';
}
bool BigDecimalInt ::operator<(const BigDecimalInt &anotherDec)
{
    string comp1, comp2;
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2)
    {
        comp1 += '0';
        len1++;
    }
    while (len2 < len1)
    {
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if (signNumber == '-' && anotherDec.signNumber == '+')
    {
        return true;
    }
    else if (signNumber == '+' && anotherDec.signNumber == '-')
    {
        return false;
    }
    else if (signNumber == '+' && anotherDec.signNumber == '+')
    {
        return comp1 < comp2;
    }
    else
    {
        return comp1 > comp2;
    }
}
bool BigDecimalInt ::operator>(const BigDecimalInt &anotherDec)
{
    string comp1, comp2;
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2)
    {
        comp1 += '0';
        len1++;
    }
    while (len2 < len1)
    {
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if (signNumber == '-' && anotherDec.signNumber == '+')
    {
        return false;
    }
    else if (signNumber == '+' && anotherDec.signNumber == '-')
    {
        return true;
    }
    else if (signNumber == '+' && anotherDec.signNumber == '+')
    {
        return comp1 > comp2;
    }
    else
    {
        return comp1 < comp2;
    }
}
bool BigDecimalInt ::operator==(const BigDecimalInt anotherDec)
{
    if (signNumber == anotherDec.signNumber && number == anotherDec.number)
    {
        return true;
    }
    else
    {
        return false;
    }
}
BigDecimalInt &BigDecimalInt ::operator=(const BigDecimalInt& anotherDec)
{
    signNumber = anotherDec.signNumber;
    number = anotherDec.number;
    return *this;
}
string addition(string num1, string num2)
{
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res;
    int carry = 0;
    while (it1 != num1.rend())
    {
        int twoDigitsSum;
        carry = 0;
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0') + carry);
        if (twoDigitsSum >= 10)
        {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
        it1++;
        it2++;
    }
    if (carry)
    {
        res = char((carry) + '0') + res;
    }
    return res;
}
string subtraction(string num1, string num2)
{
    deque<long long> d;
    string res;
    for (long long i = num1.length() - 1; i >= 0; i--)
    {
        if (num1[i] < num2[i])
        {
            num1[i] = char(((num1[i] - '0') + 10) + '0');
            num1[i - 1] = char(((num1[i - 1] - '0') - 1) + '0');
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
        else
        {
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
    }

    for (auto i : d)
    {
        res += to_string(i);
    }
    return res;
}
BigDecimalInt BigDecimalInt ::operator+(BigDecimalInt anotherDec)
{
    BigDecimalInt result;
    char signNumber1 = signNumber, signNumber2 = anotherDec.signNumber;
    string num1 = number, num2 = anotherDec.number;
    BigDecimalInt number1 = *this;
    if (signNumber1 == signNumber2)
    {
        result.signNumber = signNumber1;
        result.number = addition(num1, num2);
    }
    else
    {

        if (number1.signNumber == '-')
        {
            number1.signNumber = '+';
            result = (anotherDec - number1);
        }
        else
        {
            anotherDec.signNumber = '+';
            result = (number1 - anotherDec);
        }
    }
    bool right = false;
    for (long long i = 0; i < result.number.length(); i++)
    {
        if (result.number[i] != '-' && result.number[i] != '0')
        {
            right = true;
        }
        if (!right && result.number[i] == '0' && result.number.length() >= num1.length())
        {
            result.number.erase(i, 1);
            i--;
        }
    }
    return result;
}
BigDecimalInt BigDecimalInt ::operator-(BigDecimalInt& anotherDec)
{
    BigDecimalInt obj;
    deque<long long> d;
    string str_min, res;
    string num1 = number, num2 = anotherDec.number;
    char sign1 = signNumber, sign2 = anotherDec.signNumber;
    bool ok = false, is_determined = false;
    if (num1 < num2)
    {
        swap(num1, num2);
        swap(sign1, sign2);
        ok = true;
    }

    if (sign1 == sign2)
    {
        res = subtraction(num1, num2);
        if (sign1 == '-')
            ok = !ok;
    }
    else
    {
        res = addition(num1, num2);
        if (signNumber == '-')
        {
            obj.signNumber = '-';
            is_determined = true;
        }
        else
        {
            obj.signNumber = '+';
            is_determined = true;
        }
    }

    bool right = false;
    for (long long i = 0; i < res.length(); i++)
    {
        if (res[i] != '-' && res[i] != '0')
        {
            right = true;
        }
        if (!right && res[i] == '0' && res.length() >= num1.length())
        {
            res.erase(i, 1);
            i--;
        }
    }

    if (res.empty())
        res = "0";
    if (!is_determined && (ok))
    {
        obj.signNumber = '-';
    }
    else if (!is_determined)
    {
        obj.signNumber = '+';
    }

    obj.number = res;
    return obj;
}
unsigned long long BigDecimalInt ::size()
{
    return number.size();
}
int BigDecimalInt ::sign() const
{
    if (signNumber == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
string BigDecimalInt::getNumber()
{
    return number;
}
void BigDecimalInt::setSign(char s)
{
    signNumber = s;
}
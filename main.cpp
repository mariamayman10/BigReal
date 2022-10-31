#include <iostream>
#include <deque>
#include <regex>

using namespace std;
#include<iostream>
#include <string>
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
int carry = 0, borrow = 0;
// Default Constructor
BigReal::BigReal() {
    Int = "0";
    Float = "0";
    signNumber = '+';
}

// constructor that takes a string as an input.
BigReal::BigReal(string num){
    bool validNumber = checkValidInput(num);
    if(validNumber){
        if(Int[0] == '+'){
            Int.erase(0,1);
            signNumber = '+';
        }
        else if (Int[0] == '-'){
            Int.erase(0,1);
            signNumber = '-';
        }
        else{
            signNumber = '+';
        }
    }
    else
    {
        cout << "Invalid" << "\n";
        exit(1);
    }
}

//addition implementation.
string addition(string num1,string num2)
{
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
    bool check_float = false;
    if(num1[0] == '*' && num2[0] == '*'){
        check_float = true;
        num1.erase(0, 1);
        num2.erase(0, 1);
        it1++;it2++;
    }
    while (it1 != num1.rend())
    {
        int twoDigitsSum;
        if(carry == 1){
            *(it1) = char(((*(it1) - '0') + carry) + '0');
            carry = 0;
        }
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
        if (twoDigitsSum >= 10)
        {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        it1++;
        it2++;
    }
    if (carry && !check_float)
    {
        res = char((carry) + '0') + res;
    }
    return res;
}

//subtraction implementation
string subtraction(string num1,string num2){
    string res;
    bool check_float = false;
    if(num1[0] == '*' && num2[0] == '*'){
        check_float = true;
        num1.erase(0, 1);
        num2.erase(0, 1);
    }
    for (long long i = num1.length() - 1; i >= 0; i--)
    {
        if(borrow == 1){
            num1[i] = char(((num1[i] - '0') - borrow) + '0');
            borrow = 0;
        }
        if (num1[i] < num2[i])
        {
            num1[i] = char (((num1[i] - '0') + 10) + '0');
            res = char((num1[i] - '0') - (num2[i] - '0') + '0') + res;
            borrow = 1;
        }
        else
        {
            res = char((num1[i] - '0') - (num2[i] - '0') + '0') + res;
        }
    }
    return res;
}

// operator + overloading function.
BigReal BigReal :: operator + (BigReal number2)
{
    BigReal result;
    char signNumber1 = signNumber, signNumber2 = number2.signNumber;
    string int1 = Int, int2 = number2.Int;
    string float1 = Float, float2 = number2.Float;
    BigReal number1 = *this;
    while (int1.length() < int2.length()){
        int1 = '0' + int1;
    }
    while (int2.length() < int1.length()){
        int2 = '0' + int2;
    }
    while (float1.length() < float2.length()){
        float1 += '0';
    }
    while (float2.length() < float1.length()){
        float2 += '0';
    }
    float1 = '*' + float1;
    float2 = '*' + float2;
    if (signNumber1 == signNumber2){
        result.signNumber = signNumber1;
        result.Float = addition(float1, float2);
        result.Int = addition(int1,int2);
        if(result.Float.empty()){
            result.Float = "0";
        }
        if(result.signNumber == '+'){
            result.Whole_number = result.Int + '.' + result.Float;
        }
        else{
            result.Whole_number = result.signNumber + result.Int + '.' + result.Float;
        }
    }
    else{
        if(number1.signNumber == '-'){
            number1.signNumber = '+';
            result = (number2 - number1);
        }
        else{
            number2.signNumber = '+';
            result = (number1 - number2);
        }
    }
    return result;
}

// operator - overloading function.
BigReal BigReal :: operator - (BigReal anotherDec)
{
    BigReal obj;
    string strmin = "", res = "";
    string int1 = Int, int2 = anotherDec.Int;
    string float1 = Float, float2 = anotherDec.Float;
    char sign1 = signNumber, sign2 = anotherDec.signNumber;
    if (int1.length() > int2.length())
    {
        for (long long i = 0; i < int1.length() - int2.length(); i++)
        {
            strmin += '0';
        }
        strmin += int2;
        int2 = strmin;
    }
    else if (int1.length() < int2.length())
    {
        for (long long i = 0; i < int2.length() - int1.length(); i++)
        {
            strmin += '0';
        }
        strmin += int1;
        int1 = strmin;
    }
    if(float1.size() > float2.size()){
        while(float1.size() != float2.size()){
            float2 += '0';
        }
    }
    else{
        while(float1.size() != float2.size()){
            float1 += '0';
        }
    }

    bool ok = false, is_determined = false;
    if (int1 < int2)
    {
        swap(int1, int2);
        swap(float1, float2);
        swap(sign1, sign2);
        ok = true;
    }
    float1 = '*' + float1;
    float2 = '*' + float2;
    if (sign1 == sign2){
        obj.Float = subtraction(float1, float2);
        obj.Int = subtraction(int1,int2);
        if(sign1 == '-'){ok = !ok;}
    }
    else{
        obj.Float = addition(float1,float2);
        obj.Int = addition(int1, int2);
        if(signNumber == '-'){
            obj.signNumber = '-';
            is_determined = true;
        }
        else{
            obj.signNumber = '+';
            is_determined = true;
        }
    }

    for (long long i = 0; i < obj.Int.length(); i++)
    {
        if(obj.Int[i] == '0'){
            obj.Int.erase(i, 1);
            i++;
        }
        else{
            break;
        }
    }
    if (!is_determined && (ok))
    {
        obj.signNumber = '-';
    }
    else if(!is_determined)
    {
        obj.signNumber = '+';
    }
    if(obj.Float.empty()){
        obj.Float = "0";
    }
    if(obj.signNumber == '+'){
        obj.Whole_number = obj.Int + '.' + obj.Float;
    }
    else{
        obj.Whole_number = obj.signNumber + obj.Int + '.' + obj.Float;
    }
    return obj;
}

// function to return the size of number.
int BigReal :: size()
{
    return Int.size() + Float.size();
}

// function returns the sign.
int BigReal :: sign()
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

//function returns the number.
string BigReal:: getNumber(){
    return Whole_number;
}
// operator << overloading function.
ostream &operator << (ostream &out, BigReal num){
    if(num.sign() == 0){
        out << "-" << num.Whole_number << '\n';
        return out;
    }
    else{
        out << num.Whole_number << '\n';
        return out;
    }
}

// check the validation of a number
bool BigReal :: checkValidInput(string input)
{
    int check = 0;
    for (int i = 0; i < input.size(); ++i) {
        if((input[i] == '+' && i == 0) || (input[i] == '-' && i == 0) || (input[i] >= 48 && input[i] <=57) || (input[i] == '.' && check == 0)){
            if(input[i] == '.'){
                check = 1;
            }
            else if(check == 0){
                Int += input[i];
            }
            else {
                Float += input[i];
            }
        }
        else{
            return false;
        }
    }
    return true;
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    BigReal n1 = BigReal(s1);
    BigReal n2 = BigReal(s2);
    cout << (n1 - n2).getNumber();
}

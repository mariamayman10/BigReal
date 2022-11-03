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
    BigDecimalInt &operator=(BigDecimalInt anotherDec);
    BigDecimalInt operator+(BigDecimalInt anotherDec);
    BigDecimalInt operator-(BigDecimalInt anotherDec);
    friend ostream &operator<<(ostream &out, BigDecimalInt num);
    int size();
    int sign();
    void setNumber(string num);
    void setSign(char s);
    string getNumber();
    BigDecimalInt();
    BigDecimalInt(string num);
};
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
    string comp1 = "", comp2 = "";
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
    string comp1 = "", comp2 = "";
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
BigDecimalInt &BigDecimalInt ::operator=(BigDecimalInt anotherDec)
{
    signNumber = anotherDec.signNumber;
    number = anotherDec.number;
    return *this;
}
string addition(string num1, string num2)
{
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
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
        if (!right && result.number[i] == '0')
        {
            result.number.erase(i, 1);
            i--;
        }
    }
    return result;
}
BigDecimalInt BigDecimalInt ::operator-(BigDecimalInt anotherDec)
{
    BigDecimalInt obj;
    deque<long long> d;
    string strmin = "", res = ""; // 1000530 - 0025634
    string num1 = number, num2 = anotherDec.number;
    char sign1 = signNumber, sign2 = anotherDec.signNumber;
    bool ok = false, is_determined = false;
    if (num1 < num2)
    {
        swap(num1, num2);
        swap(sign1, sign2);
        ok = true;
    } // num1=2=100053 , num2=25634
    // res =-974.896

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
        if (!right && res[i] == '0')
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
int BigDecimalInt ::size()
{
    return number.size();
}
int BigDecimalInt ::sign()
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

////////////////////////////////////////////////////////////////////////////////////////
class BigReal
{
private:
    BigDecimalInt Before_point;
    BigDecimalInt After_point;
    int dot_pos;
    char signNumber;
    bool checkValidInput(string input);

public:
    BigReal();
    BigReal(string number);
    BigReal(double realNumber);
    /*BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment*/
    BigReal operator+(BigReal number2);
    BigReal operator-(BigReal anotherDec);
    friend ostream &operator<<(ostream &out, BigReal num);
    friend istream &operator>>(istream &in, BigReal &num);
    bool operator==(BigReal anotherDec);
    bool operator<(BigReal anotherDec);
    bool operator>(BigReal anotherDec);
    int size();
    int sign();
    string getRNumber();
};
BigReal ::BigReal()
{
    Before_point.setNumber("0");
    After_point.setNumber("0");
    signNumber = '+';
}
BigReal ::BigReal(string number)
{
    string Int, Float;
    if (checkValidInput(number))
    {
        if (number[0] == '-')
        {
            signNumber = '-';
            number.erase(0, 1);
        }
        else if (number[0] == '+')
        {
            signNumber = '+';
            number.erase(0, 1);
        }
        else
        {
            signNumber = '+';
        }
        Int = signNumber;
        Float = signNumber;
        int i = 0;
        while (number[i] != '.')
        {
            Int += number[i];
            i++;
        }
        dot_pos = i;
        i++;
        int j = i;
        while (j < number.size())
        {
            Float += number[j];
            j++;
        }
        Before_point.setNumber(Int);
        After_point.setNumber(Float);
    }
    else
    {
        cout << "Invalid, Try again";
        exit(1);
    }
}
bool BigReal ::checkValidInput(string input)
{
    regex validInput("[-+]?[0-9]+.[0-9]+");
    return regex_match(input, validInput);
}
BigReal ::BigReal(double realNumber)
{
    string num;
    num = to_string(realNumber);
    string Int{signNumber}, Float{signNumber};
    if (checkValidInput(num))
    {
        int i = 0;
        while (num[i] != '.')
        {
            Int += num[i];
            i++;
        }
        dot_pos = i;
        i++;
        int j = i;
        while (j < num.size())
        {
            Float += num[j];
        }
        Before_point.setNumber(Int);
        After_point.setNumber(Float);
    }
    else
        cout << "Invalid, Try again";
}
int BigReal ::size()
{
    return Before_point.size() + After_point.size();
}
int BigReal ::sign()
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
string BigReal ::getRNumber()
{
    return signNumber + Before_point.getNumber() + '.' + After_point.getNumber();
}
BigReal BigReal ::operator+(BigReal anotherDec)
{
    BigDecimalInt Whole_Number1, Whole_Number2, res;
    BigReal Final_Result;
    int dot_position = 0;
    string before_dot1, before_dot2, after_dot1, after_dot2;
    after_dot2 = anotherDec.After_point.getNumber();
    after_dot1 = After_point.getNumber();
    before_dot2 = anotherDec.Before_point.getNumber();
    before_dot1 = Before_point.getNumber();
    while (before_dot1.size() > before_dot2.size())
    {
        before_dot2 = "0" + before_dot2;
    }
    while (before_dot1.size() < before_dot2.size())
    {
        before_dot1 = "0" + before_dot1;
    }
    while (after_dot1.size() > after_dot2.size())
    {
        after_dot2 += "0";
    }
    while (after_dot1.size() < after_dot2.size())
    {
        after_dot1 += "0";
    }
    string whole_number1 = signNumber + before_dot1 + after_dot1;
    string whole_number2 = anotherDec.signNumber + before_dot2 + after_dot2;
    Whole_Number1.setNumber(whole_number1);
    Whole_Number2.setNumber(whole_number2);
    Whole_Number1.setSign(signNumber);
    Whole_Number2.setSign(anotherDec.signNumber);
    if (dot_pos > anotherDec.dot_pos)
    {
        dot_position = dot_pos;
    }
    else
    {
        dot_position = anotherDec.dot_pos;
    }
    res = Whole_Number1 + Whole_Number2;
    string FinalResult = res.getNumber();

    ///////////////////////////////
    for (int i = 0; i < ((before_dot1.length() + after_dot1.length()) - res.getNumber().length()); i++)
    {
        FinalResult = "0" + FinalResult;
    }
    //////////////////////////////
    if (FinalResult.size() < Whole_Number1.size())
    {
        dot_position -= (Whole_Number1.size() - FinalResult.size());
    }
    else
    {
        dot_position += (FinalResult.size() - Whole_Number1.size());
    }
    string before_dot = FinalResult.substr(0, dot_position);
    string after_dot = FinalResult.substr((dot_position - 1) + 1);
    for (int i = after_dot.length()-1; i > -1; --i) {
        if(after_dot[i] == '0'){
            after_dot.erase(i, 1);
        }
        else{
            break;
        }
    }
    Final_Result.Before_point = before_dot;
    Final_Result.After_point = after_dot;
    if (res.sign())
    {
        Final_Result.signNumber = '+';
    }
    else
    {
        Final_Result.signNumber = '-';
    }
    return Final_Result;
}
BigReal BigReal ::operator-(BigReal anotherDec)
{
    BigDecimalInt Whole_Number1, Whole_Number2, res;
    BigReal Final_Result;
    int dot_position = 0;
    string before_dot1, before_dot2, after_dot1, after_dot2;
    after_dot2 = anotherDec.After_point.getNumber();
    after_dot1 = After_point.getNumber();
    before_dot2 = anotherDec.Before_point.getNumber();
    before_dot1 = Before_point.getNumber();
    while (before_dot1.size() > before_dot2.size())
    {
        before_dot2 = "0" + before_dot2;
    }
    while (before_dot1.size() < before_dot2.size())
    {
        before_dot1 = "0" + before_dot1;
    }
    while (after_dot1.size() > after_dot2.size())
    {
        after_dot2 += "0";
    }
    while (after_dot1.size() < after_dot2.size())
    {
        after_dot1 += "0";
    }
    string whole_number1 = signNumber + before_dot1 + after_dot1;
    string whole_number2 = anotherDec.signNumber + before_dot2 + after_dot2;
    Whole_Number1.setNumber(whole_number1);
    Whole_Number2.setNumber(whole_number2);
    Whole_Number1.setSign(signNumber);
    Whole_Number2.setSign(anotherDec.signNumber);
    if (dot_pos > anotherDec.dot_pos)
    {
        dot_position = dot_pos;
    }
    else
    {
        dot_position = anotherDec.dot_pos;
    }
    res = Whole_Number1 - Whole_Number2;
    string FinalResult = res.getNumber();
    ///////////////////////////////
    for (int i = 0; i < ((before_dot1.length() + after_dot1.length()) - res.getNumber().length()); i++)
    {
        FinalResult = "0" + FinalResult;
    }
    //////////////////////////////
    if (FinalResult.size() < Whole_Number1.size())
    {
        dot_position -= (Whole_Number1.size() - FinalResult.size());
    }
    else
    {
        dot_position += (FinalResult.size() - Whole_Number1.size());
    }
    string before_dot = FinalResult.substr(0, dot_position);
    string after_dot = FinalResult.substr((dot_position - 1) + 1);
    int check = 0;
    for (int i = 0; i < before_dot.length(); ++i) {
        if(before_dot[i] == '0'){
            check++;
        }
    }
    if(check == before_dot.length()){
        before_dot = "0";
    }
    for (int i = after_dot.length()-1; i > -1; --i) {
        if(after_dot[i] == '0'){
            after_dot.erase(i, 1);
        }
        else{
             break;
        }
    }
    Final_Result.Before_point = before_dot;
    Final_Result.After_point = after_dot;
    if (res.sign())
    {
        Final_Result.signNumber = '+';
    }
    else
    {
        Final_Result.signNumber = '-';
    }
    return Final_Result;
}
ostream &operator<<(ostream &out, BigReal num)
{
    if (num.signNumber == '-')
    {
        out << num.signNumber << num.Before_point.getNumber() << '.' << num.After_point.getNumber() << '\n';
        return out;
    }
    else
    {
        out << num.Before_point.getNumber() << '.' << num.After_point.getNumber() << '\n';
        return out;
    }
}
istream &operator>>(istream &in, BigReal &num)
{
    string temp;
    in >> temp;
    // in.clear();
    // in.sync();
    num = BigReal(temp);
    return in;
}
bool BigReal ::operator<(BigReal anotherDec)
{
    if (Before_point < anotherDec.Before_point)
    {
        return true;
    }
    else if (Before_point == anotherDec.Before_point)
    {
        BigDecimalInt *smallest = &After_point;
        if (anotherDec.After_point.getNumber().length() < After_point.getNumber().length())
        {
            smallest = &anotherDec.After_point;
        }
        int difference = After_point.getNumber().length() - anotherDec.After_point.getNumber().length();
        difference = ((difference < 0) ? difference * -1 : difference);
        for (int i = 0; i < difference; i++)
        {
            smallest->setNumber(smallest->getNumber() + "0");
        }
        After_point.setSign(((Before_point.sign() == 1) ? '+' : '-'));
        anotherDec.After_point.setSign(((anotherDec.Before_point.sign() == 1) ? '+' : '-'));
        return After_point < anotherDec.After_point;
    }
    return false;
}
bool BigReal ::operator>(BigReal anotherDec)
{
    if (Before_point > anotherDec.Before_point)
    {
        return true;
    }
    else if (Before_point == anotherDec.Before_point)
    {
        BigDecimalInt *smallest = &After_point;
        int difference = After_point.getNumber().length() - anotherDec.After_point.getNumber().length();
        if (anotherDec.After_point.getNumber().length() < After_point.getNumber().length())
        {
            smallest = &anotherDec.After_point;
        }
        difference = ((difference < 0) ? difference * -1 : difference);
        for (int i = 0; i < difference; i++)
        {
            smallest->setNumber(smallest->getNumber() + "0");
        }
        After_point.setSign(((Before_point.sign() == 1) ? '+' : '-'));
        anotherDec.After_point.setSign(((anotherDec.Before_point.sign() == 1) ? '+' : '-'));
        return After_point > anotherDec.After_point;
    }
    return false;
}
bool BigReal ::operator==(BigReal anotherDec)
{
    if (Before_point == anotherDec.Before_point && After_point == anotherDec.After_point)
    {
        return true;
    }
    return false;
}

int main()
{
    BigReal a ,b;
    cin>>a >>b;
    cout<<"< test: "<<(a<b);
    cout<<"\n> test: "<<(a>b);
    cout<<"\n+ test: " << (a+b)<<endl;
    cout<<"result : "<< a-b ;
}

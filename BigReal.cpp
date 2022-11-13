#include "BigReal.h"
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
        while (i < number.length())
        {
            if (number[i] == '.')
            {
                break;
            }
            Int += number[i];
            i++;
        }
        dot_pos = i;
        i++;
        if (Int.size() - 1 == number.size())
        {
            Float = "0";
        }
        else
        {
            int j = i;
            while (j < number.size())
            {
                Float += number[j];
                j++;
            }
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
    regex validInput("[-+]?[0-9]+(.[0-9]+)?");
    return regex_match(input, validInput);
}
BigReal ::BigReal(double realNumber)
{
    string number;
    number = to_string(realNumber);
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
        while (i < number.length())
        {
            if (number[i] == '.')
            {
                break;
            }
            Int += number[i];
            i++;
        }
        dot_pos = i;
        i++;
        if (Int.size() - 1 == number.size())
        {
            Float = "0";
        }
        else
        {
            int j = i;
            while (j < number.size())
            {
                Float += number[j];
                j++;
            }
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
BigReal ::BigReal(BigDecimalInt bigInteger)
{
    Before_point.setNumber(bigInteger.getNumber());
    dot_pos = bigInteger.getNumber().size();
    After_point.setNumber("0");
}
BigReal ::BigReal(BigReal &&other) { // moving constructor
    Before_point = other.Before_point;
    After_point = other.After_point;
    dot_pos = Before_point.size();
}
BigReal ::BigReal(const BigReal &other)
{
    Before_point = other.Before_point;
    After_point = other.After_point;
    dot_pos = other.dot_pos;
    signNumber = other.signNumber;
}
BigReal &BigReal::operator=(BigReal other)
{
    Before_point = other.Before_point;
    After_point = other.After_point;
    dot_pos = other.dot_pos;
    signNumber = other.signNumber;
    return *this;
}
BigReal &BigReal::operator=(BigReal &&other){
    this->Before_point = other.Before_point;
    this->After_point = other.After_point;
    return *this;
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
BigReal BigReal ::operator+(BigReal anotherReal)
{
    BigDecimalInt Whole_Number1, Whole_Number2, res;
    BigReal Final_Result;
    int dot_position = 0, c =0;
    string before_dot1, before_dot2, after_dot1, after_dot2;

    before_dot1 = Before_point.getNumber();
    after_dot1 = After_point.getNumber();
    before_dot2 = anotherReal.Before_point.getNumber();
    after_dot2 = anotherReal.After_point.getNumber();

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
    string whole_number2 = anotherReal.signNumber + before_dot2 + after_dot2;
    Whole_Number1.setNumber(whole_number1);
    Whole_Number2.setNumber(whole_number2);
    Whole_Number1.setSign(signNumber);
    Whole_Number2.setSign(anotherReal.signNumber);
    if (dot_pos > anotherReal.dot_pos)
    {
        dot_position = dot_pos;
    }
    else
    {
        dot_position = anotherReal.dot_pos;
    }
    res = Whole_Number1 + Whole_Number2;
    string FinalResult = res.getNumber(), before_dot, after_dot;
    for (int i = 0; i < FinalResult.length(); ++i) {
        if(FinalResult[i] == '0'){
            c++;
        }
    }
    if(c == FinalResult.length()){
        before_dot = "0";
        after_dot = "0";
        dot_position = 1;
    }
    else{
        if (FinalResult.size() < Whole_Number1.size())
        {
            dot_position -= (Whole_Number1.size() - FinalResult.size());
        }
        else
        {
            dot_position += (FinalResult.size() - Whole_Number1.size());
        }
        before_dot = FinalResult.substr(0, dot_position);
        after_dot = FinalResult.substr((dot_position - 1) + 1);
        int check = 0;
        for (char i : before_dot)
        {
            if (i == '0')
            {
                check++;
            }
        }
        if (check == before_dot.length())
        {
            before_dot = "0";
        }
        else
        {
            for (int i = 0; i < before_dot.length(); ++i)
            {
                if (before_dot[i] == '0')
                {
                    before_dot.erase(i, 1);
                    i--;
                }
                else
                {
                    break;
                }
            }
        }
        for (int i = after_dot.length() - 1; i > -1; --i)
        {
            if (after_dot[i] == '0' && after_dot.length() > 1)
            {
                after_dot.erase(i, 1);
            }
            else
            {
                break;
            }
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
BigReal BigReal ::operator-(BigReal anotherReal)
{
    BigDecimalInt Whole_Number1, Whole_Number2, res;
    BigReal Final_Result;
    int dot_position = 0;
    string before_dot1, before_dot2, after_dot1, after_dot2;
    after_dot2 = anotherReal.After_point.getNumber();
    after_dot1 = After_point.getNumber();
    before_dot2 = anotherReal.Before_point.getNumber();
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
    string whole_number2 = anotherReal.signNumber + before_dot2 + after_dot2;
    Whole_Number1.setNumber(whole_number1);
    Whole_Number2.setNumber(whole_number2);
    Whole_Number1.setSign(signNumber);
    Whole_Number2.setSign(anotherReal.signNumber);
    if (dot_pos > anotherReal.dot_pos)
    {
        dot_position = dot_pos;
    }
    else
    {
        dot_position = anotherReal.dot_pos;
    }
    res = Whole_Number1 - Whole_Number2;
    string FinalResult = res.getNumber();
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
    for (char i : before_dot)
    {
        if (i == '0')
        {
            check++;
        }
    }
    if (check == before_dot.length())
    {
        before_dot = "0";
    }
    else
    {
        for (int i = 0; i < before_dot.length(); ++i)
        {
            if (before_dot[i] == '0')
            {
                before_dot.erase(i, 1);
                i--;
            }
            else
            {
                break;
            }
        }
    }
    for (int i = after_dot.length() - 1; i > -1; --i)
    {
        if (after_dot[i] == '0' && after_dot.length() > 1)
        {
            after_dot.erase(i, 1);
        }
        else
        {
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
    string b, a;
    b = num.Before_point.getNumber();a = num.After_point.getNumber();
    while(b[0] == '0' && b.length() > 1){
        b.erase(0, 1);
    }
    while(a[a.length() - 1] == '0' && a.length() > 1){
        a.erase(a.length()-1, 1);
    }
    num.Before_point = b;
    num.After_point = a;
    if (num.signNumber == '-')
    {
        if(num.Before_point.getNumber() == "0" && num.After_point.getNumber() == "0"){
            cout << "0.0" << '\n';
        }
        else{
            if (num.After_point.getNumber().empty())
            {
                num.After_point.setNumber("0");
            }
            out << num.signNumber << num.Before_point.getNumber() << '.' << num.After_point.getNumber() << '\n';
        }
        return out;
    }
    else
    {
        if (num.After_point.getNumber().empty())
        {
            num.After_point.setNumber("0");
        }
        out << num.Before_point.getNumber() << '.' << num.After_point.getNumber() << '\n';
        return out;
    }
}
istream &operator>>(istream &in, BigReal &num)
{
    string temp;
    in >> temp;
    string Int, Float;
    if (num.checkValidInput(temp))
    {
        if (temp[0] == '-')
        {
            num.signNumber = '-';
            temp.erase(0, 1);
        }
        else if (temp[0] == '+')
        {
            num.signNumber = '+';
            temp.erase(0, 1);
        }
        else
        {
            num.signNumber = '+';
        }
        Int = num.signNumber;
        Float = num.signNumber;
        int i = 0;
        while (i < temp.length())
        {
            if (temp[i] == '.')
            {
                break;
            }
            Int += temp[i];
            i++;
        }
        num.dot_pos = i;
        i++;
        if (Int.size() - 1 == temp.size())
        {
            Float = "0";
        }
        else
        {
            int j = i;
            while (j < temp.size())
            {
                Float += temp[j];
                j++;
            }
        }
        num.Before_point.setNumber(Int);
        num.After_point.setNumber(Float);
    }
    else
    {
        cout << "Invalid, Try again";
        exit(1);
    }
    return in;
}
bool BigReal ::operator<(BigReal anotherReal)
{

    if (Before_point < anotherReal.Before_point)
    {
        return true;
    }
    else if (Before_point == anotherReal.Before_point)
    {
        BigDecimalInt *smallest = &After_point;
        if (anotherReal.After_point.getNumber().length() < After_point.getNumber().length())
        {
            smallest = &anotherReal.After_point;
        }
        int difference = After_point.getNumber().length() - anotherReal.After_point.getNumber().length();
        difference = ((difference < 0) ? difference * -1 : difference);
        for (int i = 0; i < difference; i++)
        {
            smallest->setNumber(smallest->getNumber() + "0");
        }
        After_point.setSign(((Before_point.sign() == 1) ? '+' : '-'));
        anotherReal.After_point.setSign(((anotherReal.Before_point.sign() == 1) ? '+' : '-'));
        return After_point < anotherReal.After_point;
    }
    return false;
}
bool BigReal ::operator>(BigReal anotherReal)
{
    if (Before_point > anotherReal.Before_point)
    {
        return true;
    }
    else if (Before_point == anotherReal.Before_point)
    {
        BigDecimalInt *smallest = &After_point;
        int difference = After_point.getNumber().length() - anotherReal.After_point.getNumber().length();
        if (anotherReal.After_point.getNumber().length() < After_point.getNumber().length())
        {
            smallest = &anotherReal.After_point;
        }
        difference = ((difference < 0) ? difference * -1 : difference);
        for (int i = 0; i < difference; i++)
        {
            smallest->setNumber(smallest->getNumber() + "0");
        }
        After_point.setSign(((Before_point.sign() == 1) ? '+' : '-'));
        anotherReal.After_point.setSign(((anotherReal.Before_point.sign() == 1) ? '+' : '-'));
        return After_point > anotherReal.After_point;
    }
    return false;
}
bool BigReal ::operator==(BigReal anotherReal)
{
    string b, b2, a, a2;

    b = Before_point.getNumber();a = After_point.getNumber();
    while(b[0] == '0' && b.length() > 1){
        b.erase(0, 1);
    }
    while(a[a.length() - 1] == '0' && a.length() > 1){
        a.erase(a.length()-1, 1);
    }
    Before_point = b;
    After_point = a;

    b2 = anotherReal.Before_point.getNumber();a2 = anotherReal.After_point.getNumber();
    while(b2[0] == '0' && b2.length() > 1){
        b2.erase(0, 1);
    }
    while(a2[a2.length() - 1] == '0' && a2.length() > 1){
        a2.erase(a2.length()-1, 1);
    }
    anotherReal.Before_point = b2;
    anotherReal.After_point = a2;

    if (Before_point == anotherReal.Before_point && After_point == anotherReal.After_point)
    {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////

int MenuSystem(){
    cout << "The program provide the following processes:\n1-Subtract two numbers\n2-Add two numbers\n"
            "3-Check if the first number is greater than the second number\n4-Check if the first number is less than the second number\n"
            "5-Check if the two numbers are equal\n6-Assign empty number with another number\n7-Get the size of a number\n"
            "8-Get the sign of a number\n9-Get the number\n10-EXIT\n\n";
    string choice;
    int choice_int;
    cout << "Your choice is: ";
    cin >> choice;
    while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6"
          && choice != "7" && choice != "8" && choice != "9" && choice != "10"){
        cout << "Invalid Input, Try again\nYour choice is: ";
        cin >> choice;
    }
    cout << '\n';
    choice_int = stoi(choice);
    return choice_int;
}
int options(int choice){
    if(choice == 1){
        BigReal num1, num2;
        cout << "Enter the first number: ";
        cin >> num1;
        cout << "\nEnter the second number: ";
        cin >> num2;
        cout << "\nThe result of subtraction is " << num1 - num2 << "\n\n";
    }
    else if(choice == 2){
        BigReal num1, num2;
        cout << "Enter the first number: ";
        cin >> num1;
        cout << "\nEnter the second number: ";
        cin >> num2;
        cout << "\nThe result of addition is " << num1 + num2 << "\n";
    }
    else if(choice == 3){
        BigReal num1, num2;
        bool ans;
        cout << "Enter the first number: ";
        cin >> num1;
        cout << "\nEnter the second number: ";
        cin >> num2;
        ans = num1 > num2;
        if(ans)cout << "\nThe first number is greater than the second number\n\n";
        else cout << "\nThe first number isn't greater than the second number\n\n";
    }
    else if(choice == 4){
        BigReal num1, num2;
        bool ans;
        cout << "Enter the first number: ";
        cin >> num1;
        cout << "\nEnter the second number: ";
        cin >> num2;
        ans = num1 < num2;
        if(ans)cout << "\nThe first number is less than the second number\n\n";
        else cout << "\nThe first number isn't less than the second number\n\n";
    }
    else if(choice == 5){
        BigReal num1, num2;
        bool ans;
        cout << "Enter the first number: ";
        cin >> num1;
        cout << "\nEnter the second number: ";
        cin >> num2;
        ans = num1 == num2;
        if(ans)cout << "\nThe numbers are equal\n\n";
        else cout << "\nThe numbers aren't equal\n\n";
    }
    else if(choice == 6){
        BigReal num1, num2;
        cout << "Enter a number: ";
        cin >> num1;
        cout << "\nBefore assigning value in the variable n2 it equals to " << num2 << '\n';
        num2 = num1;
        cout << "After assigning value in the variable n2 it equals to " << num2 << '\n';
    }
    else if(choice == 7){
        BigReal num1;
        cout << "Enter a number: ";
        cin >> num1;
        cout << "\nThe size of the number equals to = " << num1.size() << "\n\n";
    }
    else if(choice == 8){
        BigReal num1;
        cout << "Enter a number: ";
        cin >> num1;
        int s = num1.sign();
        if(s == 1){
            cout << "\nThe number is positive" << "\n\n";
        }
        else{
            cout << "\nThe number is negative" << "\n\n";
        }
    }
    else if(choice == 9){
        BigReal num1;
        cout << "Enter a number: ";
        cin >> num1;
        cout << "\nYour number is " << num1 << '\n';
    }
    else{
        cout << "\n____________Thanks for using our Program____________\n";
    }
}

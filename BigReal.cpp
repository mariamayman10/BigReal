#include "BigReal.h"
#include "BigDecimalInt.h"

BigReal :: BigReal()
{
    Before_point.setNumber("0");
    After_point.setNumber("0");
    signNumber = '+';
    dot_pos = 1;
}
BigReal :: BigReal(string number)
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
bool BigReal :: checkValidInput(string input)
{
    regex validInput("[-+]?[0-9]+(.[0-9]+)?");
    return regex_match(input, validInput);
}
BigReal :: BigReal(double realNumber)
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
BigReal :: BigReal(BigDecimalInt bigInteger)
{
    Before_point.setNumber(bigInteger.getNumber());
    dot_pos = bigInteger.getNumber().size();
    After_point.setNumber("0");
    if(bigInteger.sign() == 1){
        signNumber = '+';
    }
    else{
        signNumber = '-';
    }
}
BigReal :: BigReal(BigReal &&other) { // moving constructor
    Before_point = other.Before_point;
    After_point = other.After_point;
    dot_pos = Before_point.size();
    signNumber = other.signNumber;
}
BigReal :: BigReal(const BigReal &other)
{
    Before_point = other.Before_point;
    After_point = other.After_point;
    dot_pos = other.dot_pos;
    signNumber = other.signNumber;
}
BigReal &BigReal :: operator=(BigReal other)
{
    Before_point = other.Before_point;
    After_point = other.After_point;
    dot_pos = other.dot_pos;
    signNumber = other.signNumber;
    return *this;
}
BigReal &BigReal :: operator=(BigReal &&other){
    this->Before_point = other.Before_point;
    this->After_point = other.After_point;
    this->signNumber = other.signNumber;
    this->dot_pos = other.dot_pos;
    return *this;
}
int BigReal :: size()
{
    return Before_point.size() + After_point.size();
}
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
string BigReal :: getRNumber()
{
    return signNumber + Before_point.getNumber() + '.' + After_point.getNumber();
}
BigReal BigReal :: operator+(BigReal anotherReal)
{
    BigDecimalInt Whole_Number1, Whole_Number2, res;
    BigReal Final_Result;
    int dot_position = 0, c = 0;
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
BigReal BigReal :: operator-(BigReal anotherReal)
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
bool BigReal :: operator<(BigReal anotherReal)
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
bool BigReal :: operator>(BigReal anotherReal)
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
bool BigReal :: operator==(BigReal anotherReal)
{
    string b1, b2,a1,a2;
    b1 = Before_point.getNumber();b2 = anotherReal.Before_point.getNumber();
    a1 = After_point.getNumber();a2 = anotherReal.After_point.getNumber();
    while(b1[0] == '0' && b1.length() > 1){
        b1.erase(0, 1);
    }
    while(b2[0] == '0' && b2.length() > 1){
        b2.erase(0, 1);
    }
    while(a1[a1.length()-1] == '0' && a1.length() > 1){
        a1.erase(0, 1);
    }
    while(a2[a2.length()-1] == '0' && a2.length() > 1){
        a2.erase(0, 1);
    }
    Before_point.setNumber(b1);
    anotherReal.Before_point.setNumber(b2);
    After_point.setNumber(a1);
    anotherReal.After_point.setNumber(a2);
    if (Before_point == anotherReal.Before_point && After_point == anotherReal.After_point)
    {
        return true;
    }
    return false;
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
    return 0;
}

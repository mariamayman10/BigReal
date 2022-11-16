#include "BigReal.h"
#include "BigDecimalInt.h"
#include <iostream>
using namespace std;

int main(){
    cout << "________Welcome to BigReal Program________\n";
    int option = MenuSystem();
    while(option != 10) {
        options(option);
        option = MenuSystem();
    }
    options(10);
    return 0;
}


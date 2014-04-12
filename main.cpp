#include <iostream>
#include <vector>
#include <utility>
#include"fractions.cpp"
#include"dict.hpp"


using namespace std;

int main()
{
    Fraction f1(4,1);
    Fraction f2(5,7);
    Fraction f3(-6,-14);

    f1.Fraction::printFraction();
    cout << endl;
    f2.Fraction::printFraction();
    cout << endl;
    f3.Fraction::printFraction();
    cout << endl;

    f1.Fraction::oppose();
    f1.Fraction::printFraction();
    cout << endl;

    f3.Fraction::reduction();
    f3.Fraction::printFraction();
    cout << endl;

    f2.Fraction::div(f3);
    f2.Fraction::printFraction();
    f3.Fraction::printFraction();
    cout << endl;

    f3.Fraction::soustraction(f2);
    f2.Fraction::printFraction();
    f3.Fraction::printFraction();
    cout << endl;

    cout << endl << endl;

    cout << "Hello world!" << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include"dict.hpp"
#include"linearProg.hpp"


using namespace std;

int main()
{
    Lp programme(2,3);

    vector<Fraction> vect1;
    vect1.push_back(Fraction(-1));
    vect1.push_back(Fraction(1));
    vect1.push_back(Fraction(-1));
    vector<Fraction> vect2;
    vect2.push_back(Fraction(-3));
    vect2.push_back(Fraction(-1));
    vect2.push_back(Fraction(-1));
    vector<Fraction> vect3;
    vect3.push_back(Fraction(4));
    vect3.push_back(Fraction(2));
    vect3.push_back(Fraction(1));

    (programme.coeffs).push_back(vect1);
    (programme.coeffs).push_back(vect2);
    (programme.coeffs).push_back(vect3);

    (programme.objectif).push_back(Fraction());
    (programme.objectif).push_back(Fraction(3));
    (programme.objectif).push_back(Fraction(1));

    programme.printLp();

    Dict dicoFinal = programme.simplex();


    cout << "Hello world!" << endl;
    return 0;
}

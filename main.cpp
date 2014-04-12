#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include"dict.hpp"


using namespace std;

int main()
{
    Dict dico(4);

    vector<Fraction> vect1;
    vect1.push_back(Fraction(4));
    vect1.push_back(Fraction(2));
    vect1.push_back(Fraction(1,4));
    vect1.push_back(Fraction());
    vect1.push_back(Fraction());
    vector<Fraction> vect2;
    vect2.push_back(Fraction(3,2));
    vect2.push_back(Fraction(2,4));
    vect2.push_back(Fraction(1));
    vect2.push_back(Fraction());
    vect2.push_back(Fraction());
    vector<Fraction> vect3;
    vect3.push_back(Fraction(5,4));
    vect3.push_back(Fraction(3));
    vect3.push_back(Fraction(1,4));
    vect3.push_back(Fraction());
    vect3.push_back(Fraction());

    cout << "coucou, "; (dico.coeffs)[0][0].printFraction();

    cerr << "coucou1 " << endl;

    dico.setBasicVar(3, vect1);

    cerr << "coucou2 " << endl;

    dico.setBasicVar(4,vect2);

    cerr << "coucou3 " << endl;
    dico.setObjectif(vect3);

    cerr << "coucou4 " << endl;

    dico.printDict();


    cout << "Hello world!" << endl;
    return 0;
}

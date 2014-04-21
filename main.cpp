#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include"dict.hpp"
#include"linearProg.hpp"
#include "parser.hpp"


using namespace std;

/*int main()
{
    Lp programme(2,3, true, false);

    vector<Fraction> vect1;
    vect1.push_back(Fraction(1));
    vect1.push_back(Fraction(1));
    vect1.push_back(Fraction(-1));
    vector<Fraction> vect2;
    vect2.push_back(Fraction(3));
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
    (programme.objectif).push_back(Fraction(1));
    (programme.objectif).push_back(Fraction(2));


    Dict dicoFinal = programme.simplex();

    return 0;
}*/

int main()
{
    ParserFich fichier("../dmOptim/toto.txt");
    Lp linearProg(0,0);

    /*char toto = (fichier.entree).peek();
    cout << "coucou, toto = " << toto << endl;

    string toto1;
    fichier.entree >> toto1;
    cout << "toto1 = " << toto1 << endl;

    int titi;
    fichier.entree >> titi;
    cout << "titi = " << titi << endl;
    for (int i = 0; i < 5; i++)
    {
        Fraction tutu = fichier.lireFrac();
        cout << "fraction = ";
        tutu.printFraction();
        cout << endl;
    }*/

    fichier.lireObj(linearProg);
    linearProg.printLp();
    fichier.lireContraintes(linearProg);

    cout << "nb de variables : " << linearProg.nbVar << endl;
    linearProg.printLp();

    return 0;

}

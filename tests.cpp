#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include"dict.hpp"
#include"linearProg.hpp"
#include "parser.hpp"


using namespace std;

const coeffMax = 10;

int test(int var, int contraintes)
{
    Lp linearProg(var,contraintes, false, true);
    linearProg.randomLp(coeffMax);
    linearProg.printLp();

    Dict dicoFinal = linearProg.simplex();

    return dicoFinal.nbPivots;

}

Fraction plusieursTests(int nbTests, int var, int contraintes)
{
    int totalPivots = 0;
    for (int i = 0; i < nbTests; i++)
    {
        totalPivots += test(var, contraintes);
    }

    return Fraction(totalPivots, nbTests);
}

void totalTests()
{
    srand(time(NULL)); //TODO initialiser srand
    for (int var = 5; var <= 50; var += 5)
    {
        for (int contraintes = 5; contraintes <= 5; contraintes += 5)
        {
            Fraction tmp = plusieursTests(10, var, contraintes);
            tmp.reduction();
            cout << "Pour " << var << " variables et " << contraintes << " contraintes, nb moyen de pivots = ";
            tmp.printFraction();
            cout << endl;
        }
    }
}

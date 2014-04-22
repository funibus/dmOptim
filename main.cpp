#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include"dict.hpp"
#include"linearProg.hpp"
#include "parser.hpp"
#include "tests.hpp"


using namespace std;


int main()
{
    ParserFich fichier("../dmOptim/tutu");

    Lp linearProg(0,0);
    fichier.lireObj(linearProg);
    fichier.lireContraintes(linearProg);
    linearProg.printLp();

    Dict difoFinal = linearProg.simplex();

    return 0;

}

/*int main()
{
    totalTests();
    return 0;
}*/

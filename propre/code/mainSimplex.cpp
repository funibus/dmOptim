#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include"dict.hpp"
#include"linearProg.hpp"
#include "parser.hpp"


using namespace std;


int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		cerr << endl << "attention, le programme prend 2 arguments : le nom du fichier ou est  le probleme et \"max\"/\"Bland\" pour le choix des variables entrantes" << endl << endl;
		exit(1);
	}
	char* nomFichier = argv[1];
	char* regle = argv[2];
    ParserFich fichier(nomFichier);

    Lp linearProg(0,0, true, true);
    if (regle[0] == 'm')
    	linearProg.regleBland = false;
    	
    fichier.lireObj(linearProg);
    fichier.lireContraintes(linearProg);

    Dict dicoFinal = linearProg.simplex();

    return 0;

}


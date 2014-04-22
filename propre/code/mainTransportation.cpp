#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include"dict.hpp"
#include"linearProg.hpp"
#include "parser.hpp"
#include "tests.hpp"
#include "transportation.hpp"


using namespace std;


int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		cerr << endl << "attention, le programme prend 2 arguments : le nom du fichier avec la matrice de couts (cf exemple pour le format), et \"affichage\"/\"pasAffichage\" si on veut afficher les etapes intermediaires du simplex ou pas" << endl << endl;
		exit(1);
	}
	char* nomFichier = argv[1];
	char* affichage = argv[2];
    ParserFich fichier(nomFichier);

    Transportation transpo(0,0);
    fichier.parseTranspo(transpo);

	if (affichage[0] != 'p')
    	transpo.printTranspo();

    Lp linearProg(0,0);
    if (affichage[0] == 'p')
    	linearProg.affichage = false;
    transpo.transpToLp(linearProg);
    Dict dico = linearProg.simplex();
    transpo.solutionTranspo(dico);

    return 0;

}

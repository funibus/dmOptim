#ifndef LINEARPROG_HPP_INCLUDED
#define LINEARPROG_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include "dict.hpp"

//TODO include le bon truc

class Lp
{
    public:

        int nbVar; //nombre de variables
        int nbContraintes;
        vector< vector<Fraction> > coeffs; //coeff[i][j] contient le coeff de xj dans la ieme contrainte, et coeff[i][0] = bi
        vector<Fraction> objectif; //contient les coefficients de la fonction objectif

        bool affichage;
        bool regleBland;

        Lp() {
            nbVar = 0;
            nbContraintes = 0;
            affichage = true;
            regleBland = true;
        }

        Lp(int var = 0, int contraintes = 0, bool aff = true, bool regle = true) {
            nbVar = var;
            nbContraintes = contraintes;
            affichage = aff;
            regleBland = regle;
        }

        void dictFromLp1Phase(Dict & dico);
        void dictFromLp2Phase(Dict & dico);
        bool besoinPremierePhase();

        void printLp();

        Dict simplex();

        void certifVide(Dict dico); //prend un dico final qui prouve que c'est vide
        void certifOpt(Dict dico); //prend le dico final
        void certifNonBorne(Dict dico, int nonBorne); //prend un dico final, et une variable non bornee

        void randomLp(int maxCoeff);//demande un Lp avec deja nbVar et nbContraintes renplis

};


#endif // LINEARPROG_HPP_INCLUDED

#ifndef LINEARPROG_HPP_INCLUDED
#define LINEARPROG_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"
#include "dict.hpp"

class Lp
{
    public:

        int nbVar; //nombre de variables
        int nbContraintes;
        vector< vector<Fraction> > coeffs; //coeff[i][j] contient le coeff de xj dans la ieme contrainte, et coeff[i][0] = bi
        vector<Fraction> objectif; //contient les coefficients de la fonction objectif

        Lp() {
            nbVar = 0;
            nbContraintes = 0;
        }

        Lp(int var, int contraintes) {
            nbVar = var;
            nbContraintes = contraintes;
        }

        void dictFromLp1Phase(Dict & dico);
        void dictFromLp2Phase(Dict & dico);
        bool besoinPremierePhase();

        void printLp();

        Dict simplex();

};


#endif // LINEARPROG_HPP_INCLUDED

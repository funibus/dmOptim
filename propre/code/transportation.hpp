#ifndef TRANSPORTATION_HPP_INCLUDED
#define TRANSPORTATION_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <utility>
#include "linearProg.hpp"

using namespace std;

class Transportation
{
    public:
        int nbProd, nbDist;
        vector<vector<int> > matCout; //matCout[i][j] c'est le cout pour envoyer une unite de la prod i à la dist j
        vector<int> capaProd;
        vector<int> objDist;

        Transportation(int N1, int N2)
        {
            nbProd = N1;
            nbDist = N2;
        }

        void transpToLp( Lp & linearProg); //prend un Lp vide en entree
        void solutionTranspo(Dict & dicoFinal);

        void printTranspo();

};

#endif // TRANSPORTATION_HPP_INCLUDED

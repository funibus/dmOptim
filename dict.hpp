#ifndef DICT_HPP_INCLUDED
#define DICT_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <utility>
#include"fractions.hpp"

using namespace std;

class Dict
{
    public:

        int nbVariables; //nombre de variables, sans compter la fonction objectif
        vector<bool> basic; //basic[i] = true ssi xi est à gauche dans le dictionnaire
        //on met le coeff constant en 0
        vector< vector<Fraction> > coeffs; //si basic[i] = true, le vecteur i contient les coeffs des variables dans l'equation xi = ...
        vector<Fraction> objectif; //contient les coefficients de la fonction objectif

        Dict(int n) {
            nbVariables = n;
            //TODO initialiser les vecteurs avec des false et des 0

        }

        void setBasicVar(int i, vector<Fraction> const & vect);
        void setNonBasic(int i);
        void setObjectif(vector<Fraction> const & vect);

        void petitPivot(int basi, int nonBasi); //echange dans ligne du pivot la variable basic et la non basic

        void printDict();

};




#endif // DICT_HPP_INCLUDED

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

        bool affichage; //mettre affichage a false si on ne veut pas d'affichage
        int nbPivots;
        bool regleBland; //mettre a false si on veut utiliser la regle du max

        Dict(int n, bool aff = true, bool regle = true) {
            nbVariables = n;
            affichage = aff;
            regleBland = regle;
            nbPivots = 0;

            for (int k = 0; k <=n; k++)
            {
                basic.push_back(false);
                vector<Fraction> tmp (n+1, Fraction());
                coeffs.push_back(tmp);
                objectif.push_back(Fraction());
            }

        }

        void setBasicVar(int i, vector<Fraction> const & vect);
        void setNonBasic(int i);
        void setObjectif(vector<Fraction> const & vect);

        void petitPivot(int basi, int nonBasi); //echange dans ligne du pivot la variable basic et la non basic
        void remplaceVar(int var1, int var2); //remplace var2 par son expression dans l'expression de var1
        void remplaceVarObj(int var2);

        void grosPivot(int varSortante, int varEntrante);

        int choixEntranteBland(); //renvoie -1 si pas de variables entrante possible
        int choixSortanteBland(int entrante); //-1 si pas de variables sortantes
        int choixEntranteMax();

        int petitSimplex1Phase(); //renvoie -1 s'il y a une sol opt, le numero de la variable qui peut augmenter sinon

        void premierePhase();

        void printDict();

};




#endif // DICT_HPP_INCLUDED

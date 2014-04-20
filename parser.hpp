#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include<fstream>
#include"fractions.hpp"
#include"linearProg.hpp"

using namespace std;

class ParserFich
{
    public:

        char* nomFichier;
        ifstream entree;
        vector<string> listeVar;

        ParserFich(char* nom)
        {
            nomFichier = nom;
            entree.open(nomFichier, ios::in);
            if (!entree)
                cerr << "attention, ouverture de " << nomFichier << " ratee" << endl;
        }

        int trouverVar(string s); //renvoie la position de s dans variables, -1 s'il y est pas
        char caractSuivant();
        Fraction lireFrac(char &carSuiv);
        void lireObj(Lp & linearProg);
        void lireContraintes(Lp & linearProg);

};




#endif // PARSER_HPP_INCLUDED

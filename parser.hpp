#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include<fstream>
#include"fractions.hpp"
#include"linearProg.hpp"

using namespace std;

int nouvelleVar(string s, vector<string> & variables); //renvoie la position de s dans variables, -1 s'il y est pas
char caractSuivant(ifstream &entree);
Fraction lireFrac(ifstream &entree, char &carSuiv);

void lireObj(ifstream &entree, vector<Fraction> & obj, vector<string> & listVar);

#endif // PARSER_HPP_INCLUDED

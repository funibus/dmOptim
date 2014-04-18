#include "parser.hpp"

int trouverVar(string s, vector<string> & variables)
{
    for (int i = 0; i < variables.size(); i++)
    {
        if (s == variables[i])
            return i;
    }
    return -1;
}

char caractSuivant(ifstream & entree) //ignore juste les blancs, pas les retours a la ligne
{
    char c;
    entree >> c;
    while (c == ' ')
        entree.get(c);
    return c;
}

Fraction lireFrac(ifstream &entree, char & carSuiv) //renvoie dans carSuiv le caractere suivant (+, < ou \n normalement)
{
    int num, denom = 1;

    entree >> num;
    char c = caractSuivant(entree);
    if (c == '/')
    {
        entree >> denom;
        c = caractSuivant(entree);
    }

    carSuiv = c;
    return Fraction(num, denom);
}


void lireObj(ifstream &entree, Lp & linearProg, vector<string> & listVar) //obj et listVar sont vides au debut
{
    string s;
    entree >> s;
    if (s != "max:")
        cerr << "attention, l'objectif n'est pas un max, je fais comme si c'en etait un" << endl;
    char carSuiv = 'a';
    while (carSuiv != '\n' && carSuiv != EOF)
    {
        Fraction tmp = lireFrac(entree, carSuiv);
        if (carSuiv == '-') //on avait un - avant la fraction
            tmp.oppose();
        string var;
        entree >> var;
        int pos = trouverVar(var, listVar);
        if (pos == -1)
        {
            listVar.push_back(var);
            (linearProg.objectif).push_back(tmp);
            linearProg.nbVar++;
        }
        else
        {
            cerr << "attention, il y a quelque chose de bizarre dans le parsage de l'objectif" << endl;
            if (listVar.size() <= (linearProg.objectif).size())
                (linearProg.objectif)[pos].add(tmp);
        }

        carSuiv = caractSuivant(entree);
    }
}

void lireContraintes(ifstream &entree, Lp & linearProg, vector<string> & listVar)
{
    char carSuiv = 'a';
    while (carSuiv != EOF)
    {
        while (carSuiv != '\n')
        {

        }
    }
}

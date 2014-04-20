#include "parser.hpp"

int ParserFich::trouverVar(string s)
{
    for (int i = 0; i < listeVar.size(); i++)
    {
        if (s == listeVar[i])
            return i;
    }
    return -1;
}

char ParserFich::caractSuivant() //ignore juste les blancs, pas les retours a la ligne
{
    char c;
    entree.get(c);
    //cout << "coucou je suis dans la fonction" << endl;
    while (c == ' ')
    {
        //cout << "coucou, je viens de voir un blanc" << endl;
        //if (c == '\n')
            //cout << "c++ il fait n'importe quoi" << endl;
        //if (c == ' ')
            //cout << "coucou, je lis un blanc" << endl;
        entree.get(c);
    }
    return c;
}

Fraction ParserFich::lireFrac(char & carSuiv) //renvoie dans carSuiv le caractere suivant (+, < ou \n normalement)
{
    int num, denom = 1;

    entree >> num;
    char c = this->caractSuivant();
    if (c == '/')
    {
        entree >> denom;
        c = this->caractSuivant();
    }

    carSuiv = c;
    return Fraction(num, denom);
}


void ParserFich::lireObj(Lp & linearProg) //obj et listVar sont vides au debut
{
    string s;
    entree >> s;
    if (s != "max:")
        cerr << "attention, l'objectif n'est pas un max, je fais comme si c'en etait un" << endl;
    char carSuiv = 'a';
    bool prem = true; //gerer le cas ou il y a un coeff constant dans la fonction obj ou pas
    while (carSuiv != '\n' && carSuiv != EOF)
    {
        Fraction tmp = this->lireFrac(carSuiv);
        if (carSuiv == '-') //on avait un - avant la fraction
            tmp.oppose();
        if (prem)
        {
            cout << "coucou, caract suivant == " << carSuiv << endl;
            if (carSuiv != '+' && carSuiv != '-') //pas de coeff constant
                (linearProg.objectif).push_back(Fraction ());
            else //coeff constant
            {
                (linearProg.objectif).push_back(tmp);
                tmp.copie(this->lireFrac(carSuiv) );
            }
            prem = false;
        }
        cout << "coucou, carSuiv = " << carSuiv << endl;
        entree.seekg(-2, ios::cur);
        string var;
        entree >> var;
        int pos = this->trouverVar(var);
        if (pos == -1)
        {
            cout << "nouvelle var : " << var << endl;
            listeVar.push_back(var);
            (linearProg.objectif).push_back(tmp);
            linearProg.nbVar++;
        }
        else
        {
            cerr << "attention, il y a quelque chose de bizarre dans le parsage de l'objectif" << endl;
            if (listeVar.size() <= (linearProg.objectif).size())
                (linearProg.objectif)[pos].add(tmp);
        }

        carSuiv = this->caractSuivant();
    }
}

void ParserFich::lireContraintes(Lp & linearProg)
{
    char carSuiv = 'a';
    while (carSuiv != EOF)
    {
        while (carSuiv != '\n')
        {

        }
    }
}

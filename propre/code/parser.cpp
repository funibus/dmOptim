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

char ParserFich::caractSuivant() //ignore juste les blancs, pas les retours a la ligne, deplace le curseur juste avant le carac
{
    char pasDeplace, deplace;
    pasDeplace = entree.peek();
    while (pasDeplace == ' ')
    {
        entree.get(deplace);
        pasDeplace = entree.peek();
    }
    return pasDeplace;
}

char ParserFich::caractSuivantPasEntree() //ignore juste les blancs et les retour a la ligne
{
    char pasDeplace, deplace;
    pasDeplace = entree.peek();
    while (pasDeplace == ' ' || pasDeplace == '\n')
    {
        entree.get(deplace);
        pasDeplace = entree.peek();
    }
    return pasDeplace;
}

Fraction ParserFich::lireFrac() //renvoie dans carSuiv le caractere suivant (+, < ou \n normalement)
{
    int num = 1, denom = 1;
    char c = this->caractSuivantPasEntree();

    //si pas de coefficient, c'est un 1 sous entendu
    if (c == '0' || c == '1' || c == '2' ||c == '3' ||c == '4' ||c == '5' ||c == '6' ||c == '7' ||c == '8' ||c == '9' || c == '+' || c == '-')
    {
        entree >> num;

        if (c == '/')
        {
            entree >> c;
            entree >> denom;
        }
    }

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
        char c = caractSuivant();
        if (c == '+' || c == '-')
            entree >> c;
        Fraction tmp = this->lireFrac();
        if (c == '-')
            tmp.oppose();
        carSuiv = this->caractSuivant();
        if (prem)
        {
            if (carSuiv != '+' && carSuiv != '-') //pas de coeff constant
                (linearProg.objectif).push_back(Fraction ());
            else //coeff constant
            {
                (linearProg.objectif).push_back(tmp);
                c = caractSuivant();
                entree >> c;
                tmp.copie(this->lireFrac() );
                if (c == '-')
                    tmp.oppose();
            }
            prem = false;
        }
        string var;
        entree >> var;
        int pos = this->trouverVar(var);
        if (pos == -1)
        {
            listeVar.push_back(var);
            (linearProg.objectif).push_back(tmp);
            linearProg.nbVar++;
        }
        else
        {
            cerr << "attention, il y a plusieurs variables identiques dans l'objectif" << endl;
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
        vector<Fraction> tmpVect(listeVar.size()+1);
        while (carSuiv != '<' && carSuiv != EOF)
        {
            char c = caractSuivant();
            if (c == '+' || c == '-')
                entree >> c;
            Fraction tmp = this->lireFrac();
            if (c == '-')
                tmp.oppose();

            string var;
            entree >> var;

            int pos = trouverVar(var);

            if (pos == -1) //nouvelle variable, on suppose que nbVar = listeVar.size()
            {
                listeVar.push_back(var);
                linearProg.nbVar++;
                tmpVect.push_back(tmp);
            }
            else
            {
                tmpVect[pos+1].add(tmp);
            }

            carSuiv = this->caractSuivant();
        }
        entree >> carSuiv;
        if (carSuiv != '<')
            cerr << "attention, la contrainte " << linearProg.nbContraintes+1 << " n'est pas de la bonne forme" << endl;
        entree >> carSuiv;
        if (carSuiv != '=')
            cerr << "attention, la contrainte " << linearProg.nbContraintes+1 << " n'est pas de la bonne forme" << endl;

        tmpVect[0].copie(this->lireFrac());
        (linearProg.coeffs).push_back(tmpVect);
        linearProg.nbContraintes++;

        carSuiv = this->caractSuivantPasEntree();
    }

    //on complete les vecteurs avec les variables qu'on n'avait pas encore vu
    for (int i = 0; i < linearProg.nbContraintes; i++)
    {
        for (int j = (linearProg.coeffs[i]).size(); j <= linearProg.nbVar; j++)
            (linearProg.coeffs[i]).push_back(Fraction ());
    }
    for (int j = (linearProg.objectif).size(); j <= linearProg.nbVar; j++)
        (linearProg.objectif).push_back(Fraction ());
}

void ParserFich::parseTranspo( Transportation & transpo)
{
    int N1,N2;
    entree >> N1 >> N2;
    transpo.nbProd = N1;
    transpo.nbDist = N2;

    for (int i = 0; i < transpo.nbProd; i++)
    {
        vector<int> lignei;
        for (int j = 0; j < transpo.nbDist; j++)
        {
            int tmpInt;
            entree >> tmpInt;
            lignei.push_back(tmpInt);
        }
        (transpo.matCout).push_back(lignei);
    }

    string toto;

    //lecture des capacites des sites de production
    entree >> toto;
    if (toto != "production:")
        cerr << "attention, probleme de parsage, capacites des sites de production pas reconnues" << endl;
    for (int i = 0; i < transpo.nbProd; i++)
    {
        int capa;
        entree >> capa;
        (transpo.capaProd).push_back(capa);
    }

    //lecture des capacites des sites de distribution
    entree >> toto;
    if (toto != "distribution:")
        cerr << "attention, probleme de parsage, objectif des sites de distribution pas reconnu" << endl;
    for (int j = 0; j < transpo.nbDist; j++)
    {
        int obj;
        entree >> obj;
        (transpo.objDist).push_back(obj);
    }

    entree.close();
}

void ParserFich::parseAssignement( Transportation & transpo)
{
    int N;
    entree >> N;
    transpo.nbProd = N;
    transpo.nbDist = N;

    for (int i = 0; i < transpo.nbProd; i++)
    {
        vector<int> lignei;
        for (int j = 0; j < transpo.nbDist; j++)
        {
            int tmpInt = 0;
            entree >> tmpInt;
            lignei.push_back(tmpInt);
        }
        (transpo.matCout).push_back(lignei);
    }

    for (int i = 0; i < transpo.nbProd; i++)
    {
        (transpo.capaProd).push_back(1);
    }

    for (int j = 0; j < transpo.nbDist; j++)
    {
        (transpo.objDist).push_back(1);
    }

    entree.close();
}

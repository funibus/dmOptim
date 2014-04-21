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
    //cout << "coucou je suis dans la fonction" << endl;
    while (pasDeplace == ' ')
    {
        //cout << "coucou, je viens de voir un blanc" << endl;
        //if (c == '\n')
            //cout << "c++ il fait n'importe quoi" << endl;
        //if (c == ' ')
            //cout << "coucou, je lis un blanc" << endl;
        entree.get(deplace);
        pasDeplace = entree.peek();
    }
    return pasDeplace;
}

Fraction ParserFich::lireFrac() //renvoie dans carSuiv le caractere suivant (+, < ou \n normalement)
{
    int num, denom = 1;

    entree >> num;
    char c = this->caractSuivant();
    if (c == '/')
    {
        entree >> c;
        entree >> denom;
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
    //char cartmp = 'a';
    bool prem = true; //gerer le cas ou il y a un coeff constant dans la fonction obj ou pas
    while (carSuiv != '\n' && carSuiv != EOF)
    //for (int i = 0; i < 5; i++)
    {
        //cerr << "coucou, carSuiv = " << carSuiv << endl;
        Fraction tmp = this->lireFrac();
        //tmp.printFraction();
        //if (carSuiv == '-') //on avait un - avant la fraction
            //tmp.oppose();
        //carSuiv = cartmp;
        carSuiv = this->caractSuivant();
        //cout << "apres fraction, carSuiv = " << carSuiv << endl;
        if (prem)
        {
            //cout << "coucou, caract suivant == " << carSuiv << endl;
            if (carSuiv != '+' && carSuiv != '-') //pas de coeff constant
                (linearProg.objectif).push_back(Fraction ());
            else //coeff constant
            {
                (linearProg.objectif).push_back(tmp);
                tmp.copie(this->lireFrac() );
                //cout << "coeff constant, carSuiv = " << carSuiv << endl;
                //tmp.printFraction();
            }
            prem = false;
        }
        //entree.seekg(-4, ios::cur);
        string var;
        //var.append(1,carSuiv); //var = carSuiv
        //string varSuite;
        entree >> var;
        //var.append(varSuite); //var = carSuiv||varSuite
        //cout << "var = " << var << "var2 = " << var2 << endl;
        int pos = this->trouverVar(var);
        if (pos == -1)
        {
            //cout << "nouvelle var : " << var << endl;
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
    //char cartmp = 'a';
    while (carSuiv != EOF)
    {
        vector<Fraction> tmpVect(listeVar.size()+1);
        while (carSuiv != '<' && carSuiv != EOF)
        {
            Fraction tmp = this->lireFrac();

            //if (carSuiv == '-')
                //tmp.oppose();
            //carSuiv = cartmp;
            //entree.seekg(-2, ios::cur);
            string var;
            entree >> var;
            //cout << "variable : " << var << " coeff : ";
            //tmp.printFraction();
            //cout << endl;
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

        //cout << "contrainte : " << linearProg.nbContraintes <<", <= ";
        //tmpVect[0].printFraction();
        //cout << endl << endl;

        carSuiv = this->caractSuivant();
        entree.get(carSuiv);
        //if (carSuiv != '\n')
            //cout << "coucou, carSuiv = " << carSuiv << endl;
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

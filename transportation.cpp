#include "transportation.hpp"

void Transportation::transpToLp( Lp & linearProg)
{
    linearProg.nbVar = nbProd*nbDist;
    linearProg.nbContraintes = nbProd+nbDist;

    //on remplis l'objectif
    (linearProg.objectif).push_back(Fraction(0));
    for (int i = 0; i < nbProd; i++)
    {
        for (int j = 0; j < nbDist; j++)
        {
            (linearProg.objectif).push_back(Fraction(-matCout[i][j])); //on veut minimiser les couts = maximiser -couts
        }
    }

    //contraintes sur les sites de production
    for (int i = 0; i < nbProd; i++)
    {
        vector<Fraction> tmp;
        tmp.push_back(Fraction(capaProd[i]));
        for (int ibis = 0; ibis < nbProd; ibis++)
        {
            for (int j = 0; j < nbDist; j++)
            {
                if (ibis == i)
                    tmp.push_back(Fraction(1));
                else
                    tmp.push_back(Fraction(0));
            }
        }
        (linearProg.coeffs).push_back(tmp);
    }

    //contraintes sur les sites de distributions
    for (int j = 0; j < nbDist; j++)
    {
        vector<Fraction> tmp;
        tmp.push_back(Fraction(-objDist[j])); // a >= b <=> -a <= -b
        for (int i = 0; i < nbProd; i++)
        {
            for (int jbis = 0; jbis < nbDist; jbis++)
            {
                if (jbis == j)
                    tmp.push_back(Fraction(-1));
                else
                    tmp.push_back(Fraction(0));
            }
        }
        (linearProg.coeffs).push_back(tmp);
    }
}


void Transportation::printTranspo()
{
    cout << "Nb de sites de production : " << nbProd << ", nb de sites de distribution : " << nbDist << endl;
    cout << "Matrice des couts (ligne : production, colonne : distribution)" << endl;
    for (int i = 0; i < nbProd; i++)
    {
        for (int j = 0; j < nbDist; j++)
            cout << matCout[i][j] << " ";
        cout << endl;
    }

    cout << "capacite des sites de production : ";
    for (int i = 0; i < nbProd; i++)
        cout << capaProd[i] << " ";
    cout << endl << "objectif des sites de distribution : ";
    for (int j = 0; j < nbDist; j++)
        cout << objDist[j] << " ";
    cout << endl << endl;
}

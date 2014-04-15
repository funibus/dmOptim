#include "linearProg.hpp"

using namespace std;

void Lp::dictFromLp1Phase(Dict & dico)
{
    for (int k = 0; k < nbContraintes; k++)
    {
        (dico.coeffs)[k+nbVar+1][0].copie( coeffs[k][0]);
        for (int l = 1; l <= nbVar; l++)
        {
            (dico.coeffs)[k+nbVar+1][l].copie( coeffs[k][l]);
            (dico.coeffs)[k+nbVar+1][l].oppose();
        }
        (dico.basic)[k+nbVar+1] = true;
    }

    for (int l = 0; l <= nbVar; l++)
        (dico.objectif)[l].copie( objectif[l]);

}

void Lp::dictFromLp2Phase(Dict & dico)
{
    for (int k = 0; k < nbContraintes; k++)
    {
        (dico.coeffs)[k+nbVar+1][0].copie( coeffs[k][0]);
        for (int l = 1; l <= nbVar; l++)
        {
            (dico.coeffs)[k+nbVar+1][l].copie( coeffs[k][l]);
            (dico.coeffs)[k+nbVar+1][l].oppose();
        }
        (dico.coeffs)[k+nbVar+1][nbVar+nbContraintes+1].change(1,1);
        (dico.basic)[k+nbVar+1] = true;
    }

    (dico.objectif)[nbVar+nbContraintes+1].change(-1,1);

}

bool Lp::besoinPremierePhase()
{
    for (int k = 0; k < nbContraintes; k++)
        if (coeffs[k][0].estNegatif())
            return true;

    return false;
}

Dict Lp::simplex()
{
    if (affichage)
    {
        std::cout << "Le programme est :" << std::endl << std::endl;
        this->printLp();
    }

    Dict dico(nbVar+nbContraintes+1, affichage, regleBland);
    int nonBorne;

    if (this->besoinPremierePhase())
    {
        if (affichage)
            std::cout << "*****Premiere phase (x0 = x_" << nbVar+nbContraintes+1 << ")*****" << std::endl << std::endl;

        this->dictFromLp2Phase(dico);
        if (affichage)
        {
            std::cout << "Le dictionnaire initial est " << std::endl;
            dico.printDict();
        }
        dico.premierePhase();

        if ((dico.objectif)[0].nonZero())
        {
            if (affichage)
                this->certifVide(dico);
            return dico;
        }

        else //on a deja supprime x0, il faut remettre l'objectif
        {
            for (int k = 0; k <= nbVar; k++)
                (dico.objectif)[k].copie(objectif[k]);
            for (int k = 1; k <= nbVar; k++)
                if (dico.basic[k])
                    dico.remplaceVarObj(k);
            if (affichage)
                std::cout << "*****Deuxieme phase*****" << std::endl << std::endl;
        }
    }

    else
    {
        dico.nbVariables --;
        this->dictFromLp1Phase(dico);
    }

    //2eme phase du simplex (commune)
    if (affichage)
        std::cout << "Le dictionnaire initial est " << std::endl;
    nonBorne = dico.petitSimplex1Phase();

    if (affichage)
    {
        if (nonBorne == -1)
            this->certifOpt(dico);
        else
            this->certifNonBorne(dico, nonBorne);
    }
    return dico;
}


void Lp::certifVide(Dict dico)
{
    std::cout << "Le domaine est vide" << std::endl << "Nombre de pivots : " << dico.nbPivots << std::endl;
    std::cout << "Certificat : " << std::endl;
    bool prem = true;
    vector<Fraction> certif(nbVar+1);
    for (int k = nbVar+1; k <= dico.nbVariables; k++)
    {
        if ((dico.objectif)[k].nonZero ())
        {
            Fraction tmp((dico.objectif)[k]);
            tmp.oppose();
            if (prem)
                prem = false;
            else
                std::cout << " +" ;
            tmp.printFraction();
            std::cout << " contrainte " << k-nbVar;
            for (int j = 0; j <= nbVar; j++)
            {
                Fraction tmp2 (coeffs[k-nbVar-1][j]);
                tmp2.mult(tmp);
                certif[j].add(tmp2);
            }
        }
    }

    std::cout << std::endl << "Ce qui donne : ";
    for (int j = 1; j <= nbVar; j++)
    {
        if (j != 1)
            std::cout << " +";
        certif[j].printFraction();
        std::cout << " x_" << j;
    }
    std::cout << " <=";
    certif[0].printFraction();
    std::cout << std::endl << std::endl;
}

void Lp::certifOpt(Dict dico)
{
    std::cout << "Une solution optimale est :";
    for (int k = 1; k <= nbVar; k++)
    {
        if (k != 1)
            std::cout << ",";
        std::cout << " x_" << k << " =";
        (dico.coeffs)[k][0].printFraction();
    }

    std::cout << std::endl << "La valeur de cette solution est :";
    (dico.objectif)[0].printFraction();

    std::cout << std::endl << "Nombre de pivots : " << dico.nbPivots;
    std::cout << std::endl << "Le certificat d'optimalite est :";
    bool prem = true;
    vector<Fraction> certif(nbVar+1);
    for (int k = nbVar+1; k <= dico.nbVariables; k++)
    {
        if ((dico.objectif)[k].nonZero ())
        {
            Fraction tmp((dico.objectif)[k]);
            tmp.oppose();
            if (prem)
                prem = false;
            else
                std::cout << " +" ;
            tmp.printFraction();
            std::cout << " contrainte " << k-nbVar;
            for (int j = 0; j <= nbVar; j++)
            {
                Fraction tmp2 (coeffs[k-nbVar-1][j]);
                tmp2.mult(tmp);
                certif[j].add(tmp2);
            }
        }
    }

    std::cout << std::endl << "Ce qui donne : ";
    for (int j = 1; j <= nbVar; j++)
    {
        if (j != 1)
            std::cout << " +";
        certif[j].printFraction();
        std::cout << " x_" << j;
    }
    std::cout << " <=";
    certif[0].printFraction();
    std::cout << std::endl << std::endl;
}

void Lp::certifNonBorne(Dict dico, int nonBorne)
{
    std::cout << "Solution non bornee" << std::endl;
    std::cout << "Nombre de pivots : " << dico.nbPivots << std::endl << "Certificat :";

    if (nonBorne <= nbVar)
        std::cout << " augmenter x_" << nonBorne << " jusqu'a l'infini" << std::endl << std::endl;
    else
    {
        std::cout << " prendre";
        for (int j = 1; j <= nbVar; j++)
        {
            if (j != 1)
                std::cout << ",";
            std::cout << " x_" << j << " =";
            (dico.coeffs)[j][0].printFraction();
            if ((dico.basic)[j] && (dico.coeffs)[j][nonBorne].nonZero() )
            {
                std::cout << " +";
                (dico.coeffs)[j][nonBorne].printFraction();
                std::cout << " k";
            }
        }

        std::cout << " et faire tendre k vers l'infini" << std::endl << std::endl;
    }
}

void Lp::printLp()
{
    std::cout << "Maximiser ";

    objectif[0].printFraction();
    for (int k = 1; k <= nbVar; k++)
    {
        std::cout << " +";
        objectif[k].printFraction();
        std::cout << " x_" << k;
    }

    std::cout << std::endl << "Tel que" << std::endl;
    for (int l = 0; l < nbContraintes; l++)
    {
        for (int k = 1; k <= nbVar; k++)
        {
            if (k != 1)
                std::cout << " +";
            coeffs[l][k].printFraction();
            std::cout << " x_" << k;
        }
        std::cout << " <=";
        coeffs[l][0].printFraction();
        std::cout << std::endl;
    }

    for (int k = 1; k <= nbVar; k++)
    {
        if (k != 1)
            std::cout << ",";
        std::cout << " x_" << k;
    }

    std::cout <<" positifs" << std::endl << std::endl;
}

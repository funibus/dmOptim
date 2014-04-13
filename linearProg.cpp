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
    Dict dico(nbVar+nbContraintes+1);

    if (this->besoinPremierePhase())
    {
        std::cout << "*****Premiere phase (x0 = x_" << nbVar+nbContraintes+1 << ")*****" << std::endl << std::endl;

        this->dictFromLp2Phase(dico);
        std::cout << "Le dictionnaire initial est " << std::endl;
        dico.printDict();
        dico.premierePhase();

        if (objectif[0].nonZero())
        {
            std::cerr << "pas de solutions" << std::endl;
            return dico;
        }

        else //on a deja supprime x0, il faut remettre l'objectif
        {
            for (int k = 0; k <= nbVar; k++)
                (dico.objectif)[k].copie(objectif[k]);
            for (int k = 1; k <= nbVar; k++)
                if (dico.basic[k])
                    dico.remplaceVarObj(k);
            std::cout << "*****Deuxieme phase*****" << std::endl << std::endl;
        }
    }

    else
    {
        dico.nbVariables --;
        this->dictFromLp1Phase(dico);
    }

    //2eme phase du simplex (commune)
    std::cout << "Le dictionnaire initial est " << std::endl;
    dico.petitSimplex1Phase();
    return dico;
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

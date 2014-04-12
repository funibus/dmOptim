#include"dict.hpp"
#include"fractions.hpp"

void Dict::setBasicVar(int i, vector<Fraction> const & vect)
{
    for (int k = 0; k <= nbVariables; k++)
        (coeffs[i][k]).copie(vect[k]);
    basic[i] = true;
}

void Dict::setNonBasic(int i)
{
    for (int k = 0; k <= nbVariables; k++)
        (coeffs[i][k]).setZero();
    basic[i] = false;
}

void Dict::setObjectif(vector<Fraction> const & vect)
{
    for (int k = 0; k <= nbVariables; k++)
        (objectif[k]).copie(vect[k]);
}

void Dict::petitPivot(int basi, int nonBasi)
{
    Fraction coeffNonBasic = (coeffs[basi][nonBasi]).clone();

    (coeffs[nonBasi][basi]).change(1,1);
    for (int k = 0; k <= nbVariables; k++)
    {
            (coeffs[nonBasi][k]).soustraction(coeffs[basi][k]);
            (coeffs[nonBasi][k]).div(coeffNonBasic);
    }
    coeffs[nonBasi][nonBasi].setZero();
    basic[nonBasi] = true;

    this->setNonBasic(basi);
}

void Dict::printDict()
{
    for (int k = 1; k <= nbVariables; k++)
    {
        if (basic[k])
        {
            for (int l = 0; l <= nbVariables; l++)
                if (coeffs[k][l].nonZero() )
                {
                    if (coeffs[k][l].getNum() != 1 || coeffs[k][l].getDenom() != 1)
                        coeffs[k][l].printFraction();
                    if (l != 0) //si c'est le coeff constant pas de variable
                        std::cout << "x_" << l;
                }
            std::cout << std::endl;
        }
    }

    for (int k = 0; k <= 2*nbVariables; k++)
        std::cout << "_";
    std::cout << std::endl;

    std::cout << "z = ";
    for (int l = 0; l <= nbVariables; l++)
        if (objectif[l].nonZero() )
        {
            if (objectif[l].getNum() != 1 || objectif[l].getDenom() != 1)
                objectif[l].printFraction();
            if (l != 0) //si c'est le coeff constant pas de variable
                std::cout << "x_" << l;
        }
    std::cout << std::endl;
}

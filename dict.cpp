#include"dict.hpp"
#include"fractions.hpp"

void Dict::setBasicVar(int i, vector<Fraction> const & vect)
{
    if (vect.size() < nbVariables)
        cerr << "attention, vecteur trop court pour initialiser la variable" << endl;
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

void Dict::remplaceVar(int var1, int var2)
{
    for (int k = 0; k <= nbVariables; k++)
    {
        Fraction tmp = coeffs[var2][k].clone();
        tmp.mult(coeffs[var1][var2]);
        coeffs[var1][k].add(tmp);
    }
    coeffs[var1][var2].setZero();

}

void Dict::remplaceVarObj(int var2)
{
    for (int k = 0; k <= nbVariables; k++)
    {
        Fraction tmp = coeffs[var2][k].clone();
        tmp.mult(objectif[var2]);
        objectif[k].add(tmp);
    }
    objectif[var2].setZero();

}


void Dict::grosPivot(int varSortante, int varEntrante)
{
    if (basic[varEntrante])
        std::cerr << "attention, variable entrante qui n'est pas non basique" << std::endl;
    if (basic[varSortante] == false)
        std::cerr << "attention, variable sortante qui n'est pas basique" << std::endl;

    this->petitPivot(varSortante, varEntrante);
    for (int k = 1; k <= nbVariables; k++)
        if (basic[k] && k != varEntrante)
            this->remplaceVar(k,varEntrante);

    this->remplaceVarObj(varEntrante);
}


int Dict::choixEntranteBland()
{
    int k = 1;
    while (k <= nbVariables)
    {
        if (basic[k] == false && objectif[k].estPositif())
            return k;
        k++;
    }
    return -1;
}

int Dict::choixSortanteBland(int entrante)
{
    int k = 1;
    int res = -1;
    Fraction rapportMin(0,1);
    while (k <= nbVariables)
    {
        if (basic[k] && coeffs[k][entrante].estNegatif())
        {
            Fraction rapport = coeffs[k][0].clone();
            rapport.oppose();
            rapport.div(coeffs[k][entrante]);

            if (rapportMin.nonZero() == false || rapport.strictInf(rapportMin))
            {
                rapportMin.copie(rapport);
                res = k;
            }
        }
        k++;
    }
    return res;
}

int Dict::choixEntranteMax()
{
    int res = -1;
    Fraction coeffMax(0,1);
    int k = 1;
    while (k <= nbVariables)
    {
        if (basic[k] == false && coeffMax.strictInf(objectif[k]))
        {
            coeffMax.copie(objectif[k]);
            res = k;
        }
        k++;
    }
    return res;
}

void Dict::simplexUnePhase()
{
    std::cout << "Le dictionnaire initial est " << std::endl;
    this->printDict();

    int entrante = this->choixEntranteBland();
    int sortante = -1;

    while (entrante != -1)
    {
        sortante = this->choixSortanteBland(entrante);
        if (sortante == -1)
        {
            std::cout << "solution non bornee : augmenter variable x_" << entrante << "jusqu'a l'infini" << std::endl;
            return;
        }
        else
        {
            std::cout << "Variable entrante : x_" << entrante << std::endl;
            std::cout << "Variable sortante : x_" << sortante << std::endl;
            this->grosPivot(sortante, entrante);
            this->printDict();
        }
        entrante = this->choixEntranteBland();
    }
}

void Dict::printDict()
{
    bool premVar;
    for (int k = 1; k <= nbVariables; k++)
    {
        if (basic[k])
        {
            premVar = true;
            cout << "x_" << k << " = ";
            for (int l = 0; l <= nbVariables; l++)
                if (basic[l] == false )
                {
                    if (premVar)
                        premVar = false;
                    else
                        cout << " +";

                    if (coeffs[k][l].getNum() != 1 || coeffs[k][l].getDenom() != 1)
                        coeffs[k][l].printFraction();
                    if (l != 0) //si c'est le coeff constant pas de variable
                        std::cout << " x_" << l;
                }
            std::cout << std::endl;
        }
    }

    for (int k = 0; k <= 6*nbVariables; k++)
        std::cout << "-";
    std::cout << std::endl;

    std::cout << "z = ";
    premVar = true;
    for (int l = 0; l <= nbVariables; l++)
        if (basic[l] == false )
        {
            if (premVar)
                premVar = false;
            else
                cout << " +";

            if (objectif[l].getNum() != 1 || objectif[l].getDenom() != 1)
                objectif[l].printFraction();
            if (l != 0) //si c'est le coeff constant pas de variable
                std::cout << " x_" << l;
        }
    std::cout << std::endl << std::endl << std::endl;
}

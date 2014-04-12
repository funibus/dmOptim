#include"fractions.hpp"

int Fraction::PGCD(int a, int b)
{
    if (b == 0)
        return a;
    else
    {
        int r = a%b;
        return PGCD(b,r);
    }
}


void Fraction::reduction()
{
    int d = Fraction::PGCD(num, denom);
    if (d == 0)
    {
        cerr << "attention, reduction d'une fraction nulle" << endl;
        d = 1;
    }

    num = num / d;
    denom = denom / d;
}

void Fraction::inverse()
{
    if (num == 0)
        cerr << "attention, inversion d'une fraction nulle, fraction non inversee" << endl;
    else
    {
        int tmp = denom;
        denom = num;
        num = tmp;
    }

}

void Fraction::mult(Fraction f)
{
    int num2 = f.getNum();
    int denom2 = f.getDenom();

    num *= num2;
    denom *= denom2;
    this->reduction();

}

void Fraction::div(Fraction f)
{
    int num2 = f.getNum();
    int denom2 = f.getDenom();

    if (num2 == 0)
        cerr << "attention, division par une fraction nulle, division annulee" << endl;

    else
    {
        num *= denom2;
        denom *= num2;
        this->reduction();
    }
}

void Fraction::add(Fraction f)
{
    int num2 = f.getNum();
    int denom2 = f.getDenom();

    num = num2*denom+denom2*num;
    denom *= denom2;
    this->reduction();

}

void Fraction::soustraction(Fraction f)
{
    int num2 = -f.getNum();
    int denom2 = f.getDenom();

    num = num2*denom+denom2*num;
    denom *= denom2;
    this->reduction();
}

void Fraction::printFraction()
{
    if (denom == 1)
        cout << " " << num;
    else
        cout << " " << num << "/" << denom ;
}

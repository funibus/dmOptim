#include"fractions.hpp"

long long Fraction::PGCD(long long a, long long b)
{
    if (b == 0)
        return a;
    else
    {
        long long r = a%b;
        return PGCD(b,r);
    }
}


void Fraction::reduction()
{
    long long d = Fraction::PGCD(num, denom);
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
        long long tmp = denom;
        denom = num;
        num = tmp;
    }

}

void Fraction::mult(Fraction f)
{
    long long num2 = f.getNum();
    long long denom2 = f.getDenom();

    num *= num2;
    denom *= denom2;
    this->reduction();

}

void Fraction::div(Fraction f)
{
    long long num2 = f.getNum();
    long long denom2 = f.getDenom();

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
    long long num2 = f.getNum();
    long long denom2 = f.getDenom();

    num = num2*denom+denom2*num;
    denom *= denom2;
    this->reduction();

}

void Fraction::soustraction(Fraction f)
{
    long long num2 = -f.getNum();
    long long denom2 = f.getDenom();

    num = num2*denom+denom2*num;
    denom *= denom2;
    this->reduction();
}

void Fraction::printFraction()
{
    if (denom < 0)
    {
        denom = -denom;
        num = -num;
    }
    if (denom == 1)
        cout << " " << num;
    else
        cout << " " << num << "/" << denom ;
}

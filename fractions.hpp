#ifndef FRACTIONS_HPP_INCLUDED
#define FRACTIONS_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Fraction
{
    private:
        int num;
        int denom;

    public:
        Fraction() { num = 0; denom = 1;}

        Fraction(int a, int b = 1) {
            num = a;
            denom = b;
            if (b == 0)
            {
                std::cerr << "attention, creation d'une fraction dont le denominateur est nul, il est remplace par 1" << std::endl;
                denom = 1;
            }

        }

        int getNum() {return num;} ;
        int getDenom() {return denom;} ;
        void setNum(int a) {num = a;} ;
        void setDenom(int b) {denom = b;} ;
        void setZero() {num = 0; denom = 1;};
        bool nonZero() {return num != 0;};
        bool estPositif() {return (num > 0 && denom > 0) || (num < 0 && denom < 0);};
        bool estNegatif() {return (num < 0 && denom > 0) || (num > 0 && denom < 0);};
        bool strictInf(Fraction f) {Fraction g = this->clone(); g.soustraction(f); return g.estNegatif();};

        Fraction clone() {Fraction f(num, denom); return f;};
        void copie(Fraction f) {num = f.getNum(); denom = f.getDenom();};
        void change(int a, int b) {num = a; denom = b;};

        void inverse();
        void oppose() {num = -num;};
        void reduction();
        void mult(Fraction f);
        void add(Fraction f);
        void div(Fraction f);
        void soustraction(Fraction f);

        void printFraction();

        static int PGCD(int a, int b);


};


#endif // FRACTIONS_HPP_INCLUDED

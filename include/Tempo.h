#ifndef TEMPO_H
#define TEMPO_H

#include <iostream>
#include <string>

class Tempo {
    public:
        //Costruttori
        Tempo();
        Tempo(int, int);

        //Getter
        int getOra() const;
        int getMinuti() const;

        //Setter
        void setOra(int);
        void setMinuti(int);

        //Overloading operatori >, < e +
        bool operator>(const Tempo&) const;
        bool operator<(const Tempo&) const;
        Tempo operator+(const int) const;
        Tempo operator+(const Tempo&) const;
        Tempo operator-(const Tempo&) const;

    private:
        int ora;
        int minuti;
};

//Helper Function
std::ostream& operator<<(std::ostream&, const Tempo&);   

#endif
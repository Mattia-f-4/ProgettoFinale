#ifndef TEMPO_H
#define TEMPO_H

#include <iostream>
#include <string>

class Tempo {
    public:
        //Costruttori
        Tempo();
        Tempo(int h, int m);

        //Getter
        int getOra() const;
        int getMinuti() const;

        //Setter
        void setOra(int h);
        void setMinuti(int m);

    private:
        int ora;
        int minuti;
};

//Helper Function
std::ostream& operator<<(std::ostream& os, const Tempo& obj);   
Tempo calcolaOrario(const Tempo& obj, int durata); 

#endif
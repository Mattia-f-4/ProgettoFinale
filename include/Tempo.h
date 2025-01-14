/* Creato da: DAVID PADOVAN */

#ifndef TEMPO_H
#define TEMPO_H

#include <iostream>
#include <string>

class Tempo {
    public:
        
        //Costruttori
        Tempo();
        Tempo(int, int);
        Tempo(std::string);

        //Getter
        int getOra() const;
        int getMinuti() const;

        //Setter
        void setOra(int);
        void setMinuti(int);
        void setNull();

        //Overloading operatori
        bool operator>(const Tempo&) const;
        bool operator<(const Tempo&) const;
        bool operator>=(const Tempo&) const;
        bool operator<=(const Tempo&) const;
        Tempo operator+(const int) const;
        Tempo operator+(const Tempo&) const;
        Tempo operator-(const Tempo&) const;
        Tempo& operator=(const Tempo&);
        bool operator==(const Tempo&) const;
        bool operator!=(const Tempo&) const;

        //Member function
        bool isNull();                          //Per capire se il tempo è usabile oppure no
        std::string toString() const;           //Per restituire un orario nella forma [XX:YY]
        std::string toSimpleString() const;     //Per restituire un orario nella forma XX:YY

    private:
       
        //Variabili d'istanza
        int ora;
        int minuti;
};

//Helper Function
std::ostream& operator<<(std::ostream&, const Tempo&);   

#endif
#ifndef SISTEMADOMOTICO_H
#define SISTEMADOMOTICO_H

#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include <iostream>
#include <map>
#include <stack>
#include <vector>

class SistemaDomotico
{
    public:
    /* COSTRUTTORI */
    SistemaDomotico(); 
    SistemaDomotico(double);    

    void setTime(Tempo&);
    void setOff(Dispositivo&);
    void setOn(Dispositivo&);
    void setTimer(Dispositivo&, Tempo&);
    void setTimer(DispManuale&, Tempo&, Tempo&);
    void rm(DispManuale&);
    void add(DispManuale::DispDomotico);
    void add(DispCicloPrefissato::DispDomotico);
    void erase(int);

    private:
    /* CONTENITORI */   
    std::multimap<Tempo, int> TimeLine;
    std::stack<int> OrdineAccensione;
    std::map<int,Dispositivo&> DataBase;

    /* DATI MEMBRO */
    const double limitePotenza;
    double potenzaResidua;
    Tempo orario;
    int size;

    /*  FUNZIONI DI CONTROLLO */
    void sovraccarico();
};

std::ostream& show(std::ostream&, SistemaDomotico&);
std::ostream& show(std::ostream&, SistemaDomotico&, Dispositivo&);

#endif
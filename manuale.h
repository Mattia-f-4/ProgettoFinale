#ifndef MANUALE_H
#define MANUALE_H
#include "dispositivo.h"
#include <string>
#include <unordered_map>

class manuale : public dispositivo
{
    public:
    enum class dispositivoDomotico; //definita come classe interna, pubblica per poter accedere ai dati 
    //VANNO ANCORA SISTEMATI ED IMPLEMENTATI I METODI SOTTO
    manuale();


    double getConsumoTotale() const override;
    bool getStato() const override;
    double getTempoAccensione() const override;
    Tempo getOrarioAccensione() const override;

    protected:

    class caratteristiche; //definita come classe interna 
    static const std::unordered_map<dispositivoDomotico, caratteristiche> tipiDispositivi; //mappa definita come statica per non dover essere creata ogni volta, va descritta nel .cpp
    
    double consumo;

    double consumoTotale;
    Tempo orarioAccensione;
    double tempoAccensione;
    bool stato;
};









#endif
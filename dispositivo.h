#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

class dispositivo
{
    virtual double getConsumoTotale() const = 0 ;
    virtual bool getStato() const = 0;
    virtual double getTempoAccensione() const = 0;
    virtual Tempo getOrarioAccensione() const = 0;
};


#endif
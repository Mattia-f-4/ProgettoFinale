/* Creato da: GIACOMO CARLOTTO */

#include "DispManuale.h"

/* VARIABILE GLOBALE ID */
    int ManualID = 0;   //Disp. manuali hanno ID pari

/* COSTRUTTORI */
    
    //Costruttori parametrici
    DispManuale::DispManuale(std::string nome, DispDomotico tipo, Tempo accensione, Tempo spegnimento)
        : Dispositivo(nome, accensione, spegnimento), tipoDispositivo{tipo}
    {
        //Assegnamento e aggiornamento ID
        ID = ManualID;
        ManualID = ManualID +2;

        potenza = tipiDispositivi[tipoDispositivo];
    }

    DispManuale::DispManuale(std::string nome, DispDomotico tipo)
        : Dispositivo(nome), tipoDispositivo{tipo}
    {
        //Assegnamento e aggiornamento ID
        ID = ManualID;
        ManualID = ManualID +2;

        potenza = tipiDispositivi[tipoDispositivo];
    }

/* FUNZIONI MEMBRO */

    //Setter
    void DispManuale::setSpegnimento(const Tempo& t) { oraSpegnimento = t; }

/* MAPPA */

    //Mappa per tipi dispositivi manuali
    std::map<DispManuale::DispDomotico, double> DispManuale::tipiDispositivi = {
        {DispManuale::DispDomotico::Impianto_Fotovoltaico, 1.5},
        {DispManuale::DispDomotico::Pompa_di_calore_termostato, -2.0},
        {DispManuale::DispDomotico::Scaldabagno, -1.0},
        {DispManuale::DispDomotico::Frigorifero, -0.4},
    };
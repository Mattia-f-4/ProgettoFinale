#include "DispManuale.h"

/* VARIABILE GLOBALE ID */
    int ManualID = 0;   //Disp. manuali hanno ID pari

/* COSTRUTTORI */
    
    //Costruttore parametrico
    DispManuale::DispManuale(std::string nome, DispDomotico tipo, Tempo accensione, Tempo spegnimento)
        : Dispositivo(nome, accensione), tipoDispositivo{tipo}
    {
        switch(tipoDispositivo) {
            case DispDomotico::Impianto_Fotovoltaico:
                tipiDispositivi[tipoDispositivo] = 1.5;
                break;
            case DispDomotico::Pompa_di_calore_termostato:
                tipiDispositivi[tipoDispositivo] = -2.0;
                break;
            case DispDomotico::Scaldabagno:
                tipiDispositivi[tipoDispositivo] = -1.0;
                break;
            case DispDomotico::Frigorifero:
                tipiDispositivi[tipoDispositivo] = -0.4;
                break;
        }

        //Assegnamento e aggiornamento ID
        ID = ManualID;
        ManualID = ManualID +2;

        oraSpegnimento = spegnimento;
        potenza = tipiDispositivi[tipoDispositivo];
    }

/* FUNZIONI MEMBRO */

    //Setter
    void DispManuale::setSpegnimento(const Tempo& t) { oraSpegnimento = t; }
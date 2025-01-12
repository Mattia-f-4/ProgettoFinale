#include "Dispositivo.h"

using namespace std;

/* COSTRUTTORI */

    //Costruttore parametrico
    Dispositivo::Dispositivo(std::string nome, Tempo accensione, Tempo spegnimento)
        : nome{nome}, oraAccensione{accensione}, oraSpegnimento{spegnimento}, stato{false} {}
    Dispositivo::Dispositivo(std::string nome, Tempo accensione)
        : nome{nome}, oraAccensione{accensione},  stato{false} 
    {
            oraSpegnimento.setNull();
    }
    Dispositivo::Dispositivo(std::string nome)
        : nome{nome}, stato{false} 
    {
            oraAccensione.setNull();
            oraSpegnimento.setNull();
    }

/* FUNZIONI MEMBRO */

    //Getter
    int Dispositivo::getID() const { return ID; }
    string Dispositivo::getNome() const { return nome; }
    bool Dispositivo::getStato() const { return stato; }
    double Dispositivo::getPotenza() const { return potenza; }
    Tempo Dispositivo::getAccensione() const { return oraAccensione; }
    Tempo Dispositivo::getSpegnimento() const { return oraSpegnimento; }
    Tempo Dispositivo::getDurataAccensione() const { return durataAccensione; }

    //Setter
    void Dispositivo::setStato(bool s) { stato = s; }
    void Dispositivo::setAccensione(const Tempo& ora) { oraAccensione = ora; }
    void Dispositivo::setSpegnimento(const Tempo& ora) { 
        oraSpegnimento = ora; 
        
        //Oltre a dover impostare l'ora, devo aggiornare la durata di accensione del dispositivo    
        durataAccensione = durataAccensione + (getSpegnimento() - getAccensione());
    }

    //changeStatus, per accendere/spegnere il dispositivo
    void Dispositivo::changeStatus() {
        if(getStato())
            setStato(false);
        else
            setStato(true);
    }

    //consumoEnergetico
    double Dispositivo::consumoEnergetico(const Tempo& t) const {
        
        //Se il dispositivo è ancora acceso, bisogna calcolare anche la durata attuale di accensione
        Tempo durata(0,0);
        
        if(getStato()) {
            durata = t - getAccensione();
        }
        
        
        return -((getDurataAccensione()+durata).getOra() * getPotenza() + ( (double) (getDurataAccensione()+durata).getMinuti() / 60) * getPotenza());
    }

    //Metodo reset per riportare il dispositivo alle condizioni iniziali
    void Dispositivo::reset() {
        oraAccensione.setNull();
        oraSpegnimento.setNull();
        setStato(false);
        durataAccensione = Tempo(0,0);
    }
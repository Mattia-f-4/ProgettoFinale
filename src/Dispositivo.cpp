#include "Dispositivo.h"
#include <cmath>

using namespace std;

/* COSTRUTTORI */

    //Costruttore parametrico
    Dispositivo::Dispositivo(std::string nome, Tempo accensione, Tempo spegnimento)
        : nome{nome}, oraAccensione{accensione}, oraSpegnimento{spegnimento}, stato{false} {}
    Dispositivo::Dispositivo(std::string nome, Tempo accensione)
        : nome{nome}, oraAccensione{accensione}, oraSpegnimento{-1,0}, stato{false} {}
    Dispositivo::Dispositivo(std::string nome)
        : nome{nome}, oraAccensione{-1,0}, oraSpegnimento{-1,0}, stato{false} {}

/* FUNZIONI MEMBRO */

    //Getter
    int Dispositivo::getID() const { return ID; }
    string Dispositivo::getNome() const { return nome; }
    bool Dispositivo::getStato() const { return stato; }
    double Dispositivo::getPotenza() const { return potenza; }
    Tempo Dispositivo::getAccensione() const { return oraAccensione; }
    Tempo Dispositivo::getSpegnimento() const { return oraSpegnimento; }

    //Setter
    void Dispositivo::setStato(bool s) { stato = s; }
    void Dispositivo::setAccensione(const Tempo& ora) { oraAccensione = ora; }
    void Dispositivo::setSpegnimento(const Tempo& ora) { oraSpegnimento = ora; }

    //changeStatus, per accendere/spegnere il dispositivo
    void Dispositivo::changeStatus() {
        if(getStato())
            setStato(false);
        else
            setStato(true);
    }

    //consumoEnergetico
    double Dispositivo::consumoEnergetico(const Tempo& t) const {
        Tempo durata;
        double consumo;
        
        if(getAccensione() > t)
            return 0;
        
        if(t < getSpegnimento()) {
            durata = t-getAccensione();
        }
        else {
            durata = getSpegnimento()-getAccensione();
        }

        consumo = fabs(durata.getOra() * getPotenza() + ( (double) durata.getMinuti() / 60) * getPotenza());

        return consumo;
    }
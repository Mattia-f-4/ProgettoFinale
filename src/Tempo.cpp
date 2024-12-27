#include "Tempo.h"

using namespace std;

/* COSTRUTTORI */

    //Costruttore di default
    Tempo::Tempo()
        : ora{0}, minuti{0} {}

    //Costruttore parametrico
    Tempo::Tempo(int h, int m)
        : ora{h}, minuti{m} {
        if(h < 0 || h > 23)
            throw invalid_argument("Hours must be between 0 and 23");
        if(m < 0 || m > 59)
            throw invalid_argument("Minutes must be between 0 and 59");
    }

/* FUNZIONI MEMBRO */

    //Getter
    int Tempo::getOra() const { return ora; }
    int Tempo::getMinuti() const { return minuti; }

    //Setter
    void Tempo::setOra(int h) {
        if(h >= 0 && h < 24)
            ora = h;
        else   
            throw invalid_argument("Hours must be between 0 and 23");
    }

    void Tempo::setMinuti(int m) {
        if(m >= 0 && m < 60)
            minuti = m;
        else   
            throw invalid_argument("Minutes must be between 0 and 59");
    }

/* HELPER FUNCTION */

    //Overloading operatore <<
    ostream& operator<<(std::ostream& os, const Tempo& obj) {
        
        os << "[";
        
        if(obj.getOra() < 10)
            os << "0" << obj.getOra() << ":";
        else    
            os << obj.getOra() << ":";

        if(obj.getMinuti() < 10)
            os << "0" << obj.getMinuti();
        else 
            os << obj.getMinuti();

        os << "]";
        
        return os;
    }

    //calcolaOrario, per calcolare un orario a partire da un altro orario e relativa durata
    Tempo calcolaOrario(const Tempo& obj, int durata) {
        if(durata <= 0)
            throw invalid_argument("Duration must be positive");

        int newMin = obj.getMinuti() + durata;
        int newH = obj.getOra() + newMin / 60;
        newMin = newMin % 60;

        return Tempo(newH, newMin);
    }
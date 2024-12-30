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

    //Overloading operator >
    bool Tempo::operator>(const Tempo& t) const {
        if (getOra() > t.getOra()) {
            return true;
        }
        if (getOra() == t.getOra() && getMinuti() > t.getMinuti()) {
            return true;
        }
        return false;
    }

    //Overloading operator <
    bool Tempo::operator<(const Tempo& t) const {
        if (getOra() < t.getOra()) {
            return true;
        }
        if (getOra() == t.getOra() && getMinuti() < t.getMinuti()) {
            return true;
        }
        return false;
    }

    //Overloading operator +
    Tempo Tempo::operator+(const int durata) const{
        if(durata <= 0)
            throw invalid_argument("Duration must be positive");

        int newMin = getMinuti() + durata;
        int newH = getOra() + newMin / 60;
        newMin = newMin % 60;

        return Tempo(newH, newMin);
    }

    Tempo Tempo::operator+(const Tempo& durata) const{
        if(durata.getOra() < 0 && durata.getMinuti() <= 0)
            throw invalid_argument("Duration must be positive");
        
        int newMin = getMinuti() + durata.getMinuti();
        int newH = getOra() + durata.getOra() + newMin/60;
        newMin = newMin % 60;

        return Tempo(newH, newMin);
    }

    //Overloading operator -
    Tempo Tempo::operator-(const Tempo& t) const{
        if(t > *this)
            throw invalid_argument("Cannot subtract a bigger time");
        
        int newMin = getMinuti() - t.getMinuti();
        int newH = getOra() - t.getOra();
        if(newMin < 0) {
            newH--;
            newMin = (60-abs(newMin)) % 60;
        }

        return Tempo(newH, newMin);
    }

    //Overloading operator=
    Tempo& Tempo::operator=(const Tempo& t)
    {
        ora = t.getOra();
        minuti = t.getMinuti();

        return *this;
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

    //Overloading operator==
    bool Tempo::operator==(const Tempo& t) const
    {
        if(t.getOra()==ora && t.getMinuti()==minuti)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

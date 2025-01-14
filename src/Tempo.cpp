/* Creato da: DAVID PADOVAN */

#include "Tempo.h"

using namespace std;

/* COSTRUTTORI */

    //Costruttore di default
    Tempo::Tempo()
        : ora{0}, minuti{0} {}

    //Costruttore parametrico
    Tempo::Tempo(int h, int m) {
        setOra(h);
        setMinuti(m);
    }

    //Costruttore con String
    Tempo::Tempo(std::string orario) {
        int pos = orario.find(':');

        if(pos != string::npos) {
            
            //Se ci sono i due punti, la stringa conterrà l'orario nel formato 12:00
            string h = orario.substr(0, pos);
            string m = orario.substr(pos + 1);

            setOra(stoi(h));
            setMinuti(stoi(m));

        } else {
            
            //Se non ci sono i due punti, la stringa conterrà solo un numero (che è l'ora!)
            setOra(stoi(orario));
            setMinuti(0);
        }
    }

/* FUNZIONI MEMBRO */

    //Getter
    int Tempo::getOra() const { return ora; }
    int Tempo::getMinuti() const { return minuti; }

    //Setter
    void Tempo::setOra(int h) {
        
        //E' necessario controllare che l'ora sia nella forma corretta
        if(h >= 0 && h < 24)
            ora = h;
        else   
            throw invalid_argument("ERROR: Le ore devono essere comprese tra 0 e 23");
    }

    void Tempo::setMinuti(int m) {
        
        //E' necessario controllare che i minuti siano nella forma corretta
        if(m >= 0 && m < 60)
            minuti = m;
        else   
            throw invalid_argument("ERROR: I minuti devono essere compresi tra 0 e 59");
    }

    //setNull, per impostare il Tempo in formato 'null' (non utilizzabile)
    void Tempo::setNull() {
        ora = -1;
        minuti = -1;
    }

    //isNull(), per capire se il tempo è utilizzabile o meno
    bool Tempo::isNull() {
        if(ora == -1 && minuti == -1)
            return true;
        else
            return false;
    }

    //toString, per restituire un orario nella forma [XX:YY]
    string Tempo::toString() const {
        
        string s = "[";
        
        if(getOra() < 10)
            s += "0" + to_string(getOra()) + ":";
        else    
            s += to_string(getOra()) + ":";

        if(getMinuti() < 10)
            s += "0" + to_string(getMinuti());
        else 
            s += to_string(getMinuti());

        s += "]";

        return s;
    }

    //toSimpleString, per restituire un orario nella forma XX:YY
    string Tempo::toSimpleString() const {
        
        string s = "";
        
        if(getOra() < 10)
            s += "0" + to_string(getOra()) + ":";
        else    
            s += to_string(getOra()) + ":";

        if(getMinuti() < 10)
            s += "0" + to_string(getMinuti());
        else 
            s += to_string(getMinuti());

        return s;
    }

/* OVERLOADING OPERATORI */
    
    //Overloading operator >
    bool Tempo::operator>(const Tempo& t) const {
        if(getOra() > t.getOra()) {
            return true;
        }
        if(getOra() == t.getOra() && getMinuti() > t.getMinuti()) {
            return true;
        }
        return false;
    }

    //Overloading operator <
    bool Tempo::operator<(const Tempo& t) const {
        if(getOra() < t.getOra()) {
            return true;
        }
        if(getOra() == t.getOra() && getMinuti() < t.getMinuti()) {
            return true;
        }
        return false;
    }

    //Overloading operator +
    Tempo Tempo::operator+(const int durata) const{
        if(durata <= 0)
            throw invalid_argument("ERROR: La durata deve essere positiva");

        int newMin = getMinuti() + durata;
        int newH = getOra() + newMin / 60;
        
        //Normalizzo ore e minuti in modo che rimangano nel range [0,23] e [0,59]
        newH = newH % 24;
        newMin = newMin % 60;

        return Tempo(newH, newMin);
    }

    //Overloadig operator +
    Tempo Tempo::operator+(const Tempo& durata) const{
        if(durata.getOra() < 0 && durata.getMinuti() <= 0)
            throw invalid_argument("ERROR: La durata deve essere positiva");
        
        int newMin = getMinuti() + durata.getMinuti();
        int newH = getOra() + durata.getOra() + newMin/60;
        
        //Normalizzo ore e minuti in modo che rimangano nel range [0,23] e [0,59]
        newH = newH % 24;
        newMin = newMin % 60;

        return Tempo(newH, newMin);
    }

    //Overloading operator -
    Tempo Tempo::operator-(const Tempo& t) const{
        if(t > *this)
            throw invalid_argument("ERROR: Impossibile sottrarre un tempo più grande");
        
        int newMin = getMinuti() - t.getMinuti();
        int newH = getOra() - t.getOra();
        
        //Normalizzo ore e minuti in modo che rimangano nel range [0,23] e [0,59]
        if(newMin < 0) {
            newH--;
            newMin = (60-abs(newMin)) % 60;
        }

        return Tempo(newH, newMin);
    }

    //Overloading operator=
    Tempo& Tempo::operator=(const Tempo& t) {
        ora = t.getOra();
        minuti = t.getMinuti();
        return *this;
    }

    //Overloading operator==
    bool Tempo::operator==(const Tempo& t) const {
        if(t.getOra()==ora && t.getMinuti()==minuti)
            return true;
        else
            return false;
    }

    //Overloading operator!=
    bool Tempo::operator!=(const Tempo& t) const {
        if(t.getOra()!=ora || t.getMinuti()!=minuti)
            return true;
        else
            return false;
    }

    //Overloading operator >=
    bool Tempo::operator>=(const Tempo& t) const {
        if (getOra() > t.getOra())
            return true;
        if (getOra() == t.getOra() && getMinuti() >= t.getMinuti())
            return true;
        
        return false;
    }

    //Overloading operator <=
    bool Tempo::operator<=(const Tempo& t) const {
        if (getOra() < t.getOra()) 
            return true;
        if (getOra() == t.getOra() && getMinuti() <= t.getMinuti()) 
            return true;
        
        return false;
    }

/* HELPER FUNCTION */

    //Overloading operatore <<
    ostream& operator<<(std::ostream& os, const Tempo& obj) {
        
        os << obj.toString();
        return os;
    }

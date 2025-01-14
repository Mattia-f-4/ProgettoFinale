/* Creato da: DAVID PADOVAN */

#include "Logger.h"

using namespace std;

/* COSTRUTTORI */

    //Costruttore parametrico
    Logger::Logger(const string& fileName) {

        filesystem::path sourcePath(__FILE__);          //Percorso del file sorgente

        //Determina la directory padre rispetto alla directory del file sorgente (.cpp)
        filesystem::path parentDir = sourcePath.parent_path().parent_path();
        filePath = (parentDir / fileName).string();

        if(!filesystem::exists(filePath)) {
            
            //Se il file non esiste, lo creo nella cartella 'padre'
            ofstream tempFile(filePath);
            tempFile.close();
        }

        //Apre il file per scrittura ('trunc' per cancellare il contenuto ogni volta che viene aperto)
        logFile.open(filePath, ios::out | ios::trunc);
        if(!logFile) {
            throw ios_base::failure("ERROR: Impossibile aprire il file di log");
        }
    }


/* DISTRUTTORE */
    Logger::~Logger() {
        if(logFile.is_open()) {
            logFile.close();
        }
    }

/* FUNZIONI MEMBRO */
 
    //log, per scrivere sia su terminale che su file di output (con stringhe)
    void Logger::log(const string& message) {
        cout << message;       
        logFile << message;         
    }

    //log, per i Tempi
    void Logger::log(const Tempo& time) {
        cout << time;       
        logFile << time.toString();    
    }

    //logInput, per scirvere solo su file di output (serve in caso di input dell'utente da terminale)
    void Logger::logInput(const std::string& message) {
        logFile << message;         
    }


#include "Tempo.h"
#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include "SistemaDomotico.h"
#include <iostream>
#include <string>
#include <map>

/* ENUM CLASS */

// Enum class per i comandi
enum class Commands {
    set,
    rm,
    show,
    reset,
    add,
    erase,
    exit,
    unknown
};

/* MAPPE */

// Mappa per associare comando a enum class comandi
static std::map<std::string, Commands> mapCommands = {
    {"set", Commands::set},
    {"rm", Commands::rm},
    {"show", Commands::show},
    {"reset", Commands::reset},
    {"add", Commands::add},
    {"erase", Commands::erase},
    {"exit", Commands::exit}
};

/* FUNZIONI DI CONTROLLO */

// Funzione che controlla che il nome del dispositivo non abbia ':'
bool check_name(std::string device_name) {
    if(device_name.find(':') != std::string::npos)
        return false;
    return true;
}

// Funzione che controlla la correttezza del comando
bool check_command(Commands command, std::string input) {
    int pos;
    std::string pattern;
    std::string delimiter = " ";

    switch(command) {
        case Commands::set:
             pos = input.find_last_of(delimiter); // Posizione ultimo pattern
             pattern = input.substr(pos + 1); // Ultimo pattern
             // Se ultimo pattern non è un orario, o 'on' o 'off'
             if(pattern.find(':') == std::string::npos && pattern != "on" && pattern != "off") {
                return false;
             // Altrimenti se è un orario
             } else if(pattern.find(':') != std::string::npos) {
                input.erase(pos); // Cancello ultimo pattern
                pos = input.find_last_of(delimiter); // Posizione ultimo pattern
                pattern = input.substr(pos + 1); // Ultimo pattern

                pos = input.find(delimiter); // Posizione secondo pattern
                // Se comando set time e ci sono due orari
                if(pattern.find(':') != std::string::npos && input.substr(0, pos) == "time")
                    return false;
             }
            break;
        case Commands::reset:
            // Se pattern non è 'time', 'timers' o 'all'
            if(input != "time" && input != "timers" && input != "all")
                return false;
            break;
        case Commands::add:
            // Se oltre ad 'add' ci soo altri pattern
            if(input != "add")
                return false;
            break;
        case Commands::erase:
            // Se oltre a 'erase' non ci sono altri pattern (nome dispositivo)
            if(input == "erase")
                return false;
            break;
        case Commands::exit:
            // Se oltre a 'exit' ci sono altri pattern
            if(input != "exit")
                return false;
            break;
    }
    return true;
}

/* FUNZIONI PER SISTEMA DOMOTICO*/

// Funzione che chiama setOn di SistemaDomotico
void set_device_on(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.setOn(std::cout, device);
}

// Funzione che chiama setOff di SistemaDomotico
void set_device_off(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.setOff(std::cout, device);
}

// Funzione che chiama setTimer di SistemaDomotico con solo orarioAccensione
void set_device_start(SistemaDomotico& sistemaDomotico, std::string device, std::string start) {
    // Provo a creare un oggetto tempo con la stringa data
    // Se la conversione in int fallisce o il numero è fuori dal range tempo, gestisco l'eccezione
    try {
        Tempo t_start(start);
        sistemaDomotico.setTimer(std::cout, device, t_start);
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Tempo non valido" << std::endl;
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Tempo non valido" << std::endl;
    }
}

// Funzione che chiama setTimer di SistemaDomotico con orarioAccensione e orarioSpegnimento
void set_device_start_stop(SistemaDomotico& sistemaDomotico, std::string device, std::string start, std::string stop) {
    // Provo a creare due oggetti tempo con le stringhe date
    // Se la conversione in int fallisce o il numero è fuori dal range tempo, gestisco l'eccezione
    try {
        Tempo t_start(start);
        Tempo t_stop(stop);
        sistemaDomotico.setTimer(std::cout, device, t_start, t_stop);
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Tempo non valido" << std::endl;
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Tempo non valido" << std::endl;
    }
}

// Funzione che chiama rm di SistemaDomotico
void rm_device(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.rm(std::cout, device);
}

// Funzione che chiama show di SistemaDomotico di tutti i dispositivi
void show(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.show(std::cout);
}

// Funzione che chiama show di SistemaDomotico per un dispositivo
void show_device(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.show(std::cout, device);
}

// Funzione che chiama setTime di SistemaDomotico
void set_time(SistemaDomotico& sistemaDomotico, std::string time) {
    // Provo a creare un oggetto tempo con la stringa data
    // Se la conversione in int fallisce o il numero è fuori dal range tempo, gestisco l'eccezione
    try {
        Tempo t(time);
        sistemaDomotico.setTime(std::cout, t);
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Tempo non valido" << std::endl;
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Tempo non valido" << std::endl;
    } catch (std::runtime_error& e) {
        // Se il tempo settato è 23.59 gestisco la relativa eccezione di fine programma
        sistemaDomotico.printTime(std::cout);
        std::cout << " Giornata conclusa, arrivederci!" << std::endl;
        exit(0);
    }
}

// Funzione che chiama resetTime di SistemaDomotico
void reset_time(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.resetTime(std::cout);
}

// Funzione che chiama resetTimers di SistemaDomotico
void reset_timers(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.resetTimers(std::cout);
}

// Funzione che chiama resetAll di SistemaDomotico
void reset_all(SistemaDomotico& sistemaDomotico) {
    sistemaDomotico.resetAll(std::cout);
}

// Funzione che chiama add di SistemaDomotico per un dispositivo manuale
void add_manuale(SistemaDomotico& sistemaDomotico) {
    std::string answer;
    int number;

    // Menu' dispositivi manuali disponibili
    sistemaDomotico.printTime(std::cout);
    std::cout << " Digita il corrispettivo numero per il dispositivo desiderato: " << std::endl;
    std::cout << "         0) Impianto fotovoltaico" << std::endl;
    std::cout << "         1) Pompa di calore + termostato" << std::endl;
    std::cout << "         2) Scaldabagno" << std::endl;
    std::cout << "         3) Frigorifero" << std::endl << std::endl;

    // Acquisisco numero menu'
    sistemaDomotico.printTime(std::cout);
    std::cout << " Numero: ";
    std::getline(std::cin, answer);

    enum DispManuale::DispDomotico device;

    // Provo a convertire la stringa in numero ed a settare tipo dispositivo
    // Se la conversione in int fallisce, gestisco l'eccezione
    // Se numero fuori dal menu', stampo a video l'errore
    try {
        number = stoi(answer);

        switch(number) {
            case 0:
                device = DispManuale::DispDomotico::Impianto_Fotovoltaico;
                break;
            case 1:
                device = DispManuale::DispDomotico::Pompa_di_calore_termostato;
                break;
            case 2:
                device = DispManuale::DispDomotico::Scaldabagno;
                break;
            case 3:
                device = DispManuale::DispDomotico::Frigorifero;
                break;
            default:
                sistemaDomotico.printTime(std::cout);
                std::cout << " ERROR: Numero non valido" << std::endl;
                return;
        }
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Numero non valido" << std::endl;
        return;
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Numero non valido" << std::endl;
        return;
    }

    // Acquisisco nome dispositivo
    sistemaDomotico.printTime(std::cout);
    std::cout << " Nome dispositivo: ";
    std::getline(std::cin, answer);

    // Controllo se nel nome e' presente ':', in caso stampo a video l'errore
    if(!check_name(answer)) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Carattere ':' non consentito" << std::endl;
    } else
        sistemaDomotico.add(std::cout, answer, device);
}

// Funzione che chiama add di SistemaDomotico per un dispositivo a ciclo prefissato
void add_CP(SistemaDomotico& sistemaDomotico) {
    std::string answer;
    int number;

    // Menu' dispositivi a ciclo prefissato disponibili
    sistemaDomotico.printTime(std::cout);
    std::cout << " Digita il corrispettivo numero per il dispositivo desiderato: " << std::endl;
    std::cout << "         0) Lavatrice" << std::endl;
    std::cout << "         1) Lavastoviglie" << std::endl;
    std::cout << "         2) Tapparelle elettriche" << std::endl;
    std::cout << "         3) Forno a microonde" << std::endl;
    std::cout << "         4) Asciugatrice" << std::endl;
    std::cout << "         5) Televisore" << std::endl << std::endl;

    // Acquisisco numero menu'
    sistemaDomotico.printTime(std::cout);
    std::cout << " Numero: ";
    std::getline(std::cin, answer);

    enum DispCicloPrefissato::DispDomotico device;

    // Provo a convertire la stringa in numero ed a settare tipo dispositivo
    // Se la conversione in int fallisce, gestisco l'eccezione
    // Se numero fuori dal menu', stampo a video l'errore
    try {
        number = stoi(answer);

        switch(number) {
            case 0:
                device = DispCicloPrefissato::DispDomotico::Lavatrice;
                break;
            case 1:
                device = DispCicloPrefissato::DispDomotico::Lavastoviglie;
                break;
            case 2:
                device = DispCicloPrefissato::DispDomotico::Tapparelle_elettriche;
                break;
            case 3:
                device = DispCicloPrefissato::DispDomotico::Forno_a_microonde;
                break;
            case 4:
                device = DispCicloPrefissato::DispDomotico::Asciugatrice;
                break;
            case 5:
                device = DispCicloPrefissato::DispDomotico::Televisore;
                break;
            default:
                sistemaDomotico.printTime(std::cout);
                std::cout << " ERROR: Numero non valido" << std::endl;
                return;
        }
    } catch(std::invalid_argument& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Numero non valido" << std::endl;
        return;
    } catch(std::out_of_range& e) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Numero non valido" << std::endl;
        return;
    }

    // Acquisisco nome dispositivo
    sistemaDomotico.printTime(std::cout);
    std::cout << " Nome dispositivo: ";
    std::getline(std::cin, answer);

    // Controllo se nel nome e' presente ':', in caso stampo a video l'errore
    if(!check_name(answer)) {
        sistemaDomotico.printTime(std::cout);
        std::cout << " ERROR: Carattere ':' non consentito" << std::endl;
    } else
        sistemaDomotico.add(std::cout, answer, device);
}

// Funzione che chiama erase di SistemaDomotico
void erase(SistemaDomotico& sistemaDomotico, std::string device) {
    sistemaDomotico.erase(std::cout, device);
}

/* MAIN */

int main() {  
    SistemaDomotico sistemaDomotico;

    std::string answer;
    std::string delimiter = " ";

    // Log di introduzione con legenda comandi

    std::cout << std::endl;
    std::cout << "-----------------------------------------------------------------------------" << std::endl;
    std::cout << "------------------------------ SISTEMA DOMOTICO ----------------------------- " << std::endl;
    std::cout << "----------------------------------------------------------------------------- " << std::endl << std::endl;
    
    std::cout << "Le operazioni che puoi eseguire con il tuo sistema domotico sono le seguenti: " << std::endl;
    std::cout << "# set ${DEVICENAME} on" << std::endl;
    std::cout << "# set ${DEVICENAME} off" << std::endl;
    std::cout << "# set ${DEVICENAME} ${START} [${STOP}]" << std::endl;
    std::cout << "# rm ${DEVICENAME}" << std::endl;
    std::cout << "# show" << std::endl;
    std::cout << "# show ${DEVICENAME}" << std::endl;
    std::cout << "# set time ${TIME}" << std::endl;
    std::cout << "# reset time" << std::endl;
    std::cout << "# reset timers" << std::endl;
    std::cout << "# reset all" << std::endl;
    std::cout << "# add" << std::endl;
    std::cout << "# erase ${DEVICENAME}" << std::endl << std::endl;
    std::cout << "Per uscire digitare: exit" << std::endl;

    // Ciclo per emulare l'interfaccia utente
    while(true) {
        int pos;
        answer = "";

        // Acquisisco riga di comando
        std::cout << std::endl;
        sistemaDomotico.printTime(std::cout);
        std::cout << " Cosa vuoi fare?" << std::endl;
        std::getline(std::cin, answer);

        // Acquisisco l'input ed estraggo il comando
        pos = answer.find(delimiter);
        std::string command = answer.substr(0, pos);
        answer.erase(0, pos + delimiter.length());

        std::string device;
        std::string pattern;

        Commands cmd;

        // Controllo se esiste o meno il comando
        if(mapCommands.find(command) != mapCommands.end())
            cmd = mapCommands[command];
        else
            cmd = Commands::unknown;

        // Switch statement per confrontare comando in input con quelli presenti nella mappa
        switch(cmd) {
            case Commands::set:
                // Controllo sintassi comando
                if(!check_command(mapCommands[command], answer)) {
                    sistemaDomotico.printTime(std::cout);
                    std::cout << " ERROR: Sintassi comando" << std::endl;
                    break;
                }
                pos = answer.find(delimiter); // Posizione secondo pattern
                // Se comando set time ${TIME}
                if(answer.substr(0, pos) == "time") {
                    pos = answer.find_last_of(delimiter); // Posizione ultimo pattern
                    std::string time = answer.substr(pos + 1); // Ultimo pattern
                    set_time(sistemaDomotico, time);

                } else {
                    pos = answer.find_last_of(delimiter); // Posizione ultimo pattern
                    pattern = answer.substr(pos + 1); // Ultimo pattern

                    // Se comando set ${DEVICENAME} on oppure set ${DEVICENAME} off
                    if(pattern == "on" || pattern == "off") {
                        answer.erase(pos); // Cancello ultimo pattern
                        device = answer; // Nome dispositivo

                        if(pattern == "on")
                            set_device_on(sistemaDomotico, device);
                        else if ( pattern == "off")
                            set_device_off(sistemaDomotico, device);
                    }
                    else {
                        answer.erase(pos); // Cancello ultimo pattern
                        pos = answer.find_last_of(delimiter); // Posizione ultimo pattern
                        // Se comando set ${DEVICENAME} ${START}
                        if(answer.find_last_of(':') == std::string::npos) {
                            std::string start = pattern; // Orario accensione
                            device = answer; // Nome dispositivo

                            set_device_start(sistemaDomotico, device, start);
                        // Se comando set ${DEVICENAME} ${START} [${STOP}]
                        } else if (answer.substr(pos + 1).find(":") != std::string::npos) {
                            std::string stop = pattern; // Orario spegnimento
                            std::string start = answer.substr(pos + 1); // Orario accensione

                            answer.erase(pos); // Cancello ultimo pattern
                            device = answer; // Nome dispositivo

                            set_device_start_stop(sistemaDomotico, device, start, stop);
                        // Altrimenti comando errato
                        } else {
                            sistemaDomotico.printTime(std::cout);
                            std::cout << " ERROR: Sintassi comando" << std::endl;
                        }
                    }
                }
                break;

            case Commands::rm:
                device = answer;
                rm_device(sistemaDomotico, device);
                break;

            case Commands::show:
                // Se comando show
                if(answer == "show")
                    show(sistemaDomotico);
                // Altrimenti comando show ${DEVICENAME}
                else{
                    device = answer;
                    show_device(sistemaDomotico, device);
                }
                break;

            case Commands::reset:
                // Controllo sintassi comando
                if(!check_command(mapCommands[command], answer)) {
                    sistemaDomotico.printTime(std::cout);
                    std::cout << " ERROR: Sintassi comando" << std::endl;
                    break;
                }
                pos = answer.find(delimiter);
                pattern = answer.substr(0, pos);
                // Se comando reset time
                if(pattern == "time")
                    reset_time(sistemaDomotico);
                // Se comando reset timers
                else if(pattern == "timers")
                    reset_timers(sistemaDomotico);
                // Altrimenti comando reset all
                else
                    reset_all(sistemaDomotico);
                break;

            case Commands::add:
                // Controllo sintassi comando
                if(!check_command(mapCommands[command], answer)) {
                    sistemaDomotico.printTime(std::cout);
                    std::cout << " ERROR: Sintassi comando" << std::endl;
                    break;
                }
                // Chiedo se si vuole aggiungere un dispositivo manuale o CP
                sistemaDomotico.printTime(std::cout);
                std::cout << " Digita M (manuale) o CP (ciclo prefissato): ";
                std::getline(std::cin, answer);
                std::cout << std::endl;
                // Se dispositivo manuale
                if(answer == "M")
                    add_manuale(sistemaDomotico);
                // Se dispositivo a ciclo prefissato
                else if(answer == "CP")
                    add_CP(sistemaDomotico);
                else {
                    sistemaDomotico.printTime(std::cout);
                    std::cout << " ERROR: Risposta non valida" << std::endl;
                }
                break;

            case Commands::erase:
                // Controllo sintassi comando
                if(!check_command(mapCommands[command], answer)) {
                    sistemaDomotico.printTime(std::cout);
                    std::cout << " ERROR: Nome dispositivo mancante" << std::endl;
                    break;
                }
                device = answer;
                erase(sistemaDomotico, device);
                break;

            case Commands::exit:
                // Controllo sintassi comando
                if(!check_command(mapCommands[command], answer)) {
                    sistemaDomotico.printTime(std::cout);
                    std::cout << " ERROR: Sintassi comando" << std::endl;
                    break;
                }
                exit(0);
                break;

            default:
                sistemaDomotico.printTime(std::cout);
                std::cout << " ERROR: Comando '" << command << "' non esistente!" << std::endl;
        }
    }

    return 0; 
}
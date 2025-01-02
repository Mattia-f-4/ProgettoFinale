#include "Tempo.h"
#include "SistemaDomotico.h"
#include "DispManuale.h"
#include "DispCicloPrefissato.h"
#include <iostream>
#include <string>
#include <map>

enum class Commands {
    set,
    rm,
    show,
    reset,
    exit
};

static std::map<std::string, Commands> mapCommands = {
    {"set", Commands::set},
    {"rm", Commands::rm},
    {"show", Commands::show},
    {"reset", Commands::reset},
    {"exit", Commands::exit}
};

SistemaDomotico sistemaDomotico;

void set_device_on(std::string device){
    sistemaDomotico.setOn(std::cout, device);
}

void set_device_off(std::string device){
    sistemaDomotico.setOff(std::cout, device);
}

void set_device_start(std::string device, std::string start){
    std::string delimiter = ":";

    int start_h = stoi(start.substr(0, start.find(delimiter)));
    start.erase(0, start.find(delimiter) + delimiter.length());
    int start_m = stoi(start.substr(0, start.find(delimiter)));

    Tempo t_start(start_h, start_m);

    sistemaDomotico.setTimer(std::cout, device, t_start);
}

void set_device_start_stop(std::string device, std::string start, std::string stop){
    std::string delimiter = ":";

    int start_h = stoi(start.substr(0, start.find(delimiter)));
    start.erase(0, start.find(delimiter) + delimiter.length());
    int start_m = stoi(start.substr(0, start.find(delimiter)));

    int stop_h = stoi(stop.substr(0, stop.find(delimiter)));
    stop.erase(0, stop.find(delimiter) + delimiter.length());
    int stop_m = stoi(stop.substr(0, stop.find(delimiter)));

    Tempo t_start(start_h, start_m);
    Tempo t_stop(stop_h, stop_m);

    sistemaDomotico.setTimer(std::cout, device, t_start, t_stop);
}

void rm_device(std::string device){
    sistemaDomotico.rm(std::cout, device);
}

void show(){
    sistemaDomotico.show(std::cout);
}

void show_device(std::string device){
    sistemaDomotico.show(std::cout, device);
}

void set_time(std::string time){
    std::string delimiter = ":";

    int time_h = stoi(time.substr(0, time.find(delimiter)));
    time.erase(0, time.find(delimiter) + delimiter.length());
    int time_m = stoi(time.substr(0, time.find(delimiter)));

    Tempo t(time_h, time_m);

    sistemaDomotico.setTime(std::cout, t);
}

void reset_time(){
    sistemaDomotico.resetTime(std::cout);
}

void reset_timers(){
    sistemaDomotico.resetTimers();
}

void reset_all(){
    sistemaDomotico.resetAll();
}

int main() {  

    std::string answer;
    std::string delimiter = " ";

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
    std::cout << "# reset all" << std::endl << std::endl;
    std::cout << "Per uscire digitare: exit" << std::endl;

    while(true){
        answer = "";

        std::cout << std::endl << "Cosa vuoi fare?" << std::endl;
        std::getline(std::cin, answer);

        std::string command = answer.substr(0, answer.find(delimiter));
        answer.erase(0, answer.find(delimiter) + delimiter.length());

        std::string device;
        std::string pattern;
        
        switch(mapCommands[command]){
            case Commands::set:
                if(answer.substr(0, answer.find(delimiter)) == "time"){
                    pattern = answer.substr(0, answer.find(delimiter));
                    answer.erase(0, answer.find(delimiter) + delimiter.length());
                    set_time(answer.substr(0, answer.find(delimiter)));
                } else {
                    device = answer.substr(0, answer.find(delimiter));
                    answer.erase(0, answer.find(delimiter) + delimiter.length());
                    pattern = answer.substr(0, answer.find(delimiter));

                    if(pattern == "on")
                        set_device_on(device);
                    else if ( pattern == "off")
                        set_device_off(device);
                    else {
                        answer.erase(0, answer.find(delimiter) + delimiter.length());
                        if(answer.substr(0, answer.find(delimiter)) == pattern)
                            set_device_start(device, pattern);
                        else
                            set_device_start_stop(device, pattern, answer.substr(0, answer.find(delimiter)));
                    }
                }
                break;

            case Commands::rm:
                device = answer.substr(0, answer.find(delimiter));
                rm_device(device);
                break;

            case Commands::show:
                if(answer == "show")
                    show();
                else{
                    device = answer.substr(0, answer.find(delimiter));
                    show_device(device);
                }
                break;

            case Commands::reset:
                pattern = answer.substr(0, answer.find(delimiter));
                if(pattern == "time")
                    reset_time();
                else if(pattern == "timers")
                    reset_timers();
                else
                    reset_all();
                break;

            case Commands::exit:
                exit(0);
                break;
        }
    }

    /*Tempo t1(25, -2);
    Tempo t2(18, 0);
    Tempo t3(20, 0);
    Tempo t4(22, 0);*/  

    /*DispManuale disp1("Scaldabagno 1", DispManuale::DispDomotico::Scaldabagno, t1, t2);
    DispManuale disp2("Scaldabagno 2", DispManuale::DispDomotico::Scaldabagno, t3, t4);

    std::cout << "ID: " << disp1.getID() << std::endl;
    std::cout << "Nome: " << disp1.getNome() << std::endl;
    std::cout << "Potenza: " << disp1.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp1.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp1.getSpegnimento() << std::endl;

    std::cout << std::endl;

    std::cout << "ID: " << disp2.getID() << std::endl;
    std::cout << "Nome: " << disp2.getNome() << std::endl;
    std::cout << "Potenza: " << disp2.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp2.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp2.getSpegnimento() << std::endl;

    Tempo t5(10, 30);
    Tempo t6(12, 30);

    DispCicloPrefissato disp3("Microonde 1", DispCicloPrefissato::DispDomotico::Forno_a_microonde, t5);
    DispCicloPrefissato disp4("Microonde 2", DispCicloPrefissato::DispDomotico::Forno_a_microonde, t6);

    std::cout << std::endl;

    std::cout << "ID: " << disp3.getID() << std::endl;
    std::cout << "Nome: " << disp3.getNome() << std::endl;
    std::cout << "Potenza: " << disp3.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp3.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp3.getDurata() << std::endl;

    std::cout << std::endl;

    std::cout << "ID: " << disp4.getID() << std::endl;
    std::cout << "Nome: " << disp4.getNome() << std::endl;
    std::cout << "Potenza: " << disp4.getPotenza() << std::endl;
    std::cout << "Tempo accensione: " << disp4.getAccensione() << std::endl;
    std::cout << "Tempo spegnimento: " << disp4.getDurata() << std::endl;

    
    SistemaDomotico casa;
    casa.setOn(std::cout,"Lavastoviglie");
    casa.setOff(std::cout,"Lavatrice");*/

    return 0; 
}
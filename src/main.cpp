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
    Tempo t_start(start);
    sistemaDomotico.setTimer(std::cout, device, t_start);
}

void set_device_start_stop(std::string device, std::string start, std::string stop){
    Tempo t_start(start);
    Tempo t_stop(stop);

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
    Tempo t(time);

    sistemaDomotico.setTime(std::cout, t);
}

void reset_time(){
    sistemaDomotico.resetTime(std::cout);
}

void reset_timers(){
    sistemaDomotico.resetTimers(std::cout);
}

void reset_all(){
    sistemaDomotico.resetAll(std::cout);
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
                    std::string time = answer.substr(answer.find_last_of(delimiter) + 1);
                    set_time(time);

                } else {
                    pattern = answer.substr(answer.find_last_of(delimiter) + 1); 

                    if(pattern == "on" || pattern == "off") {
                        answer.erase(answer.find_last_of(delimiter));
                        device = answer;

                        if(pattern == "on")
                            set_device_on(device);
                        else if ( pattern == "off")
                            set_device_off(device);
                    }
                    else {
                        answer.erase(answer.find_last_of(delimiter));
                        if(answer.find_last_of(':') == std::string::npos){
                            std::string start = pattern;
                            device = answer;

                            set_device_start(device, start);
                        } else {
                            std::string stop = pattern;
                            std::string start = answer.substr(answer.find_last_of(delimiter) + 1);

                            answer.erase(answer.find_last_of(delimiter));
                            device = answer;

                            set_device_start_stop(device, start, stop);
                        }
                    }
                }
                break;

            case Commands::rm:
                device = answer;
                std::cout << device << std::endl;
                rm_device(device);
                break;

            case Commands::show:
                if(answer == "show")
                    show();
                else{
                    device = answer;
                    std::cout << device << std::endl;
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

    return 0; 
}
# Sistema Domotico

### Autori:
* _David Francesco Padovan_
* _Mattia Favretto_
* _Giacomo Carlotto_

### Indice
1. [Struttura progetto](#1-struttura-progetto)
2. [Scelte implementative](#2-scelte-implementative)
3. [Timer](#3-Timer)
4. [Aggiunta dispositivi](#4-aggiunta-dispositivi)
5. [Dispositivo, DispManuale e DispCicloPrefissato](#5-dispositivo-dispmanuale-e-dispcicloprefissato)
6. [Reset](#6-reset)
7. [Sistema Domotico](#7-sistema-domotico)
8. [Utilizzo](#8-utilizzo)
9. [Considerazioni finali](#9-considerazioni-finali)

## 1. Struttura progetto

### 1.1.

    SistemaDomotico
    ├── build
    ├── include
    │   ├── DispCicloPrefissato.h
    │   ├── DispManuale.h
    │   ├── Dispositivo.h
    │   ├── Logger.h
    │   ├── SistemaDomotico.h
    │   └── Tempo.h
    ├── src
    │   ├── DispCicloPrefissato.cpp
    │   ├── DispManuale.cpp
    │   ├── Dispositivo.cpp
    │   ├── Logger.cpp
    │   ├── SistemaDomotico.cpp
    │   ├── Tempo.cpp
    │   └── main.cpp
    ├── README.md
    ├── CMakeLists.txt
    ├── logExample1.txt
    └── logExample2.txt

## 2. Scelte implementative

### 2.1.
I metodi ```setOn``` e ```setOff``` sono stati duplicati, creandone una copia chiamata ```setOnbyTimer``` e ```setOffbyTimer``` nel caso in cui l'**accensione** di un **dispositivo** derivi da un timer _pre-impostato_.<br>
Tale copia è stata resa ```private``` per essere richiamata solo da ```setTime```. Questa scelta ha prodotto una maggiore semplicità a livello logico nella gestione delle condizioni possibili. 

## 3. Timer

### 3.1.
All'interno del programma si è deciso di dare la possibilità di avere più **timer** _preimpostati_ simultaneamente per lo stesso **dispositivo**, tali **timer** non devono però essere _sovrapposti_ o "_intrecciati_". 

### 3.2.
Per i **dispositivi manuali** si è deciso che nel caso in cui venga impostato un **timer** e prima della sua **accensione** il **dispositivo** venga acceso _manualmente_, all'ora di **accensione** del **timer** questo verrà ignorato in quanto il **dispositivo** è già acceso, ma l'eventuale **timer** di **spegnimento** viene invece applicato. 

### 3.3.
Per i **dispositivi CP** si è deciso che nel caso in cui venga impostato un **timer** e prima della sua **accensione** il **dispositivo** venga acceso _manualmente_, all'ora di **accensione** del **timer** nel caso in cui il **dispositivo** sia ancora acceso viene ignorato il **timer** di **accensione** e si elimina il **timer** di **spegnimento** associato ad esso. 

### 3.4.
Nel caso in cui sia già presente un **timer** per lo stesso orario di **accensione**, per lo stesso **dispositivo**, viene impedita la creazione di un nuovo **timer**, seppur eventualmente abbia un orario di fine differente.

## 4. Aggiunta dispositivi

### 4.1.
Il **sistema domotico** prevede la possibilità di aggiungere altri **dispositivi**, scegliendone un nome che però deve essere unico e quindi diverso da tutti gli altri dispositivi già presenti.<br>
Il **tipo** dei nuovi **dipositivi** aggiunti deve essere uno tra quelli previsti nella consegna del progetto, non sono quindi previste aggiunte di **dispositivi** completamente nuovi. <br>
Per quanto riguarda il formato del nome del **dispositivo**, si è deciso che non possa contenere il carattere '_:_' per evitare conflitti con **orari**.

## 5. Dispositivo, DispManuale e DispCicloPrefissato

### 5.1.
L'**ID** è stato da noi usato come parametro per distinguere i **dispositivi CP** dai **dispositivi manuali**, i **dispositivi CP** hanno infatti **ID** _dispari_ e i **manuali** hanno un **ID** _pari_.

## 6. Reset

### 6.1.
Il metodo ```resetAll()``` comporta un **reset** anche del **database** dei **dispositivi**, quindi vengono rimossi eventuali **dispositivi** nuovi e ripristinati quelli inizialmente presenti di **default**.
Questo comportamento non è previsto per ```resetTimers()``` e per ```resetTime()```.

### 6.2.
Il metodo ```resetTimers()``` elimina tutti i **timer** attualmente presenti nel sistema tranne i **timer** di **spegnimento** dei **dispositivi a ciclo prefissato** che sono attualmente accesi.

## 7. Sistema Domotico

### 7.1.
All'interno di ```SistemaDomotico.cpp``` sono state lasciate _2_ funzioni di **debug**, chiamate ```printTimeLine``` e ```debugDataBase```, le quali non hanno alcuna utilità nel progetto finale ma sono state utilizzate durante lo sviluppo per risolvere eventuali problematiche.<br>
Sono state lasciate nel file finale per completezza e per mostrare il processo di sviluppo.

## 8. Utilizzo

### 8.1.
Per compilare con ***CMake*** ed eseguire il programma, eseguire i seguenti comandi da dentro la cartella ```build```:

```shell
CMake ..
make
./main
```

## 9. Considerazioni finali

### 9.1.
Nonostante ci sia stata una netta suddivisione del carico e sviluppo del lavoro, il progetto è stato realizzato in comune accordo sulle scelte implementative. <br>
La progettazione dei file è stata eseguita con il supporto di ciascun membro nelle idee e risoluzione di eventuali errori e bug di percorso.
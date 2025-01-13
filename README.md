SCELTE IMPLEMENTATIVE

1. 
I metodi setOn e setOff sono stati duplicati, creandone una copia chiamata setOnbyTimer e setOffbyTimer nel caso in cui l'accensione di un dispositivo derivi da un timer pre-impostato. Tale copia è stata resa private per essere richiamata solo da setTime. Questa scelta ha prodotto una maggiore semplicità a livello logico nella gestione delle condizioni possibili. 

*/TIMER/*
2. 
All'interno del programma si è deciso di dare la possibilità di avere più timer preimpostati simultaneamente per lo stesso dispositivo, tali timer non devono però essere sovrapposti o "intrecciati". 

3. 
Per i dispositivi manuali si è deciso che nel caso in cui venga impostato un timer e prima della sua accensione il dispositivo venga acceso manualmente, all'ora di accensione del timer questo verrà ignorato in quanto il dispositivo è già acceso, ma l'eventuale timer di spegnimento viene invece applicato. 

4. 
Per i dispositivi CP si è deciso che nel caso in cui venga impostato un timer e prima della sua accensione il dispositivo venga acceso manualmente, all'ora di accensione del timer nel caso in cui il dispositivo sia ancora acceso viene ignorato il timer di accensione e si elimina il timer di spegnimento associato ad esso. 

5. 
Nel caso in cui sia già presente un timer per lo stesso orario di accensione, per lo stesso dispositivo, viene impedita la creazione di un nuovo timer, seppur eventualmente abbia un orario di fine differente.

*/AGGIUNTA DISPOSITIVI/*

6.
Il SistemaDomotico prevede la possibilità di aggiungere altri dispositivi, scegliendone un nome che però deve essere unico e quindi diverso da tutti gli altri dispositivi già presenti. Il tipo dei nuovi dipositivi aggiunti deve essere uno tra quelli previsti nella consegna del progetto, non sono quindi previste aggiunte di dispositivi completamente nuovi.

*/CLASSI DISPOSITIVO, DISPMANUALE, DISPCICLOPREFISSATO/*

7.
L'ID è stato da noi usato come parametro per distinguere i dispositivi CP dai dispositivi Manuali, i dispositivi CP hanno infatti ID dispari e i manuali hanno un ID pari.

*/MAIN/*

8.
Si è deciso che per i tutti i comandi nei nomi dei dispositivi ci fosse tolleranza tra maiscole e minuscole, in modo da permettere ad esempio "set Lavatrice on" o "set lavatrice on" come comandi possibili per accendere lo stesso dispositivo.

*/RESET/*

9.
Il metodo 'resetAll()' comporta un reset anche del database dei dispositivi, quindi vengono rimossi eventuali dispositivi nuovi e ripristinati quelli inizialmente presenti di default.
Questo comportamento non è previsto per 'resetTimers()' e per 'resetTime()'


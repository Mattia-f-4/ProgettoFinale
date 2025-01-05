SCELTE IMPLEMENTATIVE

1. 
I metodi setOn e setOff sono stati duplicati, creandone una copia chiamata setOnbyTimer e setOffbyTimer nel caso in cui l'accensione di un dispositivo derivi da un timer pre-impostato. Tale copia è stata resa private per essere richiamata solo da setTime. Questa scelta ha prodotto una maggiore semplicità a livello logico nella gestione delle condizioni possibili. 

2. 
All'interno del programma si è deciso di dare la possibilità di avere più timer preimpostati simultaneamente per lo stesso dispositivo. 

3. 
Per i dispositivi manuali si è deciso di impedire la situazione in cui i vari timer siano intrecciati tra di loro, mantenendo quindi l'orario di fine di un timer minore rispetto all'orario di inizio di un altro timer. 

4. 
Per i dispositivi a ciclo prefissato si è invece reso possibile l'accensione di un dispositivo con orario di termine superiore rispetto all'inizio di un altro timer, estendendo quindi la durata nel caso in cui i 2 timer si dovessero sovrapporre.  

se c'è gia un timer per lo stesso orario di accensione per lo stesso dispositivo impedisco la creazione di un nuovo timer
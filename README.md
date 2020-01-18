# allarme-scambi
Sketch per Arduino, monitorizza assorbimento corrente e stacca dopo x secondi.

Il progetto nasce dopo un inconveniente tecnico ad un circuito per alimentare gli scambi dei trenini elettrici, comandati da una bobina elettromagnetica in AC (o DC).
Il sistema di comando è rimasto attivato, la sfortuna ha voluto che la bobina non facesse alcun rumore, e non essendoci nessun microswitch di fine corsa, la bobina si è surriscaldata danneggiandosi.

Ho quindi provato a costruire qualcosa con Arduino, approfittando anche dell'occasione per imparare ad utilizzare questo interessante microcontrollore.
Ho deciso di utilizzare il sensore di assorbimento basato su ACS712 per avere un segnale di riferimento. Non mi serviva tanto sapere QUANTO assorbimento c'è, il comando agli scambi è sostanzialmente un BASSO/ALTO; più che altro mi serve sapere il tempo di azionamento, e il sensore mi è sembrato comunque il sistema più comodo da inserire in serie al circuito AC.

Risltato da ottenere: monitorare l'assorbimento in AC dal trasformatore di comando; se rilevo assorbimento per più di 3/4 secondi azionare un buzzer di allarme e contemporaneamente un relè che toglie l'alimentazione AC, sfruttando i contatti NC del relè stesso.
Dato che il caso di allarme, in teoria, dovrebbe essere molto raro, non ho implementato nulla per ripristinare il sistema se non il semplice reset di arduino per riavviare il codice e riportare bassa l'uscita che comanda il relè, e quindi ripristinare il collegamento.

PREMESSA IMPORTANTE: il codice rispecchia la mia ignoranza su tutto quello che può rendere più efficiente il codice stesso, non ho mai programmato in C++ e sto imparando.

Sono attualmente in fase di test con la versione V4, ma nutro buone speranze di funzionamento affidabile.

Il problema principale era costruire la parte di codice che mi desse risultati affidabili con il sensore ACS712 (su breakout board) e una misurazione di corrente alternata.
Ho recuperato un codice funzionante su youtube e l'ho implementato con le mie logiche ed i primi risultati sono incoraggianti.

La V4 fa le seguenti cose: all'avvio esegue un test del buzzer e del relè; nel ciclo loop c'è un doppio IF che monitora l'assorbimento e fa partire un contatore se questo aumenta oltre una certa soglia di isteresi.
All'azionamento dello scambio il sensore riporta assorbimento positivo, il contatore parte e quando il tempo di azionamento raggiunge i 3/4 secondi suona il buzzer e attiva il relè. Il buzzer rimane attivo 5 secondi e poi riprende il monitoraggio dell'assorbimento, anche se sarà per forza a zero, visto che l'uscita al relè rimane alta. 

Per ripristinare tutto va resettato arduino.

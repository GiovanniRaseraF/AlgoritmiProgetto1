# AlgoritmiProgetto1
Scopo del progetto di laboratorio è verificare che lo studente sia in grado di progettare, implementare e analizzare la complessità di un programma usando gli strumenti illustrati durante le lezioni del corso di algoritmi e strutture dati. I programmi prodotti dovranno risolvere alcuni problemi classici di natura computazionale e dovranno essere formalmente corretti. Ogni progetto di laboratorio consiste nella produzione di uno o più programmi che risolvano un problema computazionale assegnato, nella stima empirica della complessità di tali programmi al variare della dimensione dell'input e di eventuali altri parametri, e nella redazione di una relazione in cui si discutano puntualmente alcune scelte implementative e si faccia un'analisi della stima di complessità.

Di seguito sono riportate le consegne per la prima parte del progetto di laboratorio, da consegnare necessariamente prima dell'iscrizione all'esame finale di teoria.

La prima parte del progetto richiede l'implementazione e l'analisi dei tempi medi di esecuzione di tre algoritmi di selezione (calcolo del k-esimo elemento più piccolo in un vettore non ordinato di interi). I tre algoritmi di selezione, denominati rispettivamente "quick select", "heap select" e "median-of-medians select", dovranno avere le seguenti caratteristiche:

Quick select

Si tratta di una variante dell'algoritmo di ordinamento "quick sort", in cui ogni chiamata ricorsiva su un intervallo [i,j] del vettore fornito in input termina in tempo costante ogniqualvolta il parametro k non sia contenuto nell'intervallo [i,j]. L'algoritmo deve avere complessità temporale asintotica Θ(n2) nel caso pessimo e O(n) nel caso medio, dove n è il numero di elementi del vettore.

Heap select

Questo algoritmo di selezione utilizza due min-heap, denominate H1 e H2. La prima heap H1 é costruita a partire dal vettore fornito in input in tempo lineare e non viene modificata. La seconda heap H2 contiene inizialmente un solo nodo, corrispondente alla radice di H1. All'i-esima iterazione, per i che va da 1 a k−1, l'algoritmo estrae la radice di H2, che corrisponde a un nodo xi in H1, e reinserisce in H2 i nodi successori (figli sinistro e destro) di xi nella heap H1. Dopo k−1 iterazioni, la radice di H2 corrisponderà al k-esimo elemento più piccolo del vettore fornito in input.
L'algoritmo descritto ha complessità temporale O(n+klogk) sia nel caso pessimo che in quello medio. Per k sufficientemente piccolo, quindi, l'algoritmo "heap select" sarà preferibile, almeno nel caso pessimo, all'algoritmo "quick select". È possibile implementare una variante che utilizzi opportunamente min-heap o max-heap, a seconda del valore di k.

Median-of-medians select

L'algoritmo è basato sulla suddivisione del vettore fornito in input in blocchi di dimensione limitata e sul calcolo della mediana delle mediane. Più precisamente, l'algoritmo esegue le seguenti operazioni:
- divisione dell'array in blocchi di 5 elementi, escluso eventualmente l'ultimo blocco che potrà contenere meno di 5 elementi,
- ordinamento e calcolo della mediana di ciascun blocco,
- calcolo della mediana M delle mediate dei blocchi, attraverso chiamata ricorsiva allo stesso algoritmo
- partizionamento dell'intero array attorno alla mediana M, attraverso una variante della procedura "partition" dell'algoritmo "quick sort"
- chiamata ricorsiva nella parte di array che sta a sinistra o a destra della mediana M, in funzione del valore k fornito in input.
Il modo più semplice per implementare quest'algoritmo consiste nell'allocare, ad ogni chiamata ricorsiva, un nuovo vettore per memorizzare le mediane dei blocchi. Esiste tuttavia un approccio più efficiente e "in place" che riutilizza lo spazio allocato per il vettore originariamente fornito in input. La valutazione del progetto terrà conto della variante implementata (quella "in place", essendo più complicata ma anche più efficiente, sarà valutata con un punteggio più alto).
Indipendentemente dalla variante implementata, nel caso pessimo l'algoritmo dovrà avere complessità, sia temporale che spaziale, pari a Θ(n).



Modalità di consegna

Si richiede:

1) L'implementazione in un linguaggio a scelta (ad esempio, C, C++, Java) dei tre algoritmi descritti sopra, in modo che siano formalmente corretti (è possibile assumere che gli input siano ben formati, ovvero che i vettori non siano vuoti e che il parametro k sia sempre positivo e minore o uguale alla dimensione n del vettore). Per agevolare la verifica di correttezza da parte del docente sono stati predisposti tre moduli "Virtual Programming Laboratory" (VPL) da utilizzare per caricare il codice degli algoritmi. Una condizione necessaria alla valutazione dell'elaborato è il superamento di tutti i test previsti, per tutti e tre gli algoritmi. Nota: l'esecuzione di un programma lato server attraverso un modulo VPL garantisce uno spazio di memoria di almeno 64KB, giudicato ampiamente sufficiente per risolvere il problema assegnato con qualunque algoritmo fra quelli sopra descritti.

2) La stima dei tempi medi di esecuzione per tre algoritmi, al variare della dimensione n del vettore ed eventualmente del parametro k (nei casi, ovviamente, in cui si ritenga esista una correlazione fra tempo di esecuzione e parametro k). Il vettore in input deve essere generato in modo pseudo-casuale con interi, eventualmente anche negativi, e il tempo di inizializzazione dell'input dev'essere opportunamente scomputato dalla stima del tempo di esecuzione. Gli algoritmi valutati in questa parte dovranno essere gli stessi di quelli presentati al punto 1) (ad esclusione, ovviamente, delle parti di codice che gestiscono l'input e l'output). I tempi di esecuzione devono essere misurati con un errore relativo massimo pari a 0.01 (1%), utilizzando un orologio di sistema monotono di tipo "stopwatch" e calcolandone preliminarmente la risoluzione. Dal momento che i tempi di esecuzione dipenderanno dall'input generato in modo pseudo-casuale, si richiede la stima del tempo medio di esecuzione e della sua deviazione standard. Anche per questa parte è stato predisposto un modulo VPL da utilizzare per caricare il programma che raccoglie i tempi medi di esecuzione e le deviazioni standard per ciascuno dei tre algoritmi (in questo caso non sarà predisposto alcun test automatico, e per ovvie ragioni si sconsiglia l'esecuzione del programma lato server...). Tale programma dovrà produrre in output una sequenza di record nel formato "N K T1 D1 T2 D2 T3 D3", dove N è la dimensione del vettore generato, K è un'istanza del parametro k, Ti (per i=1,2,3) è una stima del tempo medio del i-esimo algoritmo e Di una stima della relativa deviazione standard. Si consiglia di generare un centinaio di campioni della dimensione N che variano indicativamente fra 100 e 5000000, con una distribuzione esponenziale o geometrica (ovvero, i campioni di N tenderanno a essere più "densi" negli intervalli di valori bassi).

3) I dati raccolti al punto 2) devono essere presentati e discussi in una relazione, da caricare sul server in formato PDF. La valutazione della relazione contribuirà in modo significativo al voto finale del progetto di laboratorio. Non è necessario inviare una relazione con molte pagine: qualche decina di pagine è largamente sufficiente a discutere gli aspetti importanti dell'implementazione e dell'analisi dei tempi di esecuzione. Si consiglia l'uso di grafici comparativi, sia in scale lineari - N vs t(N) - che doppiamente logaritmiche - log(N) vs log(t(N)).



NOTA BENE: Durante l'elaborazione del progetto, sarà possibile caricare diverse versioni dei programmi sui vari moduli VPL (sostituendo ovviamente i vecchi file). Il progetto viene considerato come consegnato una volta che la relazione in formato PDF viene caricata online. A partire da quel momento il docente potrà prendere visione della relazione e dei codici sorgente forniti.

Sono ammessi gruppi di massimo 4 persone per lo svolgimento del progetto. Il sito e-learning dell'università non permette la creazione autonoma di gruppi; si consiglia quindi di procedere scegliendo un "rappresentante" per ogni gruppo, che avrà la responsabilità di caricare tutti i file sul sito, inclusa la relazione finale. È importante che la relazione riporti in chiaro i nomi, i cognomi, le email, e i numeri di matricola di ciascun componente del gruppo.

Non è fissata una data di consegna stretta per gli elaborati. Si consiglia comunque di cercare di consegnare la prima parte del progetto all'inizio del secondo semestre, prima di cominciare a lavorare sulla seconda parte del progetto. I progetti consegnati verranno valutati dal docente a intervalli regolari (approssimativamente ogni 2-3 settimane). Qualora fosse necessaria una valutazione in tempi brevi, si prega di contattare il docente per e-mail (gabriele.puppis@uniud.it) oppure venire a ricevimento.
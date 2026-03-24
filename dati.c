/**
 * @file dati.c
 * @brief Modulo che gestisce le strutture dati principali
 * e le relative operazioni per la creazione, manipolazione, accesso e distruzione.
 *
 * Questo file contiene l'implementazione concreta degli Abstract Data Type (ADT)
 * dichiarati in `dati.h`: `Animale`, `Lista`, `Nodo` e `NegozioData`.
 * Tutte le operazioni sui dati avvengono internamente, garantendo l'incapsulamento
 * e fornendo un'interfaccia pubblica ben definita tramite i puntatori opachi.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#include "dati.h"
#include "controlli.h" // Necessario per le costanti come MAXCHAR1, SEPARATORE, ecc. se non solo in dati.h

#include <stdlib.h> // Per malloc, free
#include <string.h> // Per strncpy, strlen
#include <stdio.h>  // Per printf, puts, fprintf

/**
 * @brief Definizione concreta della struttura `Nodo`.
 * Rappresenta un elemento generico in una lista concatenata.
 * Contiene un puntatore `dato` a un tipo generico (void*) e un puntatore al `next` nodo.
 */
struct Nodo {
    void* dato;
    struct Nodo* next;
};

/**
 * @brief Definizione concreta della struttura `Lista`.
 * Rappresenta l'intestazione di una lista concatenata generica.
 * Contiene un puntatore `head` al primo nodo della lista.
 */
struct Lista {
    Nodo* head;
};

/**
 * @brief Definizione concreta della struttura `Animale`.
 * Contiene i campi specifici per un animale: ID, razza, nome, età e prezzo.
 */
struct Animale {
    unsigned int id;
    char razza[MAXCHAR1];
    char nome[MAXCHAR1];
    int eta;
    float prezzo;
};

/**
 * @brief Definizione concreta della struttura `NegozioData`.
 * Contiene i dati specifici di un negozio: ID e un puntatore alla sua lista di inventario di animali.
 */
struct NegozioData {
    unsigned int id;
    Lista* inventarioAnimali; // Questo è un puntatore alla struttura Lista definita sopra
};


/**
 * @brief Crea un nuovo nodo per la lista generica.
 * Questa è una funzione statica, interna al modulo `dati.c`.
 *
 * @param dato Il puntatore al dato che il nodo dovrà contenere.
 * @return Un puntatore al nuovo nodo creato, o NULL se l'allocazione fallisce.
 */
static NodoPtr creaNodo(void* dato) {
    NodoPtr nuovo = (NodoPtr) malloc(sizeof(Nodo));
    if (nuovo != NULL) {
        nuovo->dato = dato;
        nuovo->next = NULL;
    }
    return nuovo;
}

/**
 * @brief Distrugge un singolo nodo, liberando la memoria allocata per esso.
 * Questa è una funzione statica, interna al modulo `dati.c`.
 * Non libera il dato contenuto nel nodo; la responsabilità è del chiamante
 * o della funzione `distruggiLista`.
 *
 * @param nodo Il puntatore al nodo da distruggere.
 */
static void distruggiNodo(NodoPtr nodo) {
    free(nodo);
}

/**
 * @brief Controlla se un puntatore a nodo è NULL.
 * Questa è una funzione statica, interna al modulo `dati.c`.
 *
 * @param n Il puntatore al nodo da controllare.
 * @return 1 se il nodo è NULL, 0 altrimenti.
 */
static int isNodoNull(const NodoPtr n) {
    return (n == NULL);
}

/**
 * @brief Crea una nuova lista generica vuota.
 *
 * @return Un puntatore alla nuova lista creata, o NULL se l'allocazione fallisce.
 */
ListaPtr creaLista() {
    ListaPtr nuovaLista = (ListaPtr) malloc(sizeof(Lista));
    if (nuovaLista != NULL) {
        nuovaLista->head = NULL;
    }
    return nuovaLista;
}

/**
 * @brief Distrugge una lista generica, liberando tutta la memoria associata.
 *
 * Itera attraverso tutti i nodi della lista, liberando prima il dato contenuto
 * in ciascun nodo (se `distruggiDatoFn` è fornita) e poi il nodo stesso.
 * Infine, libera la memoria della struttura `Lista`.
 *
 * @param lista Il puntatore alla lista da distruggere.
 * @param distruggiDatoFn Un puntatore a funzione che sarà chiamato per liberare
 * il dato contenuto in ciascun nodo. Può essere NULL se
 * il dato non necessita di deallocazione o è gestito altrove.
 */
void distruggiLista(ListaPtr lista, void (*distruggiDatoFn)(void*)) {
    if (lista == NULL) return;
    NodoPtr current = lista->head;
    NodoPtr nextNode;
    while (current != NULL) {
        nextNode = current->next;
        if (distruggiDatoFn != NULL && current->dato != NULL) {
            distruggiDatoFn(current->dato); // Chiama la funzione di distruzione specifica per il dato
        }
        distruggiNodo(current); // Libera la memoria del nodo
        current = nextNode;
    }
    free(lista); // Libera la memoria della struttura Lista
}

/**
 * @brief Inserisce un dato all'inizio di una lista generica.
 *
 * Crea un nuovo nodo con il dato fornito e lo inserisce come primo elemento della lista.
 *
 * @param lista Il puntatore alla lista in cui inserire il dato.
 * @param dato Il puntatore generico al dato da inserire.
 * @return 1 se l'inserimento è avvenuto con successo, 0 altrimenti (es. lista o dato NULL, fallimento allocazione).
 */
int inserisciInLista(ListaPtr lista, void* dato) {
    if (lista == NULL || dato == NULL) {
        return 0;
    }
    NodoPtr nuovoNodo = creaNodo(dato);
    if (nuovoNodo == NULL) {
        puts("ATTENZIONE, impossibile allocare memoria per nuovo Nodo");
        return 0;
    }
    nuovoNodo->next = lista->head; // Il nuovo nodo punta all'attuale head
    lista->head = nuovoNodo;       // Il nuovo nodo diventa la head
    return 1;
}

/**
 * @brief Controlla se una lista generica è vuota.
 *
 * @param lista Il puntatore alla lista da controllare.
 * @return 1 se la lista è NULL o non contiene nodi (head è NULL), 0 altrimenti.
 */
int isListaVuota(const ListaPtr lista) {
    return (lista == NULL || lista->head == NULL);
}

/**
 * @brief Restituisce il puntatore al primo nodo (head) di una lista generica.
 *
 * @param lista Il puntatore alla lista.
 * @return Il puntatore al nodo head della lista, o NULL se la lista è NULL o vuota.
 */
NodoPtr getListaHeadNode(const ListaPtr lista) {
    return (lista == NULL) ? NULL : lista->head;
}

/**
 * @brief Restituisce il contenuto (dato) di un nodo generico.
 *
 * @param nodo Il puntatore al nodo.
 * @return Il puntatore al dato contenuto nel nodo, o NULL se il nodo è NULL.
 */
void* getNodoContent(const NodoPtr nodo) {
    return (nodo == NULL) ? NULL : nodo->dato;
}

/**
 * @brief Restituisce il puntatore al nodo successivo nella lista.
 *
 * @param nodo Il puntatore al nodo corrente.
 * @return Il puntatore al nodo successivo, o NULL se il nodo corrente è NULL o è l'ultimo.
 */
NodoPtr getNodoNextNode(const NodoPtr nodo) {
    return (nodo == NULL) ? NULL : nodo->next;
}

/**
 * @brief Restituisce il puntatore al primo nodo di una lista di animali (cast a NodoAnimalePtr).
 *
 * Questa è una funzione di convenienza per operare sulle liste di animali usando il tipo specifico.
 *
 * @param lista Il puntatore alla lista di animali.
 * @return Il puntatore al nodo head della lista, castato a NodoAnimalePtr, o NULL se la lista è NULL o vuota.
 */
NodoAnimalePtr getListaAnimaliHeadNode(const ListaPtr lista) {
    return (NodoAnimalePtr)getListaHeadNode(lista);
}

/**
 * @brief Restituisce il contenuto (AnimalePtr) di un nodo che si presume contenga un Animale.
 *
 * Questa è una funzione di convenienza per accedere al dato Animale da un NodoAnimalePtr.
 *
 * @param nodo Il puntatore al nodo Animale.
 * @return Il puntatore all'Animale contenuto nel nodo, o NULL se il nodo è NULL.
 */
AnimalePtr getNodoAnimaleContent(const NodoAnimalePtr nodo) {
    return (AnimalePtr)getNodoContent(nodo);
}

/**
 * @brief Restituisce il puntatore al nodo Animale successivo.
 *
 * Questa è una funzione di convenienza per navigare una lista di animali.
 *
 * @param nodo Il puntatore al nodo Animale corrente.
 * @return Il puntatore al nodo Animale successivo, o NULL se il nodo corrente è NULL o è l'ultimo.
 */
NodoAnimalePtr getNodoAnimaleNextNode(const NodoAnimalePtr nodo) {
    return (NodoAnimalePtr)getNodoNextNode(nodo);
}

/**
 * @brief Restituisce il puntatore al nodo Negozio successivo.
 *
 * Questa è una funzione di convenienza per navigare una lista di negozi.
 *
 * @param nodo Il puntatore al nodo Negozio corrente.
 * @return Il puntatore al nodo Negozio successivo, o NULL se il nodo corrente è NULL o è l'ultimo.
 */
NodoNegozioPtr getNodoNegozioNext(const NodoNegozioPtr nodo) {
    return (NodoNegozioPtr)getNodoNextNode(nodo);
}

/**
 * @brief Funzione helper statica per la deallocazione di un dato di tipo Animale.
 *
 * Questa funzione è passata a `distruggiLista` quando si vuole deallocare una lista di Animali.
 *
 * @param dato Il puntatore generico al dato di tipo Animale da distruggere.
 */
static void distruggiDatoAnimale(void* dato) {
    distruggiAnimale((AnimalePtr)dato);
}

/**
 * @brief Crea un nuovo oggetto `Animale` e lo inizializza con i dati forniti.
 *
 * Alloca memoria per una nuova struttura `Animale` e copia i valori nei suoi campi.
 *
 * @param id L'ID dell'animale.
 * @param razza La razza dell'animale.
 * @param nome Il nome dell'animale.
 * @param eta L'età dell'animale.
 * @param prezzo Il prezzo dell'animale.
 * @return Un puntatore al nuovo oggetto `Animale` creato, o NULL se l'allocazione fallisce.
 */
AnimalePtr creaAnimale(unsigned int id, const char* razza, const char* nome, int eta, float prezzo) {
    AnimalePtr nuovo = (AnimalePtr) malloc(sizeof(struct Animale));
    if (nuovo != NULL) {
        nuovo->id = id;
        strncpy(nuovo->razza, razza, MAXCHAR1 - 1); // Copia sicura della stringa
        nuovo->razza[MAXCHAR1 - 1] = '\0';          // Assicura la terminazione null
        strncpy(nuovo->nome, nome, MAXCHAR1 - 1);
        nuovo->nome[MAXCHAR1 - 1] = '\0';
        nuovo->eta = eta;
        nuovo->prezzo = prezzo;
    }
    return nuovo;
}

/**
 * @brief Distrugge un oggetto `Animale`, liberando la memoria allocata per esso.
 *
 * @param a Il puntatore all'oggetto `Animale` da distruggere.
 */
void distruggiAnimale(AnimalePtr a) {
    free(a);
}

/**
 * @brief Restituisce l'ID di un animale.
 *
 * @param a Il puntatore costante all'oggetto `Animale`.
 * @return L'ID dell'animale, o 0 se il puntatore è NULL.
 */
unsigned int getAnimaleId(const AnimalePtr a) {
    return (a == NULL) ? 0 : a->id;
}

/**
 * @brief Restituisce la razza di un animale.
 *
 * @param a Il puntatore costante all'oggetto `Animale`.
 * @return La stringa della razza dell'animale, o NULL se il puntatore è NULL.
 */
const char* getAnimaleRazza(const AnimalePtr a) {
    return (a == NULL) ? NULL : a->razza;
}

/**
 * @brief Restituisce il nome di un animale.
 *
 * @param a Il puntatore costante all'oggetto `Animale`.
 * @return La stringa del nome dell'animale, o NULL se il puntatore è NULL.
 */
const char* getAnimaleNome(const AnimalePtr a) {
    return (a == NULL) ? NULL : a->nome;
}

/**
 * @brief Restituisce l'età di un animale.
 *
 * @param a Il puntatore costante all'oggetto `Animale`.
 * @return L'età dell'animale, o 0 se il puntatore è NULL.
 */
int getAnimaleEta(const AnimalePtr a) {
    return (a == NULL) ? 0 : a->eta;
}

/**
 * @brief Restituisce il prezzo di un animale.
 *
 * @param a Il puntatore costante all'oggetto `Animale`.
 * @return Il prezzo dell'animale, o 0.0f se il puntatore è NULL.
 */
float getAnimalePrezzo(const AnimalePtr a) {
    return (a == NULL) ? 0.0f : a->prezzo;
}

/**
 * @brief Imposta la razza di un animale.
 *
 * Copia la nuova razza nella struttura `Animale`, assicurando la terminazione null.
 *
 * @param a Il puntatore all'oggetto `Animale` da modificare.
 * @param razza La nuova stringa della razza.
 */
void setAnimaleRazza(AnimalePtr a, const char* razza) {
    if (a != NULL && razza != NULL) {
        strncpy(a->razza, razza, MAXCHAR1 - 1);
        a->razza[MAXCHAR1 - 1] = '\0';
    }
}

/**
 * @brief Imposta il nome di un animale.
 *
 * Copia il nuovo nome nella struttura `Animale`, assicurando la terminazione null.
 *
 * @param a Il puntatore all'oggetto `Animale` da modificare.
 * @param nome Il nuovo nome dell'animale.
 */
void setAnimaleNome(AnimalePtr a, const char* nome) {
    if (a != NULL && nome != NULL) {
        strncpy(a->nome, nome, MAXCHAR1 - 1);
        a->nome[MAXCHAR1 - 1] = '\0';
    }
}

/**
 * @brief Imposta l'età di un animale.
 *
 * @param a Il puntatore all'oggetto `Animale` da modificare.
 * @param eta La nuova età dell'animale.
 */
void setAnimaleEta(AnimalePtr a, int eta) {
    if (a != NULL) {
        a->eta = eta;
    }
}

/**
 * @brief Imposta il prezzo di un animale.
 *
 * @param a Il puntatore all'oggetto `Animale` da modificare.
 * @param prezzo Il nuovo prezzo dell'animale.
 */
void setAnimalePrezzo(AnimalePtr a, float prezzo) {
    if (a != NULL) {
        a->prezzo = prezzo;
    }
}

/**
 * @brief Crea una nuova lista specificamente destinata a contenere oggetti `Animale`.
 *
 * È una wrapper per `creaLista()` che ne specifica l'uso.
 *
 * @return Un puntatore alla nuova lista di animali, o NULL se l'allocazione fallisce.
 */
ListaPtr creaListaAnimali() {
    return creaLista();
}

/**
 * @brief Distrugge una lista di animali, liberando tutti gli animali e i nodi associati.
 *
 * Utilizza la funzione generica `distruggiLista` passando la funzione specifica
 * `distruggiDatoAnimale` per la corretta deallocazione di ogni `Animale`.
 *
 * @param lista Il puntatore alla lista di animali da distruggere.
 */
void distruggiListaAnimali(ListaPtr lista) {
    distruggiLista(lista, distruggiDatoAnimale);
}

/**
 * @brief Inserisce un nuovo oggetto `Animale` in una lista di animali.
 *
 * Prima di inserire, controlla se un animale con lo stesso ID esiste già nella lista
 * per prevenire duplicati. Se non ci sono duplicati, inserisce l'animale all'inizio della lista.
 *
 * @param lista Il puntatore alla lista di animali in cui inserire.
 * @param nuovoAnimale Il puntatore all'oggetto `Animale` da inserire.
 * @return 1 se l'inserimento è avvenuto con successo (nessun duplicato ID), 0 altrimenti.
 */
int inserisciAnimaleInLista(ListaPtr lista, AnimalePtr nuovoAnimale) {
    if (lista == NULL || nuovoAnimale == NULL) {
        return 0;
    }

    // Controlla se l'ID è già presente
    if (ricercaAnimalePerIdInLista(lista, getAnimaleId(nuovoAnimale)) != NULL) {
        // puts("Errore: Animale con lo stesso ID già presente nella lista."); // Debug o messaggio all'utente
        return 0; // ID duplicato
    }

    // Inserisce l'animale nella lista generica
    return inserisciInLista(lista, (void*)nuovoAnimale);
}

/**
 * @brief Ricerca un animale all'interno di una lista di animali tramite il suo ID.
 *
 * Scorre la lista e confronta l'ID di ogni animale con l'ID fornito.
 *
 * @param lista Il puntatore costante alla lista di animali in cui cercare.
 * @param id L'ID dell'animale da ricercare.
 * @return Un puntatore all'oggetto `Animale` se trovato, o NULL se non trovato o la lista è vuota/NULL.
 */
AnimalePtr ricercaAnimalePerIdInLista(const ListaPtr lista, unsigned int id) {
    if (lista == NULL || isListaVuota(lista)) {
        return NULL;
    }
    NodoPtr current = lista->head;
    while (!isNodoNull(current)) {
        AnimalePtr a = (AnimalePtr)getNodoContent(current); // Recupera l'Animale dal nodo
        if (getAnimaleId(a) == id) { // Confronta l'ID usando la funzione getter
            return a;
        }
        current = getNodoNextNode(current); // Passa al nodo successivo
    }
    return NULL;
}

/**
 * @brief Stampa a console i dettagli di tutti gli animali presenti in una lista.
 *
 * @param lista Il puntatore costante alla lista di animali da stampare.
 * @return 1 se la lista è stata stampata (anche se vuota), 0 se la lista è NULL.
 */
int stampaListaAnimali(const ListaPtr lista) {
    if (lista == NULL || isListaVuota(lista)) {
        puts("Inventario animali vuoto.");
        return 0; // Ritorna 0 per indicare che la lista era vuota (o NULL)
    }
    NodoPtr current = lista->head;
    while (!isNodoNull(current)) {
        AnimalePtr a = (AnimalePtr)getNodoContent(current);
        printf("  - ID: %u, Razza: %s, Nome: %s, Eta: %d, Prezzo: %.2f\n",
               getAnimaleId(a),      // Accesso tramite getter
               getAnimaleRazza(a),   // Accesso tramite getter
               getAnimaleNome(a),    // Accesso tramite getter
               getAnimaleEta(a),     // Accesso tramite getter
               getAnimalePrezzo(a)); // Accesso tramite getter
        current = getNodoNextNode(current);
    }
    return 1;
}

/**
 * @brief Controlla se una lista di animali è vuota.
 *
 * È una wrapper per `isListaVuota()` che ne specifica l'uso.
 *
 * @param lista Il puntatore costante alla lista di animali da controllare.
 * @return 1 se la lista è vuota (o NULL), 0 altrimenti.
 */
int isListaAnimaliVuota(const ListaPtr lista) {
    return isListaVuota(lista);
}

/**
 * @brief Funzione helper statica per la deallocazione di un dato di tipo NegozioData.
 *
 * Questa funzione è passata a `distruggiNodo` quando un nodo contiene `NegozioDataPtr`.
 * Si occupa di liberare prima l'inventario animali del negozio e poi la struttura `NegozioData` stessa.
 *
 * @param dato Il puntatore generico al dato di tipo NegozioData da distruggere.
 */
static void distruggiDatoNegozio(void* dato) {
    if (dato != NULL) {
        NegozioDataPtr negozio = (NegozioDataPtr)dato;
        distruggiListaAnimali(negozio->inventarioAnimali); // Distrugge la lista degli animali del negozio
        free(negozio); // Libera la struttura NegozioData
    }
}

/**
 * @brief Crea un nuovo nodo che contiene i dati di un negozio (`NegozioData`).
 *
 * Alloca memoria per una nuova struttura `NegozioData`, la inizializza con l'ID fornito
 * e crea un inventario vuoto per essa. Poi crea un `Nodo` generico per contenere questi dati.
 *
 * @param id L'ID del negozio.
 * @return Un puntatore al `NodoNegozioPtr` (che è un `NodoPtr` contenente `NegozioDataPtr`),
 * o NULL se l'allocazione fallisce in qualsiasi fase.
 */
NodoNegozioPtr creaNegozio(unsigned int id) {
    // Alloca i dati specifici del negozio
    NegozioDataPtr nuoviDatiNegozio = (NegozioDataPtr)malloc(sizeof(struct NegozioData));
    if (nuoviDatiNegozio == NULL) {
        return NULL;
    }
    nuoviDatiNegozio->id = id;
    nuoviDatiNegozio->inventarioAnimali = creaListaAnimali(); // Crea l'inventario vuoto
    if (nuoviDatiNegozio->inventarioAnimali == NULL) {
        free(nuoviDatiNegozio); // Pulizia in caso di fallimento allocazione lista
        return NULL;
    }

    // Crea il nodo generico per contenere i dati del negozio
    NodoNegozioPtr nuovoNodoNegozio = creaNodo((void*)nuoviDatiNegozio);
    if (nuovoNodoNegozio == NULL) {
        distruggiListaAnimali(nuoviDatiNegozio->inventarioAnimali); // Pulizia in caso di fallimento allocazione nodo
        free(nuoviDatiNegozio);
        return NULL;
    }
    return nuovoNodoNegozio;
}

/**
 * @brief Distrugge un nodo che contiene i dati di un negozio, inclusi il suo inventario e il nodo stesso.
 *
 * @param n Il puntatore al `NodoNegozioPtr` da distruggere.
 */
void distruggiNegozio(NodoNegozioPtr n) {
    if (n != NULL) {
        // Chiama la funzione di distruzione specifica per il dato 'NegozioData'
        distruggiDatoNegozio(n->dato);
        // Libera il nodo stesso
        distruggiNodo(n);
    }
}

/**
 * @brief Restituisce l'ID di un negozio dato il suo nodo.
 *
 * Accede all'ID attraverso l'ADT `NegozioData` contenuto nel nodo.
 *
 * @param n Il puntatore costante al `NodoNegozioPtr` del negozio.
 * @return L'ID del negozio, o 0 se il nodo o i suoi dati sono NULL.
 */
unsigned int getNegozioId(const NodoNegozioPtr n) {
    if (isNodoNull(n)) {
        return 0;
    }
    NegozioDataPtr dati = (NegozioDataPtr)getNodoContent(n); // Recupera i dati del negozio dal nodo
    return (dati == NULL) ? 0 : dati->id; // Accede all'ID direttamente dalla struct interna
}

/**
 * @brief Restituisce il puntatore all'inventario animali di un negozio.
 *
 * Accede all'inventario attraverso l'ADT `NegozioData` contenuto nel nodo.
 *
 * @param n Il puntatore al `NodoNegozioPtr` del negozio.
 * @return Il puntatore all'ADT `Lista` che rappresenta l'inventario degli animali del negozio,
 * o NULL se il nodo o i suoi dati sono NULL.
 */
ListaPtr getInventarioNegozio(NodoNegozioPtr n) {
    if (isNodoNull(n)) {
        return NULL;
    }
    NegozioDataPtr dati = (NegozioDataPtr)getNodoContent(n); // Recupera i dati del negozio dal nodo
    return (dati == NULL) ? NULL : dati->inventarioAnimali; // Accede all'inventario direttamente dalla struct interna
}

/**
 * @brief Imposta l'inventario animali di un negozio.
 *
 * Sostituisce l'inventario esistente del negozio con quello fornito. Se un inventario
 * precedente esisteva e non è lo stesso, viene distrutto per evitare memory leak.
 *
 * @param n Il puntatore al `NodoNegozioPtr` del negozio da modificare.
 * @param inventario Il puntatore all'ADT `Lista` che sarà il nuovo inventario.
 */
void setInventarioNegozio(NodoNegozioPtr n, ListaPtr inventario) {
    if (n != NULL && inventario != NULL) {
        NegozioDataPtr dati = (NegozioDataPtr)getNodoContent(n); // Recupera i dati del negozio dal nodo
        if (dati != NULL) {
            // Se esiste un inventario precedente e non è lo stesso che stiamo impostando, distruggilo.
            if (dati->inventarioAnimali != NULL && dati->inventarioAnimali != inventario) {
                distruggiListaAnimali(dati->inventarioAnimali);
            }
            dati->inventarioAnimali = inventario; // Assegna il nuovo inventario
        }
    }
}

/**
 * @brief Inserisce un nuovo nodo negozio nella lista globale dei negozi, mantenendola ordinata per ID.
 *
 * La lista globale è gestita come una lista ordinata. La funzione trova la posizione corretta
 * per il nuovo negozio in base al suo ID e lo inserisce. Gestisce anche il caso di lista vuota.
 *
 * @param topPtrNegozi Un puntatore al puntatore del primo nodo della lista globale dei negozi (head).
 * Questo permette di modificare la head della lista se necessario.
 * @param nuovoNegozio Il puntatore al `NodoNegozioPtr` del negozio da inserire.
 * @return 1 se l'inserimento è avvenuto con successo (ID non duplicato), 0 altrimenti (es. ID duplicato).
 */
int inserisciNegozioInListaGlobale(NodoNegozioPtr* topPtrNegozi, NodoNegozioPtr nuovoNegozio) {
    if (nuovoNegozio == NULL) {
        return 0;
    }

    unsigned int nuovoNegozioId = getNegozioId(nuovoNegozio); // Ottiene l'ID del nuovo negozio tramite getter
    NodoPtr current = *topPtrNegozi;
    NodoPtr prev = NULL;

    // Trova la posizione corretta per l'inserimento (mantenendo l'ordine per ID)
    while (current != NULL && getNegozioId(current) < nuovoNegozioId) { // Confronto ID tramite getter
        prev = current;
        current = current->next; // Accesso diretto a 'next' del nodo, poiché stiamo lavorando internamente al modulo dati.c
    }

    // Controlla per duplicati ID
    if (current != NULL && getNegozioId(current) == nuovoNegozioId) {
        // puts("Errore: Negozio con lo stesso ID già presente nella lista globale."); // Debug o messaggio all'utente
        return 0; // ID duplicato
    }

    // Inserisce il nuovo negozio
    if (prev == NULL) { // Inserimento in testa o lista vuota
        nuovoNegozio->next = *topPtrNegozi;
        *topPtrNegozi = nuovoNegozio;
    } else { // Inserimento al centro o in coda
        nuovoNegozio->next = current;
        prev->next = nuovoNegozio;
    }

    return 1;
}

/**
 * @brief Stampa a console i dettagli di tutti i negozi presenti nella lista globale.
 *
 * Per ogni negozio, stampa l'ID e poi chiama `stampaListaAnimali` per mostrare l'inventario.
 *
 * @param topPtrNegozi Il puntatore costante al primo nodo della lista globale dei negozi.
 * @return 1 se la lista è stata stampata (anche se vuota), 0 se la lista è NULL.
 */
int stampaListaGlobaleNegozi(const NodoNegozioPtr topPtrNegozi) {
    if (isNodoNull(topPtrNegozi)) {
        puts("Nessun negozio presente nella lista globale.");
        return 0;
    }
    NodoPtr current = topPtrNegozi;
    while (!isNodoNull(current)) {
        printf("--- NEGOZIO ID: %u ---\n", getNegozioId(current)); // Stampa ID negozio tramite getter
        ListaPtr inventario = getInventarioNegozio((NodoNegozioPtr)current); // Ottiene inventario tramite getter
        stampaListaAnimali(inventario); // Stampa l'inventario
        printf("\n");
        current = getNodoNextNode(current); // Passa al nodo successivo
    }
    return 1;
}

/**
 * @brief Libera tutta la memoria allocata per la lista globale dei negozi e i loro contenuti.
 *
 * Itera attraverso la lista, distruggendo ogni nodo negozio e il suo contenuto (inventario animali)
 * tramite `distruggiNegozio`.
 *
 * @param topPtrNegozi Il puntatore al primo nodo della lista globale dei negozi.
 */
void liberaListaGlobaleNegozi(NodoNegozioPtr topPtrNegozi) {
    NodoPtr current = topPtrNegozi;
    NodoPtr next;
    while (current != NULL) {
        next = current->next;
        distruggiNegozio(current); // Distrugge il nodo negozio e il suo contenuto
        current = next;
    }
}

/**
 * @brief Ricerca un negozio nella lista globale tramite il suo ID.
 *
 * Scorre la lista e confronta l'ID di ogni negozio con l'ID fornito.
 *
 * @param topPtrNegozi Il puntatore costante al primo nodo della lista globale dei negozi.
 * @param id L'ID del negozio da ricercare.
 * @return Un puntatore al `NodoNegozioPtr` del negozio se trovato, o NULL se non trovato o la lista è vuota/NULL.
 */
NodoNegozioPtr ricercaNegozioPerIdGlobale(const NodoNegozioPtr topPtrNegozi, unsigned int id) {
    NodoPtr current = topPtrNegozi;
    while (!isNodoNull(current)) {
        if (getNegozioId(current) == id) { // Confronta l'ID del negozio tramite getter
            return (NodoNegozioPtr)current; // Trovato, restituisce il nodo
        }
        current = getNodoNextNode(current); // Passa al nodo successivo
    }
    return NULL; // Non trovato
}

/**
 * @brief Scrive i dettagli degli animali di un inventario su un file.
 *
 * Itera attraverso la lista di animali e formatta ogni animale come una riga di testo
 * (ID*Razza*Nome*Età*Prezzo) scrivendola nel file di destinazione.
 *
 * @param lista Il puntatore costante alla lista di animali da scrivere.
 * @param fileDiDestinazione Il puntatore al file (già aperto in modalità scrittura) su cui scrivere.
 * @return 1 se la scrittura è avvenuta con successo, 0 in caso di lista vuota/NULL,
 * file NULL, o errore di scrittura. Se la lista è vuota, scrive un messaggio nel file.
 */
int scriviInventarioAnimaliSuFile(const ListaPtr lista, FILE* fileDiDestinazione) {
    if (isListaVuota(lista) || fileDiDestinazione == NULL) {
        if (fileDiDestinazione != NULL) {
            fprintf(fileDiDestinazione, "Inventario_animali_vuoto.\n"); // Messaggio se l'inventario è vuoto
        }
        return (fileDiDestinazione != NULL); // Ritorna 1 se il file è valido anche con inventario vuoto
    }

    NodoPtr current = lista->head;
    while (!isNodoNull(current)) {
        AnimalePtr a = (AnimalePtr)getNodoContent(current); // Recupera l'Animale dal nodo

        // Scrive i dettagli dell'animale nel file utilizzando le funzioni getter
        int charScritti = fprintf(fileDiDestinazione, "%u*%s*%s*%d*%.2f\n",
                                  getAnimaleId(a),
                                  getAnimaleRazza(a),
                                  getAnimaleNome(a),
                                  getAnimaleEta(a),
                                  getAnimalePrezzo(a));

        if (charScritti < 0) {
            return 0; // Errore di scrittura
        }
        current = getNodoNextNode(current); // Passa al nodo successivo
    }
    return 1; // Scrittura completata con successo
}

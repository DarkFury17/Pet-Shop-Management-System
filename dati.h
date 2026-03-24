/**
 * @file dati.h
 * @brief Questo file definisce le **interfacce degli Abstract Data Type (ADT)**
 * `Animale`, `Lista` (per gli inventari) e `NegozioData` (per i dati dei negozi),
 * insieme al loro elemento costitutivo `Nodo` (per le liste).
 *
 * Tutte le strutture sono dichiarate come **tipi opachi (forward declarations)**,
 * nascondendo i dettagli della loro implementazione. Ciò significa che gli altri
 * moduli interagiranno con queste strutture solo attraverso i puntatori (`AnimalePtr`,
 * `ListaPtr`, `NodoPtr`, `NegozioDataPtr`, ecc.) e le funzioni qui dichiarate.
 * Le definizioni complete delle strutture e l'implementazione delle funzioni si trovano in `dati.c`.
 *
 * Questo modulo facilita la gestione incapsulata e robusta degli animali e dei negozi
 * all'interno del programma.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#ifndef DATI_H_INCLUDED
#define DATI_H_INCLUDED

#include <stdio.h>

#define NUM_SEPARATORI 4
#define NUM_CAMPi_RECORD 5
#define MAXCHAR_BUFFER 256
#define MAX_LINE_BUFFER 256
#define MAX_ID_LEN 10
#define MAX_STR_LEN 50
#define MAX_NUMERO_LEN 3
#define MAX_PREZZO_LEN 10
#define SEPARATORE '*'
#define MAXCHAR1 50


typedef struct Animale Animale;
typedef struct Nodo Nodo;
typedef struct Lista Lista;
typedef struct NegozioData NegozioData;


typedef Animale* AnimalePtr;
typedef Nodo* NodoPtr;
typedef Lista* ListaPtr;
typedef NegozioData* NegozioDataPtr;


typedef NodoPtr NodoNegozioPtr;
typedef NodoPtr NodoAnimalePtr;

/**
 * @brief Crea una nuova istanza di un Animale.
 * @details Alloca memoria per una nuova struttura `Animale` e la inizializza con i valori forniti.
 * @param id L'identificativo unico dell'animale.
 * @param razza La razza dell'animale.
 * @param nome Il nome dell'animale.
 * @param eta L'età dell'animale.
 * @param prezzo Il prezzo dell'animale.
 * @return Un puntatore al nuovo `Animale` creato, o `NULL` in caso di errore nell'allocazione.
 */
AnimalePtr creaAnimale(unsigned int id, const char* razza, const char* nome, int eta, float prezzo);

/**
 * @brief Libera la memoria allocata per un Animale.
 * @details Dealloca la memoria associata alla struttura `Animale` puntata da `a`.
 * @param a Puntatore all'Animale da distruggere.
 */
void distruggiAnimale(AnimalePtr a);

/**
 * @brief Restituisce l'ID di un Animale.
 * @param a Puntatore costante all'Animale.
 * @return L'ID dell'Animale.
 */
unsigned int getAnimaleId(const AnimalePtr a);

/**
 * @brief Restituisce la razza di un Animale.
 * @param a Puntatore costante all'Animale.
 * @return La stringa della razza dell'Animale.
 */
const char* getAnimaleRazza(const AnimalePtr a);

/**
 * @brief Restituisce il nome di un Animale.
 * @param a Puntatore costante all'Animale.
 * @return La stringa del nome dell'Animale.
 */
const char* getAnimaleNome(const AnimalePtr a);

/**
 * @brief Restituisce l'età di un Animale.
 * @param a Puntatore costante all'Animale.
 * @return L'età dell'Animale.
 */
int getAnimaleEta(const AnimalePtr a);

/**
 * @brief Restituisce il prezzo di un Animale.
 * @param a Puntatore costante all'Animale.
 * @return Il prezzo dell'Animale.
 */
float getAnimalePrezzo(const AnimalePtr a);

/**
 * @brief Imposta la razza di un Animale.
 * @param a Puntatore all'Animale da modificare.
 * @param razza La nuova razza.
 */
void setAnimaleRazza(AnimalePtr a, const char* razza);

/**
 * @brief Imposta il nome di un Animale.
 * @param a Puntatore all'Animale da modificare.
 * @param nome Il nuovo nome.
 */
void setAnimaleNome(AnimalePtr a, const char* nome);

/**
 * @brief Imposta l'età di un Animale.
 * @param a Puntatore all'Animale da modificare.
 * @param eta La nuova età.
 */
void setAnimaleEta(AnimalePtr a, int eta);

/**
 * @brief Imposta il prezzo di un Animale.
 * @param a Puntatore all'Animale da modificare.
 * @param prezzo Il nuovo prezzo.
 */
void setAnimalePrezzo(AnimalePtr a, float prezzo);

/**
 * @brief Crea una nuova lista per contenere animali.
 * @details Alloca memoria per una nuova struttura `Lista` e la inizializza come lista vuota.
 * @return Un puntatore alla nuova `Lista` creata, o `NULL` in caso di errore nell'allocazione.
 */
ListaPtr creaListaAnimali();

/**
 * @brief Libera tutta la memoria allocata per una lista di animali e i suoi nodi.
 * @details Dealloca ricorsivamente tutti i nodi e gli animali contenuti nella lista.
 * @param lista Puntatore alla Lista di animali da distruggere.
 */
void distruggiListaAnimali(ListaPtr lista);

/**
 * @brief Inserisce un nuovo animale nella lista.
 * @details Aggiunge l'animale fornito alla lista. La politica di inserimento (es. in testa, in coda, ordinato)
 * dipende dall'implementazione in `dati.c`.
 * @param lista Puntatore alla Lista in cui inserire l'animale.
 * @param nuovoAnimale Puntatore all'Animale da inserire.
 * @return 1 in caso di successo, 0 in caso di fallimento (es. animale NULL, ID duplicato se non permesso).
 */
int inserisciAnimaleInLista(ListaPtr lista, AnimalePtr nuovoAnimale);

/**
 * @brief Ricerca un animale nella lista tramite il suo ID.
 * @param lista Puntatore costante alla Lista in cui cercare.
 * @param id L'ID dell'animale da cercare.
 * @return Un puntatore all'Animale trovato, o `NULL` se non presente.
 */
AnimalePtr ricercaAnimalePerIdInLista(const ListaPtr lista, unsigned int id);

/**
 * @brief Stampa a console tutti gli animali presenti nella lista.
 * @param lista Puntatore costante alla Lista di animali da stampare.
 * @return 1 in caso di successo (anche se la lista è vuota), 0 in caso di errore (es. lista NULL).
 */
int stampaListaAnimali(const ListaPtr lista);

/**
 * @brief Verifica se una lista di animali è vuota.
 * @param lista Puntatore costante alla Lista da controllare.
 * @return 1 se la lista è vuota, 0 altrimenti.
 */
int isListaAnimaliVuota(const ListaPtr lista);

/**
 * @brief Crea un nuovo nodo che rappresenta un negozio.
 * @details Alloca memoria per un `NodoNegozioPtr` e inizializza il `NegozioData` al suo interno
 * con l'ID fornito e un inventario vuoto.
 * @param id L'identificativo unico del negozio.
 * @return Un puntatore al nuovo `NodoNegozioPtr` creato, o `NULL` in caso di errore.
 */
NodoNegozioPtr creaNegozio(unsigned int id);

/**
 * @brief Libera la memoria allocata per un nodo negozio e i suoi contenuti.
 * @details Dealloca il `NegozioData` associato, inclusa la sua lista di inventario, e il nodo stesso.
 * @param n Puntatore al NodoNegozioPtr da distruggere.
 */
void distruggiNegozio(NodoNegozioPtr n);

/**
 * @brief Restituisce l'ID del negozio da un nodo negozio.
 * @param n Puntatore costante al NodoNegozioPtr.
 * @return L'ID del negozio.
 */
unsigned int getNegozioId(const NodoNegozioPtr n);

/**
 * @brief Restituisce il puntatore all'inventario di animali di un negozio.
 * @param n Puntatore al NodoNegozioPtr.
 * @return Un puntatore alla Lista degli animali nell'inventario del negozio.
 */
ListaPtr getInventarioNegozio(NodoNegozioPtr n);

/**
 * @brief Imposta l'inventario di animali per un negozio.
 * @details Assegna una nuova lista di animali come inventario del negozio.
 * La vecchia lista di inventario (se esistente) dovrebbe essere gestita esternamente (liberata).
 * @param n Puntatore al NodoNegozioPtr da modificare.
 * @param inventario Puntatore alla nuova Lista di animali da assegnare.
 */
void setInventarioNegozio(NodoNegozioPtr n, ListaPtr inventario);

/**
 * @brief Inserisce un nuovo negozio nella lista globale dei negozi.
 * @details Aggiunge il `nuovoNegozio` alla lista collegata dei negozi, mantenuta dal puntatore `topPtrNegozi`.
 * @param topPtrNegozi Indirizzo del puntatore alla testa della lista globale dei negozi.
 * @param nuovoNegozio Puntatore al negozio da inserire.
 * @return 1 in caso di successo, 0 in caso di fallimento (es. negozio NULL, ID duplicato).
 */
int inserisciNegozioInListaGlobale(NodoNegozioPtr* topPtrNegozi, NodoNegozioPtr nuovoNegozio);

/**
 * @brief Stampa a console tutti i negozi presenti nella lista globale, inclusi i loro inventari.
 * @param topPtrNegozi Puntatore costante alla testa della lista globale dei negozi.
 * @return 1 in caso di successo (anche se la lista è vuota), 0 in caso di errore.
 */
int stampaListaGlobaleNegozi(const NodoNegozioPtr topPtrNegozi);

/**
 * @brief Libera tutta la memoria allocata per la lista globale dei negozi e i loro contenuti.
 * @details Dealloca ricorsivamente tutti i nodi negozio, i loro dati `NegozioData` e le rispettive liste di inventario.
 * @param topPtrNegozi Puntatore alla testa della lista globale dei negozi da liberare.
 */
void liberaListaGlobaleNegozi(NodoNegozioPtr topPtrNegozi);

/**
 * @brief Ricerca un negozio nella lista globale tramite il suo ID.
 * @param topPtrNegozi Puntatore costante alla testa della lista globale dei negozi.
 * @param id L'ID del negozio da cercare.
 * @return Un puntatore al `NodoNegozioPtr` trovato, o `NULL` se non presente.
 */
NodoNegozioPtr ricercaNegozioPerIdGlobale(const NodoNegozioPtr topPtrNegozi, unsigned int id);

/**
 * @brief Scrive l'inventario di animali di una lista su un file specificato.
 * @details I record degli animali vengono scritti nel formato appropriato sul file di destinazione.
 * @param lista Puntatore costante alla Lista di animali da scrivere.
 * @param fileDiDestinazione Puntatore al `FILE` su cui scrivere.
 * @return 1 in caso di successo, 0 in caso di errore (es. file non aperto, lista NULL).
 */
int scriviInventarioAnimaliSuFile(const ListaPtr lista, FILE* fileDiDestinazione);


#endif // DATI_H_INCLUDED

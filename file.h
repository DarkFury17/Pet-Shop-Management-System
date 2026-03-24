/**
 * @file file.h
 * @brief Questo file contiene le dichiarazioni delle funzioni per la gestione delle operazioni sui file.
 *
 * Le funzioni qui definite si occupano dell'apertura e chiusura di file,
 * dell'estrazione di dati strutturati (token) da stringhe lette da file,
 * della lettura di interi inventari di negozi e della scrittura di singoli negozi su file.
 * L'obiettivo è astrarre le operazioni di I/O per facilitare la gestione dei dati persistenti.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED

#include "dati.h"
#include "controlli.h"
#include "utils.h"

/**
 * @brief Apre un file specificato in una determinata modalità.
 * @details Questa funzione gestisce l'apertura di un file, fornendo un meccanismo centralizzato
 * per le operazioni di I/O.
 * @param nomeFile Stringa contenente il percorso e il nome del file da aprire.
 * @param mod Stringa contenente la modalità di apertura (es. "r" per lettura, "w" per scrittura, "a" per append).
 * @return 1 se il file è stato aperto con successo, 0 altrimenti.
 */
int apriFile(char* nomeFile, char* mod);

/**
 * @brief Chiude il file attualmente aperto.
 * @details Questa funzione è responsabile della chiusura del file che è stato precedentemente
 * aperto tramite `apriFile`.
 * @return 1 se il file è stato chiuso con successo, 0 altrimenti (es. nessun file aperto).
 */
int chiudiFile();

/**
 * @brief Estrae token da una stringa formattata e li converte in dati di un Animale.
 * @details Prende una stringa `tokenizedStr` (es. "ID*Razza*Nome*Eta*Prezzo"), la parsa
 * utilizzando il carattere separatore e popola le variabili puntate da `tempId`, `tempRazza`,
 * `tempNome`, `tempEta`, `tempPrezzo`. Esegue anche controlli di validità sui dati estratti
 * e verifica eventuali duplicati ID nella `listaAnimaliDestinazione`.
 * @param tokenizedStr Stringa da cui estrarre i token.
 * @param tempId Puntatore all'unsigned int dove memorizzare l'ID estratto.
 * @param tempRazza Puntatore alla stringa dove memorizzare la razza estratta.
 * @param tempNome Puntatore alla stringa dove memorizzare il nome estratto.
 * @param tempEta Puntatore all'int dove memorizzare l'età estratta.
 * @param tempPrezzo Puntatore al float dove memorizzare il prezzo estratto.
 * @param listaAnimaliDestinazione Puntatore costante alla lista di animali esistente per il controllo duplicati.
 * @return 1 se l'estrazione e la validazione dei token avvengono con successo, 0 altrimenti.
 */
int estrazioneToken(char* tokenizedStr, unsigned int* tempId, char* tempRazza, char* tempNome, int* tempEta, float* tempPrezzo, const Lista* listaAnimaliDestinazione);

/**
 * @brief Legge i dati dei negozi e dei loro inventari da un file.
 * @details Questa funzione apre un file specificato, legge i record di ogni negozio
 * e i rispettivi animali, popolando la lista globale dei negozi (`topPtrNegozi`).
 * @param nomeFile Stringa contenente il percorso e il nome del file da leggere.
 * @param topPtrNegozi Indirizzo del puntatore alla testa della lista globale dei negozi.
 * @return 1 se la lettura del file e la costruzione della struttura dati avvengono con successo, 0 altrimenti.
 */
int letturaFile(char* nomeFile, NodoNegozioPtr * topPtrNegozi);

/**
 * @brief Scrive i dati di un singolo negozio e del suo inventario su un file.
 * @details Questa funzione prende un puntatore a un nodo negozio e scrive le sue informazioni
 * (ID del negozio e dettagli degli animali nel suo inventario) nel file specificato.
 * @param nomeFile Stringa contenente il percorso e il nome del file su cui scrivere.
 * @param negozioPtr Puntatore costante al nodo negozio da scrivere sul file.
 * @return 1 se la scrittura del negozio sul file avviene con successo, 0 altrimenti.
 */
int scritturaSingoloNegozioFile(char * nomeFile, const NodoNegozioPtr negozioPtr);

#endif // FILE_H_INCLUDED

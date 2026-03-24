/**
 * @file funzioni.h
 * @brief Questo file contiene le dichiarazioni delle funzioni principali
 * per la gestione delle funzionalità dell'applicazione, inclusi i criteri di confronto,
 * le operazioni di acquisizione dati, uguaglianza e ordinamento, e la gestione del menu.
 *
 * Le funzioni qui definite orchestrano le interazioni tra le diverse strutture dati
 * e le operazioni di I/O, fornendo le logiche di business dell'applicazione.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */


#ifndef FUNZIONI_H_INCLUDED
#define FUNZIONI_H_INCLUDED

#include "dati.h"
#include "controlli.h"
#include "file.h"
#include "utils.h"
#include <stdio.h>


/**
 * @brief Determina se la prima stringa precede la seconda in ordine lessicografico.
 * @details Utilizza una logica di confronto stringhe per stabilire l'ordinamento.
 * @param str1 La prima stringa da confrontare.
 * @param str2 La seconda stringa da confrontare.
 * @return 1 se `str1` precede `str2`, 0 altrimenti.
 */
int criterioStringaPrecede(char* str1, char* str2);

/**
 * @brief Determina se la prima stringa segue la seconda in ordine lessicografico.
 * @details Utilizza una logica di confronto stringhe per stabilire l'ordinamento.
 * @param str1 La prima stringa da confrontare.
 * @param str2 La seconda stringa da confrontare.
 * @return 1 se `str1` segue `str2`, 0 altrimenti.
 */
int criterioStringaSegue(char* str1, char* str2);


/**
 * @brief Determina se due istanze di `Animale` sono uguali.
 * @details Il criterio di uguaglianza si basa su tutti i campi rilevanti di un animale (ID, razza, nome, età, prezzo).
 * @param animale1 Puntatore costante al primo animale.
 * @param animale2 Puntatore costante al secondo animale.
 * @return 1 se i due animali sono considerati uguali, 0 altrimenti.
 */
int criterioUguaglianzaAnimale(const AnimalePtr animale1, const AnimalePtr animale2);


/**
 * @brief Gestisce il processo di acquisizione dei dati per i negozi e i loro inventari.
 * @details Questa funzione è responsabile dell'interazione con l'utente per acquisire
 * le informazioni sui negozi e sugli animali, e di inserirle nella struttura dati globale.
 * Include la lettura da file e l'inserimento manuale.
 * @param topPtrNegozi Indirizzo del puntatore alla testa della lista globale dei negozi.
 * @return 1 se l'acquisizione dei dati è avvenuta con successo, 0 in caso di errori.
 */
int funzionalitaAcquisizione(NodoNegozioPtr * topPtrNegozi);

/**
 * @brief Implementa la funzionalità di confronto per uguaglianza tra negozi.
 * @details Questa funzione analizza la lista globale dei negozi e identifica
 * i negozi che contengono inventari uguali o elementi comuni, scrivendo i risultati in un file.
 * @param topPtrNegozi Puntatore alla testa della lista globale dei negozi.
 */
void funzionalitaUguaglianza(NodoNegozioPtr topPtrNegozi);

/**
 * @brief Implementa la funzionalità di ordinamento dei negozi.
 * @details Questa funzione riorganizza la lista globale dei negozi o i loro inventari
 * secondo un criterio di ordinamento predefinito (es. per ID, nome, ecc.),
 * e scrive i risultati in un file.
 * @param topPtrNegozi Puntatore alla testa della lista globale dei negozi.
 */
void funzionalitaOrdine(NodoNegozioPtr topPtrNegozi);

/**
 * @brief Visualizza il menu principale dell'applicazione e gestisce le scelte dell'utente.
 * @details Questa funzione presenta le opzioni disponibili all'utente e invoca le funzioni
 * appropriate in base alla selezione.
 */
void menu();


/**
 * @brief Confronta due negozi per trovare elementi comuni o determinarne l'uguaglianza.
 * @details Questa funzione prende due puntatori a negozi e restituisce un nuovo nodo negozio
 * che rappresenta gli elementi comuni tra i loro inventari.
 * @param negozio1 Puntatore costante al primo negozio da confrontare.
 * @param negozio2 Puntatore costante al secondo negozio da confrontare.
 * @return Un puntatore a un nuovo `NodoNegozioPtr` contenente gli animali comuni,
 * o `NULL` se non ci sono animali comuni o in caso di errore.
 */
NodoNegozioPtr uguaglianzaNegozi(const NodoNegozioPtr negozio1, const NodoNegozioPtr negozio2);

/**
 * @brief Ordina due negozi o i loro inventari basandosi su un criterio specifico.
 * @details Questa funzione riceve due puntatori a negozi e li confronta secondo
 * un criterio di ordinamento predefinito, restituendo il negozio che "precede" l'altro
 * o un nuovo negozio ordinato. L'implementazione esatta può variare (es. ordinamento interno degli animali,
 * ordinamento dei negozi stessi).
 * @param negozio1 Puntatore costante al primo negozio da ordinare/confrontare.
 * @param negozio2 Puntatore costante al secondo negozio da ordinare/confrontare.
 * @return Un puntatore al `NodoNegozioPtr` risultante dall'operazione di ordinamento.
 */
NodoNegozioPtr ordinamentoNegozi(const NodoNegozioPtr negozio1, const NodoNegozioPtr negozio2);

#endif // FUNZIONI_H_INCLUDED

/**
 * @file controlli.h
 * @brief Questo file contiene le dichiarazioni delle funzioni per la validazione e il controllo dei dati.
 *
 * Le funzioni dichiarate in questo file sono utilizzate per verificare la correttezza
 * dei formati di stringhe, nomi di file e record di animali, garantendo l'integrità
 * dei dati all'interno del sistema.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#ifndef CONTROLLI_H
#define CONTROLLI_H

#include <stdio.h>
#include "dati.h"


#define MAXCHAR 51
#define MAXCHAR_NUMSTUD 4
#define MAXCHAR_ID 5
#define NUM_SEPARATORI 4
#define NUM_RIGHE 3
#define MAX_LINE_BUFFER 256
#define MAX_STR_LEN 50
#define SEPARATORE '*'

/**
 * @brief Verifica il formato di un nome di file.
 * @details Controlla se il nome del file segue un formato specifico (es. "negozio_ID.txt").
 * @param nomeFile Stringa contenente il nome del file da controllare.
 * @return 1 se il formato è valido, 0 altrimenti.
 */
int formatoNomeFile(char* nomeFile);

/**
 * @brief Verifica il formato generale di una stringa.
 * @details Questa funzione potrebbe implementare controlli generici sulla validità dei caratteri.
 * @param str La stringa da controllare.
 * @return 1 se la stringa ha un formato valido, 0 altrimenti.
 */
int formatoStringa(const char* str);

/**
 * @brief Verifica se una stringa contiene solo caratteri numerici.
 * @details Controlla che tutti i caratteri nella stringa siano cifre da '0' a '9'.
 * @param str La stringa da controllare.
 * @return 1 se la stringa contiene solo numeri, 0 altrimenti.
 */
int stringaSoloNumeri(const char* str);

/**
 * @brief Verifica se una stringa contiene solo caratteri numerici o decimali.
 * @details Controlla che la stringa sia composta solo da cifre e al massimo un punto decimale.
 * @param str La stringa da controllare.
 * @return 1 se la stringa contiene solo numeri o decimali, 0 altrimenti.
 */
int stringaSoloNumeriODecimali(const char* str);

/**
 * @brief Verifica se una stringa contiene solo caratteri alfabetici.
 * @details Controlla che tutti i caratteri nella stringa siano lettere dell'alfabeto.
 * @param str La stringa da controllare.
 * @return 1 se la stringa contiene solo caratteri alfabetici, 0 altrimenti.
 */
int stringaSoloCaratteri(const char* str);

/**
 * @brief Verifica se la lunghezza di una stringa non supera un valore massimo.
 * @details Confronta la lunghezza della stringa con il valore massimo specificato.
 * @param str La stringa da controllare.
 * @param massimo La lunghezza massima consentita.
 * @return 1 se la lunghezza della stringa è minore o uguale al massimo, 0 altrimenti.
 */
int lunghezzaMassimaStringa(const char* str, int massimo);

/**
 * @brief Verifica se una stringa è vuota.
 * @details Controlla se la stringa è NULL o se la sua lunghezza è zero dopo la rimozione di spazi bianchi.
 * @param str La stringa da controllare.
 * @return 1 se la stringa è vuota, 0 altrimenti.
 */
int stringaVuota(const char* str);

/**
 * @brief Controlla la presenza di un codice identificativo duplicato in una lista.
 * @details Scorre una lista di elementi (es. animali) per verificare se un dato ID esiste già.
 * @param id L'ID da controllare per la duplicazione.
 * @param lista Puntatore alla lista in cui cercare il duplicato.
 * @return 1 se il codice è un duplicato (già presente), 0 se non è presente.
 */
int controllaDoppioCodice(unsigned int id, const Lista* lista);

/**
 * @brief Esegue un controllo sulle righe di un file.
 * @details Questa funzione potrebbe verificare il numero di righe o il formato di ciascuna riga nel file.
 * @param file Puntatore al file da controllare.
 * @return 1 se le righe del file sono valide, 0 altrimenti.
 */
int controlloRigheFile(FILE *file);

/**
 * @brief Controlla il numero di divisori (separatori) in una stringa.
 * @details Utile per verificare se un record di dati delimitato ha il numero atteso di campi.
 * @param str La stringa da analizzare.
 * @return Il numero di divisori trovati nella stringa.
 */
int controlloNumeroDivisori(const char* str);

/**
 * @brief Valida una singola riga di record di un animale.
 * @details Analizza una stringa che si presume essere un record di animale (es. "ID*Razza*Nome*Eta*Prezzo")
 * e verifica la correttezza di ogni campo, inclusa la non duplicazione dell'ID nella lista esistente.
 * @param record_line La stringa contenente il record dell'animale.
 * @param listaAnimali Puntatore alla lista di animali esistente per il controllo dei duplicati.
 * @return 1 se il record è valido, 0 altrimenti.
 */
int validaRecordAnimale(char *record_line, const Lista* listaAnimali);

#endif

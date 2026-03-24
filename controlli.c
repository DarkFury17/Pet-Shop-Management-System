/**
 * @file controlli.c
 * @brief Modulo che si occupa della gestione e validazione dei dati e dei formati.
 *
 * Questo file contiene una collezione di funzioni ausiliarie dedicate al controllo
 * della validità dell'input dell'utente, dei nomi dei file, dei formati delle stringhe
 * e dei record di dati, garantendo l'integrità delle informazioni all'interno del sistema.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "controlli.h"
#include "dati.h"

/**
 * @brief Controlla se un nome di file rispetta il formato atteso "negozio_ID.txt".
 *
 * Verifica che il nome del file inizi con "negozio_", termini con ".txt" e che
 * la parte centrale sia composta esclusivamente da cifre numeriche che rappresentano l'ID.
 *
 * @param filename La stringa del nome del file da controllare.
 * @return 1 se il formato del nome del file è valido, 0 altrimenti.
 */
int formatoNomeFile(char *filename) {
    const char *prefix = "negozio_";
    const char *suffix = ".txt";
    int prefix_len = strlen(prefix);
    int suffix_len = strlen(suffix);
    int filename_len = strlen(filename);

    if (filename_len <= prefix_len + suffix_len) {
        return 0;
    }

    if (strncmp(filename, prefix, prefix_len) != 0) {
        return 0;
    }

    if (strcmp(filename + filename_len - suffix_len, suffix) != 0) {
        return 0;
    }

    for (int i = prefix_len; i < filename_len - suffix_len; i++) {
        if (!isdigit(filename[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Controlla il formato generale di una stringa.
 *
 * Verifica che la stringa non sia NULL o vuota, non inizi o termini con uno spazio,
 * e non contenga doppi spazi consecutivi.
 *
 * @param str La stringa da controllare.
 * @return 1 se la stringa rispetta il formato, 0 altrimenti.
 */
int formatoStringa(const char* str) {
    if(str == NULL || str[0] == '\0') {
        return 0;
    }
    if(str[0] == ' '){
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' && str[i+1] == ' ') {
            return 0;
        }
    }
    if (str[strlen(str) - 1] == ' ') {
        return 0;
    }
    return 1;
}

/**
 * @brief Controlla se una stringa è composta esclusivamente da cifre numeriche.
 *
 * @param str La stringa da controllare.
 * @return 1 se la stringa contiene solo numeri, 0 altrimenti (inclusi NULL o vuota).
 */
int stringaSoloNumeri(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Controlla se una stringa è composta da numeri o contiene un singolo punto decimale.
 *
 * Valida stringhe che rappresentano numeri interi o decimali (float/double).
 * Non accetta stringhe che iniziano o finiscono con un punto decimale, o che contengono più di un punto.
 *
 * @param str La stringa da controllare.
 * @return 1 se la stringa è un numero intero o decimale valido, 0 altrimenti.
 */
int stringaSoloNumeriODecimali(const char* str) {
    int count_decimal_points = 0;
    if (str == NULL || str[0] == '\0') {
        return 0;
    }
    if (str[0] == '.') {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            count_decimal_points++;
            if (count_decimal_points > 1) {
                return 0;
            }
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    if (count_decimal_points == 1 && str[strlen(str) - 1] == '.') {
        return 0;
    }
    return 1;
}

/**
 * @brief Controlla se una stringa è composta esclusivamente da caratteri alfabetici o spazi.
 *
 * @param str La stringa da controllare.
 * @return 1 se la stringa contiene solo lettere e spazi, 0 altrimenti (inclusi NULL o vuota).
 */
int stringaSoloCaratteri(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Controlla se la lunghezza di una stringa non supera un valore massimo specificato.
 *
 * @param str La stringa da controllare.
 * @param massimo Il valore massimo consentito per la lunghezza della stringa (esclusi il terminatore nullo).
 * @return 1 se la lunghezza della stringa è minore o uguale al massimo, 0 altrimenti (o se str è NULL).
 */
int lunghezzaMassimaStringa(const char* str, int massimo) {
    if (str == NULL) {
        return 0;
    }
    return strlen(str) <= massimo;
}

/**
 * @brief Controlla se una stringa è NULL o vuota.
 *
 * @param str La stringa da controllare.
 * @return 1 se la stringa è NULL o ha lunghezza zero, 0 altrimenti.
 */
int stringaVuota(const char* str) {
    return (str == NULL || *str == '\0');
}

/**
 * @brief Controlla la presenza di un codice ID duplicato all'interno di una lista di animali.
 *
 * Utilizza la funzione di ricerca dell'ADT Lista (`ricercaAnimalePerIdInLista`) per verificare
 * se un animale con l'ID specificato esiste già nella lista fornita.
 *
 * @param id L'ID numerico da controllare per la duplicazione.
 * @param lista Il puntatore all'ADT Lista di animali in cui effettuare la ricerca.
 * @return 1 se l'ID non è duplicato (ovvero, non trovato nella lista), 0 se l'ID è già presente.
 */
int controllaDoppioCodice(unsigned int id, const Lista* lista) {
    Animale* risultato = ricercaAnimalePerIdInLista(lista, id);
    if(risultato != NULL && getAnimaleId(risultato) == id){
        return 0; // ID duplicato trovato
    }
    return 1; // ID non duplicato
}

/**
 * @brief Controlla se un file contiene un numero minimo di righe.
 *
 * Scorri il file per contare le righe fino a un massimo predefinito (NUM_RIGHE).
 * La funzione riavvolge il puntatore del file all'inizio (`rewind`) prima di tornare.
 *
 * @param file Il puntatore al file (già aperto) da controllare.
 * @return 1 se il numero di righe è maggiore o uguale a NUM_RIGHE, 0 altrimenti.
 * NOTA: Assumendo che NUM_RIGHE sia una macro definita in 'controlli.h'
 * o altrove e rappresenti il numero minimo di righe attese.
 */
int controlloRigheFile(FILE *file) {
    char buffer[MAXCHAR_BUFFER];
    int i = 0;
    // Assumendo che NUM_RIGHE sia una macro valida
    while (fgets(buffer, MAXCHAR_BUFFER, file) != NULL && i < NUM_RIGHE) {
        ++i;
    }
    rewind(file); // Riporta il puntatore all'inizio del file
    if (i < NUM_RIGHE) {
        return 0;
    }
    return 1;
}

/**
 * @brief Controlla se una stringa (riga di record) contiene il numero corretto di separatori.
 *
 * Scansiona la stringa e conta le occorrenze del carattere `SEPARATORE`.
 *
 * @param str La stringa (riga di record) da analizzare.
 * @return 1 se il numero di separatori corrisponde a `NUM_SEPARATORI`, 0 altrimenti.
 * NOTA: `SEPARATORE` e `NUM_SEPARATORI` sono macro definite in 'dati.h' o 'controlli.h'.
 */
int controlloNumeroDivisori(const char* str) {
    if (str == NULL) {
        return 0;
    }
    int nTokens = 0;
    for(int i = 0; str[i]!='\0'; ++i) {
        if(str[i] == SEPARATORE) { // SEPARATORE è una macro definita in dati.h
            ++nTokens;
        }
    }
    if(nTokens == NUM_SEPARATORI) { // NUM_SEPARATORI è una macro definita in dati.h
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Valida un'intera riga di testo che rappresenta un record di Animale.
 *
 * Esegue una serie di controlli approfonditi su ciascun campo del record:
 * - Numero corretto di separatori.
 * - Validità e formato dell'ID (numerico, lunghezza, range, non duplicato).
 * - Validità e formato di Razza e Nome (solo caratteri, formato stringa generale, lunghezza).
 * - Validità e formato dell'Età (numerica, lunghezza, range).
 * - Validità e formato del Prezzo (numerico/decimale, lunghezza, valore positivo).
 * - Assenza di campi in eccesso.
 *
 * Stampa messaggi di errore specifici in caso di fallimento della validazione.
 *
 * @param record_line La stringa che contiene l'intero record dell'animale da validare.
 * @param listaAnimali Il puntatore all'ADT Lista di animali corrente, usato per controllare i duplicati ID.
 * @return 1 se il record è completamente valido, 0 altrimenti.
 */
int validaRecordAnimale(char *record_line, const Lista* listaAnimali) {
    char temp_buffer[MAX_LINE_BUFFER];
    char *token;
    int field_count = 0;
    unsigned int current_id;
    int eta_animale;
    float prezzo_animale;

    char delimiter_str[2];
    delimiter_str[0] = SEPARATORE;
    delimiter_str[1] = '\0';

    // Prima copia per controllo separatori, per non alterare record_line per strtok successivo
    strncpy(temp_buffer, record_line, MAX_LINE_BUFFER - 1);
    temp_buffer[MAX_LINE_BUFFER - 1] = '\0';

    if(!controlloNumeroDivisori(temp_buffer)) {
        puts("Errore: numero campi record non corretto.");
        return 0;
    }

    // Ricopia per strtok, dato che strtok modifica la stringa in-place
    strncpy(temp_buffer, record_line, MAX_LINE_BUFFER - 1);
    temp_buffer[MAX_LINE_BUFFER - 1] = '\0';

    // Validazione ID
    token = strtok(temp_buffer, delimiter_str);
    if (stringaVuota(token)) {
        puts("Errore: ID mancante.");
        return 0;
    }
    if (!stringaSoloNumeri(token) || !lunghezzaMassimaStringa(token, MAX_ID_LEN)) {
        puts("Errore: ID non valido (non numerico o troppo lungo).");
        return 0;
    }
    char* endptr;
    long id_long = strtol(token, &endptr, 10);
    // Controllo errori di strtol e overflow/underflow per unsigned int
    if (*endptr != '\0' || id_long < 0 || id_long > UINT_MAX) { // UINT_MAX da <limits.h>
        puts("Errore: ID non valido (conversione fallita o fuori range).");
        return 0;
    }
    current_id = (unsigned int)id_long;

    // Controllo duplicato ID utilizzando l'ADT Lista
    if (!controllaDoppioCodice(current_id, listaAnimali)) {
        puts("Errore: ID duplicato.");
        return 0;
    }
    field_count++;

    // Validazione Razza
    token = strtok(NULL, delimiter_str);
    if (stringaVuota(token)) {
        puts("Errore: Razza mancante.");
        return 0;
    }
    if (!stringaSoloCaratteri(token) || !formatoStringa(token) || !lunghezzaMassimaStringa(token, MAX_STR_LEN)) {
        puts("Errore: Razza non valida (contiene numeri/simboli, formato errato o troppo lunga).");
        return 0;
    }
    field_count++;

    // Validazione Nome
    token = strtok(NULL, delimiter_str);
    if (stringaVuota(token)) {
        puts("Errore: Nome mancante.");
        return 0;
    }
    if (!stringaSoloCaratteri(token) || !formatoStringa(token) || !lunghezzaMassimaStringa(token, MAX_STR_LEN)) {
        puts("Errore: Nome animale non valido (contiene numeri/simboli, formato errato o troppo lungo).");
        return 0;
    }
    field_count++;

    // Validazione Età
    token = strtok(NULL, delimiter_str);
    if (stringaVuota(token)) {
        puts("Errore: Eta' mancante.");
        return 0;
    }
    if (!stringaSoloNumeri(token) || !lunghezzaMassimaStringa(token, MAX_NUMERO_LEN)) { // MAX_NUMERO_LEN è una macro
        puts("Errore: Eta' non valida (non numerica o troppo lunga).");
        return 0;
    }
    eta_animale = atoi(token);
    if (eta_animale < 0 || eta_animale > 200) {
        puts("Errore: Eta' fuori intervallo (deve essere tra 0 e 200).");
        return 0;
    }
    field_count++;

    // Validazione Prezzo
    token = strtok(NULL, delimiter_str);
    if (stringaVuota(token)) {
        puts("Errore: Prezzo mancante.");
        return 0;
    }
    if (!stringaSoloNumeriODecimali(token) || !lunghezzaMassimaStringa(token, MAX_PREZZO_LEN)) { // MAX_PREZZO_LEN è una macro
        puts("Errore: Prezzo non valido (non numerico/decimale o troppo lungo).");
        return 0;
    }
    prezzo_animale = (float)atof(token);
    if (prezzo_animale <= 0) {
        puts("Errore: Prezzo non valido (deve essere maggiore di zero).");
        return 0;
    }
    field_count++;

    // Controllo campi in eccesso
    token = strtok(NULL, delimiter_str);
    if (token != NULL) {
        puts("Errore: Campi in eccesso nel record.");
        return 0;
    }

    // Controllo finale sul conteggio dei campi
    if (field_count == NUM_CAMPi_RECORD) { // NUM_CAMPi_RECORD è una macro definita in dati.h
        return 1;
    } else {
        puts("Errore: Conteggio campi inconsistente."); // Questo caso dovrebbe essere già catturato da controlloNumeroDivisori
        return 0;
    }
}

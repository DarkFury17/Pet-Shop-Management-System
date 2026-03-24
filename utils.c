/**
 * @file utils.c
 * @brief Implementazione di funzioni di utilità generiche per la gestione dell'input utente,
 * la pulizia della console e l'estrazione di informazioni dai nomi dei file.
 *
 * Questo file contiene le definizioni delle funzioni ausiliarie utilizzate in diverse
 * parti del programma per compiti comuni che non rientrano direttamente nella
 * gestione dei dati principali o nei controlli specifici.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#include "utils.h"
#include "controlli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Acquisisce l'input dell'utente da stdin.
 * @details Legge una riga di testo dall'input standard e la memorizza nel buffer fornito.
 * Gestisce la rimozione del carattere di newline finale e svuota il buffer di input
 * nel caso l'input superi la dimensione massima consentita.
 * @param buffer Puntatore al buffer di caratteri dove memorizzare l'input.
 * @param maxChar Dimensione massima del buffer (numero massimo di caratteri da leggere).
 */
void inputUtente(char* buffer, int maxChar)
{
    fgets(buffer, maxChar, stdin);
    int lunghezzaStr = strlen(buffer);
    if (lunghezzaStr > 0 && buffer[lunghezzaStr - 1] == '\n') {
        buffer[lunghezzaStr - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

/**
 * @brief Pulisce la console e opzionalmente mette in pausa l'esecuzione.
 * @details Utilizza comandi di sistema per pulire lo schermo della console.
 * Se il parametro `pausa` è vero (diverso da zero), il programma si mette in pausa
 * attendendo un input da tastiera prima di pulire la console.
 * @param pausa Un intero che indica se mettere in pausa l'esecuzione (1 per pausa, 0 per non pausa).
 */
void cleanConsole(int pausa) {
    if (pausa) {
        system("pause");
    }
    system("cls");
}

/**
 * @brief Estrae l'ID del negozio da una stringa che rappresenta un nome di file.
 * @details La funzione si aspetta un nome di file nel formato "prefisso_ID.estensione",
 * dove ID è un numero intero. Verifica il formato del nome del file
 * tramite la funzione `formatoNomeFile` prima di tentare l'estrazione.
 * Restituisce l'ID del negozio come intero.
 * @param nomeFile Stringa contenente il nome del file da cui estrarre l'ID.
 * @return L'ID del negozio come intero se il formato del nome del file è valido e l'ID può essere estratto,
 * altrimenti restituisce 0 (zero) in caso di formato non valido o impossibilità di estrazione.
 */
int ottenereIdNegozioDaNome(char* nomeFile) {
    if (!formatoNomeFile(nomeFile)) {
        return 0;
    }
    char* underscore = strchr(nomeFile, '_');
    char* punto = strchr(underscore, '.');
    int length = (int)(punto - underscore - 1);
    char numeroStr[20];
    strncpy(numeroStr, underscore + 1, length);
    numeroStr[length] = '\0';
    int numero = atoi(numeroStr);
    return numero;
}

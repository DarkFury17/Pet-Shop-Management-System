/**
 * @file utils.h
 * @brief Dichiarazioni delle funzioni di utilità generiche.
 *
 * Questo file contiene le firme delle funzioni ausiliarie utilizzate
 * in diverse parti del programma per compiti comuni come la gestione
 * dell'input utente, la pulizia della console e l'estrazione di
 * informazioni dai nomi dei file.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "dati.h"
#include "file.h"

/**
 * @brief Pulisce la console e opzionalmente mette in pausa l'esecuzione.
 * @details Questa funzione è progettata per migliorare l'interazione utente
 * pulendo lo schermo e, se richiesto, mettendo in pausa il programma
 * fino a quando l'utente non preme un tasto.
 * @param pausa Un valore intero: se diverso da zero, il programma si mette in pausa;
 * altrimenti, la console viene pulita immediatamente.
 */
void cleanConsole(int pausa);

/**
 * @brief Estrae l'ID di un negozio da una stringa che rappresenta il nome di un file.
 * @details Questa funzione è utile per ricavare l'identificativo numerico di un negozio
 * direttamente dal nome del file ad esso associato, seguendo un formato predefinito.
 * @param nomeFile Una stringa contenente il nome del file da cui estrarre l'ID.
 * @return L'ID del negozio come intero, o 0 se il formato del nome del file non è valido
 * o l'ID non può essere estratto.
 */
int ottenereIdNegozioDaNome(char* nomeFile);

/**
 * @brief Acquisisce una riga di input dall'utente tramite la console.
 * @details Legge una stringa di caratteri dall'input standard (tastiera)
 * fino al newline o fino al raggiungimento della dimensione massima specificata,
 * gestendo correttamente il carattere di newline.
 * @param buffer Un puntatore a un array di caratteri dove verrà memorizzato l'input dell'utente.
 * @param maxChar La dimensione massima del buffer, inclusivo del carattere null terminatore,
 * per prevenire overflow.
 */
void inputUtente(char* buffer, int maxChar);

#endif // UTILS_H_INCLUDED

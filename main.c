/**
 * @file main.c
 * @brief Punto di ingresso principale del programma.
 *
 * Questo file contiene la funzione `main`, che avvia l'applicazione
 * richiamando la funzione `menu()` per mostrare il menu principale
 * all'utente. Contiene anche commenti per l'inclusione di funzioni di test,
 * utili per la verifica del corretto funzionamento dei vari moduli.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#include <stdio.h>    // Per funzioni standard di input/output come printf, puts
#include <stdlib.h>   // Per funzioni standard di utilità come exit, malloc, free
#include "funzioni.h" // Include le dichiarazioni delle funzioni principali del programma, in particolare `menu()`
#include "test.h"     // Include le dichiarazioni delle funzioni di test per i vari moduli

/**
 * @brief Funzione principale del programma.
 *
 * Questa è la funzione da cui l'esecuzione del programma ha inizio.
 * Il suo compito principale è invocare la funzione `menu()`, che gestisce
 * l'interazione con l'utente e le varie funzionalità dell'applicazione.
 *
 * Al suo interno sono presenti anche chiamate commentate a diverse funzioni di test.
 * Queste funzioni sono state implementate per la verifica unitaria dei moduli
 * `dati`, `utils`, `controlli`, `file` e `funzioni`. Possono essere uncommentate
 * per scopi di debugging o per l'esecuzione di test specifici.
 *
 * @return 0 se il programma termina con successo, un valore diverso da 0 in caso di errore.
 */
int main()
{
    // Avvia il menu interattivo dell'applicazione.
    // La funzione `menu()` contiene il ciclo principale del programma,
    // gestendo l'input dell'utente e la navigazione tra le diverse funzionalità.
    menu();

    // Le seguenti righe sono dedicate alle funzioni di test.
    // Sono commentate di default per il funzionamento normale del programma.
    // Per eseguire i test, rimuovere il commento dalla funzione di test desiderata.
    // Ogni funzione di test è responsabile della verifica del proprio modulo.
    // testDati();      // Esegue i test relativi al modulo 'dati.h' e 'dati.c'
    // testUtils();     // Esegue i test relativi al modulo 'utils.h' e 'utils.c'
    // testControlli(); // Esegue i test relativi al modulo 'controlli.h' e 'controlli.c'
    // testFile();      // Esegue i test relativi al modulo 'file.h' e 'file.c'
    // testFunzioni();  // Esegue i test relativi al modulo 'funzioni.h' e 'funzioni.c'

    return 0; // Indica che il programma è terminato con successo.
}

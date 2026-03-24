/**
 * @file test.h
 * @brief Dichiarazioni delle funzioni di test per i vari moduli del programma.
 *
 * Questo file contiene le firme delle funzioni di test unitario, ciascuna
 * dedicata alla verifica della correttezza e del comportamento atteso
 * delle funzioni implementate nei rispettivi moduli: dati, utilità, controlli,
 * gestione file e funzionalità principali.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

/**
 * @brief Esegue i test unitari per il modulo `dati`.
 * @details Questa funzione verifica il corretto funzionamento delle strutture dati
 * e delle operazioni ad esse associate (creazione, distruzione, accesso, modifica, ecc.)
 * definite in `dati.h` e implementate in `dati.c`.
 */
void testDati();

/**
 * @brief Esegue i test unitari per il modulo `utils`.
 * @details Questa funzione verifica la correttezza delle funzioni di utilità generiche,
 * come la gestione dell'input utente, la pulizia della console e l'estrazione di dati
 * dai nomi dei file, definite in `utils.h` e implementate in `utils.c`.
 */
void testUtils();

/**
 * @brief Esegue i test unitari per il modulo `controlli`.
 * @details Questa funzione verifica il comportamento delle funzioni di validazione
 * e controllo dei dati (es. formati di stringhe, ID duplicati, ecc.),
 * definite in `controlli.h` e implementate in `controlli.c`.
 */
void testControlli();

/**
 * @brief Esegue i test unitari per il modulo `file`.
 * @details Questa funzione verifica la correttezza delle operazioni sui file,
 * inclusa l'apertura, chiusura, lettura, scrittura e l'estrazione di token,
 * definite in `file.h` e implementate in `file.c`.
 */
void testFile();

/**
 * @brief Esegue i test unitari per il modulo `funzioni`.
 * @details Questa funzione verifica la logica di business principale dell'applicazione,
 * inclusi i criteri di confronto, le funzionalità di acquisizione, uguaglianza e ordinamento,
 * e la gestione del menu, definite in `funzioni.h` e implementate in `funzioni.c`.
 */
void testFunzioni();

#endif // TEST_H_INCLUDED

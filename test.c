/**
 * @file test.c
 * @brief Implementazione delle funzioni di test per le varie componenti del programma.
 *
 * Questo file contiene le implementazioni delle funzioni di test per la gestione dei dati (animali e negozi),
 * le utilità generiche e le funzioni di controllo dei formati. Utilizza asserzioni per verificare la correttezza
 * del comportamento delle funzioni testate, assicurando che le componenti del programma
 * funzionino come previsto.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#include <stdio.h>     // Per le funzioni di input/output (puts, printf, fopen, fclose, remove)
#include <stdlib.h>    // Per funzioni di utilità generale (es. atoi, per possibili espansioni)
#include <string.h>    // Per le manipolazioni di stringhe (strcpy, strlen, strcmp)
#include <stdbool.h>   // Per l'uso del tipo booleano (bool)
#include "test.h"      // Dichiarazioni delle funzioni di test
#include "utils.h"     // Funzioni di utilità (es. ottenereIdNegozioDaNome, inputUtente, cleanConsole)
#include "dati.h"      // Strutture dati e funzioni di gestione (es. creaAnimale, creaListaAnimali, inserisciAnimaleInLista, creaNegozio, inserisciNegozioInListaGlobale, ecc.)
#include "controlli.h" // Funzioni di validazione e controllo (es. formatoNomeFile, stringaSoloNumeriODecimali, validaRecordAnimale)
#include "file.h"      // Funzioni di gestione file (es. letturaFile, scritturaSingoloNegozioFile, anche se qui non direttamente chiamate per il test)
#include "funzioni.h"  // Funzioni principali del programma (es. uguaglianzaNegozi, ordinamentoNegozi, ma non direttamente testate qui)
#include <assert.h>    // Per l'uso della macro assert() per le verifiche in fase di sviluppo

/**
 * @brief Esegue test unitari sulle funzioni di gestione dei dati (modulo `dati.c`).
 *
 * Questa funzione testa:
 * - La creazione e l'inserimento di oggetti `Animale` in una `Lista` di animali.
 * - La stampa della lista di animali.
 * - La creazione e l'inserimento di oggetti `Negozio` in una lista globale di negozi.
 * - La stampa della lista globale dei negozi.
 * - La ricerca di un animale per ID all'interno di una lista, sia per casi di successo che di fallimento.
 *
 * Vengono utilizzate asserzioni (`assert`) per verificare che le operazioni
 * restituiscano i valori attesi e che le strutture dati siano manipolate correttamente.
 * Alla fine, tutta la memoria allocata durante il test viene liberata.
 */
void testDati()
{
    puts("--- INIZIO TEST FUNZIONI DI GESTIONE DATI ---\n");

    puts("TEST INSERIMENTO ANIMALE");

    // Test: Creazione di una lista di animali
    Lista* listaAnimaliTest = creaListaAnimali();
    // Asserzione: Verifica che la lista sia stata creata correttamente (non sia NULL)
    assert(listaAnimaliTest != NULL);
    printf("Creazione lista animali: OK\n");

    // Test: Creazione di diversi oggetti Animale
    Animale* a1 = creaAnimale(101, "Cane", "Fido", 3, 110.0f);
    Animale* a2 = creaAnimale(102, "Gatto", "Micio", 5, 80.0f);
    Animale* a3 = creaAnimale(103, "Uccello", "Cip", 1, 20.0f);
    Animale* a4 = creaAnimale(104, "Pesce", "Nemo", 0, 5.0f);
    Animale* a5 = creaAnimale(105, "Coniglio", "Roger", 2, 40.0f);
    // Asserzione: Verifica che tutti gli animali siano stati creati correttamente
    assert(a1 != NULL && a2 != NULL && a3 != NULL && a4 != NULL && a5 != NULL);
    printf("Creazione animali: OK\n");

    // Test: Inserimento degli animali nella lista
    inserisciAnimaleInLista(listaAnimaliTest, a1);
    inserisciAnimaleInLista(listaAnimaliTest, a2);
    inserisciAnimaleInLista(listaAnimaliTest, a3);
    inserisciAnimaleInLista(listaAnimaliTest, a4);
    inserisciAnimaleInLista(listaAnimaliTest, a5);
    printf("Inserimento animali in lista: OK\n");

    // Test: Stampa della lista di animali per verifica visiva
    printf("\nStringa di test (corretta - output atteso della lista animali):\n");
    // Asserzione: Verifica che la stampa della lista avvenga correttamente (ritorna 1 in caso di successo)
    assert(stampaListaAnimali(listaAnimaliTest) == 1);
    printf("Stampa lista animali: OK\n\n");

    puts("TEST INSERIMENTO NEGOZIO");

    // Test: Creazione di una testa per la lista globale dei negozi (inizialmente NULL)
    NodoNegozioPtr testaNe = NULL;
    // Test: Creazione di liste di animali per i negozi
    Lista* listaAn_negozio1 = creaListaAnimali();
    Lista* listaAn_negozio2 = creaListaAnimali();
    // Asserzione: Verifica che le liste siano state create
    assert(listaAn_negozio1 != NULL && listaAn_negozio2 != NULL);
    printf("Creazione liste animali per negozi: OK\n");

    // Test: Creazione e inserimento di animali per il negozio 1
    Animale* n1_a1 = creaAnimale(11, "Cane", "Buddy", 6, 23.0f);
    Animale* n1_a2 = creaAnimale(22, "Gatto", "Whiskers", 12, 123.0f);
    Animale* n1_a3 = creaAnimale(12, "Uccello", "Tweety", 15, 213.0f);
    Animale* n1_a4 = creaAnimale(16, "Pesce", "Goldie", 5, 27.0f);
    Animale* n1_a5 = creaAnimale(111, "Coniglio", "Thumper", 22, 38.0f);
    assert(n1_a1 != NULL && n1_a2 != NULL && n1_a3 != NULL && n1_a4 != NULL && n1_a5 != NULL);
    inserisciAnimaleInLista(listaAn_negozio1, n1_a1);
    inserisciAnimaleInLista(listaAn_negozio1, n1_a2);
    inserisciAnimaleInLista(listaAn_negozio1, n1_a3);
    inserisciAnimaleInLista(listaAn_negozio1, n1_a4);
    inserisciAnimaleInLista(listaAn_negozio1, n1_a5);
    printf("Animali per Negozio 1 creati e inseriti: OK\n");


    // Test: Creazione e inserimento di animali per il negozio 2
    Animale* n2_a1 = creaAnimale(101, "Criceto", "Hammy", 6, 23.0f);
    Animale* n2_a2 = creaAnimale(102, "Serpente", "Sly", 12, 123.0f);
    assert(n2_a1 != NULL && n2_a2 != NULL);
    inserisciAnimaleInLista(listaAn_negozio2, n2_a1);
    inserisciAnimaleInLista(listaAn_negozio2, n2_a2);
    printf("Animali per Negozio 2 creati e inseriti: OK\n");

    // Test: Creazione del negozio 1 e inserimento nella lista globale
    NodoNegozioPtr negozio1 = creaNegozio(1);
    assert(negozio1 != NULL);
    // Asserzione: Verifica l'inserimento nella lista globale
    assert(inserisciNegozioInListaGlobale(&testaNe, negozio1) == 1);
    setInventarioNegozio(negozio1, listaAn_negozio1); // Collega l'inventario al negozio
    printf("Negozio 1 creato e inserito globalmente con inventario: OK\n");

    // Test: Creazione del negozio 2 e inserimento nella lista globale
    NodoNegozioPtr negozio2 = creaNegozio(2);
    assert(negozio2 != NULL);
    // Asserzione: Verifica l'inserimento nella lista globale
    assert(inserisciNegozioInListaGlobale(&testaNe, negozio2) == 1);
    setInventarioNegozio(negozio2, listaAn_negozio2); // Collega l'inventario al negozio
    printf("Negozio 2 creato e inserito globalmente con inventario: OK\n");

    // Test: Stampa della lista globale dei negozi per verifica visiva
    printf("\nStringa di test (corretta - output atteso della lista globale negozi):\n");
    stampaListaGlobaleNegozi(testaNe);
    printf("Stampa lista globale negozi: OK\n\n");

    puts("TEST RICERCA ANIMALE PER ID");

    // Test: Creazione di una lista di animali per la ricerca
    Lista* listaAn_ricerca = creaListaAnimali();
    assert(listaAn_ricerca != NULL);
    printf("Creazione lista per ricerca: OK\n");

    // Test: Creazione e inserimento di animali nella lista di ricerca
    Animale* r1 = creaAnimale(11, "Cane", "Rex", 3, 110.0f);
    Animale* r2 = creaAnimale(12, "Gatto", "Silvestro", 4, 80.0f);
    Animale* r3 = creaAnimale(13, "Uccello", "Pio", 1, 20.0f);
    Animale* r4 = creaAnimale(14, "Pesce", "Dory", 0, 5.0f);
    Animale* r5 = creaAnimale(15, "Coniglio", "Bugs", 2, 40.0f);
    assert(r1 != NULL && r2 != NULL && r3 != NULL && r4 != NULL && r5 != NULL);
    inserisciAnimaleInLista(listaAn_ricerca, r1);
    inserisciAnimaleInLista(listaAn_ricerca, r2);
    inserisciAnimaleInLista(listaAn_ricerca, r3);
    inserisciAnimaleInLista(listaAn_ricerca, r4);
    inserisciAnimaleInLista(listaAn_ricerca, r5);
    printf("Animali per ricerca creati e inseriti: OK\n");

    // Test: Ricerca di un animale esistente (caso di successo)
    printf("Stringa di test (corretta - ricerca ID 11):\n");
    Animale* found_a = ricercaAnimalePerIdInLista(listaAn_ricerca, 11);
    // Asserzione: Verifica che l'animale sia stato trovato e che il suo ID sia valido
    assert(found_a != NULL && getAnimaleId(found_a) == 11);
    printf("Risultato ricerca: ID %u trovato\n", getAnimaleId(found_a));
    printf("Ricerca esistente: OK\n\n");

    // Test: Ricerca di un animale non esistente (caso di fallimento)
    printf("Stringa di test (errata - ricerca ID 21):\n");
    Animale* not_found_a = ricercaAnimalePerIdInLista(listaAn_ricerca, 21);
    // Asserzione: Verifica che l'animale non sia stato trovato (NULL)
    assert(not_found_a == NULL);
    printf("Risultato ricerca: %s\n", not_found_a == NULL ? "NULL (non trovato)" : "TROVATO (ERRORE)");
    printf("Ricerca non esistente: OK\n\n");

    // Liberazione della memoria allocata per i test
    distruggiListaAnimali(listaAnimaliTest);
    distruggiListaAnimali(listaAn_negozio1);
    distruggiListaAnimali(listaAn_negozio2);
    liberaListaGlobaleNegozi(testaNe); // Questa funzione dovrebbe liberare tutti i negozi e i loro inventari
    distruggiListaAnimali(listaAn_ricerca); // Anche se gli animali sono stati trovati, la lista va distrutta
    printf("Memoria liberata: OK\n");

    puts("\n--- TUTTI I TEST DI GESTIONE DATI SONO STATI ESEGUITI CON SUCCESSO! ---\n");
}

/**
 * @brief Esegue test unitari sulle funzioni di utilità (modulo `utils.c`).
 *
 * Questa funzione testa:
 * - `ottenereIdNegozioDaNome`: verifica l'estrazione corretta dell'ID da nomi di file validi e
 * il ritorno di 0 per nomi di file non conformi.
 * - `inputUtente`: Viene notato che questo test è manuale e non può essere automatizzato
 * completamente con `assert` per via della sua interattività.
 *
 * Vengono utilizzate asserzioni (`assert`) per verificare la correttezza dei risultati.
 */
void testUtils()
{
    puts("--- INIZIO TEST FUNZIONI DI UTILITÀ ---\n");

    puts("TEST ottenereIdNegozioDaNome");

    // Test case validi per ottenereIdNegozioDaNome
    char filename[] = "negozio_23.txt";
    printf("Stringa di test (giusta): \"%s\" -> ID %u ", filename, ottenereIdNegozioDaNome(filename));
    assert(ottenereIdNegozioDaNome(filename) == 23);
    printf("%s\n", "OK");

    // Test cases non validi per ottenereIdNegozioDaNome
    char filename1[] = "23.txt"; // Manca prefisso "negozio_"
    printf("Stringa di test (sbagliato - no prefisso): \"%s\" -> ID %u ", filename1, ottenereIdNegozioDaNome(filename1));
    assert(ottenereIdNegozioDaNome(filename1) == 0);
    printf("%s\n", "OK");

    char filename2[] = "negozio_23"; // Manca estensione ".txt"
    printf("Stringa di test (sbagliato - no estensione): \"%s\" -> ID %u ", filename2, ottenereIdNegozioDaNome(filename2));
    assert(ottenereIdNegozioDaNome(filename2) == 0);
    printf("%s\n", "OK");

    char filename3[] = "_23.txt"; // Manca prefisso "negozio"
    printf("Stringa di test (sbagliato - prefisso incompleto): \"%s\" -> ID %u ", filename3, ottenereIdNegozioDaNome(filename3));
    assert(ottenereIdNegozioDaNome(filename3)==0);
    printf("%s\n", "OK");

    char filename4[] = "negozio23.txt"; // Manca underscore
    printf("Stringa di test (sbagliato - underscore mancante): \"%s\" -> ID %u ", filename4, ottenereIdNegozioDaNome(filename4));
    assert(ottenereIdNegozioDaNome(filename4) == 0);
    printf("%s\n", "OK");

    char filename5[] = "negozio_23txt"; // Manca punto prima dell'estensione
    printf("Stringa di test (sbagliato - punto estensione mancante): \"%s\" -> ID %u ", filename5, ottenereIdNegozioDaNome(filename5));
    assert(ottenereIdNegozioDaNome(filename5) == 0);
    printf("%s\n", "OK");

    char filename6[] = "nomesbagliato"; // Formato completamente errato
    printf("Stringa di test (sbagliato - formato generico): \"%s\" -> ID %u ", filename6, ottenereIdNegozioDaNome(filename6));
    assert(ottenereIdNegozioDaNome(filename6) == 0);
    printf("%s\n", "OK");

    char filename7[] = "_23."; // Estensione vuota o incompleta
    printf("Stringa di test (sbagliato - estensione vuota): \"%s\" -> ID %u ", filename7, ottenereIdNegozioDaNome(filename7));
    assert(ottenereIdNegozioDaNome(filename7)==0);
    printf("%s\n", "OK");

    char filename8[] = "negozio__23.txt"; // Doppio underscore
    printf("Stringa di test (sbagliato - doppio underscore): \"%s\" -> ID %u ", filename8, ottenereIdNegozioDaNome(filename8));
    assert(ottenereIdNegozioDaNome(filename8) == 0);
    printf("%s\n", "OK");

    puts("");

    puts("TEST inputUtente");
    // Questa funzione è interattiva e difficile da testare automaticamente con assert.
    // L'utente deve fornire manualmente l'input durante l'esecuzione dei test.
    printf("InputUtente testato manualmente, commentato per test automatici.\n");
    // Per testare manualmente:
    /*
    char buffer[MAXCHAR];
    printf("Inserisci una stringa per testare inputUtente: ");
    inputUtente(buffer, MAXCHAR);
    printf("Hai inserito: \"%s\"\n", buffer);
    */

    puts("\n--- TUTTI I TEST DI UTILITÀ SONO STATI ESEGUITI CON SUCCESSO! ---\n");
}

/**
 * @brief Esegue test unitari sulle funzioni di controllo e validazione (modulo `controlli.c`).
 *
 * Questa funzione testa:
 * - `formatoNomeFile`: verifica la correttezza del formato dei nomi dei file.
 * - `formatoStringa`: controlla la presenza di spazi iniziali/finali o tabulazioni nelle stringhe.
 * - `stringaSoloNumeriODecimali`: verifica se una stringa contiene solo numeri o decimali.
 * - `stringaSoloCaratteri`: verifica se una stringa contiene solo caratteri alfabetici.
 * - `lunghezzaMassimaStringa`: controlla la lunghezza massima consentita per una stringa.
 * - `controlloRigheFile`: verifica che ogni riga di un file termini con un newline, inclusa l'ultima.
 * - `controlloNumeroDivisori`: conta e valida il numero di separatori in una stringa di record.
 * - `validaRecordAnimale`: funzione complessa che valida un'intera stringa di record di animale
 * considerando tutti i criteri (formato, duplicati, lunghezze, tipi di dato).
 *
 * Per i test sui file, vengono creati temporaneamente dei file (`.txt`) che vengono poi rimossi.
 * Vengono utilizzate asserzioni (`assert`) per verificare la correttezza dei risultati in ogni test case.
 */
void testControlli()
{
    puts("--- INIZIO TEST FUNZIONI DI CONTROLLO ---\n");

    puts("TEST: formatoNomeFile");

    // Test case validi per formatoNomeFile
    char filename[] = "negozio_23.txt";
    printf("Stringa di test (giusta): \"%s\" ", filename);
    assert(formatoNomeFile(filename) == 1); // Deve essere 1 (true)
    printf("%s\n","OK");

    // Test case non validi per formatoNomeFile
    char filename1[] = "23.txt"; // Manca prefisso "negozio_"
    printf("Stringa di test (sbagliata - no prefisso): \"%s\" ", filename1);
    assert(formatoNomeFile(filename1) == 0); // Deve essere 0 (false)
    printf("%s\n","OK");

    char filename2[] = "negozio_23"; // Manca estensione ".txt"
    printf("Stringa di test (sbagliata - no estensione): \"%s\" ", filename2);
    assert(formatoNomeFile(filename2) == 0);
    printf("%s\n","OK");

    char filename3[] = "_23.txt"; // Manca prefisso "negozio"
    printf("Stringa di test (sbagliata - prefisso mancante): \"%s\" ", filename3);
    assert(formatoNomeFile(filename3) == 0);
    printf("%s\n","OK");

    char filename4[] = "negozio23.txt"; // Manca underscore
    printf("Stringa di test (sbagliata - underscore mancante): \"%s\" ", filename4);
    assert(formatoNomeFile(filename4) == 0);
    printf("%s\n","OK");

    char filename5[] = "negozio_23txt"; // Manca punto prima dell'estensione
    printf("Stringa di test (sbagliata - punto estensione mancante): \"%s\" ", filename5);
    assert(formatoNomeFile(filename5) == 0);
    printf("%s\n","OK");

    char filename6[] = "nomesbagliato"; // Formato completamente errato
    printf("Stringa di test (sbagliata - formato generico): \"%s\" ", filename6);
    assert(formatoNomeFile(filename6) == 0);
    printf("%s\n","OK");

    char filename7[] = "_23."; // Estensione vuota o incompleta
    printf("Stringa di test (sbagliata - estensione vuota): \"%s\" ", filename7);
    assert(formatoNomeFile(filename7)==0);
    printf("%s\n","OK");

    char filename8[] = "negozio__23.txt"; // Doppio underscore
    printf("Stringa di test (sbagliata - doppio underscore): \"%s\" ", filename8);
    assert(formatoNomeFile(filename8) == 0);
    printf("%s\n","OK");

    puts("\nTEST: formatoStringa");

    // Test case validi per formatoStringa (no spazi iniziali/finali, no tab)
    char stringa1[] = "ciao";
    printf("Stringa di test (giusta - no spazi iniziali/finali, no tab): \"%s\" ", stringa1);
    assert(formatoStringa(stringa1) == 1);
    printf("%s\n","OK");

    char stringa2[] = "ciao pino"; // Spazi interni sono permessi
    printf("Stringa di test (giusta - con spazi interni): \"%s\" ", stringa2);
    assert(formatoStringa(stringa2) == 1);
    printf("%s\n","OK");

    // Test case non validi per formatoStringa
    char stringa3[] = " ciao"; // Spazio iniziale
    printf("Stringa di test (sbagliata - spazio iniziale): \"%s\" ", stringa3);
    assert(formatoStringa(stringa3) == 0);
    printf("%s\n","OK");

    char stringa4[] = "ciao nonno\t"; // Tabulazione finale
    printf("Stringa di test (sbagliata - tabulazione): \"ciao nonno\\t\" ");
    assert(formatoStringa(stringa4) == 0);
    printf("%s\n","OK");

    char stringa5[] = "ciao nonno "; // Spazio finale
    printf("Stringa di test (sbagliata - spazio finale): \"%s\" ", stringa5);
    assert(formatoStringa(stringa5) == 0);
    printf("%s\n","OK");


    puts("\nTEST: stringaSoloNumeriODecimali");

    // Test case validi per stringaSoloNumeriODecimali
    char stringa6[] = "123";
    printf("Stringa di test (giusta - solo numeri): \"%s\" ", stringa6);
    assert(stringaSoloNumeriODecimali(stringa6) == 1);
    printf("%s\n","OK");

    char stringa6_1[] = "123.45";
    printf("Stringa di test (giusta - con decimali): \"%s\" ", stringa6_1);
    assert(stringaSoloNumeriODecimali(stringa6_1) == 1);
    printf("%s\n","OK");

    // Test case non validi per stringaSoloNumeriODecimali
    char stringa7[] = "34f5t"; // Caratteri non numerici
    printf("Stringa di test (sbagliata - caratteri non numerici): \"%s\" ", stringa7);
    assert(stringaSoloNumeriODecimali(stringa7) == 0);
    printf("%s\n","OK");

    puts("\nTEST: stringaSoloCaratteri");

    // Test case validi per stringaSoloCaratteri
    char stringa8[] = "abcd";
    printf("Stringa di test (giusta - solo alfabetici): \"%s\" ", stringa8);
    assert(stringaSoloCaratteri(stringa8) == 1);
    printf("%s\n","OK");

    // Test case non validi per stringaSoloCaratteri
    char stringa9[] = "34f5t"; // Contiene numeri
    printf("Stringa di test (sbagliata - contiene numeri/non alfabetici): \"%s\" ", stringa9);
    assert(stringaSoloCaratteri(stringa9) == 0);
    printf("%s\n","OK");

    char stringa9_1[] = "stringa con spazi"; // Contiene spazi (non sono considerati caratteri alfabetici qui)
    printf("Stringa di test (sbagliata - contiene spazi): \"%s\" ", stringa9_1);
    assert(stringaSoloCaratteri(stringa9_1) == 0);
    printf("%s\n","OK");

    puts("\nTEST: lunghezzaMassimaStringa");

    // Test case validi per lunghezzaMassimaStringa
    char stringa10[] = "abcdefg";
    printf("Stringa di test (giusta - lunghezza %zu <= 50): \"%s\" ", strlen(stringa10), stringa10);
    assert(lunghezzaMassimaStringa(stringa10,50) == 1);
    printf("%s\n","OK");

    char stringa11[] = "qwertyuioppoiuytrewqqwertyuiopoiuytrewqwertyuuiopi"; // Lunghezza 50
    printf("Stringa di test (giusta - lunghezza %zu <= 50): \"%s\" ", strlen(stringa11), stringa11);
    assert(lunghezzaMassimaStringa(stringa11,50) == 1);
    printf("%s\n","OK");

    // Test case non validi per lunghezzaMassimaStringa
    char stringa12[] = "qwertyuioppoiuytrewqqwertyuiopoiuytrewqwertyuuioperwerweri"; // Lunghezza 56 > 50
    printf("Stringa di test (sbagliata - lunghezza %zu > 50): \"%s\" ", strlen(stringa12), stringa12);
    assert(lunghezzaMassimaStringa(stringa12,50) == 0);
    printf("%s\n","OK");

    puts("\nTEST: controlloRigheFile");

    // Creazione di file temporanei per i test
    FILE *f_testRighe1 = fopen("testRighe1.txt", "w");
    if (f_testRighe1) { fprintf(f_testRighe1, "linea1\nlinea2\nlinea3"); fclose(f_testRighe1); } // Ultima riga SENZA newline

    FILE *f_testRighe2 = fopen("testRighe2.txt", "w");
    if (f_testRighe2) { fprintf(f_testRighe2, "linea1\nlinea2\nlinea3\n"); fclose(f_testRighe2); } // Tutte le righe CON newline

    FILE *f_testRighe3 = fopen("testRighe3.txt", "w");
    if (f_testRighe3) { fprintf(f_testRighe3, "linea1\n"); fclose(f_testRighe3); } // Singola riga CON newline

    // Test con file senza newline all'ultima riga
    char filenameA[] = "testRighe1.txt";
    FILE *filePtrA = fopen(filenameA,"r");
    printf("File di test (ultima riga SENZA newline): \"%s\" ", filenameA);
    assert(filePtrA && controlloRigheFile(filePtrA) == 0); // Deve restituire 0
    if (filePtrA) fclose(filePtrA);
    printf("%s\n","OK");

    // Test con file con tutti i newline
    char filenameB[] = "testRighe2.txt";
    FILE *filePtrB = fopen(filenameB,"r");
    printf("File di test (tutte le righe CON newline): \"%s\" ", filenameB);
    assert(filePtrB && controlloRigheFile(filePtrB) == 1); // Deve restituire 1
    if (filePtrB) fclose(filePtrB);
    printf("%s\n","OK");

    // Test con file con singola riga e newline
    char filenameC[] = "testRighe3.txt";
    FILE *filePtrC = fopen(filenameC,"r");
    printf("File di test (singola riga CON newline): \"%s\" ", filenameC);
    assert(filePtrC && controlloRigheFile(filePtrC) == 1); // Deve restituire 1
    if (filePtrC) fclose(filePtrC);
    printf("%s\n","OK");

    puts("\nTEST: controlloNumeroDivisori");

    // Test case validi per controlloNumeroDivisori (4 separatori attesi)
    char stringa13_copy[MAXCHAR];
    strcpy(stringa13_copy, "1*Cane*Fido*3*200"); // 4 divisori ('*')
    printf("Stringa di test (giusta, 4 divisori): \"%s\"\n", stringa13_copy);
    assert(controlloNumeroDivisori(stringa13_copy) == 1);
    printf("%s\n","OK");

    // Test case non validi per controlloNumeroDivisori
    char stringa14_copy[MAXCHAR];
    strcpy(stringa14_copy, "1*Cane*Fido*3"); // 3 divisori
    printf("Stringa di test (sbagliata, 3 divisori): \"%s\"\n", stringa14_copy);
    assert(controlloNumeroDivisori(stringa14_copy) == 0);
    printf("%s\n","OK");

    char stringa15_copy[MAXCHAR];
    strcpy(stringa15_copy, "1*Cane*Fido*3*200*Extra"); // 5 divisori
    printf("Stringa di test (sbagliata, 5 divisori): \"%s\"\n", stringa15_copy);
    assert(controlloNumeroDivisori(stringa15_copy) == 0);
    printf("%s\n","OK");

    // Pulizia dei file temporanei creati per i test di controlloRigheFile
    remove("testRighe1.txt");
    remove("testRighe2.txt");
    remove("testRighe3.txt");

    // Prepara una lista di animali per il test di controlloDoppioCodice e validaRecordAnimale
    Lista* lista_doppioCodice = creaListaAnimali();
    assert(lista_doppioCodice != NULL);

    Animale* dc1 = creaAnimale(33, "Cane", "Bob", 6, 23.0f);
    Animale* dc2 = creaAnimale(22, "Gatto", "Tom", 12, 123.0f);
    assert(dc1 != NULL && dc2 != NULL);

    inserisciAnimaleInLista(lista_doppioCodice, dc1);
    inserisciAnimaleInLista(lista_doppioCodice, dc2);

    puts("\nTEST: controllaDoppioCodice (con ricercaAnimalePerIdInLista)");

    // Test: ricerca di un codice esistente nella lista
    unsigned int codice1 = 33;
    printf("Codice test (duplicato esistente): %u\n", codice1);
    assert(ricercaAnimalePerIdInLista(lista_doppioCodice, codice1) != NULL); // Dovrebbe trovare il codice 33
    printf("%s\n","OK");

    // Test: ricerca di un codice non esistente
    unsigned int codice2 = 99;
    printf("Codice test (non duplicato): %u\n", codice2);
    assert(ricercaAnimalePerIdInLista(lista_doppioCodice, codice2) == NULL); // Non dovrebbe trovare il codice 99
    printf("%s\n","OK");

    puts("\nTEST: validaRecordAnimale (ex controlloRecord)");
    // Nota: validaRecordAnimale è una funzione composita che internamente chiama molti dei controlli precedenti.

    char tc_copy[MAXCHAR]; // Buffer per copiare le stringhe di test

    // Test case validi per validaRecordAnimale
    strcpy(tc_copy, "1*Cane*Fido*3*200"); // Record valido, ID 1 non duplicato nella lista_doppioCodice
    printf("Stringa di test (giusta): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 1);
    printf("%s\n","OK");

    // Test case non validi per validaRecordAnimale (vari errori)
    strcpy(tc_copy, "2*Cane*Fido*3"); // Numero divisori errato
    printf("Stringa di test (sbagliata - numero divisori errato): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "3*Cane*Fido*3*200*Extra"); // Numero divisori errato
    printf("Stringa di test (sbagliata - numero divisori errato): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "12345678901*Cane*Fido*3*200"); // ID troppo grande (oltre i limiti di unsigned int o logici)
    printf("Stringa di test (sbagliata - ID troppo grande/formato): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "abc*Cane*Fido*3*200"); // ID non numerico
    printf("Stringa di test (sbagliata - ID non numerico): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "33*Cane*Fido*3*200"); // Codice duplicato (33 è già in lista_doppioCodice)
    printf("Stringa di test (sbagliata - codice duplicato): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "4*RazzaMoltoLungaPerTestOltreIlLimiteMassimoConTantiCaratteri*Nome*3*200"); // Razza troppo lunga
    printf("Stringa di test (sbagliata - razza troppo lunga): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "5*Cane Errore*Fido*3*200"); // Razza con spazi iniziali/finali o tab (non validi per formatoStringa su razza)
    printf("Stringa di test (sbagliata - razza con spazi non validi): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "6*Cane*Fido123*3*200"); // Nome con numeri (non validi per stringaSoloCaratteri su nome)
    printf("Stringa di test (sbagliata - nome con numeri): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "7*Cane*Nome Errore*3*200"); // Nome con spazi iniziali/finali o tab (non validi per formatoStringa su nome)
    printf("Stringa di test (sbagliata - nome con spazi non validi): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "8*Cane*Fido*abc*200"); // Età non numerica
    printf("Stringa di test (sbagliata - eta' non numerica): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "9*Cane*Fido*130000000*200"); // Età troppo grande (oltre i limiti definiti o di int)
    printf("Stringa di test (sbagliata - eta' troppo grande): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "10*Cane*Fido*3*abc"); // Prezzo non numerico
    printf("Stringa di test (sbagliata - prezzo non numerico): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    strcpy(tc_copy, "11*Cane*Fido*3*200000000000.00"); // Prezzo troppo grande (oltre i limiti di float o logici)
    printf("Stringa di test (sbagliata - prezzo troppo grande): \"%s\"\n", tc_copy);
    assert(validaRecordAnimale(tc_copy, lista_doppioCodice) == 0);
    printf("%s\n","OK");

    distruggiListaAnimali(lista_doppioCodice); // Libera la memoria della lista di test

    puts("\n--- TUTTI I TEST DEI CONTROLLI SONO STATI ESEGUITI CON SUCCESSO! ---\n");
}

void testFile()
{
    puts("TEST FILE");
    puts("");
    puts("TEST APERTURA e CHIUSURA");
    char filename[] = "file_esistente_test.txt";
    char mod1[] = "r";

    // Create a temporary file for testing existing file open
    FILE *temp_file = fopen(filename, "w");
    if (temp_file) {
        fprintf(temp_file, "Questo e' un file di test.\n");
        fclose(temp_file);
    }

    printf("Apertura File (giusta) %s, %s ", filename, mod1);
    /**
     * @brief Tests the `apriFile` function with an existing file in read mode.
     * @details This assertion verifies that `apriFile` returns 1 (success)
     * when attempting to open a pre-existing file in "r" (read) mode.
     */
    assert(apriFile(filename, mod1) == 1);
    printf("%s\n", "OK");

    printf("Chiusura file ");
    /**
     * @brief Tests the `chiudiFile` function after a successful file open.
     * @details This assertion verifies that `chiudiFile` returns 1 (success)
     * after a file has been successfully opened.
     */
    assert(chiudiFile() == 1);
    printf("%s\n", "OK");

    char mod2[] = "w";
    printf("Apertura File (giusta) %s, %s ", filename, mod2);
    /**
     * @brief Tests the `apriFile` function with an existing file in write mode.
     * @details This assertion verifies that `apriFile` returns 1 (success)
     * when attempting to open a pre-existing file in "w" (write) mode.
     */
    assert(apriFile(filename, mod2) == 1);
    printf("%s\n", "OK");

    printf("Chiusura file (giusta): ");
    /**
     * @brief Tests the `chiudiFile` function after a successful file open in write mode.
     * @details This assertion verifies that `chiudiFile` returns 1 (success)
     * after a file has been successfully opened in "w" mode.
     */
    assert(chiudiFile() == 1);
    printf("%s\n", "OK");

    char filename1[] = "file_NON_esistente_test.txt";
    printf("Apertura File (errata) %s, %s ", filename1, mod1);
    /**
     * @brief Tests the `apriFile` function with a non-existent file in read mode.
     * @details This assertion verifies that `apriFile` returns 0 (failure)
     * when attempting to open a non-existent file in "r" (read) mode.
     */
    assert(apriFile(filename1, mod1) == 0);
    printf("%s\n", "OK");

    printf("Chiusura file (errata): ");
    /**
     * @brief Tests the `chiudiFile` function when no file is currently open.
     * @details This assertion verifies that `chiudiFile` returns 0 (failure)
     * when attempting to close a file when no file is currently open.
     */
    assert(chiudiFile() == 0);
    printf("%s\n", "OK");

    puts("");

    puts("TEST lettura/scrittura");

    // Create a temporary "negozio_1.txt" file for reading
    FILE *f_negozio1 = fopen("negozio_1.txt", "w");
    if (f_negozio1) {
        fprintf(f_negozio1, "1*Cane*Fido*3*150.00\n");
        fprintf(f_negozio1, "2*Gatto*Micio*5*120.00\n");
        fclose(f_negozio1);
    }

    // Create an empty "testScrittura.txt" file for writing
    FILE *f_testScrittura = fopen("testScrittura.txt", "w");
    if (f_testScrittura) fclose(f_testScrittura);

    NodoNegozioPtr testa3 = NULL;
    /**
     * @brief Tests the `letturaFile` function.
     * @details This call attempts to read data from "negozio_1.txt" and populate
     * a linked list of `NodoNegozioPtr`.
     */
    letturaFile("negozio_1.txt",&testa3);
    stampaListaGlobaleNegozi(testa3);
    NodoNegozioPtr currPtr = testa3;
    while(currPtr != NULL)
    {
        /**
         * @brief Tests the `scritturaSingoloNegozioFile` function.
         * @details This loop iterates through the loaded `NodoNegozioPtr` list
         * and writes each node's data to "testScrittura.txt".
         */
        scritturaSingoloNegozioFile("testScrittura.txt",currPtr);
        currPtr = getNodoNegozioNext(currPtr);
    }
    liberaListaGlobaleNegozi(testa3);
    puts("Controllo manuale del file 'testScrittura.txt' per verifica scrittura.\n");

    puts("");

    puts("TEST estrazioneToken");

    char tokenizedStr[] = "1*Cane*Fido*3*200.00";
    unsigned int tempId = 0;
    char tempRazza[MAXCHAR_BUFFER];
    char tempNome[MAXCHAR_BUFFER];
    int tempEta = 0;
    float tempPrezzo = 0.0f;

    Lista* listaAnimali_estrazione = creaListaAnimali();
    assert(listaAnimali_estrazione != NULL);
    printf("Estrazione Token (giusta) \n");

    /**
     * @brief Tests the `estrazioneToken` function with a valid input string.
     * @details This assertion verifies that `estrazioneToken` correctly parses
     * a well-formatted string and returns 1 (success). It also prints the extracted
     * values for manual verification.
     */
    assert(estrazioneToken(tokenizedStr, &tempId, tempRazza, tempNome, &tempEta, &tempPrezzo, listaAnimali_estrazione) == 1);
    printf("ID: %u, Razza: %s, Nome: %s, Eta: %d, Prezzo: %.2f\n", tempId, tempRazza, tempNome, tempEta, tempPrezzo);
    printf("%s\n", "OK");

    char tokenizedStr1[] = "22Fisica*Is1acco*12*123";
    Lista* listaAnimali_estrazione1 = creaListaAnimali();
    assert(listaAnimali_estrazione1 != NULL);
    printf("Estrazione Token (sbagliata) \n");
    /**
     * @brief Tests the `estrazioneToken` function with an invalid input string.
     * @details This assertion verifies that `estrazioneToken` returns 0 (failure)
     * when provided with a malformed string that cannot be parsed correctly.
     */
    assert(estrazioneToken(tokenizedStr1, &tempId, tempRazza, tempNome, &tempEta, &tempPrezzo, listaAnimali_estrazione1) == 0);
    printf("%s\n", "OK");

    distruggiListaAnimali(listaAnimali_estrazione);
    distruggiListaAnimali(listaAnimali_estrazione1);

    // Clean up temporary files
    remove("file_esistente_test.txt");
    remove("file_NON_esistente_test.txt");
    remove("testRighe1.txt"); // Assuming these are created by other tests or a previous run
    remove("testRighe2.txt");
    remove("testRighe3.txt");
    remove("negozio_1.txt");
    remove("testScrittura.txt");
}

void testFunzioni()
{
    puts("TEST FUNZIONI");

    puts("NEGOZI UGUALI");
    NodoNegozioPtr testaNe = NULL;
    Lista* listaAn_uguale1 = creaListaAnimali();
    Lista* listaAn_uguale2 = creaListaAnimali();
    assert(listaAn_uguale1 != NULL && listaAn_uguale2 != NULL);

    Animale* u1_a1 = creaAnimale(11, "Cane", "Max", 6, 23.0f);
    Animale* u1_a2 = creaAnimale(22, "Gatto", "Luna", 12, 123.0f);
    Animale* u1_a3 = creaAnimale(12, "Uccello", "Pino", 15, 213.0f);
    Animale* u1_a4 = creaAnimale(16, "Pesce", "Nemo", 5, 27.0f);
    Animale* u1_a5 = creaAnimale(111, "Coniglio", "Bianco", 22, 38.0f);
    assert(u1_a1 != NULL && u1_a2 != NULL && u1_a3 != NULL && u1_a4 != NULL && u1_a5 != NULL);

    inserisciAnimaleInLista(listaAn_uguale1, u1_a1);
    inserisciAnimaleInLista(listaAn_uguale1, u1_a2);
    inserisciAnimaleInLista(listaAn_uguale1, u1_a3);
    inserisciAnimaleInLista(listaAn_uguale1, u1_a4);
    inserisciAnimaleInLista(listaAn_uguale1, u1_a5);

    Animale* u2_a1 = creaAnimale(11, "Cane", "Max", 6, 23.0f);
    Animale* u2_a2 = creaAnimale(22, "Gatto", "Luna", 12, 123.0f);
    Animale* u2_a3 = creaAnimale(12, "Uccello", "Pino", 15, 213.0f);
    Animale* u2_a4 = creaAnimale(16, "Pesce", "Nemo", 5, 27.0f);
    Animale* u2_a5 = creaAnimale(111, "Coniglio", "Bianco", 22, 38.0f);
    assert(u2_a1 != NULL && u2_a2 != NULL && u2_a3 != NULL && u2_a4 != NULL && u2_a5 != NULL);

    inserisciAnimaleInLista(listaAn_uguale2, u2_a1);
    inserisciAnimaleInLista(listaAn_uguale2, u2_a2);
    inserisciAnimaleInLista(listaAn_uguale2, u2_a3);
    inserisciAnimaleInLista(listaAn_uguale2, u2_a4);
    inserisciAnimaleInLista(listaAn_uguale2, u2_a5);

    NodoNegozioPtr negozio_uguale1 = creaNegozio(1);
    assert(negozio_uguale1 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe, negozio_uguale1) == 1);
    setInventarioNegozio(negozio_uguale1, listaAn_uguale1);

    NodoNegozioPtr negozio_uguale2 = creaNegozio(2);
    assert(negozio_uguale2 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe, negozio_uguale2) == 1);
    setInventarioNegozio(negozio_uguale2, listaAn_uguale2);

    stampaListaGlobaleNegozi(testaNe);

    /**
     * @brief Tests the `uguaglianzaNegozi` function with two identical shops.
     * @details This call attempts to find common animals between two shops that have
     * the exact same inventory. It then asserts that a non-NULL result (indicating
     * common elements) is returned and prints the resulting common list.
     */
    NodoNegozioPtr test_uguaglianza_ptr = uguaglianzaNegozi(getNodoNegozioNext(negozio_uguale2), negozio_uguale1);

    printf("Test (corretto):\n");
    if(test_uguaglianza_ptr != NULL) {
        stampaListaGlobaleNegozi(test_uguaglianza_ptr);
        assert(getNegozioId(test_uguaglianza_ptr) != 0); // Asserting that the returned node is valid
    } else {
        printf("Nessun negozio uguale trovato (o fallback 0*0*0*0*0 nel file)\n");
        assert(test_uguaglianza_ptr == NULL); // Should not happen with identical shops
    }
    printf("OK\n");

    liberaListaGlobaleNegozi(testaNe);


    puts("NEGOZI DIVERSI");
    NodoNegozioPtr testaNe2 = NULL;
    Lista* listaAn_diverso1 = creaListaAnimali();
    Lista* listaAn_diverso2 = creaListaAnimali();
    assert(listaAn_diverso1 != NULL && listaAn_diverso2 != NULL);

    Animale* d1_a1 = creaAnimale(11, "Cane", "Bob", 6, 23.0f);
    Animale* d1_a2 = creaAnimale(22, "Gatto", "Garfield", 12, 123.0f);
    Animale* d1_a3 = creaAnimale(2, "Uccello", "Kiwi", 15, 213.0f);
    Animale* d1_a4 = creaAnimale(16, "Pesce", "Squalo", 5, 27.0f);
    Animale* d1_a5 = creaAnimale(111, "Coniglio", "Fuzzy", 22, 38.0f);
    assert(d1_a1 != NULL && d1_a2 != NULL && d1_a3 != NULL && d1_a4 != NULL && d1_a5 != NULL);

    inserisciAnimaleInLista(listaAn_diverso1, d1_a1);
    inserisciAnimaleInLista(listaAn_diverso1, d1_a2);
    inserisciAnimaleInLista(listaAn_diverso1, d1_a3);
    inserisciAnimaleInLista(listaAn_diverso1, d1_a4);
    inserisciAnimaleInLista(listaAn_diverso1, d1_a5);

    Animale* d2_a1 = creaAnimale(100, "AltroCane", "Bob", 6, 23.0f);
    Animale* d2_a2 = creaAnimale(200, "AltroGatto", "Garfield", 12, 123.0f);
    Animale* d2_a3 = creaAnimale(300, "AltroUccello", "Kiwi", 15, 213.0f);
    Animale* d2_a4 = creaAnimale(400, "AltroPesce", "Squalo", 5, 27.0f);
    Animale* d2_a5 = creaAnimale(500, "AltroConiglio", "Fuzzy", 22, 38.0f);
    assert(d2_a1 != NULL && d2_a2 != NULL && d2_a3 != NULL && d2_a4 != NULL && d2_a5 != NULL);

    inserisciAnimaleInLista(listaAn_diverso2, d2_a1);
    inserisciAnimaleInLista(listaAn_diverso2, d2_a2);
    inserisciAnimaleInLista(listaAn_diverso2, d2_a3);
    inserisciAnimaleInLista(listaAn_diverso2, d2_a4);
    inserisciAnimaleInLista(listaAn_diverso2, d2_a5);

    NodoNegozioPtr negozio_diverso1 = creaNegozio(1);
    assert(negozio_diverso1 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe2, negozio_diverso1) == 1);
    setInventarioNegozio(negozio_diverso1, listaAn_diverso1);

    NodoNegozioPtr negozio_diverso2 = creaNegozio(2);
    assert(negozio_diverso2 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe2, negozio_diverso2) == 1);
    setInventarioNegozio(negozio_diverso2, listaAn_diverso2);

    stampaListaGlobaleNegozi(testaNe2);

    /**
     * @brief Tests the `uguaglianzaNegozi` function with two shops having different inventories.
     * @details This call attempts to find common animals between two shops with entirely
     * different inventories. It then asserts that a NULL result (indicating no common elements)
     * is returned.
     */
    NodoNegozioPtr test_uguaglianza_ptr1 = uguaglianzaNegozi(getNodoNegozioNext(negozio_diverso2), negozio_diverso1);

    printf("Test (corretto - nessun record comune):\n");
    if(test_uguaglianza_ptr1 != NULL) {
        stampaListaGlobaleNegozi(test_uguaglianza_ptr1); // Should not be reached
    } else {
        printf("Nessun negozio uguale trovato (o fallback 0*0*0*0*0 nel file)\n");
        assert(test_uguaglianza_ptr1 == NULL);
    }
    printf("%s\n", "OK");

    liberaListaGlobaleNegozi(testaNe2);


    puts("NEGOZIO CON DOPPIONI (INTERNI ALLA LISTA ANIMALI DEL NEGOZIO)");
    NodoNegozioPtr testaNe3 = NULL;
    Lista* listaAn_doppioni1 = creaListaAnimali();
    Lista* listaAn_doppioni2 = creaListaAnimali();
    assert(listaAn_doppioni1 != NULL && listaAn_doppioni2 != NULL);

    Animale* dupl1_a1 = creaAnimale(11, "Cane", "Leo", 6, 23.0f);
    Animale* dupl1_a2 = creaAnimale(22, "Gatto", "Molly", 12, 123.0f);
    Animale* dupl1_a3 = creaAnimale(22, "Gatto", "Molly", 12, 123.0f); // Duplicate
    Animale* dupl1_a4 = creaAnimale(16, "Pesce", "Bubbles", 5, 27.0f);
    Animale* dupl1_a5 = creaAnimale(111, "Coniglio", "Snowy", 22, 38.0f);
    assert(dupl1_a1 != NULL && dupl1_a2 != NULL && dupl1_a3 != NULL && dupl1_a4 != NULL && dupl1_a5 != NULL);

    inserisciAnimaleInLista(listaAn_doppioni1, dupl1_a1);
    inserisciAnimaleInLista(listaAn_doppioni1, dupl1_a2);
    inserisciAnimaleInLista(listaAn_doppioni1, dupl1_a3);
    inserisciAnimaleInLista(listaAn_doppioni1, dupl1_a4);
    inserisciAnimaleInLista(listaAn_doppioni1, dupl1_a5);

    Animale* dupl2_a1 = creaAnimale(11, "Cane", "Leo", 6, 23.0f);
    Animale* dupl2_a2 = creaAnimale(22, "Gatto", "Molly", 12, 123.0f);
    Animale* dupl2_a3 = creaAnimale(11, "Uccello", "Polly", 15, 213.0f); // Different animal, same ID as dupl2_a1
    Animale* dupl2_a4 = creaAnimale(16, "Pesce", "Bubbles", 5, 27.0f);
    Animale* dupl2_a5 = creaAnimale(111, "Coniglio", "Snowy", 22, 38.0f);
    assert(dupl2_a1 != NULL && dupl2_a2 != NULL && dupl2_a3 != NULL && dupl2_a4 != NULL && dupl2_a5 != NULL);

    inserisciAnimaleInLista(listaAn_doppioni2, dupl2_a1);
    inserisciAnimaleInLista(listaAn_doppioni2, dupl2_a2);
    inserisciAnimaleInLista(listaAn_doppioni2, dupl2_a3);
    inserisciAnimaleInLista(listaAn_doppioni2, dupl2_a4);
    inserisciAnimaleInLista(listaAn_doppioni2, dupl2_a5);

    NodoNegozioPtr negozio_doppioni1 = creaNegozio(1);
    assert(negozio_doppioni1 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe3, negozio_doppioni1) == 1);
    setInventarioNegozio(negozio_doppioni1, listaAn_doppioni1);

    NodoNegozioPtr negozio_doppioni2 = creaNegozio(2);
    assert(negozio_doppioni2 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe3, negozio_doppioni2) == 1);
    setInventarioNegozio(negozio_doppioni2, listaAn_doppioni2);

    stampaListaGlobaleNegozi(testaNe3);

    /**
     * @brief Tests the `uguaglianzaNegozi` function with shops containing internal duplicates.
     * @details This call attempts to find common animals between two shops where one or both
     * lists of animals might contain duplicate entries (based on ID, name, etc.). It then
     * prints the resulting common list or confirms no common elements are found.
     */
    NodoNegozioPtr test_uguaglianza_ptr2 = uguaglianzaNegozi(getNodoNegozioNext(negozio_doppioni2), negozio_doppioni1);

    printf("Test (corretto - negozio con duplicati interni):\n");
    if(test_uguaglianza_ptr2 != NULL) {
        stampaListaGlobaleNegozi(test_uguaglianza_ptr2);
    } else {
        printf("Nessun negozio uguale trovato (o fallback 0*0*0*0*0 nel file)\n");
        assert(test_uguaglianza_ptr2 == NULL);
    }
    printf("%s\n", "OK");

    liberaListaGlobaleNegozi(testaNe3);


    puts("FUNZIONALITA' UGUALIANZA");

    NodoNegozioPtr testaNe_funzUguaglianza = NULL;
    Lista* ts_fu1 = creaListaAnimali();
    Lista* ts_fu2 = creaListaAnimali();
    assert(ts_fu1 != NULL && ts_fu2 != NULL);

    Animale* fu1_a1 = creaAnimale(1, "CaneA", "NomeA", 1, 1.0f);
    Animale* fu1_a2 = creaAnimale(2, "CaneB", "NomeB", 2, 2.0f);
    assert(fu1_a1 != NULL && fu1_a2 != NULL);
    inserisciAnimaleInLista(ts_fu1, fu1_a1);
    inserisciAnimaleInLista(ts_fu1, fu1_a2);

    Animale* fu2_a1 = creaAnimale(1, "CaneA", "NomeA", 1, 1.0f);
    Animale* fu2_a2 = creaAnimale(4, "CaneD", "NomeD", 4, 4.0f);
    assert(fu2_a1 != NULL && fu2_a2 != NULL);
    inserisciAnimaleInLista(ts_fu2, fu2_a1);
    inserisciAnimaleInLista(ts_fu2, fu2_a2);

    NodoNegozioPtr negozio_fu1 = creaNegozio(10);
    assert(negozio_fu1 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe_funzUguaglianza, negozio_fu1) == 1);
    setInventarioNegozio(negozio_fu1, ts_fu1);

    NodoNegozioPtr negozio_fu2 = creaNegozio(20);
    assert(negozio_fu2 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe_funzUguaglianza, negozio_fu2) == 1);
    setInventarioNegozio(negozio_fu2, ts_fu2);

    /**
     * @brief Tests the `funzionalitaUguaglianza` function.
     * @details This function call processes the global list of shops and
     * writes the results of equality comparisons to a file named "Uguaglianza.txt".
     * Manual verification of the output file is required to confirm correctness.
     */
    funzionalitaUguaglianza(testaNe_funzUguaglianza);
    printf("Test funzionalitaUguaglianza (verificare output manuale nel file Uguaglianza.txt)\n");
    liberaListaGlobaleNegozi(testaNe_funzUguaglianza);


    puts("TEST ORDINAMENTO");

    NodoNegozioPtr testaNe4 = NULL;
    Lista* listaAn_ordine1 = creaListaAnimali();
    Lista* listaAn_ordine2 = creaListaAnimali();
    assert(listaAn_ordine1 != NULL && listaAn_ordine2 != NULL);

    Animale* ord1_a1 = creaAnimale(11, "Gatto", "Muffin", 6, 23.0f);
    Animale* ord1_a2 = creaAnimale(22, "Cane", "Spike", 12, 123.0f);
    Animale* ord1_a3 = creaAnimale(12, "Uccello", "Kiwi", 15, 213.0f);
    Animale* ord1_a4 = creaAnimale(16, "Pesce", "Nemo", 5, 27.0f);
    Animale* ord1_a5 = creaAnimale(111, "Coniglio", "Bunny", 22, 38.0f);
    assert(ord1_a1 != NULL && ord1_a2 != NULL && ord1_a3 != NULL && ord1_a4 != NULL && ord1_a5 != NULL);

    inserisciAnimaleInLista(listaAn_ordine1, ord1_a1);
    inserisciAnimaleInLista(listaAn_ordine1, ord1_a2);
    inserisciAnimaleInLista(listaAn_ordine1, ord1_a3);
    inserisciAnimaleInLista(listaAn_ordine1, ord1_a4);
    inserisciAnimaleInLista(listaAn_ordine1, ord1_a5);

    Animale* ord2_a1 = creaAnimale(11, "Tartaruga", "Sheldon", 6, 23.0f);
    Animale* ord2_a2 = creaAnimale(22, "Serpente", "Kaa", 12, 123.0f);
    Animale* ord2_a3 = creaAnimale(12, "Criceto", "Nibbles", 15, 213.0f);
    Animale* ord2_a4 = creaAnimale(16, "Furetto", "Bandit", 5, 27.0f);
    Animale* ord2_a5 = creaAnimale(111, "Maiale", "Babe", 22, 38.0f);
    assert(ord2_a1 != NULL && ord2_a2 != NULL && ord2_a3 != NULL && ord2_a4 != NULL && ord2_a5 != NULL);

    inserisciAnimaleInLista(listaAn_ordine2, ord2_a1);
    inserisciAnimaleInLista(listaAn_ordine2, ord2_a2);
    inserisciAnimaleInLista(listaAn_ordine2, ord2_a3);
    inserisciAnimaleInLista(listaAn_ordine2, ord2_a4);
    inserisciAnimaleInLista(listaAn_ordine2, ord2_a5);

    NodoNegozioPtr negozio_ordine1 = creaNegozio(1);
    assert(negozio_ordine1 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe4, negozio_ordine1) == 1);
    setInventarioNegozio(negozio_ordine1, listaAn_ordine1);

    NodoNegozioPtr negozio_ordine2 = creaNegozio(2);
    assert(negozio_ordine2 != NULL);
    assert(inserisciNegozioInListaGlobale(&testaNe4, negozio_ordine2) == 1);
    setInventarioNegozio(negozio_ordine2, listaAn_ordine2);

    stampaListaGlobaleNegozi(testaNe4);

    puts("FUNZIONALITA' ORDINE");

    /**
     * @brief Tests the `funzionalitaOrdine` function.
     * @details This function call processes the global list of shops and
     * writes the results of the sorting operation to a file named "Ordine.txt".
     * Manual verification of the output file is required to confirm correctness
     * of the sorting logic.
     */
    funzionalitaOrdine(testaNe4);
    printf("Test funzionalitaOrdine (verificare output manuale nel file Ordine.txt)\n");

    liberaListaGlobaleNegozi(testaNe4);
}

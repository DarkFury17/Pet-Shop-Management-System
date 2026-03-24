/**
 * @file funzioni.c
 * @brief Modulo contenente le implementazioni delle funzionalità principali del programma,
 * inclusa l'acquisizione dei dati, il confronto di uguaglianza tra negozi,
 * l'ordinamento dei negozi e la gestione del menu utente.
 *
 * Questo modulo funge da strato logico principale dell'applicazione, coordinando le
 * operazioni sui dati tramite le API esposte dai moduli `dati`, `file`, `controlli` e `utils`.
 * Gestisce l'interazione con l'utente tramite un menu e orchestra le funzionalità
 * richieste.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#include "funzioni.h"
#include "dati.h"      // Per le strutture dati e le relative funzioni (es. AnimalePtr, NodoNegozioPtr, getAnimaleId, ecc.)
#include "controlli.h" // Per le funzioni di validazione dell'input (es. stringaSoloNumeriODecimali)
#include "file.h"      // Per le funzioni di gestione dei file (es. letturaFile, scritturaSingoloNegozioFile)
#include "utils.h"     // Per le funzioni di utilità (es. inputUtente, cleanConsole)

#include <string.h>  // Per strcmp, strcasecmp, strncpy
#include <stdlib.h>  // Per atoi, atof, strtoul
#include <stdio.h>   // Per printf, puts, fprintf, perror
#include <strings.h> // Per strcasecmp (su alcuni sistemi è in string.h, ma per compatibilità meglio includere entrambi)
#include <math.h>    // Per fabs (valore assoluto di float per confronto precisione)

/**
 * @brief Funzione statica helper che scrive un record "fallback" in un file e restituisce NULL.
 *
 * Questa funzione viene utilizzata per scrivere una riga di placeholder ("0*0*0*0*0\n")
 * in un file quando le condizioni di input per una funzionalità non sono soddisfatte (es. negozi o inventari vuoti),
 * garantendo che il file di output esista comunque con un contenuto predefinito.
 *
 * @param outFile Il puntatore al file su cui scrivere.
 * @param debug_message Un messaggio di debug (attualmente non usato internamente, ma utile per contesto).
 * @return Sempre NULL, indicando un fallimento logico o una condizione di non-risultato.
 */
static NodoNegozioPtr writeFallbackAndReturnEmpty(FILE *outFile, const char* debug_message) {
    fprintf(outFile, "0*0*0*0*0\n"); // Scrive il record di fallback
    return NULL;
}

/**
 * @brief Criterio di confronto per stringhe: verifica se `str1` precede alfabeticamente `str2`.
 *
 * @param str1 La prima stringa da confrontare.
 * @param str2 La seconda stringa da confrontare.
 * @return 1 se `str1` precede `str2` (strcmp < 0), 0 altrimenti (inclusi casi di NULL).
 */
int criterioStringaPrecede(char* str1, char* str2) {
    if (str1 == NULL || str2 == NULL) return 0;
    return strcmp(str1, str2) < 0;
}

/**
 * @brief Criterio di confronto per stringhe: verifica se `str1` segue alfabeticamente `str2`.
 *
 * @param str1 La prima stringa da confrontare.
 * @param str2 La seconda stringa da confrontare.
 * @return 1 se `str1` segue `str2` (strcmp > 0), 0 altrimenti (inclusi casi di NULL).
 */
int criterioStringaSegue(char* str1, char* str2) {
    if (str1 == NULL || str2 == NULL) return 0;
    return strcmp(str1, str2) > 0;
}

/**
 * @brief Trova la razza "estrema" (minima o massima alfabeticamente) in un inventario di animali.
 *
 * Questa è una funzione statica, interna al modulo `funzioni.c`.
 * Scorre la lista di animali e, usando la funzione di confronto `criterioConfronto` fornita,
 * determina la razza che soddisfa il criterio (es. la prima alfabeticamente o l'ultima).
 *
 * @param lista Il puntatore alla lista di animali in cui cercare.
 * @param criterioConfronto Un puntatore a funzione che definisce il criterio di confronto tra due stringhe (razze).
 * @return Un puntatore alla stringa che rappresenta la razza estrema trovata, o NULL se la lista è vuota.
 */
static char* findExtremeBrand(const ListaPtr lista, int (*criterioConfronto)(char*, char*)) {
    if (isListaAnimaliVuota(lista)) {
        return NULL;
    }

    // Inizializza con la razza del primo animale
    NodoAnimalePtr headNode = getListaAnimaliHeadNode(lista);
    char* extremeBrand = (char*)getAnimaleRazza((AnimalePtr)getNodoContent(headNode));
    NodoAnimalePtr current = getNodoNextNode(headNode);

    // Scorre la lista confrontando le razze
    while (current != NULL) {
        // Se la razza corrente soddisfa il criterio rispetto all'attuale extremeBrand, aggiorna
        if (criterioConfronto((char*)getAnimaleRazza((AnimalePtr)getNodoContent(current)), extremeBrand)) {
            extremeBrand = (char*)getAnimaleRazza((AnimalePtr)getNodoContent(current));
        }
        current = getNodoNextNode(current);
    }
    return extremeBrand;
}

/**
 * @brief Definisce il criterio di uguaglianza completa tra due oggetti `Animale`.
 *
 * Confronta tutti i campi rilevanti (ID, razza, nome, età, prezzo) tra due animali.
 * Per le stringhe, usa un confronto case-insensitive (`strcasecmp`).
 * Per i float, usa un confronto con tolleranza (`fabs`).
 *
 * @param animale1 Il puntatore al primo oggetto `Animale`.
 * @param animale2 Il puntatore al secondo oggetto `Animale`.
 * @return 1 se i due animali sono considerati uguali, 0 altrimenti.
 */
int criterioUguaglianzaAnimale(const AnimalePtr animale1, const AnimalePtr animale2) {
    // Confronta gli ID
    if(getAnimaleId(animale1) != getAnimaleId(animale2)) {
        return 0;
    }
    // Confronta le razze (case-insensitive)
    if(strcasecmp(getAnimaleRazza(animale1), getAnimaleRazza(animale2)) != 0) {
        return 0;
    }
    // Confronta i nomi (case-insensitive)
    if(strcasecmp(getAnimaleNome(animale1), getAnimaleNome(animale2)) != 0) {
        return 0;
    }
    // Confronta le età
    if(getAnimaleEta(animale1) != getAnimaleEta(animale2)) {
        return 0;
    }
    // Confronta i prezzi con una tolleranza per i numeri in virgola mobile
    if(fabs(getAnimalePrezzo(animale1) - getAnimalePrezzo(animale2)) > 0.001) { // Tolleranza 0.001
        return 0;
    }
    return 1; // Tutti i campi sono uguali
}

/**
 * @brief Confronta gli inventari di due negozi per trovare animali identici e li scrive su un file.
 *
 * La funzione esegue i seguenti passaggi:
 * 1. Apre il file "Uguaglianza.txt" in modalità scrittura.
 * 2. Esegue controlli preliminari sui negozi e sui loro inventari (non NULL e non vuoti).
 * 3. **Controllo interno per duplicati:** Verifica che non ci siano duplicati identici all'interno
 * dell'inventario di `negozio1` e `negozio2` stessi. Se ne trova, scrive un fallback e termina.
 * 4. Scorre l'inventario del `negozio1` e, per ogni animale, lo confronta con ogni animale
 * dell'inventario del `negozio2` usando `criterioUguaglianzaAnimale`.
 * 5. Se trova un animale identico in entrambi gli inventari, lo scrive nel file "Uguaglianza.txt".
 * 6. Se nessun record comune viene trovato, scrive un record di fallback nel file.
 * 7. Chiude il file.
 *
 * @param negozio1 Il puntatore costante al primo `NodoNegozioPtr` da confrontare.
 * @param negozio2 Il puntatore costante al secondo `NodoNegozioPtr` da confrontare.
 * @return Il puntatore al `negozio1` se sono stati trovati record comuni e scritti,
 * o NULL se non sono stati trovati record comuni, se gli input non sono validi,
 * o se ci sono duplicati interni rilevati.
 */
NodoNegozioPtr uguaglianzaNegozi(const NodoNegozioPtr negozio1, const NodoNegozioPtr negozio2) {
    // Apre il file di output
    FILE *outFile = fopen("Uguaglianza.txt", "w");
    if (outFile == NULL) {
        perror("Errore nell'apertura del file Uguaglianza.txt");
        return NULL;
    }

    // Controlli preliminari sui negozi e inventari
    if (negozio1 == NULL || negozio2 == NULL ||
        isListaAnimaliVuota(getInventarioNegozio(negozio1)) ||
        isListaAnimaliVuota(getInventarioNegozio(negozio2)))
    {
        NodoNegozioPtr result = writeFallbackAndReturnEmpty(outFile, "Input negozio o inventario vuoto.");
        fclose(outFile);
        return result;
    }

    NodoAnimalePtr currPtrAnimale1 = NULL;
    NodoAnimalePtr currPtrAnimale2 = NULL;
    int found_common_record = 0; // Flag per tracciare se è stato trovato almeno un record comune

    // --- Controllo per duplicati interni in negozio1 ---
    NodoAnimalePtr tempPtrAnimale1_outer = getListaAnimaliHeadNode(getInventarioNegozio(negozio1));
    while (tempPtrAnimale1_outer != NULL) {
        NodoAnimalePtr tempPtrAnimale1_inner = getNodoNextNode(tempPtrAnimale1_outer);
        while (tempPtrAnimale1_inner != NULL) {
            if (criterioUguaglianzaAnimale((AnimalePtr)getNodoContent(tempPtrAnimale1_outer), (AnimalePtr)getNodoContent(tempPtrAnimale1_inner))) {
                NodoNegozioPtr result = writeFallbackAndReturnEmpty(outFile, "Duplicato interno in negozio1.");
                fclose(outFile);
                return result; // Duplicato interno trovato, errore
            }
            tempPtrAnimale1_inner = getNodoNextNode(tempPtrAnimale1_inner);
        }
        tempPtrAnimale1_outer = getNodoNextNode(tempPtrAnimale1_outer);
    }

    // --- Controllo per duplicati interni in negozio2 ---
    NodoAnimalePtr tempPtrAnimale2_outer = getListaAnimaliHeadNode(getInventarioNegozio(negozio2));
    while (tempPtrAnimale2_outer != NULL) {
        NodoAnimalePtr tempPtrAnimale2_inner = getNodoNextNode(tempPtrAnimale2_outer);
        while (tempPtrAnimale2_inner != NULL) {
            if (criterioUguaglianzaAnimale((AnimalePtr)getNodoContent(tempPtrAnimale2_outer), (AnimalePtr)getNodoContent(tempPtrAnimale2_inner))) {
                NodoNegozioPtr result = writeFallbackAndReturnEmpty(outFile, "Duplicato interno in negozio2.");
                fclose(outFile);
                return result; // Duplicato interno trovato, errore
            }
            tempPtrAnimale2_inner = getNodoNextNode(tempPtrAnimale2_inner);
        }
        tempPtrAnimale2_outer = getNodoNextNode(tempPtrAnimale2_outer);
    }

    // --- Confronto degli animali tra i due negozi ---
    currPtrAnimale1 = getListaAnimaliHeadNode(getInventarioNegozio(negozio1));
    while (currPtrAnimale1 != NULL) {
        currPtrAnimale2 = getListaAnimaliHeadNode(getInventarioNegozio(negozio2));
        while (currPtrAnimale2 != NULL) {
            // Se due animali sono uguali secondo il criterio
            if (criterioUguaglianzaAnimale((AnimalePtr)getNodoContent(currPtrAnimale1), (AnimalePtr)getNodoContent(currPtrAnimale2))) {
                AnimalePtr a = (AnimalePtr)getNodoContent(currPtrAnimale1); // Prende il dato Animale
                // Scrive l'animale comune nel file, formattato con il SEPARATORE
                fprintf(outFile, "%u%c%s%c%s%c%d%c%.2f\n",
                                 getAnimaleId(a), SEPARATORE, getAnimaleRazza(a), SEPARATORE, getAnimaleNome(a),
                                 SEPARATORE, getAnimaleEta(a), SEPARATORE, getAnimalePrezzo(a));
                found_common_record = 1; // Imposta il flag a 1
            }
            currPtrAnimale2 = getNodoNextNode(currPtrAnimale2);
        }
        currPtrAnimale1 = getNodoNextNode(currPtrAnimale1);
    }

    // Se nessun record comune è stato trovato, scrive un fallback
    if (!found_common_record) {
        NodoNegozioPtr result = writeFallbackAndReturnEmpty(outFile, "Nessun record comune trovato.");
        fclose(outFile);
        return result;
    }

    fclose(outFile); // Chiude il file
    return (NodoNegozioPtr)negozio1; // Ritorna negozio1 per indicare successo (qualcosa è stato scritto)
}

/**
 * @brief Permette all'utente di scegliere un criterio per ordinare due negozi in base alle razze dei loro animali.
 *
 * La funzione presenta all'utente due opzioni:
 * 1. Trovare il negozio che "precede" (la cui razza più piccola alfabeticamente precede l'altra).
 * 2. Trovare il negozio che "segue" (la cui razza più grande alfabeticamente segue l'altra).
 * 3. Annullare l'operazione.
 *
 * Utilizza la funzione `findExtremeBrand` con il criterio scelto per determinare la "razza estrema"
 * di ciascun negozio e poi confronta queste razze per decidere quale negozio "precede" o "segue".
 *
 * @param negozio1 Il puntatore costante al primo `NodoNegozioPtr` da confrontare.
 * @param negozio2 Il puntatore costante al secondo `NodoNegozioPtr` da confrontare.
 * @return Il puntatore al `NodoNegozioPtr` del negozio selezionato secondo il criterio scelto,
 * o NULL se l'operazione è stata annullata, o se ci sono errori (es. negozi/inventari vuoti, errore interno).
 */
NodoNegozioPtr ordinamentoNegozi(const NodoNegozioPtr negozio1, const NodoNegozioPtr negozio2) {
    int scelta = 0;
    char tempScelta[MAXCHAR];
    int controllo = 0;

    // Controlli preliminari sui negozi e inventari
    if (negozio1 == NULL || isListaAnimaliVuota(getInventarioNegozio(negozio1))) {
        puts("ATTENZIONE: NEGOZIO 1 O IL SUO INVENTARIO SONO VUOTI. Impossibile ordinare.");
        return NULL;
    }
    if (negozio2 == NULL || isListaAnimaliVuota(getInventarioNegozio(negozio2))) {
        puts("ATTENZIONE: NEGOZIO 2 O IL SUO INVENTARIO SONO VUOTI. Impossibile ordinare.");
        return NULL;
    }

    // Menu per la scelta del criterio di ordinamento
    do {
        printf("\n--- SCELTA CRITERIO DI ORDINAMENTO TRA NEGOZI ---\n");
        printf("Digita 1 per trovare il negozio che PRECEDE (razza alfabeticamente piu' piccola).\n");
        printf("Digita 2 per trovare il negozio che SEGUE (razza alfabeticamente piu' grande).\n");
        printf("Digita 3 per annullare e tornare al menu precedente.\n");
        printf("La tua scelta: ");
        inputUtente(tempScelta, MAXCHAR); // Acquisisce l'input utente

        // Validazione dell'input
        if (stringaSoloNumeriODecimali(tempScelta)) {
            scelta = atoi(tempScelta); // Converte l'input in intero
            if (!(scelta >= 1 && scelta <= 3)) {
                controllo = 0;
                puts("Scelta inserita non corretta, riprovare (1, 2 o 3).");
            } else {
                controllo = 1;
            }
        } else {
            controllo = 0;
            puts("Scelta non valida. Inserisci un numero.");
        }
    } while (!controllo); // Ripete finché l'input non è valido

    // Se l'utente ha scelto di annullare
    if (scelta == 3) {
        puts("Ordinamento annullato.");
        return NULL;
    }

    // Imposta il puntatore a funzione in base alla scelta dell'utente
    int (*criterioScelto)(char*, char*) = NULL;
    if (scelta == 1) {
        criterioScelto = &criterioStringaPrecede;
    } else { // scelta == 2
        criterioScelto = &criterioStringaSegue;
    }

    // Trova la razza estrema (minima o massima) per ogni negozio
    char* extremeBrand1 = findExtremeBrand(getInventarioNegozio(negozio1), criterioScelto);
    char* extremeBrand2 = findExtremeBrand(getInventarioNegozio(negozio2), criterioScelto);

    if (extremeBrand1 == NULL || extremeBrand2 == NULL) {
        puts("ERRORE INTERNO: Impossibile determinare la razza estrema per uno o entrambi i negozi.");
        return NULL;
    }

    // Confronta le razze estreme
    int comparison_result = strcmp(extremeBrand1, extremeBrand2);

    if (comparison_result == 0) {
        printf("Le razze rappresentative dei due negozi sono identiche. Nessuno precede/segue l'altro.\n");
        return NULL; // Nessun negozio "vince"
    }

    // Restituisce il negozio che soddisfa il criterio
    if (scelta == 1) { // Criterio "precede"
        if (comparison_result < 0) {
            printf("Il negozio che PRECEDE gli altri (ID: %u) e' stato selezionato.\n", getNegozioId(negozio1));
            return (NodoNegozioPtr)negozio1;
        } else {
            printf("Il negozio che PRECEDE gli altri (ID: %u) e' stato selezionato.\n", getNegozioId(negozio2));
            return (NodoNegozioPtr)negozio2;
        }
    } else { // Criterio "segue"
        if (comparison_result > 0) {
            printf("Il negozio che SEGUE gli altri (ID: %u) e' stato selezionato.\n", getNegozioId(negozio1));
            return (NodoNegozioPtr)negozio1;
        } else {
            printf("Il negozio che SEGUE gli altri (ID: %u) e' stato selezionato.\n", getNegozioId(negozio2));
            return (NodoNegozioPtr)negozio2;
        }
    }
}

/**
 * @brief Implementa la funzionalità di acquisizione dati dal file system.
 *
 * Tenta di leggere i dati da "negozio_1.txt" e "negozio_2.txt" e li inserisce
 * nella lista globale dei negozi. Successivamente, stampa l'intera lista globale.
 *
 * @param topPtrNegozi Un puntatore al puntatore del primo nodo della lista globale dei negozi.
 * @return 1 se l'acquisizione di entrambi i negozi e la stampa sono avvenuti con successo, 0 altrimenti.
 */
int funzionalitaAcquisizione(NodoNegozioPtr * topPtrNegozi) {
    // Tenta di leggere il primo file del negozio
    char nomeNegozio_1[] = "negozio_1.txt";
    if (!letturaFile(nomeNegozio_1, topPtrNegozi)) {
        return 0; // Fallimento nella lettura del primo file
    }
    // Tenta di leggere il secondo file del negozio
    char nomeNegozio_2[] = "negozio_2.txt";
    if (!letturaFile(nomeNegozio_2, topPtrNegozi)) {
        return 0; // Fallimento nella lettura del secondo file
    }
    // Stampa l'intera lista globale dei negozi (con i loro inventari)
    if (!stampaListaGlobaleNegozi(*topPtrNegozi)) {
        return 0; // Fallimento nella stampa
    }
    return 1; // Acquisizione completata con successo
}

/**
 * @brief Implementa la funzionalità di confronto di uguaglianza tra i primi due negozi della lista globale.
 *
 * Verifica la presenza di almeno due negozi validi nella lista globale. Se le condizioni non sono
 * soddisfatte, stampa un messaggio di errore e scrive un fallback nel file "Uguaglianza.txt".
 * Altrimenti, chiama `uguaglianzaNegozi` per effettuare il confronto e gestisce l'esito.
 *
 * @param topPtrNegozi Il puntatore al primo nodo della lista globale dei negozi.
 */
void funzionalitaUguaglianza(NodoNegozioPtr topPtrNegozi) {
    // Controlla se ci sono almeno due negozi validi nella lista globale
    if (topPtrNegozi == NULL || getNodoNegozioNext(topPtrNegozi) == NULL ||
        getNegozioId(topPtrNegozi) == 0 || getNegozioId(getNodoNegozioNext(topPtrNegozi)) == 0) {
        puts("Errore: Non ci sono abbastanza negozi validi nella lista per il confronto di uguaglianza.");
        // Chiama ugualianzaNegozi con parametri potenzialmente NULL per gestire il fallback file
        uguaglianzaNegozi(topPtrNegozi, getNodoNegozioNext(topPtrNegozi));
        return;
    }

    // Esegue il confronto di uguaglianza tra i primi due negozi
    NodoNegozioPtr risultato = uguaglianzaNegozi(topPtrNegozi, getNodoNegozioNext(topPtrNegozi));

    // Gestisce l'esito del confronto
    if (risultato == NULL) {
        puts("Confronto tra negozi completato. L'esito e' stato salvato in Uguaglianza.txt (probabilmente '0*0*0*0*0').");
    } else {
        puts("Confronto tra negozi completato. I record comuni sono stati salvati in Uguaglianza.txt.");
    }
}

/**
 * @brief Implementa la funzionalità di ordinamento tra i primi due negozi della lista globale.
 *
 * Verifica la presenza di almeno due negozi con inventari non vuoti nella lista globale.
 * Se le condizioni non sono soddisfatte, stampa un messaggio di errore e scrive un fallback
 * nel file "Ordine.txt". Altrimenti, chiama `ordinamentoNegozi` per ottenere il negozio
 * risultante e tenta di scriverlo nel file "Ordine.txt".
 *
 * @param topPtrNegozi Il puntatore al primo nodo della lista globale dei negozi.
 */
void funzionalitaOrdine(NodoNegozioPtr topPtrNegozi) {
    NodoNegozioPtr risultato;

    // Controlla se ci sono almeno due negozi validi nella lista globale
    if (topPtrNegozi == NULL || getNodoNegozioNext(topPtrNegozi) == NULL ||
        getNegozioId(topPtrNegozi) == 0 || getNegozioId(getNodoNegozioNext(topPtrNegozi)) == 0) {
        puts("ATTENZIONE: Sono necessari almeno due negozi validi nella lista per l'ordinamento.");

        // Scrive il fallback nel file "Ordine.txt"
        FILE *outFile = fopen("Ordine.txt", "w");
        if (outFile != NULL) {
            fprintf(outFile, "0*0*0*0*0\n");
            fclose(outFile);
        } else {
            perror("Errore nell'apertura del file Ordine.txt per scrivere il fallback");
        }
        return;
    }
    // Controlla se gli inventari dei primi due negozi non sono vuoti
    if (isListaAnimaliVuota(getInventarioNegozio(topPtrNegozi)) ||
        isListaAnimaliVuota(getInventarioNegozio(getNodoNegozioNext(topPtrNegozi)))) {
        puts("ATTENZIONE: Sono necessari almeno due negozi con inventari non vuoti per l'ordinamento.");

        // Scrive il fallback nel file "Ordine.txt"
        FILE *outFile = fopen("Ordine.txt", "w");
        if (outFile != NULL) {
            fprintf(outFile, "0*0*0*0*0\n");
            fclose(outFile);
        } else {
            perror("Errore nell'apertura del file Ordine.txt per scrivere il fallback");
        }
        return;
    }

    // Esegue l'ordinamento tra i primi due negozi
    risultato = ordinamentoNegozi(topPtrNegozi, getNodoNegozioNext(topPtrNegozi));

    // Gestisce l'esito dell'ordinamento
    if (risultato == NULL) {
        puts("Operazione di ordinamento completata. Nessun negozio e' stato determinato come 'risultante' (o operazione annullata).");
        puts("Scrivo il fallback '0*0*0*0*0' nel file Ordine.txt.");

        // Scrive il fallback nel file "Ordine.txt"
        FILE *outFile = fopen("Ordine.txt", "w");
        if (outFile != NULL) {
            fprintf(outFile, "0*0*0*0*0\n");
            fclose(outFile);
        } else {
            perror("Errore nell'apertura del file Ordine.txt per scrivere il fallback");
        }
    } else {
        // Se un negozio è stato determinato come risultato, tenta di scriverlo su file
        if (!scritturaSingoloNegozioFile("Ordine.txt", risultato)) {
            puts("ERRORE: Non e' stato possibile scrivere il negozio risultato sul file Ordine.txt.");
        } else {
            puts("Il negozio risultante e' stato salvato con successo sul file Ordine.txt.");
        }
    }
}

/**
 * @brief Gestisce il menu principale dell'applicazione.
 *
 * Questo è il ciclo principale dell'applicazione che presenta all'utente un menu di opzioni:
 * acquisizione dati, ordinamento negozi, confronto di uguaglianza tra negozi ed uscita.
 * Gestisce l'input utente, valida le scelte e chiama le funzioni appropriate.
 * Si occupa anche di mantenere lo stato dell'acquisizione dati e di liberare la memoria
 * della lista globale dei negozi all'uscita.
 */
void menu() {
    int scelta = 0;
    int flagAcquisizione = 0; // Flag per controllare se i dati sono stati acquisiti (0 = no, 1 = sì)
    int controllo = 0;
    char tempScelta[MAXCHAR];
    NodoNegozioPtr topPtrNegozi = NULL; // Puntatore alla head della lista globale dei negozi

    do {
        // Stampa il menu principale
        printf("\n");
        printf("+-------------------------------------+\n");
        printf("|           MENU PRINCIPALE           |\n");
        printf("+-------------------------------------+\n");
        printf("| 1 - Acquisizione Dati Negozi        |\n");
        printf("| 2 - Ordina Negozi                   |\n");
        printf("| 3 - Confronta Uguaglianza Negozi    |\n");
        printf("| 4 - Esci dal Programma              |\n");
        printf("+-------------------------------------+\n");
        printf("Scegli un'opzione: ");

        // Loop per l'acquisizione e validazione dell'input utente per la scelta del menu
        do {
            inputUtente(tempScelta, MAXCHAR); // Acquisisce l'input come stringa
            if (stringaSoloNumeriODecimali(tempScelta)) { // Controlla se la stringa contiene solo numeri
                scelta = atoi(tempScelta); // Converte la stringa in intero
                if (!(scelta >= 1 && scelta <= 4)) { // Controlla se la scelta è nel range valido
                    controllo = 0;
                    puts("Scelta non valida. Inserisci un numero tra 1 e 4.");
                    printf("La tua scelta: ");
                } else {
                    controllo = 1; // Input valido
                }
            } else {
                controllo = 0;
                puts("Input non valido. Inserisci solo numeri.");
                printf("La tua scelta: ");
            }
        } while (!controllo); // Ripete finché l'input non è valido

        // Esegue l'azione in base alla scelta dell'utente
        switch (scelta) {
            case 1:
                cleanConsole(0); // Pulisce la console prima dell'output della funzionalità
                if (flagAcquisizione == 0) { // Controlla se l'acquisizione è già stata fatta
                    puts("--- Acquisizione Dati ---");
                    flagAcquisizione = funzionalitaAcquisizione(&topPtrNegozi); // Esegue l'acquisizione
                } else {
                    puts("L'acquisizione è già stata effettuata.");
                }
                cleanConsole(1); // Mette in pausa la console dopo l'output
                break;
            case 2:
                cleanConsole(0);
                if (flagAcquisizione == 1) { // L'ordinamento richiede che i dati siano già stati acquisiti
                    puts("--- Ordinamento Negozi ---");
                    funzionalitaOrdine(topPtrNegozi); // Esegue la funzionalità di ordinamento
                } else {
                    puts("Impossibile eseguire l'ordinamento: acquisizione non effettuata.");
                }
                cleanConsole(1);
                break;
            case 3:
                cleanConsole(0);
                if (flagAcquisizione == 1) { // Il confronto richiede che i dati siano già stati acquisiti
                    puts("--- Confronto Uguaglianza Negozi ---");
                    funzionalitaUguaglianza(topPtrNegozi); // Esegue la funzionalità di uguaglianza
                } else {
                    puts("Impossibile eseguire il confronto: acquisizione non effettuata.");
                }
                cleanConsole(1);
                break;
            case 4:
                // Messaggi di chiusura del programma
                puts("\n--- Chiusura Programma ---");
                puts("Grazie per aver utilizzato il programma!");
                puts("Premere INVIO per chiudere...");
                getchar(); // Aspetta un input per chiudere la console
                break;
            default:
                // Questo caso dovrebbe essere già gestito dal loop di validazione, ma è un fallback
                puts("Opzione non riconosciuta. Riprova.");
                break;
        }
    } while (scelta != 4); // Il loop continua finché l'utente non sceglie di uscire

    // Libera tutta la memoria allocata per la lista globale dei negozi prima di terminare
    liberaListaGlobaleNegozi(topPtrNegozi);
}

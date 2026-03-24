/**
 * @file file.c
 * @brief Modulo che gestisce le operazioni di input/output su file,
 * inclusa l'apertura, chiusura, lettura e scrittura di dati relativi a negozi e animali.
 *
 * Questo modulo si interfaccia con il file system per caricare gli inventari dei negozi
 * e degli animali da file di testo e per salvare i dati attuali del sistema su file.
 * Utilizza le funzioni di validazione del modulo `controlli` e gli ADT del modulo `dati`
 * per garantire l'integrità e la coerenza dei dati.
 *
 * @authors Favale Giuseppe, Di Palma Marco, Gobbo Angelo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "file.h"
#include "dati.h"
#include "controlli.h"
#include "utils.h" // Presumibilmente per la funzione ottenereIdNegozioDaNome

/**
 * @brief Puntatore globale al file attualmente aperto.
 *
 * Viene utilizzato dalle funzioni `apriFile`, `chiudiFile`, `letturaFile` e `scritturaSingoloNegozioFile`
 * per gestire l'accesso al file.
 */
FILE* filePtr;

/**
 * @brief Apre un file specificato in una determinata modalità.
 *
 * Imposta il puntatore `filePtr` al file aperto.
 *
 * @param nomeFile Il percorso e il nome del file da aprire.
 * @param mod La modalità di apertura del file (es. "r" per lettura, "w" per scrittura).
 * @return 1 se il file è stato aperto con successo, 0 altrimenti.
 */
int apriFile(char* nomeFile, char* mod) {
    filePtr = fopen(nomeFile, mod);
    return (filePtr != NULL);
}

/**
 * @brief Chiude il file attualmente aperto, puntato da `filePtr`.
 *
 * @return 1 se il file è stato chiuso con successo, 0 altrimenti.
 */
int chiudiFile() {
    return (fclose(filePtr) == 0);
}

/**
 * @brief Estrae i token da una riga di testo che rappresenta un record Animale.
 *
 * La funzione valida prima la riga usando `validaRecordAnimale`. Se la validazione ha successo,
 * effettua il parsing della stringa usando il `SEPARATORE` per estrarre l'ID, la razza,
 * il nome, l'età e il prezzo, convertendoli nei tipi di dato appropriati.
 *
 * @param rigaOriginale La riga di testo contenente i dati dell'animale.
 * @param tempId Puntatore all'unsigned int dove verrà memorizzato l'ID estratto.
 * @param tempRazza Puntatore all'array di char dove verrà memorizzata la razza estratta.
 * @param tempNome Puntatore all'array di char dove verrà memorizzato il nome estratto.
 * @param tempEta Puntatore all'int dove verrà memorizzata l'età estratta.
 * @param tempPrezzo Puntatore al float dove verrà memorizzato il prezzo estratto.
 * @param listaAnimaliDestinazione Puntatore alla lista di animali (utilizzata per la validazione ID duplicato).
 * @return 1 se l'estrazione e la validazione dei token avvengono con successo, 0 altrimenti.
 */
int estrazioneToken(char* rigaOriginale, unsigned int* tempId, char* tempRazza,
                    char* tempNome, int* tempEta, float* tempPrezzo,
                    const Lista* listaAnimaliDestinazione)
{
    // Prima si valida l'intera riga per assicurare che il formato sia corretto e non ci siano duplicati ID
    if (!validaRecordAnimale(rigaOriginale, listaAnimaliDestinazione))
    {
        return 0; // Se la riga non è valida, l'estrazione non può procedere
    }

    // Crea una copia della riga originale perché strtok modifica la stringa in-place
    char rigaCopia[MAXCHAR_BUFFER];
    strncpy(rigaCopia, rigaOriginale, MAXCHAR_BUFFER - 1);
    rigaCopia[MAXCHAR_BUFFER - 1] = '\0'; // Assicura la terminazione della stringa

    char* currentToken;
    char delimitatori[2] = {SEPARATORE, '\0'}; // Delimitatore per strtok (es. '*')

    // Estrazione e conversione dell'ID
    currentToken = strtok(rigaCopia, delimitatori);
    if (currentToken == NULL) return 0; // Errore: token mancante
    *tempId = (unsigned int)strtoul(currentToken, NULL, 10); // Conversione da stringa a unsigned long, base 10

    // Estrazione della Razza
    currentToken = strtok(NULL, delimitatori);
    if (currentToken == NULL) return 0;
    strncpy(tempRazza, currentToken, MAXCHAR1 - 1); // Copia sicura della stringa
    tempRazza[MAXCHAR1 - 1] = '\0';

    // Estrazione del Nome
    currentToken = strtok(NULL, delimitatori);
    if (currentToken == NULL) return 0;
    strncpy(tempNome, currentToken, MAXCHAR1 - 1);
    tempNome[MAXCHAR1 - 1] = '\0';

    // Estrazione e conversione dell'Età
    currentToken = strtok(NULL, delimitatori);
    if (currentToken == NULL) return 0;
    *tempEta = atoi(currentToken); // Conversione da stringa a int

    // Estrazione e conversione del Prezzo
    currentToken = strtok(NULL, delimitatori);
    if (currentToken == NULL) return 0;
    *tempPrezzo = (float)atof(currentToken); // Conversione da stringa a float

    return 1; // Tutti i token estratti e validati con successo
}

/**
 * @brief Legge i dati di un negozio e il suo inventario di animali da un file.
 *
 * La funzione esegue i seguenti passaggi:
 * 1. Valida il formato del nome del file.
 * 2. Tenta di aprire il file in modalità lettura.
 * 3. Crea una lista temporanea per l'inventario degli animali del negozio.
 * 4. Effettua un controllo preliminare sul numero di righe del file.
 * 5. Legge il file riga per riga, estraendo i dati di ogni animale e creando oggetti `Animale`.
 * 6. Inserisce gli animali nella lista temporanea.
 * 7. Estrae l'ID del negozio dal nome del file.
 * 8. Crea un nuovo oggetto `Negozio` e vi associa l'inventario appena letto.
 * 9. Inserisce il nuovo negozio nella lista globale dei negozi (`topPtrNegozi`), gestendo l'ordinamento e i duplicati.
 * 10. Chiude il file.
 * In caso di qualsiasi errore durante il processo, la funzione pulisce la memoria allocata e stampa un messaggio di avviso.
 *
 * @param nomeFile Il nome del file da cui leggere i dati del negozio.
 * @param topPtrNegozi Un puntatore al puntatore del primo nodo della lista globale dei negozi.
 * Questo permette di modificare la head della lista globale.
 * @return 1 se la lettura e l'inserimento del negozio sono avvenuti con successo, 0 altrimenti.
 */
int letturaFile(char* nomeFile, NodoNegozioPtr *topPtrNegozi)
{
    // 1. Validazione del formato del nome del file
    if (!formatoNomeFile(nomeFile))
    {
        puts("ATTENZIONE: Formato del nome file errato, impossibile procedere.");
        return 0;
    }
    // 2. Apertura del file in modalità lettura
    if (!apriFile(nomeFile, "r"))
    {
        puts("ATTENZIONE: Impossibile aprire il file specificato.");
        return 0;
    }

    int rigaCorrente = 1;
    char buffer[MAXCHAR_BUFFER];
    unsigned int tempId;
    char tempRazza[MAXCHAR1];
    char tempNome[MAXCHAR1];
    int tempEta;
    float tempPrezzo;

    // 3. Creazione della lista temporanea per l'inventario del negozio
    Lista* inventarioAnimaliLocale = creaListaAnimali();
    if (inventarioAnimaliLocale == NULL) {
        puts("ATTENZIONE: Impossibile creare l'inventario animali locale.");
        chiudiFile();
        return 0;
    }

    // 4. Controllo preliminare sul numero di righe del file
    if (!controlloRigheFile(filePtr))
    {
        puts("ATTENZIONE: Il file non ha il numero di righe atteso o presenta problemi strutturali.");
        distruggiListaAnimali(inventarioAnimaliLocale); // Pulisce la memoria allocata per l'inventario
        chiudiFile();
        return 0;
    }

    // Riporta il puntatore del file all'inizio dopo il controllo delle righe
    fseek(filePtr, 0, SEEK_SET);

    // 5. e 6. Lettura del file riga per riga ed estrazione/creazione degli animali
    while (fgets(buffer, MAXCHAR_BUFFER, filePtr) != NULL)
    {
        size_t lunghezzaStr = strlen(buffer);
        // Rimuove il carattere newline se presente
        if (lunghezzaStr > 0 && buffer[lunghezzaStr - 1] == '\n') {
            buffer[lunghezzaStr - 1] = '\0';
        }

        // Estrazione e validazione dei token della riga
        if (estrazioneToken(buffer, &tempId, tempRazza, tempNome, &tempEta, &tempPrezzo, inventarioAnimaliLocale))
        {
            // Crea un nuovo oggetto Animale
            Animale* nuovoAnimale = creaAnimale(tempId, tempRazza, tempNome, tempEta, tempPrezzo);
            if (nuovoAnimale == NULL) {
                printf("ATTENZIONE: Errore nell'allocazione dell'animale dalla riga %d del file %s.\n", rigaCorrente, nomeFile);
                distruggiListaAnimali(inventarioAnimaliLocale);
                chiudiFile();
                return 0;
            }

            // 7. Inserimento dell'animale nella lista temporanea
            if (!inserisciAnimaleInLista(inventarioAnimaliLocale, nuovoAnimale))
            {
                distruggiAnimale(nuovoAnimale); // Libera l'animale se non può essere inserito (es. ID duplicato)
                printf("ATTENZIONE: Errore nell'inserimento dell'animale dalla riga %d del file %s (potrebbe essere ID duplicato o errore di allocazione interna).\n", rigaCorrente, nomeFile);
                distruggiListaAnimali(inventarioAnimaliLocale);
                chiudiFile();
                return 0;
            }
        }
        else
        {
            printf("ATTENZIONE: Impossibile acquisire dati dalla riga %d del file %s (formato non valido o ID duplicato nel file).\n", rigaCorrente, nomeFile);
            distruggiListaAnimali(inventarioAnimaliLocale);
            chiudiFile();
            return 0;
        }
        rigaCorrente++;
    }

    // 8. Estrazione dell'ID del negozio dal nome del file (presumendo che ottenereIdNegozioDaNome sia definita in utils.h)
    unsigned int tempIdNegozio = ottenereIdNegozioDaNome(nomeFile);
    if (tempIdNegozio == 0) // Un ID 0 potrebbe indicare un errore o un ID non valido
    {
        puts("ATTENZIONE: Impossibile acquisire l'ID del negozio dal nome del file.");
        distruggiListaAnimali(inventarioAnimaliLocale);
        chiudiFile();
        return 0;
    }

    // 9. Creazione del nuovo oggetto Negozio e associazione dell'inventario
    NodoNegozioPtr nuovoNegozio = creaNegozio(tempIdNegozio);
    if (nuovoNegozio == NULL) {
        puts("ATTENZIONE: Impossibile creare il nuovo negozio.");
        distruggiListaAnimali(inventarioAnimaliLocale);
        chiudiFile();
        return 0;
    }

    // Imposta l'inventario del negozio
    setInventarioNegozio(nuovoNegozio, inventarioAnimaliLocale);

    // 10. Inserimento del nuovo negozio nella lista globale
    if (!inserisciNegozioInListaGlobale(topPtrNegozi, nuovoNegozio))
    {
        puts("ATTENZIONE: Impossibile inserire il nuovo negozio nella lista globale (potrebbe essere ID duplicato).");
        // Se l'inserimento fallisce, distruggere il negozio e il suo inventario
        distruggiNegozio(nuovoNegozio);
        chiudiFile();
        return 0;
    }

    // 11. Chiusura del file
    if (!chiudiFile())
    {
        puts("ATTENZIONE: Il file non è stato chiuso correttamente.");
        // Non si considera un errore fatale per il successo della lettura, ma si avvisa
    }

    return 1; // Lettura e inserimento del negozio completati con successo
}

/**
 * @brief Scrive i dati di un singolo negozio, incluso il suo inventario, su un file.
 *
 * La funzione esegue i seguenti passaggi:
 * 1. Valida il puntatore al negozio.
 * 2. Tenta di aprire il file specificato in modalità scrittura ("w"), sovrascrivendo il contenuto esistente.
 * 3. Scrive l'ID del negozio e un'intestazione per l'inventario.
 * 4. Utilizza la funzione `scriviInventarioAnimaliSuFile` per scrivere tutti gli animali.
 * 5. Chiude il file.
 * In caso di qualsiasi errore, la funzione stampa un messaggio di avviso e restituisce 0.
 *
 * @param nomeFile Il nome del file su cui scrivere.
 * @param negozioPtr Il puntatore costante al `NodoNegozioPtr` del negozio da scrivere.
 * @return 1 se la scrittura su file è avvenuta con successo, 0 altrimenti.
 */
int scritturaSingoloNegozioFile(char * nomeFile, const NodoNegozioPtr negozioPtr) {
    // 1. Validazione del puntatore al negozio
    if (negozioPtr == NULL) {
        puts("ATTENZIONE: Negozio da scrivere non valido (NULL).");
        return 0;
    }

    // 2. Apertura del file in modalità scrittura
    if (!apriFile(nomeFile, "w")) {
        puts("ATTENZIONE: Impossibile aprire il file per la scrittura del negozio.");
        return 0;
    }

    // 3. Scrittura dell'ID del negozio e intestazione
    int charScritti = fprintf(filePtr, "ID_Negozio:%u\n", getNegozioId(negozioPtr));
    if (charScritti < 0) {
        puts("ATTENZIONE: Impossibile scrivere l'ID del negozio su file.");
        chiudiFile();
        return 0;
    }

    fprintf(filePtr, "---INVENTARIO_ANIMALI---\n"); // Separatore per chiarezza nel file

    // Ottiene l'inventario animali del negozio
    Lista* inventario = getInventarioNegozio(negozioPtr);

    // 4. Scrittura dell'inventario animali usando la funzione dati.h
    if (!scriviInventarioAnimaliSuFile(inventario, filePtr)) {
        puts("ATTENZIONE: Errore durante la scrittura dell'inventario animali su file.");
        chiudiFile();
        return 0;
    }

    // 5. Chiusura del file
    if (!chiudiFile()) {
        puts("ATTENZIONE: File non chiuso correttamente.");
        return 0;
    }

    return 1; // Scrittura completata con successo
}

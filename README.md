# Pet Shop Management System

Un software gestionale robusto sviluppato in **C** per l'esame di Laboratorio di Informatica presso l'Università degli Studi di Bari "Aldo Moro".

## 🛠️ Caratteristiche Tecniche
- **Gestione Dati:** Implementazione di liste collegate (linked lists) per una gestione dinamica della memoria.
- **Persistenza:** Lettura e scrittura dei dati del magazzino e degli ordini su file di testo (.txt).
- **Validazione:** Modulo dedicato (`controlli.c`) per la robustezza degli input utente.
- **Documentazione:** Documentazione tecnica completa del codice generata con **Doxygen**.

## 📁 Struttura del Progetto
- `main.c`: Punto di ingresso del programma.
- `dati.c/h`: Definizione delle strutture dati e dei tipi.
- `funzioni.c/h`: Logica di business e manipolazione delle liste.
- `file.c/h`: Gestione delle operazioni di I/O.
- `utils.c/h`: Funzioni di utilità generale.

## 🚀 Come Eseguire
1. Compila il progetto usando un compilatore C (es. GCC):
   ```bash
   gcc *.c -o petshop

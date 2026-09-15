# FRED: Arduino Section

Firmware Arduino per l'analisi in tempo reale della potenza spettrale EEG per banda (delta, theta, alpha, beta, gamma) e la stima dello stato di **focus/non-focus**, con visualizzazione su display LCD 16x2.

## Come funziona

1. Un **Timer1** in modalità CTC campiona il segnale a **256 Hz** tramite interrupt, riempiendo una finestra di **256 campioni**.
2. Al completamento della finestra, viene calcolata la potenza di ciascuna banda con l'**algoritmo di Goertzel** (più efficiente di una FFT completa quando servono solo poche bande di frequenza):
   - Delta: 0.5–4 Hz
   - Theta: 4–8 Hz
   - Alpha: 8–14 Hz
   - Beta: 14–30 Hz
   - Gamma: 30–80 Hz
3. Viene identificata la **banda dominante** (potenza massima).
4. Lo stato di **focus** viene assegnato quando la banda dominante è la Beta.
5. Risultati stampati su **Serial (115200 baud)** e mostrati su **display LCD 16x2**.

## Modalità simulazione

Il firmware include una `simulationMode` (attiva di default) che genera un'onda sinusoidale a frequenza scelta (default 20 Hz → banda Beta) con rumore casuale sovrapposto, utile per validare la pipeline di analisi senza un segnale EEG reale. Per passare all'acquisizione reale:

```cpp
const bool simulationMode = false; // legge da A0
```

## Hardware

- Arduino Uno R3
- Display LCD 16x2 (HD44780-compatibile), collegato in **modalità 4-bit**

| Segnale LCD | Pin Arduino |
|---|---|
| RS  | D12 |
| E   | D11 |
| DB4 | D5  |
| DB5 | D4  |
| DB6 | D3  |
| DB7 | D2  |
| R/W | GND (fisso, solo scrittura) |

Ingresso EEG (modalità reale): **A0**

## File

- `FREDARDUINOSCRIPT.ino` — sketch principale (acquisizione, analisi spettrale, LCD)
- `wdt_init.cpp` — disabilita il Watchdog Timer all'avvio prima che venga eseguito `setup()`. Serve a evitare il classico loop di reset infinito su Arduino Uno (bootloader senza gestione del WDT) quando il watchdog viene lasciato attivo da un reset precedente

## Utilizzo

1. Apri `FREDARDUINOSCRIPT.ino` in Arduino IDE (assicurati che `wdt_init.cpp` sia nella stessa cartella dello sketch)
2. Seleziona board **Arduino Uno** e la porta seriale corretta
3. Carica lo sketch
4. Apri il Serial Monitor a **115200 baud** per il log dettagliato delle potenze di banda

## Stato del progetto

Modulo firmware in sviluppo nell'ambito del progetto FRED (tesi di tirocinio, Politecnico di Torino). Interfaccia LCD e mappatura pin verificate su schema KiCad.

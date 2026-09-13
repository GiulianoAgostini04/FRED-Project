# FRED — Focus-Related Encephalographic Device

Sistema di acquisizione e classificazione EEG per il monitoraggio in tempo reale dello stato di concentrazione, basato sull'analisi della potenza in banda alpha/beta del segnale frontale.

Progetto a carattere didattico/dimostrativo, sviluppato nell'ambito di un corso di ingegneria elettronica.

---

## Descrizione del progetto

FRED acquisisce il segnale EEG dal lobo frontale tramite elettrodi, lo condiziona attraverso una catena analogica dedicata (PCB custom), e ne classifica lo stato di concentrazione confrontando la potenza nelle bande alpha e beta. Il risultato viene mostrato in tempo reale su display LCD e tramite indicatori LED.

Il progetto è affiancato da un modulo VHDL che modella digitalmente la logica di selezione canale e la macchina a stati per la classificazione, con finalità principalmente didattiche (non necessariamente sintetizzato su FPGA fisica).

---

## Architettura del sistema

Il sistema è organizzato su quattro livelli:

- **PCB (FRED)** — scheda di acquisizione EEG custom: front-end analogico completo (elettrodi → protezione → multiplexer canali → strumentazione → filtraggio → isolamento galvanico → buffer d'uscita) e blocco digitale di selezione canale.
- **Livello PC** — OpenBCI Ganglion + BrainFlow estraggono la potenza in banda alpha/beta via FFT e inviano i dati via seriale ad Arduino.
- **Livello Arduino** — riceve i dati elaborati, pilota il display LCD 16x2 (frequenza EEG, banda, stato "Concentrato"/"Non concentrato") e i LED in base al rapporto alpha/beta. Alimentazione via USB.
- **Livello VHDL** — digital twin della logica di selezione canale e della FSM di decisione/isteresi, a scopo educativo.

---

## Stato del progetto

### PCB (KiCad) — in fase avanzata
- Stack-up a 4 layer (Sig_Top, GND_split, PWR_split, Sig_Bottom), componenti THT/DIP per assemblaggio manuale
- Routing completato: percorso analogico, blocco digitale, distribuzione di potenza, connettori LCD/Arduino
- Classi di potenza configurate (0.6 mm per le piste di alimentazione, 0.25 mm per il segnale)
- **Problema DRC aperto:** oggetto grafico "Rectangle" su Sig_Top erroneamente assegnato alla rete GND, sovrapposto a Edge.Cuts → violazione di clearance da risolvere manualmente
- Fori di montaggio assenti — da valutare
- Manca il condensatore di disaccoppiamento sul pin 8 dell'NE555 (U8) — da aggiungere in schematico

### VHDL — due moduli completati e verificati
- `channel_selector.vhd`: blocco digitale di selezione canale, verificato in GTKWave
- `focus_comparator.vhd`: FSM a doppia soglia con isteresi, verificata in GTKWave
- In sviluppo: `alpha_beta_comparator`, il modulo educativo principale

---

## Struttura della repository

```
FRED/
├── KiCad/
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_pro   # file di progetto
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_sch   # schematico radice
│   ├── FRED_Electrical_Scheme_KiCAD_2.kicad_sch # foglio gerarchico
│   ├── FRED_Electrical_Scheme_KiCAD_3.kicad_sch # foglio gerarchico
│   ├── FRED_Electrical_Scheme_KiCAD_4.kicad_sch # foglio gerarchico
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_pcb   # layout PCB
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_prl   # impostazioni locali del progetto
│   ├── FRED_Electrical_Scheme_KiCAD.step        # modello 3D della scheda
│   └── PDF/                                      # stampe schematico/PCB esportate da KiCad
├── VHDL/
│   ├── src/                                      # sorgenti VHDL
│   └── sim/                                       # output di simulazione (testbench, waveform)
├── Arduino/                                       # firmware di acquisizione, elaborazione e pilotaggio LCD
└── Report/                                         # relazione tecnica del progetto
```

> Nota: file di export intermedi (`.cad`, `.cmp`, `.dsn`, `.emn`, `.emp`, `.hyp`, `.wrl`) e i report di verifica (`DRC.rpt`, `ERC.rpt`, `report.txt`) generati automaticamente da KiCad non sono versionati, in quanto derivabili in qualsiasi momento dai file di progetto.

---

## Catena analogica (sintesi)

Elettrodi → protezione con clamp a diodi → multiplexer CD4052B → amplificatore da strumentazione INA128 → filtro passa-alto Sallen-Key (fc = 1 Hz) → stadio di amplificazione (A = 10) → notch Twin-T a 50 Hz → isolamento galvanico (modulazione PWM via NE555 + optoisolatore 4N35 + demodulazione) → filtro passa-banda anti-aliasing → buffer d'uscita → ADC Arduino.

Stadio DRL (Driven Right Leg) in parallelo ai connettori degli elettrodi per la reiezione di modo comune.

---

## Strumenti utilizzati

| Strumento | Utilizzo |
|---|---|
| KiCad 10.0 | Schematico e layout PCB |
| TinkerCAD | Prototipazione e validazione della catena analogica |
| VS Code + TerosHDL | Sviluppo VHDL |
| GHDL 6.0.0 | Simulazione VHDL |
| GTKWave 3.3.100 | Visualizzazione delle waveform |
| OpenBCI Ganglion + BrainFlow | Acquisizione EEG ed estrazione della potenza in banda |
| Arduino UNO R3 | Elaborazione, pilotaggio LCD e LED |

---

## Come aprire il progetto

1. Clonare la repository
2. Aprire `KiCad/FRED_Electrical_Scheme_KiCAD.kicad_pro` con KiCad 10.0 o successivo
3. Per la simulazione VHDL: `ghdl -a` → `ghdl -e` → `ghdl -r --wave=output.ghw` → `gtkwave output.ghw`

---

## Prossimi sviluppi

- [ ] Correzione del problema DRC sul rettangolo in rete GND
- [ ] Aggiunta del condensatore di disaccoppiamento mancante sull'NE555
- [ ] Completamento del modulo VHDL `alpha_beta_comparator`
- [ ] Sviluppo del firmware Arduino (pipeline di elaborazione, integrazione BrainFlow, pilotaggio LCD)
- [ ] Stesura della relazione tecnica

---

## Autore

Giuliano Agostini — Ingegneria Elettronica

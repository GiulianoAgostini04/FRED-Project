# FRED: Focus-Related Encephalographic Device

Real-time EEG acquisition and classification system for monitoring concentration state, based on alpha/beta band power analysis of frontal-lobe signals.

Didactic/demonstrative project, developed as part of an electronic engineering course.

---

## Project overview

FRED acquires the EEG signal from the frontal lobe via electrodes, conditions it through a dedicated analog chain (custom PCB), and classifies the concentration state by comparing alpha and beta band power. The result is displayed in real time on an LCD and through LED indicators.

The project also includes a VHDL module that digitally models the channel-selection logic and the classification finite-state machine, mainly for educational purposes. It is not necessarily meant to be synthesized on a physical FPGA.

---

## System architecture

The system is organized into four layers:

- **PCB (FRED).** Custom EEG acquisition board. Includes the full analog front-end (electrodes, protection, channel multiplexer, instrumentation amplifier, filtering, galvanic isolation, output buffer) and the digital channel-selection block.
- **PC layer.** OpenBCI Ganglion and BrainFlow extract alpha/beta band power via FFT and send the data serially to Arduino.
- **Arduino layer.** Receives the processed data, drives the 16x2 LCD display (EEG frequency, band, "Focused"/"Not focused" state) and the LEDs based on the alpha/beta ratio. Powered via USB.
- **VHDL layer.** Digital twin of the channel-selection logic and the decision/hysteresis FSM, for educational purposes.

---

## Project status

### PCB (KiCad), nearing completion
- 4-layer stackup (Sig_Top, GND_split, PWR_split, Sig_Bottom), THT/DIP components for hand-soldering
- Routing completed: analog signal path, digital block, power distribution, LCD/Arduino connectors
- Power classes configured (0.6 mm for power traces, 0.25 mm for signal traces)
- **Open DRC issue:** a "Rectangle" graphic object on Sig_Top was accidentally assigned to the GND net and overlaps Edge.Cuts, causing a clearance violation that needs a manual fix
- Mounting holes missing, still to be evaluated
- Missing decoupling capacitor on NE555 (U8) pin 8, to be added in the schematic

### VHDL, two modules completed and verified
- `channel_selector.vhd`: digital channel-selection block, verified in GTKWave
- `focus_comparator.vhd`: dual-threshold hysteresis FSM, verified in GTKWave
- In progress: `alpha_beta_comparator`, the core educational module

---

## Repository structure

```
FRED/
├── KiCad/
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_pro   # project file
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_sch   # root schematic
│   ├── FRED_Electrical_Scheme_KiCAD_2.kicad_sch # hierarchical sheet
│   ├── FRED_Electrical_Scheme_KiCAD_3.kicad_sch # hierarchical sheet
│   ├── FRED_Electrical_Scheme_KiCAD_4.kicad_sch # hierarchical sheet
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_pcb   # PCB layout
│   ├── FRED_Electrical_Scheme_KiCAD.kicad_prl   # local project settings
│   ├── FRED_Electrical_Scheme_KiCAD.step        # 3D board model
│   └── PDF/                                      # schematic/PCB prints exported from KiCad
├── VHDL/
│   ├── src/                                      # VHDL sources
│   └── sim/                                       # simulation outputs (testbenches, waveforms)
├── Arduino/                                       # acquisition, processing, and LCD-driving firmware
└── Report/                                         # technical project report
```

Note: intermediate export files (`.cad`, `.cmp`, `.dsn`, `.emn`, `.emp`, `.hyp`, `.wrl`) and auto-generated check reports (`DRC.rpt`, `ERC.rpt`, `report.txt`) are not versioned, since they can be regenerated at any time from the project files.

---

## Analog chain (summary)

Electrodes, then diode clamp protection, then the CD4052B multiplexer, then the INA128 instrumentation amplifier, then a Sallen-Key high-pass filter (fc = 1 Hz), then an amplification stage (A = 10), then a 50 Hz Twin-T notch filter, then galvanic isolation (NE555 PWM modulation with a 4N35 optocoupler and demodulation), then an anti-aliasing band-pass filter, then an output buffer, and finally the Arduino ADC.

A DRL (Driven Right Leg) stage runs in parallel with the electrode connectors for common-mode rejection.

---

## Tools used

| Tool | Purpose |
|---|---|
| KiCad 10.0 | Schematic and PCB layout |
| TinkerCAD | Analog chain prototyping and validation |
| VS Code + TerosHDL | VHDL development |
| GHDL 6.0.0 | VHDL simulation |
| GTKWave 3.3.100 | Waveform visualization |
| OpenBCI Ganglion + BrainFlow | EEG acquisition and band-power extraction |
| Arduino UNO R3 | Processing, LCD and LED driving |

---

## How to open the project

1. Clone the repository.
2. Open `KiCad/FRED_Electrical_Scheme_KiCAD.kicad_pro` with KiCad 10.0 or later.
3. For VHDL simulation, run `ghdl -a`, then `ghdl -e`, then `ghdl -r --wave=output.ghw`, then `gtkwave output.ghw`.

---

## Next steps

- [ ] Fix the DRC issue on the GND-net rectangle
- [ ] Add the missing NE555 decoupling capacitor
- [ ] Complete the `alpha_beta_comparator` VHDL module
- [ ] Develop the Arduino firmware (processing pipeline, BrainFlow integration, LCD driving)
- [ ] Write the technical report

---

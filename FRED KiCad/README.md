# FRED: KiCad Section

This repository contains the KiCad design files for FRED (Focus-Related Encephalographic Device), a custom EEG acquisition board developed for an electronic engineering course project.

The board handles the full analog front-end for EEG signal acquisition (electrode input, protection, channel multiplexing, instrumentation amplification, filtering, galvanic isolation, output buffering) and a digital channel-selection block, and sends the processed signal to an Arduino for further analysis and display.

## Board overview

The design includes:

- Electrode input stage with protection and a DRL (Driven Right Leg) reference stage for common-mode rejection
- CD4052B dual multiplexer for electrode channel selection
- INA128 instrumentation amplifier
- Sallen-Key high-pass filter (fc = 1 Hz)
- Fixed-gain amplification stage (A = 10)
- 50 Hz Twin-T notch filter
- Galvanic isolation stage based on NE555 PWM modulation, a 4N35 optocoupler, and Sallen-Key demodulation
- Anti-aliasing band-pass filter and output buffer toward the Arduino ADC
- Digital block for channel selection (slide switches, 74HC74 flip-flop, 74HC04/74HC08 logic, status LEDs)

Note: intermediate export files (`.cad`, `.cmp`, `.dsn`, `.emn`, `.emp`, `.hyp`, `.wrl`) and auto-generated check reports (`DRC.rpt`, `ERC.rpt`, `report.txt`) are not versioned, since they can be regenerated at any time from the project files.

## Tools used

| Tool | Purpose |
|---|---|
| KiCad 10.0 | Schematic and PCB layout |

## How to open the project

1. Clone the repository.
2. Open `FRED_Electrical_Scheme_KiCAD.kicad_pro` with KiCad 10.0 or later.
3. Schematic and PCB print PDFs are available in the `PDF/` folder for a quick look without opening KiCad.

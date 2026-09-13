# FRED, TinkerCAD Prototype

This repository contains the TinkerCAD prototype used to validate the FRED (Focus-Related Encephalographic Device) analog EEG acquisition chain before moving to the custom PCB design.

The circuit reproduces the full analog front-end on breadboards, together with the digital channel-selection block, and connects to an Arduino Uno driving an LCD 16x2 display.

---

## Circuit overview

The prototype implements, stage by stage:

- Three 741 op-amps configured as the instrumentation amplifier (INA)
- A Sallen-Key high-pass filter stage (HPF)
- A fixed-gain amplification stage (Amplif1)
- A Twin-T notch filter at 50 Hz
- A galvanic isolation stage based on a 555 timer (PWM modulation), an optocoupler, and a low-pass demodulation filter (LPF)
- An anti-aliasing band-pass filter (BPF)
- A final output amplification stage before the Arduino input
- A digital channel-selection block built from a dual D flip-flop, an inverter array, and a quad AND gate, with status LEDs
- An Arduino Uno R3 reading the processed signal and driving an LCD 16x2 display

---

## Repository structure

```
TinkerCAD/
├── FRED_Circuit_Prototype.pdf              # schematic export, 4 sheets (INA/HPF/Amplif, digital block, isolation/BPF, output stage + Arduino/LCD)
├── FRED_Circuit_Prototype.png              # breadboard wiring view
└── FRED_Circuit_Prototype_Components.csv   # full bill of materials with reference designators
```

---

## Bill of materials (summary)

| Component | Qty | Notes |
|---|---|---|
| 741 op-amp | 10 | INA (x3), HPF, Amplif1, Notch Twin-T, LPF, BPF, Exit Amplif, U1 |
| Breadboard | 3 | Full-size |
| Breadboard mini | 9 | |
| 555 timer | 1 | Isolation stage PWM modulator |
| Optocoupler | 1 | Isolation stage |
| Quad AND gate | 1 | Channel-selection LED decoding |
| Dual D flip-flop | 1 | Channel-selection logic |
| Hex inverter | 1 | Channel-selection logic |
| Slide switch | 2 | Channel selection input |
| Pushbutton | 1 | Clock for the flip-flop |
| Red LED | 4 | Channel status indicators |
| Arduino Uno R3 | 1 | Signal processing and LCD driving |
| LCD 16x2 | 1 | Display output |
| Resistors, various values | 30+ | See CSV for full list with reference designators |
| Capacitors, various values | 11 | See CSV for full list with reference designators |

The complete list with reference designators and exact values is in `FRED_Circuit_Prototype_Components.csv`.

---

## Notes

- This prototype was used to validate the analog signal path before finalizing the PCB schematic, in particular for the Twin-T notch stage and the isolation amplifier, which TinkerCAD's simulator does not always model accurately.
- Component values here reflect an earlier iteration of the design and may not match the final PCB values one to one.

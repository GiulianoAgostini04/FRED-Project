# FRED: TinkerCAD Section

The circuit reproduces the full analog front-end on breadboards, together with the digital channel-selection block, and connects to an Arduino Uno driving an LCD 16x2 display.

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
Tinkercad link: https://www.tinkercad.com/things/7vpgewQdkgf-fred-project-tinkercad-prototype?sharecode=xSgztrpAMZcsTz5ceLgSdRwczz_olruaQzaf4oagjvc

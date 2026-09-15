# FRED — Focus-Related Electroencephalographic Device

Arduino firmware for real-time EEG band-power analysis (delta, theta, alpha, beta, gamma) and focus/not-focus state estimation, with output on a 16x2 LCD.

## How it works

1. A **Timer1** in CTC mode samples the signal at **256 Hz** via interrupt, filling a window of **256 samples**.
2. Once the window is full, the power of each band is computed with the **Goertzel algorithm** (more efficient than a full FFT when only a few frequency bands are needed):
   - Delta: 0.5–4 Hz
   - Theta: 4–8 Hz
   - Alpha: 8–14 Hz
   - Beta: 14–30 Hz
   - Gamma: 30–80 Hz
3. The **dominant band** (highest power) is identified.
4. **Focus** state is assigned when the dominant band is Beta.
5. Results are printed over **Serial (115200 baud)** and shown on the **16x2 LCD**.

## Simulation mode

The firmware includes a `simulationMode` (enabled by default) that generates a sine wave at a chosen frequency (default 20 Hz → Beta band) with random noise on top, useful for validating the analysis pipeline without a real EEG signal. To switch to real acquisition:

```cpp
const bool simulationMode = false; // reads from A0
```

## Hardware

- Arduino Uno R3
- 16x2 LCD (HD44780-compatible), wired in **4-bit mode**

| LCD signal | Arduino pin |
|---|---|
| RS  | D12 |
| E   | D11 |
| DB4 | D5  |
| DB5 | D4  |
| DB6 | D3  |
| DB7 | D2  |
| R/W | GND (fixed, write-only) |

EEG input (real mode): **A0**

## Files

- `FREDARDUINOSCRIPT.ino` — main sketch (acquisition, spectral analysis, LCD)
- `wdt_init.cpp` — disables the Watchdog Timer at boot before `setup()` runs. Prevents the classic infinite reset loop on Arduino Uno (bootloader without WDT handling) when the watchdog is left enabled by a previous reset

## Usage

1. Open `FREDARDUINOSCRIPT.ino` in the Arduino IDE (make sure `wdt_init.cpp` is in the same sketch folder)
2. Select **Arduino Uno** as the board and the correct serial port
3. Upload the sketch
4. Open the Serial Monitor at **115200 baud** for the detailed band-power log

## Project status

Firmware module developed as part of the FRED project (internship thesis, Politecnico di Torino). LCD interface and pin mapping verified against the KiCad schematic.

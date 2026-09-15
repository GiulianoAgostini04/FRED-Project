# FRED: Arduino Section

Arduino firmware for EEG band-power analysis and focus/not-focus state estimation, with output on a 16x2 LCD.

## How it works

1. A **Timer1** in CTC mode samples the signal at **256 Hz** via interrupt, filling a window of **256 samples**.
2. Once the window is full, the power of each band is computed with the **Goertzel algorithm**
3. The **dominant band** (highest power) is identified.
4. **Focus** state is assigned when the dominant band is Beta.
5. Results are printed over **Serial (115200 baud)** and shown on the **16x2 LCD**.

## Files

- `FREDARDUINOSCRIPT.ino` — main sketch 
- `wdt_init.cpp` — disables the Watchdog Timer at boot before `setup()` runs. Prevents the classic infinite reset loop on Arduino Uno when the watchdog is left enabled by a previous reset

## Usage

1. Open `FREDARDUINOSCRIPT.ino` in the Arduino IDE (make sure `wdt_init.cpp` is in the same sketch folder)
2. Select **Arduino Uno** as the board and the correct serial port
3. Upload the sketch
4. Open the Serial Monitor at **115200 baud** for the detailed band-power log

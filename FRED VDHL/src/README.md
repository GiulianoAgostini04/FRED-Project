# FRED. VHDL Modules

This repository contains the VHDL modules developed as a digital twin of part of the FRED (Focus-Related Encephalographic Device) logic: the channel-selection block and the focus/not-focus classification finite-state machine, together with their testbenches.

These modules are developed for educational purposes, to model in VHDL the same logic implemented in hardware on the PCB and, at a higher level, the classification performed on the acquired EEG bands. They are not necessarily meant to be synthesized on a physical FPGA.

---

## Modules

### `channel_selector`
Models the digital channel-selection block. On the rising edge of `btn`, the 2-bit input `sw` is latched into the output `q`, which selects one of four channels. The four outputs in `led` are a one-hot decoding of `q`, used to drive the status LEDs.

| Port | Direction | Type | Description |
|---|---|---|---|
| `sw` | in | `std_logic_vector(1 downto 0)` | Channel selection switches |
| `btn` | in | `std_logic` | Latches `sw` into the output on its rising edge |
| `q` | out | `std_logic_vector(1 downto 0)` | Selected channel |
| `led` | out | `std_logic_vector(3 downto 0)` | One-hot LED indicator for the selected channel |

### `focus_comparator`
Models the classification logic between a "focus" and a "not focus" state, based on two 8-bit inputs, with dual-threshold hysteresis to avoid state chattering around the decision boundary.

| Port | Direction | Type | Description |
|---|---|---|---|
| `clk` | in | `std_logic` | Clock |
| `rstas` | in | `std_logic` | Asynchronous active-low reset |
| `focus_in` | in | `std_logic_vector(7 downto 0)` | Focus-related band power |
| `notFocus_in` | in | `std_logic_vector(7 downto 0)` | Not-focus-related band power |
| `data_valid` | in | `std_logic` | Qualifies when the inputs are valid and the state may update |
| `ledFocus` | out | `std_logic` | High when the FSM is in the focus state |
| `ledNotFocus` | out | `std_logic` | High when the FSM is in the not-focus state |

The FSM computes `diff = focus_in - notFocus_in` and switches from not-focus to focus when `diff` exceeds `threshold_focus` (15), and back from focus to not-focus when `diff` drops below `threshold_not_focus` (5). Between the two thresholds the state is held, which is the hysteresis dead zone.

---

## Status

Both modules are complete and verified in GTKWave against their testbenches.

- `channel_selector`: verified across all four switch combinations, latch-on-button behavior confirmed
- `focus_comparator`: verified including reset behavior, transition above the focus threshold, transition below the not-focus threshold, and correct state holding inside the dead zone

Next step: development of `alpha_beta_comparator`, the core module that will classify the concentration state directly from the alpha/beta band power values.

---

## Repository structure

```
VHDL/
├── src/
│   ├── channel_selector.vhd
│   └── focus_comparator.vhd
└── sim/
    ├── channel_selector_tb.vhd
    └── focus_comparator_tb.vhd
```

---

## Tools used

| Tool | Purpose |
|---|---|
| VS Code + TerosHDL | VHDL editing |
| GHDL 6.0.0 | Compilation and simulation |
| GTKWave 3.3.100 | Waveform visualization |

---

## How to simulate

From the folder containing the source and testbench file:

```bash
ghdl -a channel_selector.vhd channel_selector_tb.vhd
ghdl -e channel_selector_tb
ghdl -r channel_selector_tb --wave=channel_selector.ghw
gtkwave channel_selector.ghw
```

```bash
ghdl -a focus_comparator.vhd focus_comparator_tb.vhd
ghdl -e focus_comparator_tb
ghdl -r focus_comparator_tb --wave=focus_comparator.ghw --stop-time=250ns
gtkwave focus_comparator.ghw
```

Note: `focus_comparator_tb` uses a free-running clock (`clk_tb <= not clk_tb after 10 ns`), so the `--stop-time` flag is required to terminate the simulation.


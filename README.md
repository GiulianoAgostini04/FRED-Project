# FRED-Project
Real-time concentration monitoring system based on frontal-lobe EEG signals. Features a custom PCB designed with TinkerCAD and KiCad, OpenBCI Ganglion and Arduino UNO for signal acquisition, display, and frequency-band analysis for classification. Includes circuit schematics, hardware prototyping, and a VHDL model of the decision logic.
### Title:
Design and Realisation Description of a Specialised PCB for the Study of Frontal EEG Signals Related to Mental Focus State

### Subtitle:
FRED: Focus-Related Encephalographic Device  

### Context:
Personal project developed independently

### Description:
This project involved the design of a PCB dedicated to sampling and processing EEG signals from the frontal lobe. The goal of the PCB is to monitor the user's mental state of focus, which is where the project takes its name, FRED (Focus-Related Encephalographic Device). The combination of internal components and supplemental external hardware makes it possible to correlate the system's output with the user's current focus state. Development started with a prototype built entirely on Tinkercad, which allowed to study the behaviour of each individual component and identify which ones to select for the final design. Four main stages were defined for the system: a digital stage managing the different EEG channel inputs, an analog stage handling raw signal pre-processing, a microcontroller stage built around an Arduino UNO R3 processing the output EEG signal, and an LCD stage displaying the results of the processing phase to the user. Once validated, the project moved to KiCad to produce a more stable and verified version of the prototype. The electrical schematic was organised into four sheets: digital components and input channels, analog components and pre-processing, Arduino and LCD interfacing, and the power supply scheme. This was followed by the PCB layout phase, component placement, board dimensioning, copper trace routing, and a 4-layer stack-up. The design was finally verified through ERC and DRC checks to ensure reliability. Completing the hardware side led into the software phase: describing input-channel management and LCD output control in VHDL, alongside developing the Arduino firmware to run the focus-detection algorithm.

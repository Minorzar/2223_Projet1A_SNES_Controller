# snes_project_ensea2025_software

The purpose of this document is to explain the software operation of the controller and the reasons behind our choices.

This folder contains the code written in C that will be executed on the microprocessor of the controller and the plug.

----- Constants -----
Frequency: 60 Hz / 16.67 ms
Latch duration: 12 us
Pin 1: +5 V
Pin 2: Data clock
Pin 3: Data latch
Pin 4: Serial data
Pin 5: N/A
Pin 6: N/A
Pin 7: Ground

----- Cycle -----
Clock    SNES    NES
1    B    A
2    Y    B
3    Select    Select
4    Start    Start
5    Up    Up
6    Down    Down
7    Left    Left
8    Right    Right
9    A    Low
10    X    Low
11    L    Low
12    R    Low
13    High    Low
14    High    Low
15    High    Low
16    High    Low
17    Low    Low

----- Algorithm -----
Every 16.67 ms, sends a 12 us wide pulse to pin 3.
Wait 6 us
For 16 clock cycles
    Rising edge: Serially shifts the latched button states out of pin 4
    Falling edge: Samples the data with the CPU

If the data bits from 13 to 16 are high
    SNES controller
Else if the data bits from 13 to 16 are low
    NES Controller
Else
    N/A

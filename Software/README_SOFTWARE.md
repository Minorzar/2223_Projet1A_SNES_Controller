# SNES Controller (Software)

The purpose of this document is to explain the algorithms and programming elements we've written for the two microprocessors in our project: one for the controller, the other for the plug.

## SNES Communication Protocol

The SNES console communicates with the controller and retrieves data in a specific way. That's why we have to adapt to it and ensure that our microprocessors reproduce these steps correctly.

SNES port features:
- Frequency: 60 Hz / 16.67 ms
- Clock period: 12 μs
- Pin 1: +5 V
- Pin 2: Data_clock
- Pin 3: Data_latch
- Pin 4: Serial_data
- Pin 5: N/A
- Pin 6: N/A
- Pin 7: Ground

Communication sequence:   
- [1] B
- [2] Y
- [3] Select
- [4] Start
- [5] Up
- [6] Down
- [7] Left
- [8] Right
- [9] A
- [10] X
- [11] L
- [12] R
- [13] High
- [14] High
- [15] High
- [16] High
- (17 Low)

Operation:
- Every 16.67 ms, the console sends a 12 μs wide pulse to pin 3, instructing the controller to latch the state of the buttons.
- After 6 μs, the console sends 16 clock cycles to the "Data_clock" pin.
    - On the rising edge, the controller, or our plug in particular for this project, serially shifts the states of the buttons locked on the "Serial_data" pin.
    - On the falling edge, the CPU inside the console samples the data.

Algorithm:
- In order to comply with the above-mentioned protocol, the plug's microprocessor must be able to detect the various signals sent by the console and respond accordingly.
    - If no latch command is given, the button states are regularly updated.
    - If the latch command is given, the button states are no more updated and are sent one by one after each rising edge of the clock.
    - When this is complete, the microprocessor resumes updating the button states.

## Battery

- One of the most important functions of a wireless controller is to display its battery charge, as we wouldn't want it to unexpectedly run out of power. The easiest way to do this is to measure the battery voltage. A fully charged battery will have a high voltage, and then slowly decrease as it is used. Fortunately, our microprocessor has an analog pin that allows us to do just that.
- Once we've obtained this value, we'll need to convert it into a number between 1 and 12, as we'll have 12 LEDs representing the current state of the battery.

## I2C Devices

- To make our controller, we had planned to use a set amount of digital inputs and outputs. However, as the projects progressed and new constraints were added, we ended up not having enough GPIOs to achieve all of our goals. As a result, we’ve used 2 GPIO Extenders and 1 LED Driver.
- These two devices communicate with the microprocessor via a protocol called I2C, which allows multiple modules to be connected to the same lines. The functions required to use the I2C protocol are provided by STM32CubeIDE; all you need to do is specify the device address and the payload to send or receive data.
    - GPIO Extenders are fairly easy to use, as you simply need to call the receive command at the right address to obtain the data byte in return.
    - However, the LED driver ended up more complex than the latter. It can control the light intensity of our 16 different LEDs. To use it, the microprocessor must send 2 payload bytes using the I2C protocol: the first corresponding to the register number and the second to the register value. As we only wanted the LEDs to be on or off, we created a function to modify the register of each LED so that this was the case.

## NRF24 (Wireless Communication)

As we explained in the "Hardware" section, as part of our project specifications, we needed the controller to be able to operate wirelessly. That's why we needed to be able to couple both our controller and the plug in order to receive the player's inputs.

NRF24 characteristics:
- Frequency: 2,4GHz
- Range: approx. 200m
- Maximum data flow: 2Mb/s (which is certainly much more than we'll need)

Communication between the microprocessor and the communication device:
- The operation of the NRF24 module is quite complex in itself. A series of specific actions must be performed so that it can trigger various commands such as receiving or sending data. Thanks to several of its commands, we can also read and write to the module's registers.
- The main problem will be that all of our command will have to be done through our microprocessor. This means that we will have to use another communication protocol in order to use the NRF24: the SPI protocol. Fortunately, the functions necessary to SPI communication are already provided in STM32CubeIDE, but it doesn’t change the fact that the whole process can be quite tedious.
- The main problem will be that all our commands will have to be made via our microprocessor. This means we'll have to use another communication protocol to operate the NRF24: the SPI protocol. Fortunately, the functions required for SPI communication are already provided in STM32CubeIDE, but this doesn't change the fact that the whole process can be quite tedious.
- To make the NRF24 work, we still had to write a whole library of functions. However, despite our best efforts, we couldn't get it to work, so we decided to look at other libraries that had been written by other people. In the end, we still had problems, but we did manage to transmit data between two NRF24s, although not as reliably as we'd hoped. On the other hand, we still don't know whether our first program worked or not, as it seems that our test equipment was one of the causes of its failure.

Data transmission:
- Once the library has been set up, its use can be considered fairly straightforward.
- First of all, the microprocessor needs to retrieve the controller data from inside the 2 GPIO Extenders (1 byte of data each). 
- It then sends them to the NRF24 module for wireless transmission to the plug module.
- After the data has been received on the plug module, it is sent to the CPU.
- This data is then converted into 16 bits of information corresponding to the states of our buttons.
- Finally, they are transmitted to the console according to the communication protocol.

## Readme

Main: /README.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/README.md

Hardware: /Hardware/README_HARDWARE.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/Hardware/README_HARDWARE.md

KiCad: /Hardware/Kicad/README_KICAD.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/Hardware/Kicad/README_KICAD.md

Software: /Software/README_SOFTWARE.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/Software/README_SOFTWARE.md

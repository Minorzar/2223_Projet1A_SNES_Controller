# SNES Controller (Hardware)

The purpose of this document is to explain the hardware operation of the controller and the reasons behind our choices.

Objective:
- We will attempt to recreate the SNES controller while adding a new feature that is unrelated to the original console. The initial aim of this project was to make a wireless controller for the NES or SNES.

Controller:
- The reason we chose an SNES controller over an NES controller is that, project constraints permitting, we intend to give it the ability to switch between SNES and NES modes using a toggle button. We considered that such a function should be possible, as the communication protocol between the two controllers is quite similar.

Plug:
- In order to make this controller wireless, we need a device that will act as a link between the controller and the console. With this in mind, we've opted for a plug that connects directly to the console. This plug will need a communication module, which will be the NRF24L01. The reason for this choice will be explained below and the operation of the NRF24L01 will be explained in greater detail in the software section of our project.

PCB:
- The main challenge of our project will be to design a PCB. To do this, we'll be using KiCad software. Knowing that we'll be creating a controller and a plug, we've estimated that we'll need exactly two PCBs, one for each.

Microprocessor:
- A microprocessor will be required on both the plug and the controller. Their main role will be to receive data from the controller, which will be transmitted via the NRF24L01 communication protocol to the plug, and then adapt it to the console using the SNES communication protocol. We chose to use an STM32-LK412KBTx for the plug and controller, as it was the most readily available while having sufficient GPIOs and being the smallest.

NRF24L01:
- We decided to use the NRF24 for three reasons. The first, although not very important, is its long range. The second is its low power consumption, as it costs less than many other communication devices. The third is its low latency compared with other available options.
- To use the NRF24L01 module, we decided to create two types of PCB: "Include" in which the NRF24L01 is directly included on the PCB, and "Exclude" in which the NRF24L01 will be excluded and will have to be connected to our PCB. The reason we decided on these two PCB types was to provide insurance in case the included version didn't work properly. Unfortunately, it really did happened and we had to abandon the included version, although not for the reasons we expected. It was mainly due to problems with KiCad and the antenna required for the NRF24L01. As a result, we had to fall back on the excluded version.

- We decided to use the NRF24 because it has a greater range than the ESB, for example. Another aspect is that it consumes little energy and costs less than many other devices that do the same thing. Finally, it is mainly due to the fact that it has lower latency than other devices. 
- To use the NRF24L01 module, we decided to create two types of PCB: "Include" in which the NRF24L01 is directly included on the PCB, and "Exclude" in which the NRF24L01 will be excluded and will have to be connected to our PCB. The reason we opted for these two PCB types was to provide insurance in case the included version didn't work properly.
- Unfortunately, this did happen and we had to abandon the included version, although not for the reasons we expected. This was mainly due to problems with KiCad and the antenna required for the NRF24L01. So we had to fall back on the excluded version.

## Controller

The initial controller design was to include 15 buttons, a few LEDs, a power supply with DC/DC converter and the various parts required for the NRF24L01.

Buttons:
- To reproduce the behavior of an SNES controller, we'll need at least 12 buttons, to which we'll add the pairing, power and SNES/NES mode buttons.
- [4] Directional cross (Up/Down/Left/Right)
- [6] Push buttons (A/B/X/Y/Start/Select)
- [2] Bumper buttons (L/R)
- [1] Pairing button
- [1] On/Off switch
- [1] SNES/NES mode switch

LEDs:
- To make sure our controller and plug are working properly, we've added LEDs to indicate whether certain parts are working or not. Here, we were mainly concerned with the controller's power supply.

Power supply:
- As the controller will be wireless, it will need to be powered by a power source. The most obvious solution was to use some kind of battery. We chose to use a 4.3V lithium-ion battery to compensate for the voltage drop on some parts of the controller, as most components operate on 3.3V.

DC/DC converter:
- To convert the voltage from 4.3V to 3.3V, we used a DC/DC converter. We first considered using an AMS1117 linear voltage regulator, but as it was not available, we decided to replace it with a MIC5219-3.3YMM.


## Plug

The purpose of our plug is to act as a data bridge between the controller and the console. As the console is powered by a 5V voltage, we'll need to lower it to 3.3V to suit our microprocessor. To do this, we'll use level shifters for each of the SNES signals passing through our SNES port, and once again a MIC5219-3.3YMM DC/DC converter for our microprocessor. The PCB will also differ depending on whether the NRF24L01 is included or not.
- If the NRF24L01 is excluded, only one connector needs to be added to the PCB.
- If the NRF24L01 is included, in addition to the NRF24L01 module, we'll also need to add a crystal and antenna.

LEDs:
- Similar with the controller, to make sure the plug is working properly, we've added LEDs to indicate whether certain parts are working or not, in particular the 3.3V, 5.5V voltage source and plug status. The "plug status" has deliberately not been detailed, as it will most likely be used for the various checks that may be carried out during testing.

Crystal / Antenna:
- As the "included" version has been dropped, we won't go into the details of what was used here. The only thing to note is that a certain frequency was required to select our crystal, and that we tried to use the same type of antenna found on the NRF24L01.

## Readme

Main: /README.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/README.md

Hardware: /Hardware/README_HARDWARE.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/Hardware/README_HARDWARE.md

KiCad: /Hardware/Kicad/README_KICAD.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/Hardware/Kicad/README_KICAD.md

Software: /Software/README_SOFTWARE.md
- https://github.com/Minorzar/snes_project_ensea2025/blob/main/Software/README_SOFTWARE.md

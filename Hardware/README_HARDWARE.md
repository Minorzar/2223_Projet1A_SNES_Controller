# snes_controler_ensea2025_Hardware
The purpose of this document is to explain the hardware operation of the controller and the reasons behind our choices.

Objective:
We will attempt to recreate the SNES controller while adding a new feature that is unrelated to the original console.

Controller:
The reason we chose a SNES controller over a NES controller is that we intend to give it the ability to switch between SNES and NES modes with a switch button.

Wireless:
In order to make this controller wireless, we will need a device to connect to the current console that will help us exchange information with our controller. At the moment, the NRF24L01 seems to be the most promising way, as it is also simpler than Bluetooth technology.

///// Controler /////
The controller will include 13 buttons, 2 switches, some LEDs, a power supply and a DC/DC converter.

Button:
Directional cross (Up/Down/Left/Right)
A/B/X/Y/Start/Select buttons
L/R bumpers
Pair up (to connect the controller and the console plug)

Switch:
On/Off switch
SNES/NES mode switch

LED:
TBD

Power supply:
We made the choice to use a 4.3V Lithium-ion battery as most of the components work with a voltage of 3.3V. It is worth mentioning that this type of battery is currently used in modern controllers such as the Sony PS4 controller.

DC/DC converter:
As we said previously, some components work with a voltage of 3.3V, which means that we will need a DC/DC converter. It seems possible to use the AMS1117 linear voltage regulator, however, we will first try to build one ourselves.

///// PLUG PART /////
In addition to our controller, we will have a plug that will be directly connected to the SNES. It will be composed of a NRF24L01, a STM32 microprocessor and a SNES plug.

NRF24L01:
This module will enable the console to receive data from the controller.

STM32 microprocessor:
The microprocessor will handle the data received from the NRF24L01 and convert it so that the SNES can process it.

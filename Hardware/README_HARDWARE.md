# SNES Controller (Hardware)
The purpose of this document is to explain the hardware operation of the controller and the reasons behind our choices.

Objective:
- We will attempt to recreate the SNES controller while adding a new feature that is unrelated to the original console. The original goal was to make a wireless SNES controller.

Controller:
- The reason we chose an SNES controller over an NES controller is that, project constraints permitting, we intend to give it the ability to switch between SNES and NES modes using a toggle button.

Plug:
- In order to make this controller wireless, we will need a device to connect to the actual console that will help us exchange data with our controller. With this in mind, we've opted for the use of a plug that will be connected directly to the console. For the moment, the NRF24L01 seems to be the most promising means at our disposal. The NRF24L01 part will be explained in more detail in the software part of our project.

PCB:
- The main constraint of our project is the need to design a PCB. To do this, we'll be using KiCad software. Knowing that we'll be creating a controller and a plug, we'll need exactly two PCBs, one for each.

Microprocessor:
- We'll be using an STM32-LK412KBTx for both the plug and controller, as it was the most readily available and has enough GPIOs for our project.

NRF24L01:
- To use the NRF24L01 module, we decided to create two types of PCB: one in which the NRF24L01 is directly included on the PCB, and another in which the NRF24L01 will be excluded and will have to be connected to our PCB.



---------- Controller ----------
The original design of our controller was to include 15 buttons, some LEDs and a power supply with a DC/DC converter. However, to ensure the project ran smoothly, the SNES/NES mode function was dropped early in the project. The reason behind this decision was that we needed an operational controller to make sure it worked which was not feasible due to the time constraints associated with PCB design, and that the NRF24L01 software required proved more difficult to program than anticipated.

Buttons:
To reproduce the behavior of an SNES controller, we'll need at least 12 buttons, to which we'll add the pairing button and the power button.
- Up/Down/Left/Right (Directional cross)
- A/B/X/Y/Start/Select (Push buttons)
- L/R (Bumpers buttons)
- Sync (Pairing button)
- On/Off (Switch)
- Dropped: SNES/NES Mode (Switch)

LEDs:
- To make sure our controller and plug are working properly, we've added LEDs to indicate whether certain parts are working or not.
Controller:
- Player
- Power

Power supply:
- We made the choice to use a 4.3V Lithium-ion battery as most of the components work with a voltage of 3.3V. It is worth mentioning that this type of battery is currently used in modern controllers such as the Sony PS4 controller.

DC/DC converter:
- Since some components operate with a voltage of 3.3V, we'll need a DC/DC converter. We first considered using an AMS1117 linear voltage regulator, but as it was not available, we decided to use a MIC5219-3.3YMM instead.



---------- Plug ----------
The purpose of our plug is to act as a data bridge between our controller and the SNES console. As the console is powered by a 5V voltage, we'll need to lower it to 3.3V to suit our microprocessor. To do this, we'll use level shifters for each of the SNES signals passing through our SNES port, and a MIC5219-3.3YMM DC/DC converter for our microprocessor. Three LEDs will also serve as an indicator  However, the PCB will differ depending on whether the NRF24L01 is included or not.
- If the NRF24L01 is excluded, we'll simply have to add a connector.
- If the NRF24L01 is included, in addition to the module, we'll also need to add an NRF24 crystal and antenna.


NRF24L01
Plug connector
Microprocesor

Our plug's main component is the NRF24L01 as it will mainly be used to receive data from the controller.


In addition to our controller, we will have a plug that will be directly connected to the SNES. It will be composed of a NRF24L01, a STM32 microprocessor and a SNES plug.


--- LEDs:
To make sure our controller and plug are working properly, we've added LEDs to indicate whether certain parts are working or not.
Plug:
- Player
- Status
- Power

NRF24L01:
- This module will enable the console to receive data from the controller.

STM32 microprocessor:
- The microprocessor will handle the data received from the NRF24L01 and convert it so that the SNES can process it.

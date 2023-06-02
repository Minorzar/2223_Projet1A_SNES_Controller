# SNES Controller (Hardware)
The purpose of this document is to explain the hardware operation of the controller and the reasons behind our choices.

Objective:
- We will attempt to recreate the SNES controller while adding a new feature that is unrelated to the original console. The initial aim of our project was to make a wireless controller for the NES or SNES.

Controller:
- The reason we chose an SNES controller over an NES controller is that, project constraints permitting, we intend to give it the ability to switch between SNES and NES modes using a toggle button.

Plug:
- In order to make this controller wireless, we need a device that will act as a link between the controller and the console. With this in mind, we've opted for a plug that will be directly connected to the console. This plug will therefore need a communication module. After discussion, NRF24L01 emerged as the most promising means available to us. The NRF24L01 will be explained in more detail in the software section of our project.

PCB:
- The main challenge of our project will be to design a PCB. To do this, we'll be using KiCad software. Knowing that we'll be creating a controller and a socket, we've estimated that we'll need exactly two PCBs, one for each.

Microprocessor:
- We'll be using an STM32-LK412KBTx for the connector and controller, as it was the most readily available and had sufficient GPIOs, while also being the smallest for our project.

NRF24L01:
- To use the NRF24L01 module, we decided to create two types of PCB: one in which the NRF24L01 is directly included on the PCB, and another in which the NRF24L01 will be excluded and will have to be connected to our PCB. The reason we decided on these two PCB types was to provide insurance in case the included version didn't work properly.
- Unfortunately, this happened and we had to abandon the included version. Not for the expected reasons, but due to problems involving KiCad and the antenna required for the NRF24L01, both on our plug and on our controller. We therefore had to fall back on the excluded version.



---------- Controller ----------

The initial controller design was to include 15 buttons, a few LEDs, a power supply with DC/DC converter and the parts required for the NRF24L01.

Buttons:
To reproduce the behavior of an SNES controller, we'll need at least 12 buttons, to which we'll add the pairing, power and SNES/NES mode buttons.
- Up/Down/Left/Right (Directional cross)
- A/B/X/Y/Start/Select (Push buttons)
- L/R (Bumpers buttons)
- Sync (Pairing button)
- Power On/Off (Switch)
- SNES/NES Mode (Switch)

LEDs:
To make sure our controller and plug are working properly, we've added LEDs to indicate whether certain parts are working or not. Here, we're mainly concerned with the controller's power supply.

Power supply:
- We chose to use a 4.3V lithium-ion battery to compensate for the voltage drop on some parts of the controller, as most components operate on 3.3V.

DC/DC converter:
- To convert the voltage from 4.3V to 3.3V, we need a DC/DC converter. We first considered using an AMS1117 linear voltage regulator, but as it wasn't available, we decided to use a MIC5219-3.3YMM instead.



---------- Plug ----------

The purpose of our plug is to act as a data bridge between our controller and the console. As the console is powered by a 5V voltage, we'll need to lower it to 3.3V to suit our microprocessor. To do this, we'll use level shifters for each of the SNES signals passing through our SNES port, and a MIC5219-3.3YMM DC/DC converter for our microprocessor. The PCB will also differ depending on whether the NRF24L01 is included or not.
- If the NRF24L01 is excluded, we'll simply have to add a connector.
- If the NRF24L01 is included, in addition to the module, we'll also need to add an NRF24 crystal and antenna.

LEDs:
As with the controller, to make sure the plug is working properly, we've added LEDs to indicate whether certain parts are working or not, including 3.3V, 5.5V and plug status.

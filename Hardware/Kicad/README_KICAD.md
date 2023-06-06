# SNES Controller (Hardware - KiCad)

The purpose of this document is to explain the conception of our PCB on KiCad.

---------- Folder structure ----------
Projects: This folder contains the Kicad projects of our controller.
- "Controller_NRF24L01_Exclude": refers to the controller itself, it contains the schematic and PCB with the buttons on it, and will be inserted in the shell of the controller.
- "Controller_NRF24L01_Include": refers to the controller itself, it contains the schematic and PCB with the buttons on it, and will be inserted in the shell of the controller.
- "Plug_NRF24L01_Exclude" refers to the Kicad project in which the NRF24L01 is not included in the schematic and PCB. The NRF24 module will have to be connected by cables for the receiver to work.
- "Plug_NRF24L01_Include" refers to the Kicad project where the NRF24L01 is included in the schematic and PCB.

Library: The library section contains the relevant files used in the projects.

Image:



---------- Schematic ----------
When we started the schematic, we remembered that the controller needed be ergonomic. So we planned and anticipated the positions of the buttons.
We reported the size controller on Kicad, the mounting hole of a side (R or L) are separate by a vector (+/-10,+/-20) (based on (x,y)).

Every button of the two cross (real cross and the 4 buttons (A,B,X,Y)) have been spaced by 25mm. The button Start and Select have been put at the same place as the original controller.
In order to be able to create the PCB the easiest way possible, the STM32 have been putted on the middle of the controller.

For the nRF24, for the Include version, we reproduced the schematic of the nRF24 on the PCB. We chose the condensers, crystal and resistors for it.

Moreover, all buttons were linked to the diode to impose the current way and had a resistor (1K) in purpose to avoid the link 3.3V mass.

After some discussion with the N+1, we have change the PCB shape for a hexagonal one, we have change the all the resistor and led on the button by just the button because the processor have the pull up resistor integrate for the GPIO out .

But the N+1 asked a way to see the battery level and the number of the controller, so we choose to use an multiple LED, the model was take form another projet because this one was already hear.

So , the multi-led needed 2 port (I2C SPI and CLK) and controlled 16 led. We use 4 led for the number of the controller and 12 for the battery level.

Moreover they are some problem on the number of port on the processor. Indeed the processor was impose by the teacher but this one hadn't 

UPDATES

- The V.0 was original a rectangular PCB but the unused part of copper was to high
- The spacing between button have been changed (10mm -> 25mm)

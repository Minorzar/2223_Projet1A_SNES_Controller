# SNES Controller (KiCad)

The purpose of this document is to explain the operations behind the design of our PCBs made with KiCad.

# Folder structure

Projects:
- Our KiCad projects consist of a controller and a plug, both of which have two distinct versions: the exclude and include versions. The exclude version will have a connector which will be used to connect an NRF24L01 to it. The include version will have the NRF24L01 directly on the PCB, along with the crystal and antenna corresponding to the latter's specifications.

<<<<<<< HEAD
Library:
- The library section contains the library files used in KiCad for our projects. The files there mainly concern the use of the NRF24L01 in particular.
=======
Image:
>>>>>>> 82c959ab23e3ea95cda9407755192579fc86679c

Image:
- This folder contains the progress of our PCBs in the form of images. It contains only images relating to the Plug_NRF24L01 schematic, PCB and 3D viewer.

Unused:
- The KiCad projects in this folder contain the "Include" versions of our controller and plug, as this was deemed infeasible due to bizarre antenna restrictions on the KiCad software. The only references we've found to this problem date back several years, and most of them have not been resolved on community forums and social networks.

<<<<<<< HEAD
# Schematic
When we started the schematic, we remembered that the controller needed be ergonomic. So we planned and anticipated the positions of the buttons. 
We reported the size controller on Kicad, the mounting hole of a side (R or L) are separate by a vector (+/-10,+/-20) (based on (x,y)). 
=======
---------- Schematic ----------
When we started the schematic, we remembered that the controller needed be ergonomic. So we planned and anticipated the positions of the buttons.
We reported the size controller on Kicad, the mounting hole of a side (R or L) are separate by a vector (+/-10,+/-20) (based on (x,y)).
>>>>>>> 82c959ab23e3ea95cda9407755192579fc86679c

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



The only concerns when routing our PCB were the following: the size and the use of coppers.

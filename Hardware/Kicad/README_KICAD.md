# SNES Controller (KiCad)

The purpose of this document is to explain the operations behind the design of our PCBs made with KiCad.

## Folder structure

### Projects
- Our KiCad projects consist of a controller and a plug, both of which have two distinct versions: the exclude version and the include version. The exclude version will have a connector which will be used to connect an NRF24L01 to it. The include version will have the NRF24L01 directly on the PCB, along with the crystal and antenna corresponding to the latter's specifications. As indicated in the README_HARDWARE, our project consists of 2 PCBs, one for the controller and the other for the plug. We will therefore have 4 KiCad projects with different versions over the course of the projects.

### Library
- The library section contains the libraries used in KiCad for our projects. The files found there mainly concern the use of the NRF24L01 in particular.

### Image
- This folder has no particular function other than practical. It provides quick access to the status of a KiCad project in its latest useful version in the form of images that can be shared and viewed more easily. This folder therefore contains the progress of our projects, currently mainly related to schematic, PCB and the 3D view of Plug_NRF24L01.

### Unused
- The KiCad projects in this folder contain the "Include" versions of our controller and plug, as this was deemed infeasible due to bizarre restrictions with our antenna on the KiCad software. The only references we've found to this problem date back several years, and most of them have not been resolved on community forums and social networks.

## Schematic

Designing the schematics for our PCB was fairly straightforward, as we had already planned our main components in advance. Since the purposes of our plug and controller are quite similar, namely data transmission, their schematics won't be too different. However, there are still a few notable differences, such as the fact that the controller will have a battery and more buttons; or that our plug will have several level shifters to convert signals into a voltage suitable for our microprocessor and console. More importantly, a GPIO Extender was added to our controller as other constraints were imposed during the project, such as the addition of LEDs to show the current state of our battery. This last constraint cost us a few too many pins on our microprocessor, and we ended up needing just one extra pin. That being said, after following the datasheets, all that's left to do is place the passive components needed for the IC, LEDs and buttons to work properly. The main components are as follows:

Controller:
- Microprocessor
- SWD connector
- DC/DC converter
- NRF24 connector
- Buttons and switches
- LEDs
- Mounting holes
- Battery connector
- GPIO Extender

Plug:
- Microprocessor
- SWD connector
- DC/DC converter
- NRF24 connector
- SNES connector
- Buttons and switches
- LEDs
- Mounting holes
- Level shifters

## PCB

We reported the size controller on Kicad, the mounting hole of a side (R or L) are separate by a vector (+/-10,+/-20) (based on (x,y)).

Every button of the two cross (real cross and the 4 buttons (A,B,X,Y)) have been spaced by 25mm. The button Start and Select have been put at the same place as the original controller.
In order to be able to create the PCB the easiest way possible, the STM32 have been putted on the middle of the controller.

For the nRF24, for the Include version, we reproduced the schematic of the nRF24 on the PCB. We chose the condensers, crystal and resistors for it.

Moreover, all buttons were linked to the diode to impose the current way and had a resistor (1K) in purpose to avoid the link 3.3V mass.

After some discussion with the N+1, we have change the PCB shape for a hexagonal one, we have change the all the resistor and led on the button by just the button because the processor have the pull up resistor integrate for the GPIO out .

But the N+1 asked a way to see the battery level and the number of the controller, so we choose to use an multiple LED, the model was take form another projet because this one was already hear.

So, the multi-led needed 2 port (I2C SPI and CLK) and controlled 16 led. We use 4 led for the number of the controller and 12 for the battery level.

Moreover they are some problem on the number of port on the processor. Indeed the processor was impose by the teacher but this one hadn't 


## Updates

- The V.0 was original a rectangular PCB but the unused part of copper was to high
- The spacing between button have been changed (10mm -> 25mm)

The only concerns when routing our PCB were the following: the size and the use of coppers.

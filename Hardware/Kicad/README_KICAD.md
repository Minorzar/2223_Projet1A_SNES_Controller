# SNES Controller (KiCad)

The purpose of this document is to explain the operations behind the design of our PCBs made with KiCad.

## Folder structure

Projects:
- Our KiCad projects consist of a controller and a plug, both of which have two distinct versions: the exclude version and the include version. The exclude version will have a connector which will be used to connect an NRF24L01 to it. The include version will have the NRF24L01 directly on the PCB, along with the crystal and antenna corresponding to the latter's specifications. As indicated in the README_HARDWARE, our project consists of 2 PCBs, one for the controller and the other for the plug. We will therefore have 4 KiCad projects with different versions over the course of the projects.

Library:
- The library section contains the libraries used in KiCad for our projects. The files found there mainly concern the use of the NRF24L01 in particular.

Image:
- This folder has no particular function other than practical. It provides quick access to the status of a KiCad project in its latest useful version in the form of images that can be shared and viewed more easily. Here we can see the different versions of the plug in the form of images of its schematic, routing and 3D view.

Unused:
- The KiCad projects in this folder contain the "Include" versions of our controller and plug, as this was deemed infeasible due to bizarre restrictions with our antenna on the KiCad software. The only references we've found to this problem date back several years, and most of them have not been resolved on community forums and social networks.

## Schematic

Designing the schematics for our PCBs was fairly straightforward, as we had already planned our main components in advance. Since the purposes of our plug and controller are quite similar, namely data transmission, their schematics won't be too different. However, there are still a few notable differences, such as the fact that the controller will have a battery and more buttons; or that our plug will have several level shifters to convert signals into a voltage suitable between our microprocessor and console. More importantly, GPIO Extenders were added to our controller as other constraints were imposed during the project, such as the addition of LEDs to show the current state of our battery. The latter cost us a few too many pins on our microprocessor, and we ended up needing just one extra pin. That being said, after following the datasheets, all that's left to do is place the passive components needed for the IC, LEDs and buttons to work properly. The main components are as follows:

Controller:
- Microprocessor
- SWD connector
- DC/DC converter
- NRF24 connector
- Buttons and switches
- LEDs
- Mounting holes
- Battery connector
- GPIO Extenders

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

When routing our PCBs, we had two main concerns: the size of our controller and the use of resources for our plug. As our controller had to meet certain size criteria, we couldn't afford to make it small and use as few resources as possible to make it. Our plug, on the other hand, was exactly the opposite.

Plug:
- To create the smallest possible PCB for our plug, we first grouped together all the more or less interconnected components, such as the SNES port and the level shifters with their resistors. Once this was done, we placed each connector on either side of the PCB, so that when the microprocessor was placed in the center, the connections would be made more or less easily. We also took care to place the decoupling capacitors as close as possible to each IC output voltage, to ensure proper operation. All that remained was to place the LEDs and button in an appropriate location. We also tried to reduce the use of copper by using ground vias, but with a PCB as small as it is, there wasn't much room for improvement.

Controller:
- The design of our controller PCB was based on a totally different mindset from that of the plug. We first had to measure the size of a controller and make sure the PCB met these criteria, as we were going to be soldering our buttons to it. As a rough estimate of the size of our controller, we decided to place the PCB mounting holes according to the following criteria: +/- 10mm horizontally and +/- 20mm vertically for mounting holes on the same side and +125mm between our inner mounting holes on the vertical.
- The directional cross button and the A, B, X, Y buttons are each separated by 25mm horizontally and vertically. The L and R buttons are both located on top of the controller in the form of connectors. The reason they're not buttons is that we're going to place them orthogonally to the controller, so they can't be placed on the PCB. The Start and Select buttons have been placed in the center of the controller, in a position similar to that of the original controller.
- The directional cross buttons and the A, B, X, Y buttons are each separated by 25 mm horizontally and vertically. The Start and Select buttons have both been placed in the center of the controller, in a position similar to that of the original controller. The L and R buttons are both located on the top of the controller in the form of connectors. The reason the L and R aren't buttons is that we're going to place them orthogonally to the controller, so they couldn't be placed on the PCB.
- All other components have been placed in the appropriate locations, such as the GPIO extenders close to the buttons to which they are connected.

## Updates

Over the course of our projects, we have had numerous iterations of our printed circuit boards, namely 6 plug versions and 3 controllers versions.

Plug:
- The first V0 and V1 versions can be considered as training for the routing of a complete PCB.
- Version V2 was designed to correct a number of problems, such as misplaced decoupling capacitors and optimized routing.
- From version V3 onwards, new constraints were imposed on the PCBs design: 0.5 track width, 1.6 mm via size, 0.8 via hole, almost double that of previous versions. These constraints were imposed because of problems associated with the manufacture of these printed circuits. As we gained more experience in routing our PCB, we tried this time to use the bottom surface to place the components and gain more space.
 - A new V4 version had to be made to make some necessary corrections. In particular, we realized that the previous PCB had pin assignment problems. We also took the opportunity to correct some routings that didn't fully comply with the previous constraints.
- Finally, the final version was the V5. There were no major changes from the previous version, apart from new corrections to the pin arrangements.
 
 Controller:
- Apart from the problems we've already mentioned with the plug, the controller hasn't undergone any other major changes. The only notable changes we've made are that we've changed the hexagonal shape of our PCB to a smoother form more reminiscent of the original SNES controller. 

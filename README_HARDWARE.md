# snes_controler_ensea2025_Hardware
this document have for purpose to explain how the controller Hardware works and why we have made this choice

In this project, we try to recreate a controller with one new feature: it show be without console's link
After an long discussion, we have accept to pick a SNES controller because if we create a SNES controller, it will be easy to switch to a nes controller with only a switch bouton

To make this controller wireless we need use something to plug to the real console to exchange some information between the controller and the console. The technology NRF 24 is on the table because it's more simple than Bluetooth technology

/////CONTROLLER PART/////

We have counted 13 buttons:
4 for the cross
A button
B button
Y button
X button
L/R button
Select button
Start button
1 button to push the search of the "Plug"

We have counted 2 switch:
1 switch to turn on/off the console
1 switch to switch to nes controller to snes ---> this one will be set more lately

We have some led
We don't now if we have a led with 4 feet (and with multiple colours)
We should, set up some register to fuse all button input into an unique bus of 13 bits

We have make the choice to pique a battery to 4.3V Li ion, because the most part component work with a tension of 3.3V  and this type of battery is already use in some controller like the Sony's Ps4 controller. So we can use Sony's answer to the battery problem to help us if we are stuck.

A Problem of the of the Tension source is to be as the same level as the component want. Many of our component work on 3.3V, so we should use a DC/DC convertor, after some search, we can use the STM ship ASM 1117, but for the moment we want built a DC/DC by our own means. 

///// PLUG PART /////

The plug part is the one that is directly linked to the SNES. On this part, we have a STM32 Microprocessor, the other part of the RNF24 and the SNES male plug as majors components.
The goal of this part is to receive informations from the controller(s) and convert it so the SNES can understand it. The microprocessor has to manage the RNF24 and converts the information sent to the SNES.
There will also be 4 buttons to choose which controller is being paired with the SNES.

NB : For more informations about how we convert the data so that the SNES understand it, check the data sheet in the main branch named "NES-controller-Hydra-Ch6All-v1.0"
# snes_controler_ensea2025_Hardware
this document have for purpose to explain how the controller Hardware works and why we have made this choice

In this project, we try to recreate a controller with one new feature: it show be without console's link
After an long discussion, we have accept to pic a snes controller because if we create a snes controller, it will be easy to switch to a nes controller with only a switch bouton

To make this controller wireless we need use something to plug to the real console to exchange some information between the controller and the console. The technology NRF 24 is on the table because it's more simple than Bluetooth technology

/////CONTROLLER PART/////

We have counted 13 bouton:
4 for the cross
A bouton
B bouton
Y bouton
X bouton
L/R bouton
Select bouton
Start bouton
1 bouton to push the search of the "Plug"

We have counted 2 switch:
1 switch to turn on/off the console
1 switch to switch to nes controller to snes ---> this one will be set more lately

We have some led
We don't now if we have a led with 4 feet (and with multiple color) or just 2 led

We should, set up some register to fuse all bouton imput into an unique bus of 13 bites

We have make the choice to pique a battery to 4.3V Li ion, because the most part composent work with a tension of 3.3V  and this type of battery is already use in some controller like the sony's Ps4 controller. So we can use sony's answer to the battery problem to help us if we are stuck.

A Problem of the of the Tension source is to be as the same level as the composent want. Many of our composent work on 3.3V, so we should use a DC/DC convertor, after some search, we can use the STM ship ASM 1117, but for the moment we want built a DC/DC by our own means. 

///// PLUG PART /////

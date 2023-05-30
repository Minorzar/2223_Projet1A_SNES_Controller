# NRF24L01 (Receiver)

This folder contains the Kicad projects of our controller project.
- "Controller": TBD
- "NRF24L01_Include" refers to the Kicad project where the NRF24L01 is included in the schematic and PCB.
- "NRF24L01_Exclude" refers to the Kicad project in which the NRF24L01 is not included in the schematic and PCB. The NRF24 module will have to be connected by cables for the receiver to work.
- The library section contains the relevant files used in the projects.

    In the first part we have been focus on the Controller nRF24 Include, this choice have been made by the faith in the credo ''the hard part first''. We belived in the fact that include the nRF24 will
 be harder than not include it.

When we begin the shematic, we remenber that controller needed be user-friendly. So we made first an plan on paper to anticipatate the button position. This plan was lost between some quantum physic and Signal TD. But we hade the time to report the size controller on Kicad, the mounting hole of a side (R or L) are separate by a vertor (+/-10,+/-20) (based on (x,y)). Every button of the two cross (real cross and ABXY) was separate by 1cm (10mm, this size are take between the two opposite button from the same cross), but that case a problem because this button was really near and that wasn't CAO-Frendly. So to avoid this, we separate the button by 25mm. the button Start and Select are put in way to be user-friendly, the prossessor was put in order to be easiest to root, so it was put in the middle of the PCB.

The nRF24 was made to build as the data sheet order it, it was place on the top edge of the controller (in purpose to take the place ) and the cristal was selected as the datasheet asked(can be see int the datasheet). But we forget to creat a self mass plan for the Quartz.

The V.0 was original a rectangular PCB but the unused part of copper was to high

Moreover, all button was link to the diode to impose the courant way and hade a resistor (1K) in purpose to invoide the link 3.3V mass.

After some discution with the N+1, we have change the PCB shape for a hegaconal one, we have change the all the resistor and led on the button by just the button because the processor have the pull up resistor integrate for the GPIO out .

But the N+1 asked a way to see the battery level and the number of the controller, so we choose to use an multiple LED, the model was take form another projet because this one was already hear.

So , the multi-led needed 2 port (I2C SPI and CLK) and controlled 16 led. We use 4 led for the number of the controller and 12 for the battery level.

Moreover they are some problem on the 

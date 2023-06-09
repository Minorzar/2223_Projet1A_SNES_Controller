# SNES Controller (Software)

The purpose of this document is to explain the algorithms and programming elements we've written for the two microprocessors in our project: one for the controller, the other for the plug.

## SNES Communication Protocol

The SNES console communicates with the controller and retrieves data in a specific way. That's why we have to adapt to it and ensure that our microprocessors reproduce these steps correctly.

SNES port features:
- Frequency: 60 Hz / 16.67 ms
- Clock period: 12 μs
- Pin 1: +5 V
- Pin 2: Data_clock
- Pin 3: Data_latch
- Pin 4: Serial_data
- Pin 5: N/A
- Pin 6: N/A
- Pin 7: Ground

Communication sequence:   
- 1     B       
- 2     Y       
- 3     Select  
- 4     Start   
- 5     Up      
- 6     Down    
- 7     Left    
- 8     Right   
- 9     A       
- 10    X       
- 11    L       
- 12    R       
- 13    High    
- 14    High    
- 15    High    
- 16    High    
- (17   Low)     

Operation:
- Every 16.67 ms, the console sends a 12 μs wide pulse to pin 3, instructing the controller to latch the state of the buttons.
- After 6 μs, the console sends 16 clock cycles to the "Data_clock" pin.
    - On the rising edge, the controller, or our plug in particular for this project, serially shifts the states of the buttons locked on the "Serial_data" pin.
    - On the falling edge, the CPU inside the console samples the data.

---- Algorithm ----

In order to conform to the aforementioned protocol, the processor inside the plug detects the various signals sent by the console and responds accordingly.

When the SNES doesn't send anything, it updates the button data regularly. 

When the latch order is given, it stops to update the button states and then sends them one by one after each rising edge of the clock. 

When that's finished, the CPU resumes the updates of the button data and the cycle continues.


In order to comply with the above-mentioned protocol, the plug's microprocessor must be able to detect the various signals sent by the console and respond accordingly.
- When the SNES sends nothing, it regularly updates the button data. 
- When the lock command is given, it stops to update the button states, and then sends them one by one after each rising edge of the clock. 
- When this is complete, the CPU resumes updating the button data and the cycle continues.


# Battery Information

We wanted the controller to display the charge of its battery, so that the controller doesn't run flat unexpectedly. The easiest way to know the state of the battery is to measure its voltage. Indeed, a fully charged battery has high voltage that decreases slowly as it is used.The CPU we have chosen offers a built-in solution to do that: some specific pins can be used as an AD converter that can measure analog voltages.

After obtaining the raw number from the ADC, it is used to compute an integer between 0 and 12, which indicates how many LEDS should be powered on the controller.


# I2C Devices

On the controller, we needed to have many digital inputs and outputs: we have 12 buttons to detect and 16 LEDs to power. There are just not enough GPIOs available on our CPU to connect them all. That's why we had to use specific devices to manage all of these inputs and outputs: 2 GPIO extenders and 1 LED driver.

These devices communicate with the CPU through a protocol called I2C that allows multiple modules to be hooked up to the same lines. The functions needed to use the I2C protocol were provided by STM32CubeIDE, we only needed to specify the address of the device and the payload to send or receive data.

Getting the button data from the GPIO extenders is fairly simple, you just have to use the receive command with the right address and it returns the data byte.

The LED driver is more specialized and more complicated: it can control the light intensity of 16 different LEDs. To use it you always have to edit its registers, therefore the CPU sends with I2c 2 bytes of payload: the first is the register number and the second is the register value. We only wanted the LEDs to switch on and of, so to simplify things we created a function that edits the registers according to the LED that needs to be powered up or down.

# Wireless Communication

In the specifications of our project, we wanted the controller to function without any wire connecting it to the console. That's why we had to allow the 2 parts of our project to communicate using electromagnetic signals. The NRF24 wireless module seemed particularly fitting for what we intended to do.

---- nrf24 characteristics ----
- frequency: 2,4GHz
- Range: approx. 200m
- Maximum data flow: 2Mb/s (we've never even gotten close to this number)

---- Communication between the CPU and the module ----

The operation of nrf24 module is fairly complex in itself: in order to send or receive data wirelessly, it had to perform a series of specific actions that we can trigger using various commands. The many parameters of the module are also accessed and modified via commands that can read and write the registers in the module.

The problem is that we can only program the CPU, we can't directly write commands in the module or access its information, thus it requires another communication protocol for it to respond to the processor: the SPI protocol. In addition to the SPI the NRF24 module has one more pin that is used to switch between Standby mode and RX/TX mode. Thankfully the functions necessary to SPI communication are already provided in STM32CubeIDE, but the whole process remains really convoluted.

So we had to write a whole library of functions related to communication with the nrf24 module but despite our best efforts, we were unable to make it worked, so we have decided to look at other library that were written by other people.
 With the help of thoes library, we managed to make the two STM32 used to test our code to communicate with each other.


In addition to the SPI the NRF24 module has one more pin that is used to switch between Standby mode and RX/TX mode.

---- Data transmission ----

The way we use the nrf24 module is actually fairly simple: first the CPU inside the controller retrieves the data from the 2 GPIO extenders (1 byte of data for each), then sends it to the nrf24 module that transmits the data wirelessly to the module on the other board. This module sends the data to the CPU, that derives the button states from the 16 bits of information. Finally the button states are transmitted to the console according to the communication protocol explained above.

# ArduCAN-HS
## High Speed ISO 11898-2 Dual Port CAN Bus Shield for Arduino DUE
![alt text](/Docs/img/ArduCAN-HS.jpg)

### Description
The ArduCAN-HS board is a shield for Arduino DUE that acts as a CAN bus interface according to ISO 11898-2, which is the standard normally used in vehicles for intercommunication between their electronic modules with computing capacity (known as ECU).

This board incorporates two CAN bus transceivers that are connected to the CAN ports of the microcontroller of the Arduino DUE. This microcontroller is a SAM3X8E ARM Cortex-M3, much more powerful than the ATmega328 of the classic Arduino UNO, so we will have more features to develop our CAN bus projects. Furthermore, the hardware configuration with the ArduCAN-HS board is more effective than the hardware configuration of the classic CAN bus shield for Arduino UNO. This is due to the fact that the peripheral that acts as a CAN bus controller is integrated in the SAM3X8E microcontroller of Arduino DUE, while in the ATmega328 of Arduino UNO the controller (MCP2515) is external and is managed through an SPI bus, so that the management of the sending and receiving processes are slower. The following image illustrates what has just been commented:
![alt text](/Docs/img/DUE_vs_UNO.jpg)

If we also take into account that we have 2 CAN ports on our ArduCAN-HS board, our possibilities for application development are greater.

### Applications
Some of the possible applications of the ArduCAN-HS shield together with Arduino DUE we can mention the following:
* CAN emulator (to simulate messages as in a multiplexed network of a vehicle).
* USB/CAN protocol converter.
* CAN/CAN Gateway (to communicate two networks with different baudrates or frame formats).
* CAN bus analyzer (to capture messages and analyze them).

### Features
* 2 CAN ports with speed up to 1Mb/s (support ISO 11898-2 and ISO 11898-5).
* 120Ω terminating resistors, which can be configured in two different ways and independently for each port:
  - Fixed resistors (through jumpers JP2 and JP3).
  - Switchable resistors (by program code).
* Entries to enable / disable each of the ports.
* Additional protections against ESD events.
* 3.3V power supply from regulator with 5V input.
* 5 LEDs:
  - 5V power supply.
  - Lines TX0, RX0, TX1, RX1.
* 3-terminal connection strips (CAN-H, CAN-L and GND).

### Installation
Download the ZIP file and extract it to any folder. Rename the extracted folder to ArduCAN-HS. Copy the ArduCAN-HS folder to your Arduino libraries directory (for example ... \ Documents \ Arduino \ libraries). You will now have the library available and you can open an example by accessing File -> Examples.

### More info
For more information or to know how to obtain the ArduCAN-HS board, please email me at macorchero@gmail.com

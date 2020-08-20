/****************************************************************************
 * File name: "ArduCAN_HS_Example_Send_Traffic.ino"
 * 
 * Author: Miguel A. Corchero
 *
 * Date: 20/08/2020
 * 
 * This is a basic example of a CAN bus traffic simulation. It can be useful 
 * as a starting point to emulate the multiplexed networks of a vehicle and 
 * to activate or deactivate specific functions of an electronic module 
 * or ECU that works with CAN bus. This program sends a CAN bus message 
 * every 2 milliseconds sequentially, first messages are sent through port 0 
 * and then through port 1. The purpose of this example is demonstrative, it 
 * only aims to test the operation of both ports. You can use a CAN bus analyzer 
 * to verify the operation of each transmission, as well as try turning off the 
 * terminal resistors and see how reception is not possible unless they are 
 * connected externally. Note that the "period" field in the "TrafficMessages[]" 
 * structure is not used in this example. To improve this example and assign a 
 * different period for each CAN bus message, you can implement a system of 
 * interrupt timers.
 ***************************************************************************/

// ArduCAN-HS board functions
// -----------------------------------------------------------------
#include "ArduCAN_HS.h"

extern byte canInit(byte port, long baudrate);
extern byte canTx(byte port, long Id, bool format, byte *data, byte dlc);
extern byte canRx(byte Port, long *Id, bool *format, byte *data, byte *dlc);

// ------------------------------------------------------------------
// CAN bus traffic simulation messages
// ------------------------------------------------------------------
#define NUMBER_OF_FRAMES 8

byte dataMsg1[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte dataMsg2[] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte dataMsg3[] = {0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00};
byte dataMsg4[] = {0x07, 0x08, 0x09, 0x0A, 0x00, 0x00, 0x00, 0x00};
byte dataMsg5[] = {0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x00, 0x00, 0x00};
byte dataMsg6[] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x00, 0x00};
byte dataMsg7[] = {0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x00};
byte dataMsg8[] = {0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24};

struct CANbusMessage TrafficMessages[] = {
  // Port,   ID,         Format,          Data 0...7,    DataLength,  Period
     0,     0x200,       false,           &dataMsg1[0],     1,         2,
     0,     0x38D,       false,           &dataMsg2[0],     2,         2,
     0,     0x1E4,       false,           &dataMsg3[0],     3,         2,
     0,     0x312,       false,           &dataMsg4[0],     4,         2,
     1,     0x51E,       false,           &dataMsg5[0],     5,         2,
     1,     0x50,        false,           &dataMsg6[0],     6,         2,
     1,     0x35F,       false,           &dataMsg7[0],     7,         2,
     1,     0x56,        false,           &dataMsg8[0],     8,         2 
};

void setup()
{
  // Set the serial interface baud rate
  Serial.begin(115200);

  // Initialize CAN controller for Port 0
  if(canInit(0, CAN_BPS_500K) == CAN_OK)
    Serial.print("CAN0: Initialization OK\n");
  else
    Serial.print("CAN0: Initialization ERROR\n");

  //Initialize CAN controller for Port 1
  if(canInit(1, CAN_BPS_500K) == CAN_OK)
    Serial.print("CAN1: Initialization OK\n");
  else
    Serial.print("CAN1: Initialization ERROR\n");


  pinMode(LOAD_120_PIN_CAN0,OUTPUT);      //Set pin for switchable Port 0 termination resistor as output.
  pinMode(LOAD_120_PIN_CAN1,OUTPUT);      //Set pin for switchable Port 1 termination resistor as output.

  digitalWrite(LOAD_120_PIN_CAN0,LOW);    //Port 0 termination resistor enabled. Disable it if set externally.
  digitalWrite(LOAD_120_PIN_CAN1,LOW);    //Port 1 termination resistor enabled. Disable it if set externally.
}

void loop()
{
  int i = 0;
  static unsigned long lastTime = 0;

  while(1)
  {
    if ((millis() - lastTime) > 2)        //Send a message every 2 ms.
    {
      lastTime = millis();
      
      // Send the CAN message
      if(canTx(TrafficMessages[i].Port, TrafficMessages[i].ID, TrafficMessages[i].Format, 
               TrafficMessages[i].Data, TrafficMessages[i].DataLength) != CAN_OK)
      {
        if(TrafficMessages[i].Port == 0)
          Serial.print("CAN0: transmission error.\n\r");
        else
          Serial.print("CAN1: transmission error.\n\r");
      }
      
      i++;
      if (i >= NUMBER_OF_FRAMES) i = 0;   //Restart counter.
    }    
  }
}

/*******************************************************************
                 ================================
                    ArduCAN-HS board library 
                 ================================

File name: ArduCAN_HS.cpp
*******************************************************************/

#include "ArduCAN_HS.h"


byte canInit(byte port, long baudrate)
{
  byte retval = CAN_ERROR;
  
  // Initialize the CAN port, set the proper baud rate and the enable pin.
  if(port == 0)
    retval = Can0.begin(baudrate, ENABLE_PIN_CAN0);
  else if(port == 1)
    retval = Can1.begin(baudrate, ENABLE_PIN_CAN1);
  else{};

  if(retval == CAN_OK)
  {
    if(port == 0)
    {
      Can0.watchFor();    // Allow all traffic through CAN 0
    }
    else
    {
      Can1.watchFor();    // Allow all traffic through CAN 1
    }
  }

  return retval;
  
}// end canInit

// -----------------------
// Transmit CAN message
// -----------------------

byte canTx(byte port, long Id, bool format, byte *data, byte dlc)
{
  byte retval = CAN_ERROR;
  CAN_FRAME CANmsg;

  // Build the message
  CANmsg.id = Id;
  CANmsg.extended = format;
  CANmsg.length = dlc;

  for(byte i = 0; i < 8; i++)
  {
    if(i < dlc)
      CANmsg.data.bytes[i] = data[i];
    else
      CANmsg.data.bytes[i] = 0x00;

  }
    
  // Send the message
  if(port == 0)    
  {   
    retval = Can0.sendFrame(CANmsg);
  }
  else
  {
    retval = Can1.sendFrame(CANmsg);
  }

  return retval;

}

// -----------------------
// Receive CAN message
// -----------------------

byte canRx(byte port, long *Id, bool *format, byte *data, byte *dlc)
{
  // Declarations
  byte datalength = 0;
  byte retval = CAN_ERROR;
  CAN_FRAME CANmsg_rcvd;
  
  
  if(port == 0)
  {  
    datalength = Can0.available();
    if(datalength > 0)
    {
      Can0.read(CANmsg_rcvd);
    }

  }
  else if (port == 1)
  {  
    datalength = Can1.available();
    if(datalength > 0)
    {
      Can1.read(CANmsg_rcvd);
    }    

  }

  *Id = CANmsg_rcvd.id;
  *format = CANmsg_rcvd.extended;
  
  if(datalength > 0)
  {
    // Store data
    for(byte i = 0; i < 8; i++)
    {
      data[i] = CANmsg_rcvd.data.bytes[i];
    }
    
    *dlc = CANmsg_rcvd.length;

    retval = CAN_OK;
  }// end if

  return retval;

}

/*******************************************************************
                 ================================
                    ArduCAN-HS board library 
                 ================================

File name: ArduCANHSx2.h
*******************************************************************/

#ifndef _ARDUCAN_HS_
#define _ARDUCAN_HS_

#include "due_can.h"

#define CAN_OK               1
#define CAN_ERROR            0

#define ENABLE_PIN_CAN0      51
#define ENABLE_PIN_CAN1      25

#define LOAD_120_PIN_CAN0       50
#define LOAD_120_PIN_CAN1       24

struct CANbusMessage
{
  byte Port;         // 0/1
  long ID;           // CAN message ID
  bool Format;       // TRUE -> 29-bit; FALSE = 11-bit
  byte *Data;        // CAN data
  byte DataLength;   // DLC field
  int  Period;       // Period in milli-seconds.
};

#endif

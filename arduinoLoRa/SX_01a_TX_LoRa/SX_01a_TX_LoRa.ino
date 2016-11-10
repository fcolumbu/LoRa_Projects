/*  
 *  LoRa 868 / 915MHz SX1272 LoRa module
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           1.2
 *  Design:            David Gascón
 *  Implementation:    Covadonga Albiñana, Victor Boria, Ruben Martin
 *  Modified by:       Francis M. Columbus, WA2KWR, for Amateur Radio beacon use
 *                     and to fix compatibility problems with newer versions of the Arduino IDE
 */

#include <Wire.h>

// Cooking API libraries
#include <arduinoUtils.h>

// Include the SX1272 and SPI library:
#include "arduinoLoRa.h"
#include <SPI.h>

// channel numbers to frequency are found in arduinoLoRa.h
// Please see the FREQUENCY CHANNELS: const declarations

int e;

char message0 [] = "Packet 1, CQ CQ CQ de WA2KWR";
char message1 [] = "Packet 1, wanting to see if received packet is the same as sent packet";
char message2 [] = "Packet 2, broadcast test";
char message3 [] = "Packet 2, LoRa Beacon de WA2KWR, Morgan Hill, CA 95037 USA";
char message4 [] = "Packet 3, LoRa Beacon de WA2KWR, Grid: CM97ed"; 

void setup()
{ 
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  // Print a start message
  Serial.println(F("SX1272 module and Arduino: send packets without ACK"));
  
  // Power ON the module
  e = sx1272.ON();
  Serial.print(F("Setting power ON: state "));
  Serial.println(e, DEC);
  
  // Set transmission mode and print the result
  e |= sx1272.setMode(1);
  Serial.print(F("Setting Mode: state "));
  Serial.println(e, DEC);
  
  // Set header
  e |= sx1272.setHeaderON();
  Serial.print(F("Setting Header ON: state "));
  Serial.println(e, DEC);
  
  // Select frequency channel
  e |= sx1272.setChannel(CH_02_900);          // channel 02, central freq = 907.40MHz 
  Serial.print(F("Setting Channel: state "));
  Serial.println(e, DEC);
  
  // Set CRC
  e |= sx1272.setCRC_ON();
  Serial.print(F("Setting CRC ON: state "));
  Serial.println(e, DEC);
  
  // Select output power (Max, High or Low)
  e |= sx1272.setPower('M');
  Serial.print(F("Setting Power: state "));
  Serial.println(e, DEC);
  
  // Set the node address and print the result
  e |= sx1272.setNodeAddress(252);
  Serial.print(F("Setting node address: state "));
  Serial.println(e, DEC);
  
  // Print a success message
  if (e == 0)
    Serial.println(F("SX1272 successfully configured"));
  else
    Serial.println(F("SX1272 initialization failed"));

}

void loop(void)
{
  // Send message1 and print the result
  e = sx1272.sendPacketTimeout(8, message0);
  Serial.print(F("Packet 1 sent, state "));
  Serial.println(e, DEC);
   Serial.println(message0);


  delay(15000);  

  // Send message2 broadcast and print the result
  e = sx1272.sendPacketTimeout(0, message3);
  Serial.print(F("Packet 2 sent, state "));
  Serial.println(e, DEC);
  Serial.println(message3);

  
  delay(15000);

  // Send message3 broadcast and print the result
  e = sx1272.sendPacketTimeout(0, message4);
  Serial.print(F("Packet 3 sent, state "));
  Serial.println(e, DEC);
  Serial.println(message4);

  delay(15000);   
}


/* Valid modes
 *  
 *   switch (mode)
    {
        // mode 1 (better reach, medium time on air)
        case 1:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_12);       // SF = 12
                    setBW(BW_125);      // BW = 125 KHz
                    break;
 
        // mode 2 (medium reach, less time on air)
        case 2:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_12);       // SF = 12
                    setBW(BW_250);      // BW = 250 KHz
                    break;
 
        // mode 3 (worst reach, less time on air)
        case 3:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_10);       // SF = 10
                    setBW(BW_125);      // BW = 125 KHz
                    break;
 
        // mode 4 (better reach, low time on air)
        case 4:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_12);       // SF = 12
                    setBW(BW_500);      // BW = 500 KHz
                    break;
 
        // mode 5 (better reach, medium time on air)
        case 5:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_10);       // SF = 10
                    setBW(BW_250);      // BW = 250 KHz
                    break;
 
        // mode 6 (better reach, worst time-on-air)
        case 6:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_11);       // SF = 11
                    setBW(BW_500);      // BW = 500 KHz
                    break;
 
        // mode 7 (medium-high reach, medium-low time-on-air)
        case 7:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_9);        // SF = 9
                    setBW(BW_250);      // BW = 250 KHz
                    break;
 
        // mode 8 (medium reach, medium time-on-air)
        case 8:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_9);        // SF = 9
                    setBW(BW_500);      // BW = 500 KHz
                    break;
 
        // mode 9 (medium-low reach, medium-high time-on-air)
        case 9:     setCR(CR_5);        // CR = 4/5
                    setSF(SF_8);        // SF = 8
                    setBW(BW_500);      // BW = 500 KHz
                    break;
 
        // mode 10 (worst reach, less time_on_air)
        case 10:    setCR(CR_5);        // CR = 4/5
                    setSF(SF_7);        // SF = 7
                    setBW(BW_500);      // BW = 500 KHz
                    break;

Valid Channels

  //! Variable : frequency channel.
  //!    channel = 0xD84CCC  --> CH = 10_868, 865.20MHz
  //!    channel = 0xD86000  --> CH = 11_868, 865.50MHz
  //!    channel = 0xD87333  --> CH = 12_868, 865.80MHz
  //!    channel = 0xD88666  --> CH = 13_868, 866.10MHz
  //!    channel = 0xD89999  --> CH = 14_868, 866.40MHz
  //!    channel = 0xD8ACCC  --> CH = 15_868, 866.70MHz
  //!    channel = 0xD8C000  --> CH = 16_868, 867.00MHz
  //!    channel = 0xE1C51E  --> CH = 00_900, 903.08MHz
  //!    channel = 0xE24F5C  --> CH = 01_900, 905.24MHz
  //!    channel = 0xE2D999  --> CH = 02_900, 907.40MHz
  //!    channel = 0xE363D7  --> CH = 03_900, 909.56MHz
  //!    channel = 0xE3EE14  --> CH = 04_900, 911.72MHz
  //!    channel = 0xE47851  --> CH = 05_900, 913.88MHz
  //!    channel = 0xE5028F  --> CH = 06_900, 916.04MHz
  //!    channel = 0xE58CCC  --> CH = 07_900, 918.20MHz
  //!    channel = 0xE6170A  --> CH = 08_900, 920.36MHz
  //!    channel = 0xE6A147  --> CH = 09_900, 922.52MHz
  //!    channel = 0xE72B85  --> CH = 10_900, 924.68MHz
  //!    channel = 0xE7B5C2  --> CH = 11_900, 926.84MHz

*/
  


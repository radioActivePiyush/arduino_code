/**
* First test
*
*/

#include <SPI.h>
#include <RF24.h>
#include "printf.h"

//
// Hardware configuration
//

// Configure nRF24L01 radio module on SPI bus plus pins 8 for CE & 9 for CS
// arguments are (ce, cs)

RF24 radio(7,8);

//
// Set transmit and receive addresses
//

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

void setup(void)
{

  Serial.begin(9600);
  printf_begin();
  printf("\n\rTest connection to modules\n\r");

  //
  // Setup and configure rf radio
  //

  radio.begin();
  
  // Set the TX and RX addreses in the module
  
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  

  // radio.setDataRate( RF24_2MBPS ) ;
   radio.setPALevel( RF24_PA_MAX ) ;
  radio.enableDynamicPayloads() ;
  radio.setAutoAck( true ) ;
  radio.powerUp() ;
  radio.startListening();

  //
  // Print out the configuration of the rf unit for debugging
  //

  radio.printDetails();
}

void loop(void)
{
}



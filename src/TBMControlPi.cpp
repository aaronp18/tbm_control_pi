//********************************************************************************************
//                                                                                           *
// AB&T Tecnologie Informatiche - Ivrea Italy                                                *
// http://www.bausano.net                                                                    *
// https://www.ethercat.org/en/products/791FFAA126AD43859920EA64384AD4FD.htm                 *
//                                                                                           *
//********************************************************************************************
//                                                                                           *
// This software is distributed as an example, in the hope that it could be useful,          *
// WITHOUT ANY WARRANTY, even the implied warranty of FITNESS FOR A PARTICULAR PURPOSE       *
//                                                                                           *
//********************************************************************************************

//----- EasyCAT HAT application basic example for Raspberry ----------------------------------
//----- Derived from the example project TestEasyCAT.ino for the AB&T EasyCAT Arduino shield

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#include "TBMControlPi.h"

#include "EasyCAT.h" // EasyCAT library to interface

EasyCAT EASYCAT; // EasyCAT istantiation

// The constructor allow us to choose the pin used for the EasyCAT HAT chip select
// Without any parameter pin 24 (CE0) will be used

// example:
// EasyCAT EASYCAT(RPI_GPIO_P1_26);  // pin 26 (CE1) will be used as SPI chip select

// Remember that the board must be modified to match the pin chosen

uint16_t ContaUp;  // used for sawthoot test generation
uint8_t ContaDown; //

int16_t temperatureADC, methaneADC, inclinometer0ADC, inclinometer1ADC, inclinometer2ADC;

unsigned short OutCount = 0;

int main()
{
    char cValue; // used to read the output buffer

    ContaUp = 0x0000;   //
    ContaDown = 0x0000; //

    //---- initialize the EasyCAT board -----

    if (EASYCAT.Init() == true) // initialization
    {
        printf("inizialized\n"); // succesfully completed
    }
    else // initialization failed
    {
        printf("inizialization failed\n"); // the EasyCAT board was not recognized
        return -1;
    }
    // In the main loop we must call ciclically the
    // EasyCAT task and our application
    //
    // This allows the bidirectional exachange of the data
    // between the EtherCAT master and our application
    //
    // The EasyCAT cycle and the Master cycle are asynchronous
    //
    // The delay allows us to set the EasyCAT cycle time
    // according to the needs of our application
    //
    // For user interface applications a cycle time of 100mS,
    // or even more, is appropriate, but, for data processing
    // applications, a faster cycle time may be required
    //
    // In this case we can also completely eliminate this
    // delay in order to obtain the fastest possible response

    while (1)
    {

        // Send value

        EASYCAT.MainTask(); // execute the EasyCAT task

        EASYCAT.BufferIn.Cust.status_in = 1;
        // * TODO Set buffer in for temperature, methane and inclinometers (and pi temperature) here
        // * TODO print out values every 5 seconds
        usleep(100000); // delay of 100mS
    }
}

// * Reads the values of the ADC and saves them to local variables.
void readValues()
{
}

// * Sets up the ADCs with the appropriate addresses
void initADCs()
{
    // ADC0 has addr 0x48
    // ADC1 has addr 0x49
}
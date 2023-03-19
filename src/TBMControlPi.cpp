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
#include <iostream>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

using namespace std;

#define VDD 5.3

#include "TBMControlPi.h"

#include "EasyCAT.h" // EasyCAT library to interface

#include "Adafruit_ADS1015.h" // Adafruit ADS1015 library

EasyCAT EASYCAT; // EasyCAT istantiation

Adafruit_ADS1115 ads0(0x48); // ADC0
Adafruit_ADS1115 ads1(0x49); // ADC1

// The constructor allow us to choose the pin used for the EasyCAT HAT chip select
// Without any parameter pin 24 (CE0) will be used

// example:
// EasyCAT EASYCAT(RPI_GPIO_P1_26);  // pin 26 (CE1) will be used as SPI chip select

// Remember that the board must be modified to match the pin chosen

int16_t temperatureADC, methaneADC, inclinometer0ADC, inclinometer1ADC, inclinometer2ADC;

int i = 0;

int main()
{
    //---- initialize the EasyCAT board -----

    if (EASYCAT.Init() == true) // initialization
    {
        printf("Easy CAT Initialised\n"); // succesfully completed
    }
    else // initialization failed
    {
        printf("Initialition failed\n"); // the EasyCAT board was not recognized
        return -1;
    }

    initADCs();

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

        EASYCAT.BufferIn.Cust.temperatureTBM = temperatureADC;
        // * TODO Set buffer in for temperature, methane and inclinometers (and pi temperature) here

        readValues();

        EASYCAT.BufferIn.Cust.status_in = 1;

        if (i > 25)
        {
	    i = 0;
            printf("| Status: %d\t| ", EASYCAT.BufferOut.Cust.status_out);
            printf(" Temperature: %d\t|", EASYCAT.BufferIn.Cust.temperatureTBM);
            printf(" Pi Temperature: %d\t|", EASYCAT.BufferIn.Cust.input0);
            printf(" Methane: %d\t|", EASYCAT.BufferIn.Cust.methane);
            printf(" Inclinometer0: %d\t|", EASYCAT.BufferIn.Cust.inclinometer0);
            printf(" Inclinometer1: %d\t|", EASYCAT.BufferIn.Cust.inclinometer1);
            printf(" Inclinometer2: %d\t|", EASYCAT.BufferIn.Cust.inclinometer2);
            printf("\n");
        }
        i++;

        // printAllADC();

        usleep(100000); // delay of 100mS
    }
}

// * Reads the values of the ADC and saves them to local variables.
void readValues()
{

    // * Read the values from the ADCs
    methaneADC = ads0.readADC_SingleEnded(0);
    temperatureADC = ads0.readADC_SingleEnded(1);
    inclinometer0ADC = ads1.readADC_SingleEnded(0); // X
    inclinometer1ADC = ads1.readADC_SingleEnded(1); // Y
    inclinometer2ADC = ads1.readADC_SingleEnded(2); // Pitch

    // * Convert the values to the correct units

    EASYCAT.BufferIn.Cust.temperatureTBM = getThermistorTemp(temperatureADC);

    EASYCAT.BufferIn.Cust.methane = getMethaneConc(methaneADC);

    EASYCAT.BufferIn.Cust.inclinometer0 = inclinometer0ADC * 3 / 32768;
    EASYCAT.BufferIn.Cust.inclinometer1 = inclinometer1ADC * 3 / 32768;
    EASYCAT.BufferIn.Cust.inclinometer2 = inclinometer2ADC * 3 / 32768;

    EASYCAT.BufferIn.Cust.input0 = getPiTemperature();
}

// * Sets up the ADCs with the appropriate addresses
void initADCs()
{
    // ADC0 has addr 0x48
    // ADC1 has addr 0x49

    printf("Setting up ADCs...\n");
    ads0.setGain(GAIN_TWOTHIRDS); // 0.66x gain   +/- 6.144V  1 bit = 3mV
    ads1.setGain(GAIN_TWOTHIRDS); // 0.66x gain   +/- 6.144V  1 bit = 3mV

    ads0.begin();
    ads1.begin();
    printf("ADCs setup.\n");
}

int32_t getThermistorTemp(int32_t mtemperatureADC)
{
    // ADC to voltage
    double Vout = mtemperatureADC * 6.144 / 32768.0; // 1 bit = 3mV, 16 signed bits (TODO: check this is signed)
    // double Vout = mtemperatureADC;

    // Check for zero (not connected)
    if (abs(Vout) < 0.01)
    {
        return 0;
    }

    // voltage to resistance resistance
    double R = 10000;                     // R = 10k
    double Rt = ((VDD * R) / (Vout)) - R; // Vs = 5

    // resistance to temperature
    double r0 = 10000;
    double t0 = 25;
    double b = 3950;
    double t_double = 100 * (1 / (1 / (t0 + 273.15) + log(Rt / r0) / b) - 273.15); // 100 * C

    return (int32_t)t_double;
}

int32_t getMethaneConc(int32_t mmethaneADC)
{
    // ADC to voltage
    double Vout = mmethaneADC * 6.144 / 32768; // 1 bit = 3mV, 16 signed bits (TODO: check this is signed)

    if (Vout == 0)
    {
        return 0;
    }

    // voltage to resistance resistance
    double R = 20000;                     // R = 20k
    double Rm = ((VDD * R) / (Vout)) - R; // Vs = 5

    // resistance to temperature
    double ppm_double = 1021 * pow((Rm / R), -2.7887);
    return (int32_t)ppm_double;
}

int32_t getPiTemperature()
{
    FILE *temperatureFile;
    double T;
    temperatureFile = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    fscanf(temperatureFile, "%lf", &T);
    T /= 10; // To get in 1/100th of a degree
    return T;
}

void printAllADC()
{
    std::cout << "A0-0: " << ads0.readADC_SingleEnded(0) << "\t";
    std::cout << "A0-1: " << ads0.readADC_SingleEnded(1) << "\t";
    std::cout << "A0-2: " << ads0.readADC_SingleEnded(2) << "\t";
    std::cout << "A0-3: " << ads0.readADC_SingleEnded(3) << "\t";

    std::cout << "A1-0: " << ads1.readADC_SingleEnded(0) << "\t";
    std::cout << "A1-1: " << ads1.readADC_SingleEnded(1) << "\t";
    std::cout << "A1-2: " << ads1.readADC_SingleEnded(2) << "\t";
    std::cout << "A1-3: " << ads1.readADC_SingleEnded(3) << "\t";

    std::cout << "\n";
}

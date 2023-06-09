#ifndef E2E62227_CB6B_4D58_B517_089EC0C9C4C2
#define E2E62227_CB6B_4D58_B517_089EC0C9C4C2

#include "tbmcontrolpi_EasyCAT.h"

#define CUSTOM

void readValues();
void initADCs();
int32_t getThermistorTemp(int32_t mtemperatureADC);
int32_t getMethaneConc(int32_t mmethaneADC);
int32_t getPiTemperature();

void printAllADC();

#endif /* E2E62227_CB6B_4D58_B517_089EC0C9C4C2 */

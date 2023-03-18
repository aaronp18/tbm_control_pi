#ifndef E52B2660_6331_4907_926A_34D13AB2ED12
#define E52B2660_6331_4907_926A_34D13AB2ED12
#ifndef CUSTOM_PDO_NAME_H
#define CUSTOM_PDO_NAME_H

//-------------------------------------------------------------------//
//                                                                   //
//     This file has been created by the Easy Configurator tool      //
//                                                                   //
//     Easy Configurator project tbmcontrolpi.prj
//                                                                   //
//-------------------------------------------------------------------//

#define CUST_BYTE_NUM_OUT 37
#define CUST_BYTE_NUM_IN 17
#define TOT_BYTE_NUM_ROUND_OUT 40
#define TOT_BYTE_NUM_ROUND_IN 20

typedef union //---- output buffer ----
{
	uint8_t Byte[TOT_BYTE_NUM_ROUND_OUT];
	struct
	{
		int32_t temperatureTBM;
		int32_t inclionmeter0;
		int32_t inclionmeter1;
		int32_t inclionmeter2;
		int32_t methane;
		int32_t output0;
		int32_t output1;
		int32_t output2;
		int32_t output3;
		uint8_t status;
	} Cust;
} PROCBUFFER_OUT;

typedef union //---- input buffer ----
{
	uint8_t Byte[TOT_BYTE_NUM_ROUND_IN];
	struct
	{
		int32_t input0;
		int32_t input1;
		int32_t input2;
		int32_t input3;
		uint8_t status;
	} Cust;
} PROCBUFFER_IN;

#endif

#endif /* E52B2660_6331_4907_926A_34D13AB2ED12 */

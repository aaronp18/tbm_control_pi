
#ifndef CUSTOM_PDO_NAME_H
#define CUSTOM_PDO_NAME_H

//-------------------------------------------------------------------//
//                                                                   //
//     This file has been created by the Easy Configurator tool      //
//                                                                   //
//     Easy Configurator project tbmcontrolpi.prj
//                                                                   //
//-------------------------------------------------------------------//

#define CUST_BYTE_NUM_OUT 17
#define CUST_BYTE_NUM_IN 37
#define TOT_BYTE_NUM_ROUND_OUT 20
#define TOT_BYTE_NUM_ROUND_IN 40

typedef union //---- output buffer ----
{
	uint8_t Byte[TOT_BYTE_NUM_ROUND_OUT];
	struct
	{
		int32_t output0;
		int32_t output1;
		int32_t output2;
		int32_t output3;
		uint8_t status_out;
	} Cust;
} PROCBUFFER_OUT;

typedef union //---- input buffer ----
{
	uint8_t Byte[TOT_BYTE_NUM_ROUND_IN];
	struct
	{
		int32_t inclinometer0;
		int32_t inclinometer1;
		int32_t inclinometer2;
		int32_t temperatureTBM;
		int32_t methane;
		int32_t input0;
		int32_t input1;
		int32_t input2;
		int32_t input3;
		uint8_t status_in;
	} Cust;
} PROCBUFFER_IN;

#endif

#ifndef C1FC7438_468A_4154_930F_5E2D6EEC349E
#define C1FC7438_468A_4154_930F_5E2D6EEC349E
#ifndef CUSTOM_PDO_NAME_H
#define CUSTOM_PDO_NAME_H

//-------------------------------------------------------------------//
//                                                                   //
//     This file has been created by the Easy Configurator tool      //
//                                                                   //
//     Easy Configurator project tbmcontrolpi.prj
//                                                                   //
//-------------------------------------------------------------------//

#define CUST_BYTE_NUM_OUT 36
#define CUST_BYTE_NUM_IN 16
#define TOT_BYTE_NUM_ROUND_OUT 36
#define TOT_BYTE_NUM_ROUND_IN 16

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
		int32_t input0;
		int32_t input1;
		int32_t input2;
		int32_t input3;
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
	} Cust;
} PROCBUFFER_IN;

#endif

#endif /* C1FC7438_468A_4154_930F_5E2D6EEC349E */

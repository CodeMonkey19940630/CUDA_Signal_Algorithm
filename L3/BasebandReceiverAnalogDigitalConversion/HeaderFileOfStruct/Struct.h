#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	int Total_Size_Of_Receiver_Noise_Data;
	float2 * Radar_Data_Cube_Address;
	float2 * Receiver_Noise_Data_Address;
};
struct ControlParameter
{
	double Receiver_Gain;
	double Band_Width;
	double Noise_Factor;
	double Impedance;
	double Impedance_Temperature;
	float Max_Voltage;
	int ADC_Number;
};
#endif
#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	float * Radar_Float_Data_Cube_Address;
	float2 * Radar_Float2_Data_Cube_Address;
};
struct ControlParameter
{
	double Amplitude;
	double Frequency_Modulation_Coefficient;
	double Jamming_Center_Frequency;
	double Band_Width;
	double Sampling_Frequency_Of_Medium_Frequency;
	double Sampling_Frequency_Of_Band;
	double PRT;
	bool Use_Only_Baseband;
};
#endif
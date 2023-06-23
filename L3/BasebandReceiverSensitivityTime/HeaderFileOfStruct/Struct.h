#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
//,bool Use_Window_Of_Range
struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	float2 * Radar_Data_Cube_Address;
};
struct ControlParameter
{
	float Sensitivity_Time_Control_Coefficient;
	double Window_Of_Range_Right;
	double Window_Of_Range_Left;
	float Pulse_Repetition_Time;
	bool Use_Window_Of_Range;
};
#endif
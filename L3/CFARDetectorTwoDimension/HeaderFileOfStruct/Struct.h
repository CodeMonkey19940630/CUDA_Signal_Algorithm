#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	float2 * Radar_Data_Cube_Address;
	float * CFAR_Absolute_Detected_Data;
	float * CFAR_Reference;
	bool * CFAR_Result;
};
struct ControlParameter
{
	int GuardCell_F;
	int WindowCell_F;
	int GuardCell_S;
	int WindowCell_S;
	double Min_Detect_Factor;
	double Min_Detect_Threshold;
	int CFAR_Method_Select;
};
#endif
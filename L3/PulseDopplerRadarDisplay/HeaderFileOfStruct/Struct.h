#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	float2 * Radar_Data_Cube_Address;
};
struct ControlParameter
{
	int MTIOrder; //Moving_Target_Indicator_OrderMTI½×Êý
};
#endif
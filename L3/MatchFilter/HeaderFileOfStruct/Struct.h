#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	int Total_Size;
	float2 * Baseband_Signal;
	float2 * Baseband_Signal_Kernel;
};
#endif
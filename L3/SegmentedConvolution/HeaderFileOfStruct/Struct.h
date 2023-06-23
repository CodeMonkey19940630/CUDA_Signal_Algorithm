#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int Signal_Length;
	int Kernel_Length;
	float2* Signal;
	float2 *Kernel;
};
#endif
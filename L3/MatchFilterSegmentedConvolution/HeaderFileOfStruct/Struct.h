#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int kenel_padded_size;
	int Pulse_Size;
	float Scale_Factor;
	float2* signal_padded_G;
	float2 *kernel_padded_result_G;
};
#endif
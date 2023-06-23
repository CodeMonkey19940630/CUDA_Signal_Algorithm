#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"

struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	double Signal_Transmit_Time;
	float Baseband_Sampling_Frequency;
	float2 * Radar_Float2_Data_Cube_Address;

};
struct ControlParameter
{
	double Distance_Between_Target_and_Radar;
	double Target_Velocity_Relative_to_Radar;
	double RCS;
	double Receiver_Gain;
	double Transmit_Power;
	double Antenna_Transmit_Gain;
	double Antenna_Receive_Gain;
	double Wave_Length;
	double Impedance;
	float Pulse_Width;
	float Band_Width;
	float PRT;
	int Type;
	float *PRT_List;
	int PRT_List_Size;
};
#endif

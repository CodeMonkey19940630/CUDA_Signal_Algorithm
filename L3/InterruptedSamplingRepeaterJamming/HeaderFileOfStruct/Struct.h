#ifndef STRUCT_H
#define STRUCT_H
#include "vector_types.h"
struct SignalParameter
{
	int Size_D1;
	int Size_D2;
	int Size_D3;
	double Signal_Transmit_Time;
	double Sampling_Transpond_Period;
	float Sampling_Frequency_Of_Medium_Frequency;
	float Baseband_Sampling_Frequency;
	float * Radar_Float_Data_Cube_Address;
	float2 * Radar_Float2_Data_Cube_Address;
};
struct ControlParameter
{
	double Distance_Between_Target_and_Radar;
	double RCS;
	double Target_Velocity_Relative_to_Radar;
	double Receiver_Gain;
	double Transmit_Power;
	double Antenna_Transmit_Gain;
	double Antenna_Receive_Gain;
	double Wave_Length;
	double Impedance;
	double Duty_Factor;
	double Jamming_Amplitude;
	float Medium_Frequency;
	float Pulse_Width;
	float Band_Width;
	float PRT;
	float *PRT_List;
	int PRT_List_Size;
	float * Pulse_Transmit_Interval_Time_List;
	int Pulse_Transmit_Interval_Time_List_Size;
	bool Use_Only_Baseband;
	int Type;
};
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
#include <vector>
//对外暴露void CUDAEchoSignalGeneratorAlgorithmCore()核函数,参数待定。
extern void CUDAEchoSignalGeneratorAlgorithmCore(float2 * Radar_Float2_Data_Cube_Address, int BlockSize, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, double Signal_Transmit_Time, double Distance_Between_Target_and_Radar, double Target_Velocity_Relative_to_Radar, double RCS, double Receiver_Gain, double Transmit_Power, double Antenna_Transmit_Gain, double Antenna_Receive_Gain, double Wave_Length, double Impedance, float Baseband_Sampling_Frequency, float Pulse_Width, float Band_Width, float PRT, float *PRT_List, int PRT_List_Size, int Type);


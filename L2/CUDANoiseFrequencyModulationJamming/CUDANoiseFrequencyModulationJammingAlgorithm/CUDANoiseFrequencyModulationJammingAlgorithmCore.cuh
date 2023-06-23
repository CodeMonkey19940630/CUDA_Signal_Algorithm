#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<curand.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//对外暴露void CUDACFARDetectorTwoDimensionAlgorithmCore()核函数,参数待定。
extern void CUDANoiseFrequencyModulationJammingAlgorithmCore(float * Radar_Float_Data_Cube_Address, float2 * Radar_Float2_Data_Cube_Address, int BlockSize, double Amplitude, double Frequency_Modulation_Coefficient, double Jamming_Center_Frequency, double Band_Width, double Sampling_Frequency_Of_Medium_Frequency, double Sampling_Frequency_Of_Band, double PRT, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Use_Only_Baseband);



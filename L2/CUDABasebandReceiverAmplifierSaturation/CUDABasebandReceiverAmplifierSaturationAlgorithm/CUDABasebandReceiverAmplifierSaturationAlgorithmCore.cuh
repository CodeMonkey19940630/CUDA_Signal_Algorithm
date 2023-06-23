#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<curand.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//对外暴露void CUDACFARDetectorTwoDimensionAlgorithmCore()核函数,参数待定。
extern void CUDABasebandReceiverAmplifierSaturationAlgorithmCore(float2 * Radar_Data_Cube_Address, float2 * Receiver_Noise_Data_Address, int Total_Size_Of_Receiver_Noise_Data, int BlockSize, double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature, float Voltage_Saturation, float Max_Voltage, float Saturation_Factor, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count);


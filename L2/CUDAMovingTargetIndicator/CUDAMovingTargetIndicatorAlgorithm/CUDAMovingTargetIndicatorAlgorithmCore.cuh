#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//¶ÔÍâ±©Â¶__global__ void CUDAMovingTargetIndicatorAlgorithmCore()ºËº¯Êý
extern void CUDAMovingTargetIndicatorAlgorithmCore(float2 * Radar_Data_Cube_Address, int BlockSize, int Moving_Target_Indicator_Order, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count);
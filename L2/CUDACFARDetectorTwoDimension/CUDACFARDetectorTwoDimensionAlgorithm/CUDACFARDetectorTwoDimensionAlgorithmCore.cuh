#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//对外暴露void CUDACFARDetectorTwoDimensionAlgorithmCore()核函数,参数待定。
extern void CUDACFARDetectorTwoDimensionAlgorithmCore(float2 * Radar_Data_Cube_Address, float * CFAR_Absolute_Detected_Data, float * CFAR_Reference, bool * CFAR_Result, int BlockSize, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, int GuardCell_F, int WindowCell_F, int GuardCell_S, int WindowCell_S, double Min_Detect_Factor, double Min_Detect_Threshold, int CFAR_Method_Select);

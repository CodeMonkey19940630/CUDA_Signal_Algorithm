#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<curand.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//对外暴露void CUDACFARDetectorTwoDimensionAlgorithmCore()核函数,参数待定。
extern void CUDABasebandReceiverSensitivityTimeAlgorithmCore(float2 * Radar_Data_Cube_Address, int BlockSize, double Window_Of_Range_Right, double Window_Of_Range_Left, float Sensitivity_Time_Control_Coefficient, float Pulse_Repetition_Time, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Use_Window_Of_Range);


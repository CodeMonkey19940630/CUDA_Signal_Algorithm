#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//���Ⱪ¶__global__ void CUDAPulseDopplerRadarDisplayAlgorithmCore()�˺���
extern void CUDAPulseDopplerRadarDisplayAlgorithmCore(cufftHandle Plan, float2 * Radar_Data_Cube_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count);

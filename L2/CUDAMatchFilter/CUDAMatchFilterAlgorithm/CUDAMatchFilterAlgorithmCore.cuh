#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//对外暴露void CUDAGeographyAndSeaClutterAlgorithmCore()核函数,参数待定。
extern void CUDAMatchFilterAlgorithmCore(cufftHandle Plan_Forward, cufftHandle Plan_Backword, int BlockSize, int Baseband_Total_Size, int ScaleFactor, float2 * Baseband_Signal, float2 * Baseband_Frequency_Domain_Signal_Kernel);
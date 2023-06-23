#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//对外暴露void CUDAMatchFilterSegmentedConvolutionAlgorithmCore()核函数,参数待定。
extern void CUDAMatchFilterSegmentedConvolutionAlgorithmCore(cufftHandle Plan, float2* signal_padded_G, float2 *kernel_padded_result_G, int Kenel_padded_size, int Pulse_Size, float Scale_Factor);

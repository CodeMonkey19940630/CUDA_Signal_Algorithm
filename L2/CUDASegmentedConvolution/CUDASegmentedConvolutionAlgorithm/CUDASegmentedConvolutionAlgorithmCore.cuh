#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
//对外暴露void CUDAMatchFilterSegmentedConvolutionAlgorithmCore()核函数,参数待定。
extern void CUDASegmentedConvolutionAlgorithmCore(cufftHandle Plan, int BlockSize, int Signal_Length, int Kernel_Length, float2* Signal, float2 *Kernel);

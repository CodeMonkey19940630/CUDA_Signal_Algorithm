#ifndef CUDAMATCHFILTERSEGMENTEDCONVOLUTION_H
#define CUDAMATCHFILTERSEGMENTEDCONVOLUTION_H
#ifdef CUDAMATCHFILTERSEGMENTEDCONVOLUTION_EXPORTS
#define CUDA_MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllexport)
#else
#define CUDA_MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDAMatchFilterSegmentedConvolutionNamespace
{
	class CUDA_MATCH_FILTER_SEGMENTED_CONVOLUTION_EXPORTS CUDAMatchFilterSegmentedConvolution
	{
	public:
		CUDAMatchFilterSegmentedConvolution();
		~CUDAMatchFilterSegmentedConvolution();
		void CUFFTResourceAllocation(unsigned int kenel_padded_size);
		void Procedure(float2* signal_padded_G, float2 *kernel_padded_result_G, int Kenel_padded_size, int Pulse_Size, float Scale_Factor);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cufftHandle Plan;
	};
}
#endif
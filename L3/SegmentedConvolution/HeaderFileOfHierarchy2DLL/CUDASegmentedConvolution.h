#ifndef CUDASEGMENTEDCONVOLUTION_H
#define CUDASEGMENTEDCONVOLUTION_H
#ifdef CUDASEGMENTEDCONVOLUTION_EXPORTS
#define CUDA_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllexport)
#else
#define CUDA_SEGMENTED_CONVOLUTION_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDASegmentedConvolutionNamespace
{
	class CUDA_SEGMENTED_CONVOLUTION_EXPORTS CUDASegmentedConvolution
	{
	public:
		CUDASegmentedConvolution();
		~CUDASegmentedConvolution();
		void CUFFTResourceAllocation(int Kernel_Length);
		void Procedure(int Signal_Length, int Kernel_Length, float2* Signal, float2 *Kernel);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		int BlockSize;
		cufftHandle Plan;
		cudaDeviceProp CUDA_Device_Properties;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
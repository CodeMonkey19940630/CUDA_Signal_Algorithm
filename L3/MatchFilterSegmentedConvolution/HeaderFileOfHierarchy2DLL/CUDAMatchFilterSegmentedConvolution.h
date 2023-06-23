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
		//���ģ�鲻�߱���GPU�豸����������������ز���ֻ���յ�GPU�豸�������ã���Ĭ�����á�
		cufftHandle Plan;
	};
}
#endif
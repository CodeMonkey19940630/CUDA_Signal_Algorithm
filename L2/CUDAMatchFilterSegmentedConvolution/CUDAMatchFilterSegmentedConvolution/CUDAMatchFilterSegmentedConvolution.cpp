// CUDAMatchFilterSegmentedConvolution.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDAMatchFilterSegmentedConvolution.h"
#include "../CUDAMatchFilterSegmentedConvolutionAlgorithm/CUDAMatchFilterSegmentedConvolutionAlgorithmCore.cuh"
namespace CUDAMatchFilterSegmentedConvolutionNamespace
{
	unsigned int calcSectionLength(unsigned int N) 
	{
		// Calculate section length M that M + N - 1 is powers of 2 and M is close to N
		unsigned fftlength = 1;
		while ((2 * N) > fftlength) fftlength *= 2;
		return fftlength + 1 - N;
	}
	CUDAMatchFilterSegmentedConvolution::CUDAMatchFilterSegmentedConvolution()
	{
	}
	CUDAMatchFilterSegmentedConvolution::~CUDAMatchFilterSegmentedConvolution()
	{
		cufftResult Result = cufftDestroy(this->Plan);
		if (Result != CUFFT_SUCCESS) {  // check if CUFFT plan is successfully destroyed.
			printf("Error with destroying CUFFT Plan. CUFFT Error code: %d\n", Result);
			return;
		}
	}
	void CUDAMatchFilterSegmentedConvolution::CUFFTResourceAllocation(unsigned int kenel_padded_size)
	{
		unsigned IsectionLength = calcSectionLength(kenel_padded_size);
		unsigned OsectionLength = IsectionLength + kenel_padded_size - 1;
		cufftResult Result = cufftPlan1d(&(this->Plan), OsectionLength, CUFFT_C2C, 1);
		if (Result != CUFFT_SUCCESS) {  // check whether CUFFT plan creation is successful.
			printf("Error with CUFFT plan creation. CUFFT Error code: %d\n", Result);
			return;
		}
	}
	//void CUDAMatchFilterSegmentedConvolution::Procedure()函数只有业务参数。
	void CUDAMatchFilterSegmentedConvolution::Procedure(float2* signal_padded_G, float2 *kernel_padded_result_G, int Kenel_padded_size, int Pulse_Size, float Scale_Factor)
	{
		  CUDAMatchFilterSegmentedConvolutionAlgorithmCore(this->Plan, signal_padded_G,  kernel_padded_result_G, Kenel_padded_size, Pulse_Size, Scale_Factor);
	}
}

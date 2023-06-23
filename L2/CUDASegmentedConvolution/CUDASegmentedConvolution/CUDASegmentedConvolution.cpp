// CUDASegmentedConvolution.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDASegmentedConvolution.h"
#include "../CUDASegmentedConvolutionAlgorithm/CUDASegmentedConvolutionAlgorithmCore.cuh"
namespace CUDASegmentedConvolutionNamespace
{
	int CalculateSectionLength(int Kernel_Length)
	{
		// Calculate section length M that M + N - 1 is powers of 2 and M is close to N
		int FFT_Length = 1;
		while ((2 * Kernel_Length) > FFT_Length)
		{
			FFT_Length *= 2;
		}
		return FFT_Length;
	}
	void CUDASegmentedConvolution::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}

	CUDASegmentedConvolution::CUDASegmentedConvolution()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDASegmentedConvolution::~CUDASegmentedConvolution()
	{
		cufftResult Result = cufftDestroy(this->Plan);
		if (Result != CUFFT_SUCCESS) {  // check if CUFFT plan is successfully destroyed.
			printf("Error with destroying CUFFT Plan. CUFFT Error code: %d\n", Result);
			return;
		}
	}
	void CUDASegmentedConvolution::CUFFTResourceAllocation(int Kernel_Length)
	{
		int FFT_Length = CalculateSectionLength(Kernel_Length);
		cufftPlan1d(&(this->Plan), FFT_Length, CUFFT_C2C, 1);
	}
	//void CUDAMatchFilterSegmentedConvolution::Procedure()函数只有业务参数。
	void CUDASegmentedConvolution::Procedure(int Signal_Length, int Kernel_Length, float2* Signal, float2 *Kernel)
	{
		CUDASegmentedConvolutionAlgorithmCore(this->Plan, this->BlockSize, Signal_Length, Kernel_Length, Signal, Kernel);
	}
}

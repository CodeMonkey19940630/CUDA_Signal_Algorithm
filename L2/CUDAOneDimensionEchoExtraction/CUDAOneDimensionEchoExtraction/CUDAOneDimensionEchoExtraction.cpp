// CUDAOneDimensionEchoExtraction.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDAOneDimensionEchoExtraction.h"
#include "../CUDAOneDimensionEchoExtractionAlgorithm/CUDAOneDimensionEchoExtractionAlgorithmCore.cuh"
namespace CUDAOneDimensionEchoExtractionNamespace
{
	void CUDAOneDimensionEchoExtraction::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDAOneDimensionEchoExtraction::CUDAOneDimensionEchoExtraction()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDAOneDimensionEchoExtraction::~CUDAOneDimensionEchoExtraction()
	{
	}
	//void CUDAEchoSignalGenerator::Procedure()函数只有业务参数。
	void CUDAOneDimensionEchoExtraction::Procedure(std::vector<std::pair<int, int>> &Echo_Begin_End_Index_Pair_Result, std::vector<std::pair<int, float>> &Max_Result, bool *CFAR_Result_Address, float *CFAR_Input_Absolute_Address, int Count_Of_Sampling_Point_Of_Monopulse)
	{
		CUDAOneDimensionEchoExtractionAlgorithmCore(Echo_Begin_End_Index_Pair_Result, Max_Result, CFAR_Result_Address, CFAR_Input_Absolute_Address, Count_Of_Sampling_Point_Of_Monopulse, this->BlockSize);
	}
}




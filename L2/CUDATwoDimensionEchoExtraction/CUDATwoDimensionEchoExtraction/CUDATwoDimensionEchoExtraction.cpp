// CUDATwoDimensionEchoExtraction.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDATwoDimensionEchoExtraction.h"
#include "../CUDATwoDimensionEchoExtractionAlgorithm/CUDATwoDimensionEchoExtractionAlgorithmCore.h"
namespace CUDATwoDimensionEchoExtractionNamespace
{
	void CUDATwoDimensionEchoExtraction::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDATwoDimensionEchoExtraction::CUDATwoDimensionEchoExtraction()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDATwoDimensionEchoExtraction::~CUDATwoDimensionEchoExtraction()
	{
	}
	//void CUDAEchoSignalGenerator::Procedure()函数只有业务参数。
	void CUDATwoDimensionEchoExtraction::Procedure(std::vector<std::pair<int, int>> &Up, std::vector<std::pair<int, int>> &Down, std::vector<std::pair<int, int>> &Left, std::vector<std::pair<int, int>> &Right, std::vector<std::pair<int, float>> &Max_Result, bool * CFAR_Result_Address, float *CFAR_Input_Absolute_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group)
	{
		CUDATwoDimensionEchoExtractionAlgorithmCore(Up, Down, Left, Right, Max_Result, CFAR_Result_Address, CFAR_Input_Absolute_Address, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, this->BlockSize);
	}
}




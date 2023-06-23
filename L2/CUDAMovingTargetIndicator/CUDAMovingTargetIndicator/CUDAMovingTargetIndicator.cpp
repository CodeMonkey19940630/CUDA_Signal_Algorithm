// CUDAMovingTargetIndicator.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "CUDAMovingTargetIndicator.h"
#include "../CUDAMovingTargetIndicatorAlgorithm/CUDAMovingTargetIndicatorAlgorithmCore.cuh"
namespace CUDAMovingTargetIndicatorNamespace
{
	void CUDAMovingTargetIndicator::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDAMovingTargetIndicator::CUDAMovingTargetIndicator()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDAMovingTargetIndicator::~CUDAMovingTargetIndicator()
	{

	}
	void CUDAMovingTargetIndicator::Procedure(float2 * Radar_Data_Cube_Address, int Moving_Target_Indicator_Order, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count)
	{
		CUDAMovingTargetIndicatorAlgorithmCore(Radar_Data_Cube_Address, this->BlockSize, Moving_Target_Indicator_Order, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count);
	}
}


// CUDACFARDetectorTwoDimension.cpp : 定义 DLL 应用程序的导出函数
#include "stdafx.h"
#include "CUDACFARDetectorTwoDimension.h"
#include "../CUDACFARDetectorTwoDimensionAlgorithm/CUDACFARDetectorTwoDimensionAlgorithmCore.cuh"
namespace CUDACFARDetectorTwoDimensionNamespace
{
	void CUDACFARDetectorTwoDimension::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDACFARDetectorTwoDimension::CUDACFARDetectorTwoDimension()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDACFARDetectorTwoDimension::~CUDACFARDetectorTwoDimension()
	{
	}
	//void CUDAGeographyAndSeaClutter::Procedure()函数只有业务参数。
	void CUDACFARDetectorTwoDimension::Procedure(float2 * Radar_Data_Cube_Address, 
		float * CFAR_Absolute_Detected_Data, 
		float * CFAR_Reference, 
		bool * CFAR_Result, 
		int Count_Of_Sampling_Point_Of_Monopulse, 
		int Count_Of_Pulse_Group, 
		int Antenna_Chanel_Count, 
		int GuardCell_F, 
		int WindowCell_F, 
		int GuardCell_S, 
		int WindowCell_S, 
		double Min_Detect_Factor, 
		double Min_Detect_Threshold, 
		int CFAR_Method_Select)
	{
		//调用CUDACFARDetectorTwoDimensionAlgorithmCore函数。
		CUDACFARDetectorTwoDimensionAlgorithmCore(Radar_Data_Cube_Address, 
			CFAR_Absolute_Detected_Data, 
			CFAR_Reference, 
			CFAR_Result, 
			this->BlockSize, 
			Count_Of_Sampling_Point_Of_Monopulse, 
			Count_Of_Pulse_Group, 
			Antenna_Chanel_Count, 
			GuardCell_F, 
			WindowCell_F, 
			GuardCell_S,
			WindowCell_S, 
			Min_Detect_Factor, 
			Min_Detect_Threshold, 
			CFAR_Method_Select);
	}
}



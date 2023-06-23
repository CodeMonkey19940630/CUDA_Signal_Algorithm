// CUDANoiseFrequencyModulationJamming.cpp : 定义 DLL 应用程序的导出函数。

#include "stdafx.h"
#include "CUDANoiseFrequencyModulationJamming.h"
#include "../CUDANoiseFrequencyModulationJammingAlgorithm/CUDANoiseFrequencyModulationJammingAlgorithmCore.cuh"
namespace CUDANoiseFrequencyModulationJammingNamespace
{
	void CUDANoiseFrequencyModulationJamming::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDANoiseFrequencyModulationJamming::CUDANoiseFrequencyModulationJamming()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDANoiseFrequencyModulationJamming::~CUDANoiseFrequencyModulationJamming()
	{
	}
	//void CUDAGeographyAndSeaClutter::Procedure()函数只有业务参数。
	void CUDANoiseFrequencyModulationJamming::Procedure(float * Radar_Float_Data_Cube_Address, float2 * Radar_Float2_Data_Cube_Address, double Amplitude, double Frequency_Modulation_Coefficient, double Jamming_Center_Frequency, double Band_Width, double Sampling_Frequency_Of_Medium_Frequency, double Sampling_Frequency_Of_Band, double PRT, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Use_Only_Baseband)
	{
		//调用CUDANoiseFrequencyModulationJammingAlgorithmCore函数。
		CUDANoiseFrequencyModulationJammingAlgorithmCore(Radar_Float_Data_Cube_Address, Radar_Float2_Data_Cube_Address, this->BlockSize, Amplitude, Frequency_Modulation_Coefficient, Jamming_Center_Frequency, Band_Width, Sampling_Frequency_Of_Medium_Frequency, Sampling_Frequency_Of_Band, PRT, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count, Use_Only_Baseband);

	}
}






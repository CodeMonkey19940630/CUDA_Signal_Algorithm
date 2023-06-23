// CUDABasebandReceiverAmplifierSaturation.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDABasebandReceiverAmplifierSaturation.h"
#include "../CUDABasebandReceiverAmplifierSaturationAlgorithm/CUDABasebandReceiverAmplifierSaturationAlgorithmCore.cuh"
namespace CUDABasebandReceiverAmplifierSaturationNamespace
{
	void CUDABasebandReceiverAmplifierSaturation::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDABasebandReceiverAmplifierSaturation::CUDABasebandReceiverAmplifierSaturation()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDABasebandReceiverAmplifierSaturation::~CUDABasebandReceiverAmplifierSaturation()
	{
	}
	//void CUDAGeographyAndSeaClutter::Procedure()函数只有业务参数。
	void CUDABasebandReceiverAmplifierSaturation::Procedure(float2 * Radar_Data_Cube_Address, float2 * Receiver_Noise_Data_Address, int Total_Size_Of_Receiver_Noise_Data, double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature, float Voltage_Saturation, float Max_Voltage, float Saturation_Factor, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count)
	{
		//调用CUDABasebandReceiverAlgorithmCore()函数。
		CUDABasebandReceiverAmplifierSaturationAlgorithmCore(Radar_Data_Cube_Address, Receiver_Noise_Data_Address, Total_Size_Of_Receiver_Noise_Data, this->BlockSize, Receiver_Gain, Band_Width, Noise_Factor, Impedance,Impedance_Temperature, Voltage_Saturation,Max_Voltage, Saturation_Factor, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count);
	}
}









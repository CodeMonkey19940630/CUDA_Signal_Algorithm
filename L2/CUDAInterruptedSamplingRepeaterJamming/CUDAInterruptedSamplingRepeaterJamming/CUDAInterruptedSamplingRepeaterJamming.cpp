// CUDAInterruptedSamplingRepeaterJamming.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDAInterruptedSamplingRepeaterJamming.h"
#include "../CUDAInterruptedSamplingRepeaterJammingAlgorithm/CUDAInterruptedSamplingRepeaterJammingAlgorithmCore.cuh"
namespace CUDAInterruptedSamplingRepeaterJammingNamespace
{
	void CUDAInterruptedSamplingRepeaterJamming::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDAInterruptedSamplingRepeaterJamming::CUDAInterruptedSamplingRepeaterJamming()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDAInterruptedSamplingRepeaterJamming::~CUDAInterruptedSamplingRepeaterJamming()
	{
	}
	//void CUDAInterruptedSamplingRepeaterJamming::Procedure()函数只有业务参数。
	void CUDAInterruptedSamplingRepeaterJamming::Procedure(float * Radar_Float_Data_Cube_Address, float2 * Radar_Float2_Data_Cube_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, double Distance_Between_Target_and_Radar, double RCS, double Target_Velocity_Relative_to_Radar, double Receiver_Gain, double Transmit_Power, double Antenna_Transmit_Gain, double Antenna_Receive_Gain, double Wave_Length, double Impedance, double Signal_Transmit_Time, double Duty_Factor, double Jamming_Amplitude, double Sampling_Transpond_Period, float Sampling_Frequency_Of_Medium_Frequency, float Baseband_Sampling_Frequency, float Medium_Frequency, float Pulse_Width, float Band_Width, float PRT, float *PRT_List, int PRT_List_Size, float * Pulse_Transmit_Interval_Time_List, int Pulse_Transmit_Interval_Time_List_Size, bool Use_Only_Baseband, int Type)
	{
		CUDAInterruptedSamplingRepeaterJammingAlgorithmCore(Radar_Float_Data_Cube_Address, Radar_Float2_Data_Cube_Address, this->BlockSize, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count, Distance_Between_Target_and_Radar, RCS, Target_Velocity_Relative_to_Radar, Receiver_Gain, Transmit_Power, Antenna_Transmit_Gain, Antenna_Receive_Gain, Wave_Length, Impedance, Signal_Transmit_Time, Duty_Factor, Jamming_Amplitude, Sampling_Transpond_Period, Sampling_Frequency_Of_Medium_Frequency, Baseband_Sampling_Frequency,Medium_Frequency, Pulse_Width, Band_Width, PRT, PRT_List, PRT_List_Size, Pulse_Transmit_Interval_Time_List, Pulse_Transmit_Interval_Time_List_Size, Use_Only_Baseband, Type);
	}
}






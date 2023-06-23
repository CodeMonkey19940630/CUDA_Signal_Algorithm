// CUDAEchoSignalGenerator.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDAEchoSignalGenerator.h"
#include "../CUDAEchoSignalGeneratorAlgorithm/CUDAEchoSignalGeneratorAlgorithmCore.cuh"
namespace CUDAEchoSignalGeneratorNamespace
{
	void CUDAEchoSignalGenerator::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDAEchoSignalGenerator::CUDAEchoSignalGenerator()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDAEchoSignalGenerator::~CUDAEchoSignalGenerator()
	{
	}
	//void CUDAEchoSignalGenerator::Procedure()函数只有业务参数。
	void CUDAEchoSignalGenerator::Procedure(float2 * Radar_Float2_Data_Cube_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, double Signal_Transmit_Time, double Distance_Between_Target_and_Radar, double Target_Velocity_Relative_to_Radar, double RCS, double Receiver_Gain, double Transmit_Power, double Antenna_Transmit_Gain, double Antenna_Receive_Gain, double Wave_Length, double Impedance, float Baseband_Sampling_Frequency, float Pulse_Width, float Band_Width, float PRT, float *PRT_List, int PRT_List_Size, int Type)
	{
		//调用CUDAEchoSignalGeneratorAlgorithmCore函数。
		 CUDAEchoSignalGeneratorAlgorithmCore(Radar_Float2_Data_Cube_Address, this->BlockSize, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count, Signal_Transmit_Time, Distance_Between_Target_and_Radar, Target_Velocity_Relative_to_Radar, RCS, Receiver_Gain, Transmit_Power, Antenna_Transmit_Gain, Antenna_Receive_Gain, Wave_Length, Impedance, Baseband_Sampling_Frequency, Pulse_Width, Band_Width, PRT, PRT_List, PRT_List_Size, Type);

	}
}



#ifndef CUDAECHOSIGNALGENERATOR_H
#define CUDAECHOSIGNALGENERATOR_H
#ifdef CUDAECHOSIGNALGENERATOR_EXPORTS
#define CUDA_ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllexport)
#else
#define CUDA_ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDAEchoSignalGeneratorNamespace
{
	class CUDA_ECHO_SIGNAL_GENERATOR_EXPORTS CUDAEchoSignalGenerator
	{
	public:
		CUDAEchoSignalGenerator();
		~CUDAEchoSignalGenerator();
		void Procedure(float2 * Radar_Float2_Data_Cube_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, double Signal_Transmit_Time, double Distance_Between_Target_and_Radar, double Target_Velocity_Relative_to_Radar, double RCS, double Receiver_Gain, double Transmit_Power, double Antenna_Transmit_Gain, double Antenna_Receive_Gain, double Wave_Length, double Impedance, float Baseband_Sampling_Frequency, float Pulse_Width, float Band_Width, float PRT, float *PRT_List, int PRT_List_Size, int Type);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
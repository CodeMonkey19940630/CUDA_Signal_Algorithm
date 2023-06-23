#ifndef CUDANOISEFREQUENCYMODULATIONJAMMING_H
#define CUDANOISEFREQUENCYMODULATIONJAMMING_H
#ifdef CUDANOISEFREQUENCYMODULATIONJAMMING_EXPORTS
#define CUDA_NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS __declspec(dllexport)
#else
#define CUDA_NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDANoiseFrequencyModulationJammingNamespace
{
	class CUDA_NOISE_FREQUENCY_MODULATION_JAMMING_EXPORTS CUDANoiseFrequencyModulationJamming
	{
	public:
		CUDANoiseFrequencyModulationJamming();
		~CUDANoiseFrequencyModulationJamming();
		void Procedure(float * Radar_Float_Data_Cube_Address, float2 * Radar_Float2_Data_Cube_Address, double Amplitude, double Frequency_Modulation_Coefficient, double Jamming_Center_Frequency, double Band_Width, double Sampling_Frequency_Of_Medium_Frequency, double Sampling_Frequency_Of_Band, double PRT, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Use_Only_Baseband);

	private:
		//���ģ�鲻�߱���GPU�豸����������������ز���ֻ���յ�GPU�豸�������ã���Ĭ�����á�
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
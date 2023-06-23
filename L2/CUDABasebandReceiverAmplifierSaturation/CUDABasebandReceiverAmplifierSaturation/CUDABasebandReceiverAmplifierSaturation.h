#ifndef CUDABASEBANDRECEIVERAMPLIFIERSATURATION_H
#define CUDABASEBANDRECEIVERAMPLIFIERSATURATION_H
#ifdef CUDABASEBANDRECEIVERAMPLIFIERSATURATION_EXPORTS
#define CUDA_BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS __declspec(dllexport)
#else
#define CUDA_BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDABasebandReceiverAmplifierSaturationNamespace
{
	class CUDA_BASEBAND_RECEIVER_AMPLIFIER_SATURATION_EXPORTS CUDABasebandReceiverAmplifierSaturation
	{
	public:
		CUDABasebandReceiverAmplifierSaturation();
		~CUDABasebandReceiverAmplifierSaturation();
		void Procedure(float2 * Radar_Data_Cube_Address, float2 * Receiver_Noise_Data_Address, int Total_Size_Of_Receiver_Noise_Data, double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature, float Voltage_Saturation, float Max_Voltage, float Saturation_Factor, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count);
	private:
		//���ģ�鲻�߱���GPU�豸����������������ز���ֻ���յ�GPU�豸�������ã���Ĭ�����á�
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
#ifndef CUDABASEBANDRECEIVERANALOGDIGITALCONVERSION_H
#define CUDABASEBANDRECEIVERANALOGDIGITALCONVERSION_H
#ifdef CUDABASEBANDRECEIVERANALOGDIGITALCONVERSION_EXPORTS
#define CUDA_BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllexport)
#else
#define CUDA_BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDABasebandReceiverAnalogDigitalConversionNamespace
{
	class CUDA_BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS CUDABasebandReceiverAnalogDigitalConversion
	{
	public:
		CUDABasebandReceiverAnalogDigitalConversion();
		~CUDABasebandReceiverAnalogDigitalConversion();
		void Procedure(float2 * Radar_Data_Cube_Address, float2 * Receiver_Noise_Data_Address, int Total_Size_Of_Receiver_Noise_Data, double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature, float Max_Voltage, int ADC_Number, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
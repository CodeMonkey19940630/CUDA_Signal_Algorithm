#ifndef CUDABASEBANDRECEIVER_H
#define CUDABASEBANDRECEIVER_H
#ifdef CUDABASEBANDRECEIVER_EXPORTS
#define CUDA_BASEBAND_RECEIVER_EXPORTS __declspec(dllexport)
#else
#define CUDA_BASEBAND_RECEIVER_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDABasebandReceiverNamespace
{
	class CUDA_BASEBAND_RECEIVER_EXPORTS CUDABasebandReceiver
	{
	public:
		CUDABasebandReceiver();
		~CUDABasebandReceiver();
		void Procedure(float2 * Radar_Data_Cube_Address, float2 * Receiver_Noise_Data_Address, int Total_Size_Of_Receiver_Noise_Data, int BlockSize, double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature, float Sensitivity_Time_Control_Coefficient, double Window_Of_Range_Right, double Window_Of_Range_Left, double Logarithmic_Amplifier_Voltage, float Voltage_Saturation, float Max_Voltage, float Saturation_Factor, int ADC_Number, float Pulse_Repetition_Time, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Sensitivity_Time_Control, bool Use_Window_Of_Range, bool Automatic_Gain_Control, bool Logarithmic_Amplifier, bool Amplifier_Saturation, bool Analog_Digital_Conversion);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
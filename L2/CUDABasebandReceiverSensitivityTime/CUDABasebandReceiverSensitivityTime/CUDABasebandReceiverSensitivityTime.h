#ifndef CUDABASEBANDRECEIVERSENSITIVITYTIME_H
#define CUDABASEBANDRECEIVERSENSITIVITYTIME_H
#ifdef CUDABASEBANDRECEIVERSENSITIVITYTIME_EXPORTS
#define CUDA_BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS __declspec(dllexport)
#else
#define CUDA_BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDABasebandReceiverSensitivityTimeNamespace
{
	class CUDA_BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS CUDABasebandReceiverSensitivityTime
	{
	public:
		CUDABasebandReceiverSensitivityTime();
		~CUDABasebandReceiverSensitivityTime();
		void Procedure(float2 * Radar_Data_Cube_Address, double Window_Of_Range_Right, double Window_Of_Range_Left, float Sensitivity_Time_Control_Coefficient, float Pulse_Repetition_Time, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Use_Window_Of_Range);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
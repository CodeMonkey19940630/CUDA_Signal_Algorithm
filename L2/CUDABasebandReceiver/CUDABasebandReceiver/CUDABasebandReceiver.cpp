// CUDABasebandReceiver.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDABasebandReceiver.h"
#include "../CUDABasebandReceiverAlgorithm/CUDABasebandReceiverAlgorithmCore.cuh"
namespace CUDABasebandReceiverNamespace
{
	void CUDABasebandReceiver::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDABasebandReceiver::CUDABasebandReceiver()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDABasebandReceiver::~CUDABasebandReceiver()
	{
	}
	//void CUDAGeographyAndSeaClutter::Procedure()函数只有业务参数。
	void CUDABasebandReceiver::Procedure(float2 * Radar_Data_Cube_Address, float2 * Receiver_Noise_Data_Address, int Total_Size_Of_Receiver_Noise_Data, int BlockSize, double Receiver_Gain, double Band_Width, double Noise_Factor, double Impedance, double Impedance_Temperature, float Sensitivity_Time_Control_Coefficient, double Window_Of_Range_Right, double Window_Of_Range_Left, double Logarithmic_Amplifier_Voltage, float Voltage_Saturation, float Max_Voltage, float Saturation_Factor, int ADC_Number, float Pulse_Repetition_Time, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Sensitivity_Time_Control, bool Use_Window_Of_Range, bool Automatic_Gain_Control, bool Logarithmic_Amplifier, bool Amplifier_Saturation, bool Analog_Digital_Conversion)
	{
		//调用CUDABasebandReceiverAlgorithmCore()函数。
		CUDABasebandReceiverAlgorithmCore(Radar_Data_Cube_Address, Receiver_Noise_Data_Address, Total_Size_Of_Receiver_Noise_Data, this->BlockSize, Receiver_Gain, Band_Width, Noise_Factor, Impedance, Impedance_Temperature, Sensitivity_Time_Control_Coefficient, Window_Of_Range_Right, Window_Of_Range_Left, Logarithmic_Amplifier_Voltage, Voltage_Saturation, Max_Voltage, Saturation_Factor, ADC_Number, Pulse_Repetition_Time, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count, Sensitivity_Time_Control, Use_Window_Of_Range, Automatic_Gain_Control, Logarithmic_Amplifier, Amplifier_Saturation, Analog_Digital_Conversion);
	}
}




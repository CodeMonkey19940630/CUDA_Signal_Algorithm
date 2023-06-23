// CUDABasebandReceiverSensitivityTime.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CUDABasebandReceiverSensitivityTime.h"
#include "../CUDABasebandReceiverSensitivityTimeAlgorithm/CUDABasebandReceiverSensitivityTimeAlgorithmCore.cuh"
namespace CUDABasebandReceiverSensitivityTimeNamespace
{
	void CUDABasebandReceiverSensitivityTime::CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_Device_Index)
	{
		cudaError_t CudaError = cudaGetDeviceProperties(CUDA_Device_Properties, CUDA_Device_Index);
		this->BlockSize = CUDA_Device_Properties->maxThreadsPerBlock;
	}
	CUDABasebandReceiverSensitivityTime::CUDABasebandReceiverSensitivityTime()
	{
		CUDAResourceAllocation(&(this->CUDA_Device_Properties), 0);
	}
	CUDABasebandReceiverSensitivityTime::~CUDABasebandReceiverSensitivityTime()
	{
	}
	//void CUDAGeographyAndSeaClutter::Procedure()函数只有业务参数。
	void CUDABasebandReceiverSensitivityTime::Procedure(float2 * Radar_Data_Cube_Address, double Window_Of_Range_Right, double Window_Of_Range_Left, float Sensitivity_Time_Control_Coefficient, float Pulse_Repetition_Time, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, bool Use_Window_Of_Range)
	{
		//调用CUDABasebandReceiverAlgorithmCore()函数。
		CUDABasebandReceiverSensitivityTimeAlgorithmCore(Radar_Data_Cube_Address, this-> BlockSize, Window_Of_Range_Right, Window_Of_Range_Left, Sensitivity_Time_Control_Coefficient, Pulse_Repetition_Time, Count_Of_Sampling_Point_Of_Monopulse, Count_Of_Pulse_Group, Antenna_Chanel_Count, Use_Window_Of_Range);

    }
}







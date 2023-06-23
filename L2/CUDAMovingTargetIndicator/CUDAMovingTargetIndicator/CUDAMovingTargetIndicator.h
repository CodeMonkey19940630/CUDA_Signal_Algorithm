#ifndef CUDAMOVINGTARGETINDICATOR_H
#define CUDAMOVINGTARGETINDICATOR_H
#ifdef CUDAMOVINGTARGETINDICATOR_EXPORTS
#define CUDA_MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllexport)
#else
#define CUDA_MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDAMovingTargetIndicatorNamespace
{
	class CUDA_MOVING_TARGET_INDICATOR_EXPORTS CUDAMovingTargetIndicator
	{
		public:
			CUDAMovingTargetIndicator();
			~CUDAMovingTargetIndicator();
			void Procedure(float2 * Radar_Data_Cube_Address, int Moving_Target_Indicator_Order, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count);
		private:
			//���ģ�鲻�߱���GPU�豸����������������ز���ֻ���յ�GPU�豸�������ã���Ĭ�����á�
			cudaDeviceProp CUDA_Device_Properties;
			int BlockSize;
			void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
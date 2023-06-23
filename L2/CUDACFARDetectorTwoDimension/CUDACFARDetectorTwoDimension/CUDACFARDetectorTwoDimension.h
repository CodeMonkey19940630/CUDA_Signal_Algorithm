#ifndef CUDAFARDETECTORTWODIMENSION_H
#define CUDAFARDETECTORTWODIMENSION_H
#ifdef CUDACFARDETECTORTWODIMENSION_EXPORTS
#define CUDA_CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllexport)
#else
#define CUDA_CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDACFARDetectorTwoDimensionNamespace
{
	class CUDA_CFAR_DETECTOR_TWO_DIMENSION_EXPORTS CUDACFARDetectorTwoDimension
	{
	public:
		CUDACFARDetectorTwoDimension();
		~CUDACFARDetectorTwoDimension();
		void Procedure(float2 * Radar_Data_Cube_Address, float * CFAR_Absolute_Detected_Data, float * CFAR_Reference, bool * CFAR_Result, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, int GuardCell_F, int WindowCell_F, int GuardCell_S, int WindowCell_S, double Min_Detect_Factor, double Min_Detect_Threshold, int CFAR_Method_Select);
	private:
		//���ģ�鲻�߱���GPU�豸����������������ز���ֻ���յ�GPU�豸�������ã���Ĭ�����á�
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
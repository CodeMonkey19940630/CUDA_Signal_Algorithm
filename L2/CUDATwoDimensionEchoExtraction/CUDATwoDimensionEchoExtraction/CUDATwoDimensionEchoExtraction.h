#ifndef CUDATWODIMENSIONECHOEXTRACTION_H
#define CUDATWODIMENSIONECHOEXTRACTION_H
#ifdef CUDATWODIMENSIONECHOEXTRACTION_EXPORTS
#define CUDA_TWO_DIMENSION_ECHO_EXTRACTION_EXPORTS __declspec(dllexport)
#else
#define CUDA_TWO_DIMENSION_ECHO_EXTRACTION_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
#include <vector>
#include <utility>
namespace CUDATwoDimensionEchoExtractionNamespace
{
	class CUDA_TWO_DIMENSION_ECHO_EXTRACTION_EXPORTS CUDATwoDimensionEchoExtraction
	{
	public:
		CUDATwoDimensionEchoExtraction();
		~CUDATwoDimensionEchoExtraction();
		void Procedure(std::vector<std::pair<int, int>> &Up, std::vector<std::pair<int, int>> &Down, std::vector<std::pair<int, int>> &Left, std::vector<std::pair<int, int>> &Right, std::vector<std::pair<int, float>> &Max_Result, bool * CFAR_Result_Address, float *CFAR_Input_Absolute_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group);
	private:
		//���ģ�鲻�߱���GPU�豸����������������ز���ֻ���յ�GPU�豸�������ã���Ĭ�����á�
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
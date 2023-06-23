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
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
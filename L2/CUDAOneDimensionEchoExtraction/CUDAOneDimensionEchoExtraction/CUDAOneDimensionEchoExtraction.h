#ifndef CUDAONEDIMENSIONECHOEXTRACTION_H
#define CUDAONEDIMENSIONECHOEXTRACTION_H
#ifdef CUDAONEDIMENSIONECHOEXTRACTION_EXPORTS
#define CUDA_ONE_DIMENSION_ECHO_EXTRACTION_EXPORTS __declspec(dllexport)
#else
#define CUDA_ONE_DIMENSION_ECHO_EXTRACTION_EXPORTS __declspec(dllimport)
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
namespace CUDAOneDimensionEchoExtractionNamespace
{
	class CUDA_ONE_DIMENSION_ECHO_EXTRACTION_EXPORTS CUDAOneDimensionEchoExtraction
	{
	public:
		CUDAOneDimensionEchoExtraction();
		~CUDAOneDimensionEchoExtraction();
		void Procedure(std::vector<std::pair<int, int>> &Echo_Begin_End_Index_Pair_Result, std::vector<std::pair<int, float>> &Max_Result, bool *CFAR_Result_Address, float *CFAR_Input_Absolute_Address, int Count_Of_Sampling_Point_Of_Monopulse);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
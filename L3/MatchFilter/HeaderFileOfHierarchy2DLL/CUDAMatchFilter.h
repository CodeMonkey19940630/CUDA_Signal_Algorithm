#ifndef CUDAMATCHFILTER_H
#define CUDAMATCHFILTER_H
#ifdef CUDAMATCHFILTER_EXPORTS
#define CUDA_MATCH_FILTER_EXPORTS __declspec(dllexport)
#else
#define CUDA_MATCH_FILTER_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDAMatchFilterNamespace
{
	class CUDA_MATCH_FILTER_EXPORTS CUDAMatchFilter
	{
	public:
		CUDAMatchFilter();
		~CUDAMatchFilter();
		void CUFFTResourceAllocation(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count);
		void Procedure(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, int Baseband_Total_Size, int ScaleFactor, float2 * Baseband_Signal, float2 * Baseband_Signal_Kernel);
	private:
		//因该模块不具备多GPU设备运行能力，所以相关参数只依照单GPU设备进行设置，即默认设置。
		cudaDeviceProp CUDA_Device_Properties;
		int BlockSize;
		cufftHandle Plan_Forward;
		cufftHandle Plan_Backword;
		int Rank;
		int N[1];
		int Inembed[1];
		int Istride;
		int Idist;
		int Onembed[1];
		int Ostride;
		int Odist;
		cufftType Type;
		int Batch;
		void CUDAResourceAllocation(cudaDeviceProp * CUDA_Device_Properties, int CUDA_device_Index);
	};
}
#endif
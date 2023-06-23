#ifndef CUDAPULSEDOPPLERLERRADARDISPLAY_H
#define CUDAPULSEDOPPLERLERRADARDISPLAY_H
#ifdef CUDAPULSEDOPPLERRADARDISPLAY_EXPORTS
#define CUDA_PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllexport)
#else
#define CUDA_PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include<cufft.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
namespace CUDAPulseDopplerRadarDisplayNamespace
{
	class CUDA_PULSE_DOPPLER_RADAR_DISPLAY_EXPORTS CUDAPulseDopplerRadarDisplay
	{
		public:
			CUDAPulseDopplerRadarDisplay();
			~CUDAPulseDopplerRadarDisplay();
			void CUFFTResourceAllocation(int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Moving_Target_Indicator_Order);
			void Procedure(float2 * Radar_Data_Cube_Address, int Count_Of_Sampling_Point_Of_Monopulse, int Count_Of_Pulse_Group, int Antenna_Chanel_Count, int Moving_Target_Indicator_Order);
		private:
			//不知道plan是否也应该在这创建。
			cufftHandle Plan;
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
	};
}
#endif
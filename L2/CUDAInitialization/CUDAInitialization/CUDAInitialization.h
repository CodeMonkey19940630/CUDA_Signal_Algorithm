#ifndef CUDAINIRIALIZATION_H
#define CUDAINIRIALIZATION_H
#ifdef CUDAINITIALIZATION_EXPORTS
#define CUDA_INITIALIZATION_EXPORTS __declspec(dllexport)
#else
#define CUDA_INITIALIZATION_EXPORTS __declspec(dllimport)
#endif
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include<device_functions.h>
#include<vector_types.h>
#include"../CUDAHeaderFile/helper_string.h"
#include"../CUDAHeaderFile/helper_cuda.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "../HeaderFileOfStruct/Struct.h"
namespace CUDAInitializationNamespace
{
	class CUDA_INITIALIZATION_EXPORTS CUDAInitialization
	{
	public:
		CUDAInitialization();
		~CUDAInitialization();
		//void Procedure(std::string Function_name, int Size_D1, int Size_D2, int Size_D3);
		//void Procedure(std::string Function_name, float * Destination, float * Source);
		//void Procedure(std::string Function_name, float2 * Destination, complex * Source);
		//void Procedure(std::string Function_name, complex * Destination, float2 * Source);
	//private:
		int Kernel_Size_D1;
		int Kernel_Size_D2;
		int Kernel_Size_D3;
		float * Kernel_Float_In_CPU;
		complex * Kernel_Float2_In_CPU;
		float * Kernel_Float_In_GPU;
		float2 * Kernel_Float2_In_GPU;
		void InitializeKernelFloat_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelFloat_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void CopyKernelFloatDataFromHostToDecive(float * Destination, float * Source);
		void CopyKernelFloatDataFromDeciveToHost(float * Destination, float * Source);
		void CopyKernelFloat2DataFromHostToDecive(float2 * Destination, complex * Source);
		void CopyKernelFloat2DataFromDeciveToHost(complex * Destination, float2 * Source);

		int Kernel_Padded_Size_D1;
		int Kernel_Padded_Size_D2;
		int Kernel_Padded_Size_D3;
		float * Kernel_Padded_Float_In_CPU;
		complex * Kernel_Padded_Float2_In_CPU;
		float * Kernel_Padded_Float_In_GPU;
		float2 * Kernel_Padded_Float2_In_GPU;
		void InitializeKernelPaddedFloat_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelPaddedFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelPaddedFloat_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelPaddedFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void CopyKernelPaddedFloatDataFromHostToDecive(float * Destination, float * Source);
		void CopyKernelPaddedFloatDataFromDeciveToHost(float * Destination, float * Source);
		void CopyKernelPaddedFloat2DataFromHostToDecive(float2 * Destination, complex * Source);
		void CopyKernelPaddedFloat2DataFromDeciveToHost(complex * Destination, float2 * Source);

		int Kernel_Padded_Result_Size_D1;
		int Kernel_Padded_Result_Size_D2;
		int Kernel_Padded_Result_Size_D3;
		float * Kernel_Padded_Result_Float_In_CPU;
		complex * Kernel_Padded_Result_Float2_In_CPU;
		float * Kernel_Padded_Result_Float_In_GPU;
		float2 * Kernel_Padded_Result_Float2_In_GPU;
		void InitializeKernelPaddedResultFloat_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelPaddedResultFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelPaddedResultFloat_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeKernelPaddedResultFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void CopyKernelPaddedResultFloatDataFromHostToDecive(float * Destination, float * Source);
		void CopyKernelPaddedResultFloatDataFromDeciveToHost(float * Destination, float * Source);
		void CopyKernelPaddedResultFloat2DataFromHostToDecive(float2 * Destination, complex * Source);
		void CopyKernelPaddedResultFloat2DataFromDeciveToHost(complex * Destination, float2 * Source);

		int Signal_Size_D1;
		int Signal_Size_D2;
		int Signal_Size_D3;
		float * Signal_Float_In_CPU;
		complex * Signal_Float2_In_CPU;
		float * Signal_Float_In_GPU;
		float2 * Signal_Float2_In_GPU;
		void InitializeSignalFloat_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalFloat_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void CopySignalFloatDataFromHostToDecive(float * Destination, float * Source);
		void CopySignalFloatDataFromDeciveToHost(float * Destination, float * Source);
		void CopySignalFloat2DataFromHostToDecive(float2 * Destination, complex * Source);
		void CopySignalFloat2DataFromDeciveToHost(complex * Destination, float2 * Source);

		int Signal_Padded_Size_D1;
		int Signal_Padded_Size_D2;
		int Signal_Padded_Size_D3;
		float * Signal_Padded_Float_In_CPU;
		complex * Signal_Padded_Float2_In_CPU;
		float * Signal_Padded_Float_In_GPU;
		float2 * Signal_Padded_Float2_In_GPU;
		void InitializeSignalPaddedFloat_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalPaddedFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalPaddedFloat_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalPaddedFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void CopySignalPaddedFloatDataFromHostToDecive(float * Destination, float * Source);
		void CopySignalPaddedFloatDataFromDeciveToHost(float * Destination, float * Source);
		void CopySignalPaddedFloat2DataFromHostToDecive(float2 * Destination, complex * Source);
		void CopySignalPaddedFloat2DataFromDeciveToHost(complex * Destination, float2 * Source);

		int Signal_Padded_Result_Size_D1;
		int Signal_Padded_Result_Size_D2;
		int Signal_Padded_Result_Size_D3;
		float * Signal_Padded_Result_Float_In_CPU;
		complex * Signal_Padded_Result_Float2_In_CPU;
		float * Signal_Padded_Result_Float_In_GPU;
		float2 * Signal_Padded_Result_Float2_In_GPU;
		void InitializeSignalPaddedResultFloat_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalPaddedResultFloat2_In_CPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalPaddedResultFloat_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void InitializeSignalPaddedResultFloat2_In_GPU(int Size_X, int Size_Y, int Size_Z);
		void CopySignalPaddedResultFloatDataFromHostToDecive(float * Destination, float * Source);
		void CopySignalPaddedResultFloatDataFromDeciveToHost(float * Destination, float * Source);
		void CopySignalPaddedResultFloat2DataFromHostToDecive(float2 * Destination, complex * Source);
		void CopySignalPaddedResultFloat2DataFromDeciveToHost(complex * Destination, float2 * Source);

		//std::vector < std::pair<std::string, void (CUDAInitialization::*)(int, int, int) > >Initialization_Function_List;
		//std::vector < std::pair<std::string, void (CUDAInitialization::*)(float *, float *) > >Copy_Float_To_Float_Function_List;
		//std::vector < std::pair<std::string, void (CUDAInitialization::*)(float2 *, complex *) > >Copy_Complex_To_Float2_Function_List;
		//std::vector < std::pair<std::string, void (CUDAInitialization::*)(complex *, float2 *) > >Copy_Float2_To_Complex_Function_List;
	};
}
#endif
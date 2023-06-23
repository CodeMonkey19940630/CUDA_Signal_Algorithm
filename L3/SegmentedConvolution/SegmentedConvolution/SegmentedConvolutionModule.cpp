#include "SegmentedConvolutionModule.h"
namespace GPUSignalAlgorithm
{
	SegmentedConvolutionModule::SegmentedConvolutionModule()
	{
		this->CUDA_Segmented_Convolution_Pointer = nullptr;
		this->Temporary_Storage_Input_Data.Signal = nullptr;
		this->Temporary_Storage_Input_Data.Kernel = nullptr;
		this->Temporary_Storage_Input_Data.Signal_Length = 0;
		this->Temporary_Storage_Input_Data.Kernel_Length = 0;
	}
	SegmentedConvolutionModule::~SegmentedConvolutionModule()
	{
		if (this->CUDA_Segmented_Convolution_Pointer != nullptr)
		{
			delete this->CUDA_Segmented_Convolution_Pointer;
		}
	}
	void SegmentedConvolutionModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void SegmentedConvolutionModule::Process()
	{
		if ((this->Input_Data.Signal_Length != this->Temporary_Storage_Input_Data.Signal_Length) || (this->Input_Data.Kernel_Length != this->Temporary_Storage_Input_Data.Kernel_Length))
		{
			this->CUDA_Segmented_Convolution_Pointer = new CUDASegmentedConvolutionNamespace::CUDASegmentedConvolution;
			this->CUDA_Segmented_Convolution_Pointer->CUFFTResourceAllocation(this->Input_Data.Kernel_Length);
			this->CUDA_Segmented_Convolution_Pointer->Procedure(this->Input_Data.Signal_Length, this->Input_Data.Kernel_Length, this->Input_Data.Signal, this->Input_Data.Kernel);
			this->Temporary_Storage_Input_Data.Signal_Length = this->Input_Data.Signal_Length;
			this->Temporary_Storage_Input_Data.Kernel_Length = this->Input_Data.Kernel_Length;
			this->Temporary_Storage_Input_Data.Signal = this->Input_Data.Signal;
			this->Temporary_Storage_Input_Data.Kernel = this->Input_Data.Kernel;
		}
		else
		{
			this->CUDA_Segmented_Convolution_Pointer->Procedure(this->Input_Data.Signal_Length, this->Input_Data.Kernel_Length, this->Input_Data.Signal, this->Input_Data.Kernel);
		}
	}
	struct SignalParameter SegmentedConvolutionModule::OutputData()
	{
		return this->Input_Data;
	}

}
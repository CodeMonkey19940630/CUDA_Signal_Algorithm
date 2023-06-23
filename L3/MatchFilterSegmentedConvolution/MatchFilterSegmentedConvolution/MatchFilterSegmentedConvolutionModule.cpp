#include "MatchFilterSegmentedConvolutionModule.h"
namespace GPUSignalAlgorithm
{
	MatchFilterSegmentedConvolutionModule::MatchFilterSegmentedConvolutionModule()
	{
		this->CUDA_Match_Filter_Segmented_Convolution_Pointer = nullptr;
		this->Temporary_Storage_Input_Data.kenel_padded_size = 0;
		this->Temporary_Storage_Input_Data.Pulse_Size = 0;
		this->Temporary_Storage_Input_Data.Scale_Factor = 0;
		this->Temporary_Storage_Input_Data.signal_padded_G = nullptr;
		this->Temporary_Storage_Input_Data.kernel_padded_result_G = nullptr;
	}
	MatchFilterSegmentedConvolutionModule::~MatchFilterSegmentedConvolutionModule()
	{
		if (this->CUDA_Match_Filter_Segmented_Convolution_Pointer != nullptr)
		{
			delete this->CUDA_Match_Filter_Segmented_Convolution_Pointer;
		}
	}
	void MatchFilterSegmentedConvolutionModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void MatchFilterSegmentedConvolutionModule::Process()
	{
		if ((this->Input_Data.kenel_padded_size != this->Temporary_Storage_Input_Data.kenel_padded_size))
		{
			this->CUDA_Match_Filter_Segmented_Convolution_Pointer = new CUDAMatchFilterSegmentedConvolutionNamespace::CUDAMatchFilterSegmentedConvolution;
			this->CUDA_Match_Filter_Segmented_Convolution_Pointer->CUFFTResourceAllocation(this->Input_Data.kenel_padded_size);
			this->CUDA_Match_Filter_Segmented_Convolution_Pointer->Procedure(this->Input_Data.signal_padded_G, this->Input_Data.kernel_padded_result_G, this->Input_Data.kenel_padded_size, this->Input_Data.Pulse_Size, this->Input_Data.Scale_Factor);
			this->Temporary_Storage_Input_Data.kenel_padded_size = this->Input_Data.kenel_padded_size;
			this->Temporary_Storage_Input_Data.Pulse_Size = this->Input_Data.Pulse_Size;
			this->Temporary_Storage_Input_Data.Scale_Factor = this->Input_Data.Scale_Factor;
			this->Temporary_Storage_Input_Data.signal_padded_G = this->Input_Data.signal_padded_G;
			this->Temporary_Storage_Input_Data.kernel_padded_result_G = this->Input_Data.kernel_padded_result_G;
		}
		else
		{
			this->CUDA_Match_Filter_Segmented_Convolution_Pointer->Procedure(this->Input_Data.signal_padded_G, this->Input_Data.kernel_padded_result_G, this->Input_Data.kenel_padded_size, this->Input_Data.Pulse_Size, this->Input_Data.Scale_Factor);
		}
	}
	struct SignalParameter MatchFilterSegmentedConvolutionModule::OutputData()
	{
		return this->Input_Data;
	}
}


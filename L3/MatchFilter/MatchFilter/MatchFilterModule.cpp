#include "MatchFilterModule.h"
namespace GPUSignalAlgorithm
{
	MatchFilterModule::MatchFilterModule()
	{
		this->CUDA_Match_Filter_Pointer = nullptr;
		this->Temporary_Storage_Input_Data.Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Size_D3 = 0;
		this->Temporary_Storage_Input_Data.Total_Size = 0;
		this->Temporary_Storage_Input_Data.Baseband_Signal = nullptr;
		this->Temporary_Storage_Input_Data.Baseband_Signal_Kernel = nullptr;
	}
	MatchFilterModule::~MatchFilterModule()
	{
		if (this->CUDA_Match_Filter_Pointer != nullptr)
		{
			delete this->CUDA_Match_Filter_Pointer;
		}
	}
	void MatchFilterModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void MatchFilterModule::Process()
	{
		if ((this->Input_Data.Size_D1 != this->Temporary_Storage_Input_Data.Size_D1) || (this->Input_Data.Size_D2 != this->Temporary_Storage_Input_Data.Size_D2) || (this->Input_Data.Size_D3 != this->Temporary_Storage_Input_Data.Size_D3))
		{
			this->CUDA_Match_Filter_Pointer = new CUDAMatchFilterNamespace::CUDAMatchFilter;
			this->CUDA_Match_Filter_Pointer->CUFFTResourceAllocation(this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3);
			this->CUDA_Match_Filter_Pointer->Procedure(this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Input_Data.Total_Size, 1.0 / this->Input_Data.Size_D1, this->Input_Data.Baseband_Signal, this->Input_Data.Baseband_Signal_Kernel);
			this->Temporary_Storage_Input_Data.Size_D1 = this->Input_Data.Size_D1;
			this->Temporary_Storage_Input_Data.Size_D2 = this->Input_Data.Size_D2;
			this->Temporary_Storage_Input_Data.Size_D3 = this->Input_Data.Size_D3;
			this->Temporary_Storage_Input_Data.Total_Size = this->Input_Data.Total_Size;
			this->Temporary_Storage_Input_Data.Baseband_Signal = this->Input_Data.Baseband_Signal;
			this->Temporary_Storage_Input_Data.Baseband_Signal_Kernel = this->Input_Data.Baseband_Signal_Kernel;
		}
		else
		{
			this->CUDA_Match_Filter_Pointer->Procedure(this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Input_Data.Total_Size, 1.0 / this->Input_Data.Size_D1, this->Input_Data.Baseband_Signal, this->Input_Data.Baseband_Signal_Kernel);
		}
	}
	struct SignalParameter MatchFilterModule::OutputData()
	{
		return this->Input_Data;
	}
}


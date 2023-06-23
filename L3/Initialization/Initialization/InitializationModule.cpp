#include "InitializationModule.h"
namespace GPUSignalAlgorithm
{
	InitializationModule::InitializationModule()
	{
		this->CUDA_Initialization_Pointer = new CUDAInitializationNamespace::CUDAInitialization;
		this->Temporary_Storage_Input_Data.Kernel_Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Size_D3 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D3 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D3 = 0;
		this->Temporary_Storage_Input_Data.Signal_Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Signal_Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Signal_Size_D3 = 0;
		this->Temporary_Storage_Input_Data.Signal_Padded_Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Signal_Padded_Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Signal_Padded_Size_D3 = 0;
		this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D3 = 0;
	}
	InitializationModule::~InitializationModule()
	{
		if (this->CUDA_Initialization_Pointer != nullptr)
		{
			delete this->CUDA_Initialization_Pointer;
		}
	}
	void InitializationModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void InitializationModule::Process()
	{
		if ((this->Input_Data.Kernel_Size_D1 != this->Temporary_Storage_Input_Data.Kernel_Size_D1) || (this->Input_Data.Kernel_Size_D2 != this->Temporary_Storage_Input_Data.Kernel_Size_D2) || (this->Input_Data.Kernel_Size_D3 != this->Temporary_Storage_Input_Data.Kernel_Size_D3))
		{
			this->CUDA_Initialization_Pointer->InitializeKernelFloat_In_CPU(this->Input_Data.Kernel_Size_D1, this->Input_Data.Kernel_Size_D2, this->Input_Data.Kernel_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelFloat2_In_CPU(this->Input_Data.Kernel_Size_D1, this->Input_Data.Kernel_Size_D2, this->Input_Data.Kernel_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelFloat_In_GPU(this->Input_Data.Kernel_Size_D1, this->Input_Data.Kernel_Size_D2, this->Input_Data.Kernel_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelFloat2_In_GPU(this->Input_Data.Kernel_Size_D1, this->Input_Data.Kernel_Size_D2, this->Input_Data.Kernel_Size_D3);
			this->Temporary_Storage_Input_Data.Kernel_Size_D1 = this->Input_Data.Kernel_Size_D1;
			this->Temporary_Storage_Input_Data.Kernel_Size_D2 = this->Input_Data.Kernel_Size_D2;
			this->Temporary_Storage_Input_Data.Kernel_Size_D3 = this->Input_Data.Kernel_Size_D3;
		}

		if ((this->Input_Data.Kernel_Padded_Size_D1 != this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D1) || (this->Input_Data.Kernel_Padded_Size_D2 != this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D2) || (this->Input_Data.Kernel_Padded_Size_D3 != this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D3))
		{
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedFloat_In_CPU(this->Input_Data.Kernel_Padded_Size_D1, this->Input_Data.Kernel_Padded_Size_D2, this->Input_Data.Kernel_Padded_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedFloat2_In_CPU(this->Input_Data.Kernel_Padded_Size_D1, this->Input_Data.Kernel_Padded_Size_D2, this->Input_Data.Kernel_Padded_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedFloat_In_GPU(this->Input_Data.Kernel_Padded_Size_D1, this->Input_Data.Kernel_Padded_Size_D2, this->Input_Data.Kernel_Padded_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedFloat2_In_GPU(this->Input_Data.Kernel_Padded_Size_D1, this->Input_Data.Kernel_Padded_Size_D2, this->Input_Data.Kernel_Padded_Size_D3);
			this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D1 = this->Input_Data.Kernel_Padded_Size_D1;
			this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D2 = this->Input_Data.Kernel_Padded_Size_D2;
			this->Temporary_Storage_Input_Data.Kernel_Padded_Size_D3 = this->Input_Data.Kernel_Padded_Size_D3;
		}

		if ((this->Input_Data.Kernel_Padded_Result_Size_D1 != this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D1) || (this->Input_Data.Kernel_Padded_Result_Size_D2 != this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D2) || (this->Input_Data.Kernel_Padded_Result_Size_D3 != this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D3))
		{
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedResultFloat_In_CPU(this->Input_Data.Kernel_Padded_Result_Size_D1, this->Input_Data.Kernel_Padded_Result_Size_D2, this->Input_Data.Kernel_Padded_Result_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedResultFloat2_In_CPU(this->Input_Data.Kernel_Padded_Result_Size_D1, this->Input_Data.Kernel_Padded_Result_Size_D2, this->Input_Data.Kernel_Padded_Result_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedResultFloat_In_GPU(this->Input_Data.Kernel_Padded_Result_Size_D1, this->Input_Data.Kernel_Padded_Result_Size_D2, this->Input_Data.Kernel_Padded_Result_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeKernelPaddedResultFloat2_In_GPU(this->Input_Data.Kernel_Padded_Result_Size_D1, this->Input_Data.Kernel_Padded_Result_Size_D2, this->Input_Data.Kernel_Padded_Result_Size_D3);
			this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D1 = this->Input_Data.Kernel_Padded_Result_Size_D1;
			this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D2 = this->Input_Data.Kernel_Padded_Result_Size_D2;
			this->Temporary_Storage_Input_Data.Kernel_Padded_Result_Size_D3 = this->Input_Data.Kernel_Padded_Result_Size_D3;
		}

		if ((this->Input_Data.Signal_Size_D1 != this->Temporary_Storage_Input_Data.Signal_Size_D1) || (this->Input_Data.Signal_Size_D2 != this->Temporary_Storage_Input_Data.Signal_Size_D2) || (this->Input_Data.Signal_Size_D3 != this->Temporary_Storage_Input_Data.Signal_Size_D3))
		{
			this->CUDA_Initialization_Pointer->InitializeSignalFloat_In_CPU(this->Input_Data.Signal_Size_D1, this->Input_Data.Signal_Size_D2, this->Input_Data.Signal_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalFloat2_In_CPU(this->Input_Data.Signal_Size_D1, this->Input_Data.Signal_Size_D2, this->Input_Data.Signal_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalFloat_In_GPU(this->Input_Data.Signal_Size_D1, this->Input_Data.Signal_Size_D2, this->Input_Data.Signal_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalFloat2_In_GPU(this->Input_Data.Signal_Size_D1, this->Input_Data.Signal_Size_D2, this->Input_Data.Signal_Size_D3);
			this->Temporary_Storage_Input_Data.Signal_Size_D1 = this->Input_Data.Signal_Size_D1;
			this->Temporary_Storage_Input_Data.Signal_Size_D2 = this->Input_Data.Signal_Size_D2;
			this->Temporary_Storage_Input_Data.Signal_Size_D3 = this->Input_Data.Signal_Size_D3;
		}

		if ((this->Input_Data.Signal_Padded_Size_D1 != this->Temporary_Storage_Input_Data.Signal_Padded_Size_D1) || (this->Input_Data.Signal_Padded_Size_D2 != this->Temporary_Storage_Input_Data.Signal_Padded_Size_D2) || (this->Input_Data.Signal_Padded_Size_D3 != this->Temporary_Storage_Input_Data.Signal_Padded_Size_D3))
		{
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedFloat_In_CPU(this->Input_Data.Signal_Padded_Size_D1, this->Input_Data.Signal_Padded_Size_D2, this->Input_Data.Signal_Padded_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedFloat2_In_CPU(this->Input_Data.Signal_Padded_Size_D1, this->Input_Data.Signal_Padded_Size_D2, this->Input_Data.Signal_Padded_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedFloat_In_GPU(this->Input_Data.Signal_Padded_Size_D1, this->Input_Data.Signal_Padded_Size_D2, this->Input_Data.Signal_Padded_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedFloat2_In_GPU(this->Input_Data.Signal_Padded_Size_D1, this->Input_Data.Signal_Padded_Size_D2, this->Input_Data.Signal_Padded_Size_D3);
			this->Temporary_Storage_Input_Data.Signal_Padded_Size_D1 = this->Input_Data.Signal_Padded_Size_D1;
			this->Temporary_Storage_Input_Data.Signal_Padded_Size_D2 = this->Input_Data.Signal_Padded_Size_D2;
			this->Temporary_Storage_Input_Data.Signal_Padded_Size_D3 = this->Input_Data.Signal_Padded_Size_D3;
		}

		if ((this->Input_Data.Signal_Padded_Result_Size_D1 != this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D1) || (this->Input_Data.Signal_Padded_Result_Size_D2 != this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D2) || (this->Input_Data.Signal_Padded_Result_Size_D3 != this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D3))
		{
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedResultFloat_In_CPU(this->Input_Data.Signal_Padded_Result_Size_D1, this->Input_Data.Signal_Padded_Result_Size_D2, this->Input_Data.Signal_Padded_Result_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedResultFloat2_In_CPU(this->Input_Data.Signal_Padded_Result_Size_D1, this->Input_Data.Signal_Padded_Result_Size_D2, this->Input_Data.Signal_Padded_Result_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedResultFloat_In_GPU(this->Input_Data.Signal_Padded_Result_Size_D1, this->Input_Data.Signal_Padded_Result_Size_D2, this->Input_Data.Signal_Padded_Result_Size_D3);
			this->CUDA_Initialization_Pointer->InitializeSignalPaddedResultFloat2_In_GPU(this->Input_Data.Signal_Padded_Result_Size_D1, this->Input_Data.Signal_Padded_Result_Size_D2, this->Input_Data.Signal_Padded_Result_Size_D3);
			this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D1 = this->Input_Data.Signal_Padded_Result_Size_D1;
			this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D2 = this->Input_Data.Signal_Padded_Result_Size_D2;
			this->Temporary_Storage_Input_Data.Signal_Padded_Result_Size_D3 = this->Input_Data.Signal_Padded_Result_Size_D3;
		}
	}
	struct SignalParameter InitializationModule::OutputData()
	{
		return this->Input_Data;
	}
}


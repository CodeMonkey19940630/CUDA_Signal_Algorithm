#include "NoiseFrequencyModulationJammingModule.h"
namespace GPUSignalAlgorithm
{
	NoiseFrequencyModulationJammingModule::NoiseFrequencyModulationJammingModule()
	{
		this->CUDA_Noise_Frequency_Modulation_Jamming_Pointer = new CUDANoiseFrequencyModulationJammingNamespace::CUDANoiseFrequencyModulationJamming;
	}
	NoiseFrequencyModulationJammingModule::~NoiseFrequencyModulationJammingModule()
	{
		if (this->CUDA_Noise_Frequency_Modulation_Jamming_Pointer != nullptr)
		{
			delete this->CUDA_Noise_Frequency_Modulation_Jamming_Pointer;
		}
	}
	void NoiseFrequencyModulationJammingModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void NoiseFrequencyModulationJammingModule::Process()
	{
		this->CUDA_Noise_Frequency_Modulation_Jamming_Pointer->Procedure(this->Input_Data.Radar_Float_Data_Cube_Address, this->Input_Data.Radar_Float2_Data_Cube_Address, this->Control_Parameter.Amplitude, this->Control_Parameter.Frequency_Modulation_Coefficient, this->Control_Parameter.Jamming_Center_Frequency, this->Control_Parameter.Band_Width, this->Control_Parameter.Sampling_Frequency_Of_Medium_Frequency, this->Control_Parameter.Sampling_Frequency_Of_Band, this->Control_Parameter.PRT, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Control_Parameter.Use_Only_Baseband);
	}
	void NoiseFrequencyModulationJammingModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter NoiseFrequencyModulationJammingModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	struct SignalParameter NoiseFrequencyModulationJammingModule::OutputData()
	{
		return this->Input_Data;
	}
}


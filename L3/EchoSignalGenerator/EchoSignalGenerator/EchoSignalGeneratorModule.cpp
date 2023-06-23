#include "EchoSignalGeneratorModule.h"
namespace GPUSignalAlgorithm
{
	EchoSignalGeneratorModule::EchoSignalGeneratorModule()
	{
		this->CUDA_Echo_Signal_Generator_Pointer = new CUDAEchoSignalGeneratorNamespace::CUDAEchoSignalGenerator;
	}
	EchoSignalGeneratorModule::~EchoSignalGeneratorModule()
	{
		if (this->CUDA_Echo_Signal_Generator_Pointer != nullptr)
		{
			delete this->CUDA_Echo_Signal_Generator_Pointer;
		}
	}
	void EchoSignalGeneratorModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void EchoSignalGeneratorModule::Process()
	{
		this->CUDA_Echo_Signal_Generator_Pointer->Procedure(this->Input_Data.Radar_Float2_Data_Cube_Address, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Input_Data.Signal_Transmit_Time, this->Control_Parameter.Distance_Between_Target_and_Radar, this->Control_Parameter.Target_Velocity_Relative_to_Radar, this->Control_Parameter.RCS, this->Control_Parameter.Receiver_Gain, this->Control_Parameter.Transmit_Power, this->Control_Parameter.Antenna_Transmit_Gain, this->Control_Parameter.Antenna_Receive_Gain, this->Control_Parameter.Wave_Length, this->Control_Parameter.Impedance, this->Input_Data.Baseband_Sampling_Frequency, this->Control_Parameter.Pulse_Width, this->Control_Parameter.Band_Width, this->Control_Parameter.PRT, this->Control_Parameter.PRT_List, this->Control_Parameter.PRT_List_Size, this->Control_Parameter.Type);
	}
	void EchoSignalGeneratorModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter EchoSignalGeneratorModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	struct SignalParameter EchoSignalGeneratorModule::OutputData()
	{
		return this->Input_Data;
	}
}


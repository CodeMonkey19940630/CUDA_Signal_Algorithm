#include "InterruptedSamplingRepeaterJammingModule.h"
namespace GPUSignalAlgorithm
{
	InterruptedSamplingRepeaterJammingModule::InterruptedSamplingRepeaterJammingModule()
	{
		this->CUDA_Interrupted_Sampling_Repeater_Jamming_Pointer = new CUDAInterruptedSamplingRepeaterJammingNamespace::CUDAInterruptedSamplingRepeaterJamming;
	}
	InterruptedSamplingRepeaterJammingModule::~InterruptedSamplingRepeaterJammingModule()
	{
		if (this->CUDA_Interrupted_Sampling_Repeater_Jamming_Pointer != nullptr)
		{
			delete this->CUDA_Interrupted_Sampling_Repeater_Jamming_Pointer;
		}
	}
	void InterruptedSamplingRepeaterJammingModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void InterruptedSamplingRepeaterJammingModule::Process()
	{
		this->CUDA_Interrupted_Sampling_Repeater_Jamming_Pointer->Procedure(this->Input_Data.Radar_Float_Data_Cube_Address, this->Input_Data.Radar_Float2_Data_Cube_Address, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Control_Parameter.Distance_Between_Target_and_Radar, this->Control_Parameter.RCS, this->Control_Parameter.Target_Velocity_Relative_to_Radar, this->Control_Parameter.Receiver_Gain, this->Control_Parameter.Transmit_Power, this->Control_Parameter.Antenna_Transmit_Gain, this->Control_Parameter.Antenna_Receive_Gain, this->Control_Parameter.Wave_Length, this->Control_Parameter.Impedance, this->Input_Data.Signal_Transmit_Time, this->Control_Parameter.Duty_Factor, this->Control_Parameter.Jamming_Amplitude, this->Input_Data.Sampling_Transpond_Period, this->Input_Data.Sampling_Frequency_Of_Medium_Frequency, this->Input_Data.Baseband_Sampling_Frequency, this->Control_Parameter.Medium_Frequency, this->Control_Parameter.Pulse_Width, this->Control_Parameter.Band_Width, this->Control_Parameter.PRT, this->Control_Parameter.PRT_List, this->Control_Parameter.PRT_List_Size, this->Control_Parameter.Pulse_Transmit_Interval_Time_List, this->Control_Parameter.Pulse_Transmit_Interval_Time_List_Size, this->Control_Parameter.Use_Only_Baseband, this->Control_Parameter.Type);
	}
	void InterruptedSamplingRepeaterJammingModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter InterruptedSamplingRepeaterJammingModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	struct SignalParameter InterruptedSamplingRepeaterJammingModule::OutputData()
	{
		return this->Input_Data;
	}
}


#include "BasebandReceiverLogarithmicAmplifierModule.h"
namespace GPUSignalAlgorithm
{
	BasebandReceiverLogarithmicAmplifierModule::BasebandReceiverLogarithmicAmplifierModule()
	{
		this->CUDA_Baseband_Receiver_Logarithmic_Amplifier_Pointer = new CUDABasebandReceiverLogarithmicAmplifierNamespace::CUDABasebandReceiverLogarithmicAmplifier;
	}
	BasebandReceiverLogarithmicAmplifierModule::~BasebandReceiverLogarithmicAmplifierModule()
	{
		if (this->CUDA_Baseband_Receiver_Logarithmic_Amplifier_Pointer != nullptr)
		{
			delete this->CUDA_Baseband_Receiver_Logarithmic_Amplifier_Pointer;
		}
	}
	void BasebandReceiverLogarithmicAmplifierModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void BasebandReceiverLogarithmicAmplifierModule::Process()
	{
		this->CUDA_Baseband_Receiver_Logarithmic_Amplifier_Pointer->Procedure(this->Input_Data.Radar_Data_Cube_Address, this->Input_Data.Receiver_Noise_Data_Address, this->Input_Data.Total_Size_Of_Receiver_Noise_Data, this->Control_Parameter.Receiver_Gain, this->Control_Parameter.Band_Width, this->Control_Parameter.Noise_Factor, this->Control_Parameter.Impedance, this->Control_Parameter.Impedance_Temperature, this->Control_Parameter.Logarithmic_Amplifier_Voltage, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3);
	}
	void BasebandReceiverLogarithmicAmplifierModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter BasebandReceiverLogarithmicAmplifierModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	struct SignalParameter BasebandReceiverLogarithmicAmplifierModule::OutputData()
	{
		return this->Input_Data;
	}
}


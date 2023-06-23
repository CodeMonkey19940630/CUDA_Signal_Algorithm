#include "BasebandReceiverAnalogDigitalConversionModule.h"
namespace GPUSignalAlgorithm
{
	BasebandReceiverAnalogDigitalConversionModule::BasebandReceiverAnalogDigitalConversionModule()
	{
		this->CUDA_Baseband_Receiver_Analog_Digital_Conversion_Pointer = new CUDABasebandReceiverAnalogDigitalConversionNamespace::CUDABasebandReceiverAnalogDigitalConversion;
	}
	BasebandReceiverAnalogDigitalConversionModule::~BasebandReceiverAnalogDigitalConversionModule()
	{
		if (this->CUDA_Baseband_Receiver_Analog_Digital_Conversion_Pointer != nullptr)
		{
			delete this->CUDA_Baseband_Receiver_Analog_Digital_Conversion_Pointer;
		}
	}
	void BasebandReceiverAnalogDigitalConversionModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void BasebandReceiverAnalogDigitalConversionModule::Process()
	{
		this->CUDA_Baseband_Receiver_Analog_Digital_Conversion_Pointer->Procedure(this->Input_Data.Radar_Data_Cube_Address, this->Input_Data.Receiver_Noise_Data_Address, this->Input_Data.Total_Size_Of_Receiver_Noise_Data, this->Control_Parameter.Receiver_Gain, this->Control_Parameter.Band_Width, this->Control_Parameter.Noise_Factor, this->Control_Parameter.Impedance, this->Control_Parameter.Impedance_Temperature, this->Control_Parameter.Max_Voltage, this->Control_Parameter.ADC_Number, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3);
	}
	void BasebandReceiverAnalogDigitalConversionModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter BasebandReceiverAnalogDigitalConversionModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	struct SignalParameter BasebandReceiverAnalogDigitalConversionModule::OutputData()
	{
		return this->Input_Data;
	}
}
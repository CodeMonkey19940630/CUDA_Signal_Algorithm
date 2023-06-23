#include "BasebandReceiverSensitivityTimeModule.h"
namespace GPUSignalAlgorithm
{
	BasebandReceiverSensitivityTimeModule::BasebandReceiverSensitivityTimeModule()
	{
		this->CUDA_Baseband_Receiver_Sensitivity_Time_Pointer = new CUDABasebandReceiverSensitivityTimeNamespace::CUDABasebandReceiverSensitivityTime;
	}
	BasebandReceiverSensitivityTimeModule::~BasebandReceiverSensitivityTimeModule()
	{
		if (this->CUDA_Baseband_Receiver_Sensitivity_Time_Pointer != nullptr)
		{
			delete this->CUDA_Baseband_Receiver_Sensitivity_Time_Pointer;
		}
	}
	void BasebandReceiverSensitivityTimeModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void BasebandReceiverSensitivityTimeModule::Process()
	{
		this->CUDA_Baseband_Receiver_Sensitivity_Time_Pointer->Procedure(this->Input_Data.Radar_Data_Cube_Address, this->Control_Parameter.Window_Of_Range_Right, this->Control_Parameter.Window_Of_Range_Left, this->Control_Parameter.Sensitivity_Time_Control_Coefficient, this->Control_Parameter.Pulse_Repetition_Time, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Control_Parameter.Use_Window_Of_Range);
	}
	void BasebandReceiverSensitivityTimeModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter BasebandReceiverSensitivityTimeModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	struct SignalParameter BasebandReceiverSensitivityTimeModule::OutputData()
	{
		return this->Input_Data;
	}
}


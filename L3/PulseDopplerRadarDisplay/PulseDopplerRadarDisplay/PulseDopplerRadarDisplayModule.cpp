// PulseDopplerRadarDisplay.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "PulseDopplerRadarDisplayModule.h"
namespace GPUSignalAlgorithm
{
	PulseDopplerRadarDisplayModule::PulseDopplerRadarDisplayModule()
	{
		this->CUDA_Pulse_Doppler_Radar_Display_Pointer = nullptr;
		this->Temporary_Storage_Input_Data.Size_D1 = 0;
		this->Temporary_Storage_Input_Data.Size_D2 = 0;
		this->Temporary_Storage_Input_Data.Size_D3 = 0;
		this->Temporary_Storage_Input_Data.Radar_Data_Cube_Address = nullptr;
	}
	PulseDopplerRadarDisplayModule::~PulseDopplerRadarDisplayModule()
	{
		if (this->CUDA_Pulse_Doppler_Radar_Display_Pointer != nullptr)
		{
			delete this->CUDA_Pulse_Doppler_Radar_Display_Pointer;
		}
	}
	void PulseDopplerRadarDisplayModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void PulseDopplerRadarDisplayModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter PulseDopplerRadarDisplayModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	void PulseDopplerRadarDisplayModule::Process()
	{
		if ((this->Input_Data.Size_D1 != this->Temporary_Storage_Input_Data.Size_D1) || (this->Input_Data.Size_D2 != this->Temporary_Storage_Input_Data.Size_D2) || (this->Input_Data.Size_D3 != this->Temporary_Storage_Input_Data.Size_D3))
		{
			this->CUDA_Pulse_Doppler_Radar_Display_Pointer = new CUDAPulseDopplerRadarDisplayNamespace::CUDAPulseDopplerRadarDisplay;
			this->CUDA_Pulse_Doppler_Radar_Display_Pointer->CUFFTResourceAllocation(this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3);
			this->CUDA_Pulse_Doppler_Radar_Display_Pointer->Procedure(this->Input_Data.Radar_Data_Cube_Address, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Control_Parameter.MTIOrder);
			this->Temporary_Storage_Input_Data.Size_D1 = this->Input_Data.Size_D1;
			this->Temporary_Storage_Input_Data.Size_D2 = this->Input_Data.Size_D2;
			this->Temporary_Storage_Input_Data.Size_D3 = this->Input_Data.Size_D3;
			this->Temporary_Storage_Input_Data.Radar_Data_Cube_Address = this->Input_Data.Radar_Data_Cube_Address;
		}
		else
		{
			this->CUDA_Pulse_Doppler_Radar_Display_Pointer->Procedure(this->Input_Data.Radar_Data_Cube_Address, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Control_Parameter.MTIOrder);
		}

	}
	struct SignalParameter PulseDopplerRadarDisplayModule::OutputData()
	{
		return this->Input_Data;
	}
}


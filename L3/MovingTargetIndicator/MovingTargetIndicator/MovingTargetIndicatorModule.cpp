// PulseDopplerRadarDisplay.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "MovingTargetIndicatorModule.h"
namespace GPUSignalAlgorithm
{
	MovingTargetIndicatorModule::MovingTargetIndicatorModule()
	{
		this->CUDA_Moving_Target_Indicator_Pointer = new CUDAMovingTargetIndicatorNamespace::CUDAMovingTargetIndicator;
	}
	MovingTargetIndicatorModule::~MovingTargetIndicatorModule()
	{
		if (this->CUDA_Moving_Target_Indicator_Pointer != nullptr)
		{
			delete this->CUDA_Moving_Target_Indicator_Pointer;
		}
	}
	void MovingTargetIndicatorModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void MovingTargetIndicatorModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter MovingTargetIndicatorModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	void MovingTargetIndicatorModule::Process()
	{
		this->CUDA_Moving_Target_Indicator_Pointer->Procedure(this->Input_Data.Radar_Data_Cube_Address, this->Control_Parameter.MTIOrder, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3);
	}
	struct SignalParameter MovingTargetIndicatorModule::OutputData()
	{
		return this->Input_Data;
	}
}


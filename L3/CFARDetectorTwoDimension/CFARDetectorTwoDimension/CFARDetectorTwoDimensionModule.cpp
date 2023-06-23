#include "CFARDetectorTwoDimensionModule.h"
namespace GPUSignalAlgorithm
{
	CFARDetectorTwoDimensionModule::CFARDetectorTwoDimensionModule()
	{
		this->CUDA_CFAR_Detector_Two_Dimension_Pointer = new CUDACFARDetectorTwoDimensionNamespace::CUDACFARDetectorTwoDimension;
	}
	CFARDetectorTwoDimensionModule::~CFARDetectorTwoDimensionModule()
	{
		if (this->CUDA_CFAR_Detector_Two_Dimension_Pointer != nullptr)
		{
			delete this->CUDA_CFAR_Detector_Two_Dimension_Pointer;
		}
	}
	void CFARDetectorTwoDimensionModule::InputData(struct SignalParameter Input_Data)
	{
		this->Input_Data = Input_Data;
	}
	void CFARDetectorTwoDimensionModule::Process()
	{
		this->CUDA_CFAR_Detector_Two_Dimension_Pointer->Procedure(this->Input_Data.Radar_Data_Cube_Address, this->Input_Data.CFAR_Absolute_Detected_Data, this->Input_Data.CFAR_Reference, this->Input_Data.CFAR_Result, this->Input_Data.Size_D1, this->Input_Data.Size_D2, this->Input_Data.Size_D3, this->Control_Parameter.GuardCell_F, this->Control_Parameter.WindowCell_F, this->Control_Parameter.GuardCell_S, this->Control_Parameter.WindowCell_S, this->Control_Parameter.Min_Detect_Factor, this->Control_Parameter.Min_Detect_Threshold, this->Control_Parameter.CFAR_Method_Select);
	}
	void CFARDetectorTwoDimensionModule::SetControlParameter(struct ControlParameter Control_Parameter)
	{
		this->Control_Parameter = Control_Parameter;
	}
	struct ControlParameter CFARDetectorTwoDimensionModule::GetControlParameter()
	{
		return this->Control_Parameter;
	}
	struct SignalParameter CFARDetectorTwoDimensionModule::OutputData()
	{
		return this->Input_Data;
	}
}


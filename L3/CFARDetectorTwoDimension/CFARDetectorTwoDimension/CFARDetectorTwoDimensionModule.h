#ifndef CFARDETECTORTWODIMENSIONMODULE_H
#define CFARDETECTORTWODIMENSIONMODULE_H
#ifdef CFARDETECTORTWODIMENSION_EXPORTS
#define CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllexport)
#else
#define CFAR_DETECTOR_TWO_DIMENSION_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDACFARDetectorTwoDimension.h"
namespace GPUSignalAlgorithm
{
	class CFAR_DETECTOR_TWO_DIMENSION_EXPORTS CFARDetectorTwoDimensionModule
	{
	public:
		CFARDetectorTwoDimensionModule();
		~CFARDetectorTwoDimensionModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		struct SignalParameter OutputData();
	private:
		CUDACFARDetectorTwoDimensionNamespace::CUDACFARDetectorTwoDimension * CUDA_CFAR_Detector_Two_Dimension_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//不一定用得上,先挂着。
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//不一定用得上，先挂着。
		//struct SignalParameter Output_Data;//不一定用得上，先挂着。
		//struct SignalParameter Temporary_Storage_Output_Data;//不一定用得上，先挂着。

	};
}
#endif
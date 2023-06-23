#ifndef MOVINGTARGETINDICATORMODULE_H
#define MOVINGTARGETINDICATORMODULE_H
#ifdef MOVINGTARGETINDICATOR_EXPORTS
#define MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllexport)
#else
#define MOVING_TARGET_INDICATOR_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDAMovingTargetIndicator.h"
namespace GPUSignalAlgorithm
{
	class MOVING_TARGET_INDICATOR_EXPORTS MovingTargetIndicatorModule
	{
	public:
		MovingTargetIndicatorModule();
		~MovingTargetIndicatorModule();
		void InputData(struct SignalParameter Input_Data);
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		void Process();
		struct SignalParameter OutputData();
	private:
		CUDAMovingTargetIndicatorNamespace::CUDAMovingTargetIndicator * CUDA_Moving_Target_Indicator_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�

	};
}
#endif
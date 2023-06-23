#ifndef BASEBANDRECEIVERLOGARITHMICAMPLIFIERMODULE_H
#define BASEBANDRECEIVERLOGARITHMICAMPLIFIERMODULE_H
#ifdef BASEBANDRECEIVERLOGARITHMICAMPLIFIER_EXPORTS
#define BASEBAND_RECEIVER_LOGARITHMIC_AMPLIFIER_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_LOGARITHMIC_AMPLIFIER_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDABasebandReceiverLogarithmicAmplifier.h"
namespace GPUSignalAlgorithm
{
	class BASEBAND_RECEIVER_LOGARITHMIC_AMPLIFIER_EXPORTS BasebandReceiverLogarithmicAmplifierModule
	{
	public:
		BasebandReceiverLogarithmicAmplifierModule();
		~BasebandReceiverLogarithmicAmplifierModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		struct SignalParameter OutputData();
	private:
		CUDABasebandReceiverLogarithmicAmplifierNamespace::CUDABasebandReceiverLogarithmicAmplifier * CUDA_Baseband_Receiver_Logarithmic_Amplifier_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�

	};
}
#endif
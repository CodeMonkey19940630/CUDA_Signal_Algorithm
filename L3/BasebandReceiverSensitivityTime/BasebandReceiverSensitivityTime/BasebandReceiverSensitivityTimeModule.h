#ifndef BASEBANDRECEIVERSENSITIVITYTIMEMODULE_H
#define BASEBANDRECEIVERSENSITIVITYTIMEMODULE_H
#ifdef BASEBANDRECEIVERSENSITIVITYTIME_EXPORTS
#define BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDABasebandReceiverSensitivityTime.h"
namespace GPUSignalAlgorithm
{
	class BASEBAND_RECEIVER_SENSITIVITY_TIME_EXPORTS BasebandReceiverSensitivityTimeModule
	{
	public:
		BasebandReceiverSensitivityTimeModule();
		~BasebandReceiverSensitivityTimeModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		struct SignalParameter OutputData();
	private:
		CUDABasebandReceiverSensitivityTimeNamespace::CUDABasebandReceiverSensitivityTime * CUDA_Baseband_Receiver_Sensitivity_Time_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//��һ���õ���,�ȹ��š�
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Output_Data;//��һ���õ��ϣ��ȹ��š�
		//struct SignalParameter Temporary_Storage_Output_Data;//��һ���õ��ϣ��ȹ��š�

	};
}
#endif
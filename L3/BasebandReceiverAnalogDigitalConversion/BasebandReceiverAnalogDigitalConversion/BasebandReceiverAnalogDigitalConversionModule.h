#ifndef BASEBANDRECEIVERANALOGDIGITALCONVERSIONMODULE_H
#define BASEBANDRECEIVERANALOGDIGITALCONVERSIONMODULE_H
#ifdef BASEBANDRECEIVERANALOGDIGITALCONVERSION_EXPORTS
#define BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllimport)
#endif
#include"../HeaderFileOfStruct/Struct.h"
#include "../HeaderFileOfHierarchy2DLL/CUDABasebandReceiverAnalogDigitalConversion.h"
namespace GPUSignalAlgorithm
{
	class BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS BasebandReceiverAnalogDigitalConversionModule
	{
	public:
		BasebandReceiverAnalogDigitalConversionModule();
		~BasebandReceiverAnalogDigitalConversionModule();
		void InputData(struct SignalParameter Input_Data);
		void Process();
		void SetControlParameter(struct ControlParameter Control_Parameter);
		struct ControlParameter GetControlParameter();
		struct SignalParameter OutputData();
	private:
		CUDABasebandReceiverAnalogDigitalConversionNamespace::CUDABasebandReceiverAnalogDigitalConversion * CUDA_Baseband_Receiver_Analog_Digital_Conversion_Pointer;
		struct SignalParameter Input_Data;
		//struct SignalParameter Temporary_Storage_Input_Data;//不一定用得上,先挂着。
		struct ControlParameter Control_Parameter;
		//struct ControlParameter Temporary_Storage_Control_Parameter;//不一定用得上，先挂着。
		//struct SignalParameter Output_Data;//不一定用得上，先挂着。
		//struct SignalParameter Temporary_Storage_Output_Data;//不一定用得上，先挂着。

	};
}
#endif
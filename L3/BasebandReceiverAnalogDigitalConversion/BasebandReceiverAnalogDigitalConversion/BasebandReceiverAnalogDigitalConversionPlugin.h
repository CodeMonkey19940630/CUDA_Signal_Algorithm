//只对外暴露IJamComponentFactory接口类
#ifndef BASEBANDRECEIVERANALOGDIGITALCONVERSION_H
#define BASEBANDRECEIVERANALOGDIGITALCONVERSION_H
#ifdef BASEBANDRECEIVERANALOGDIGITALCONVERSION_EXPORTS
#define BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "BasebandReceiverAnalogDigitalConversionModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS BasebandReceiverAnalogDigitalConversionPlugin
	{
	public:
		BasebandReceiverAnalogDigitalConversionPlugin();
		~BasebandReceiverAnalogDigitalConversionPlugin();
		BasebandReceiverAnalogDigitalConversionModule * PluginBasebandReceiverAnalogDigitalConversion();
	private:
		BasebandReceiverAnalogDigitalConversionModule * Baseband_Receiver_Analog_Digital_Conversion_Module_Pointer;
	};
}
#endif


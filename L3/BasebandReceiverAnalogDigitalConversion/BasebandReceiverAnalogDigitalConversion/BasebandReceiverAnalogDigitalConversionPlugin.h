//ֻ���Ⱪ¶IJamComponentFactory�ӿ���
#ifndef BASEBANDRECEIVERANALOGDIGITALCONVERSION_H
#define BASEBANDRECEIVERANALOGDIGITALCONVERSION_H
#ifdef BASEBANDRECEIVERANALOGDIGITALCONVERSION_EXPORTS
#define BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllexport)
#else
#define BASEBAND_RECEIVER_ANALOG_DIGITAL_CONVERSION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay�ӿ�������ͷ�ļ�
#include "BasebandReceiverAnalogDigitalConversionModule.h"
//PulseDopplerRadarDisplay�ӿ��ඨ��
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


// BasebandReceiverAnalogDigitalConversion.cpp : ���� DLL Ӧ�ó���ĵ���������
#include "stdafx.h"
#include "BasebandReceiverAnalogDigitalConversionPlugin.h"

namespace GPUSignalAlgorithm
{
	BasebandReceiverAnalogDigitalConversionPlugin::BasebandReceiverAnalogDigitalConversionPlugin()
	{
		this->Baseband_Receiver_Analog_Digital_Conversion_Module_Pointer = nullptr;
	}
	BasebandReceiverAnalogDigitalConversionPlugin::~BasebandReceiverAnalogDigitalConversionPlugin()
	{
		delete this->Baseband_Receiver_Analog_Digital_Conversion_Module_Pointer;
	}
	BasebandReceiverAnalogDigitalConversionModule * BasebandReceiverAnalogDigitalConversionPlugin::PluginBasebandReceiverAnalogDigitalConversion()
	{
		this->Baseband_Receiver_Analog_Digital_Conversion_Module_Pointer = new BasebandReceiverAnalogDigitalConversionModule;
		return(this->Baseband_Receiver_Analog_Digital_Conversion_Module_Pointer);
	}
}







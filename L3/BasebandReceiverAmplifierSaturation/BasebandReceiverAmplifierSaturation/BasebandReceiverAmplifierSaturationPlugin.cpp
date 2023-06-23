// BasebandReceiverAmplifierSaturation.cpp : ���� DLL Ӧ�ó���ĵ���������
#include "stdafx.h"
#include "BasebandReceiverAmplifierSaturationPlugin.h"

namespace GPUSignalAlgorithm
{
	BasebandReceiverAmplifierSaturationPlugin::BasebandReceiverAmplifierSaturationPlugin()
	{
		this->Baseband_Receiver_Amplifier_Saturation_Module_Pointer = nullptr;
	}
	BasebandReceiverAmplifierSaturationPlugin::~BasebandReceiverAmplifierSaturationPlugin()
	{
		delete this->Baseband_Receiver_Amplifier_Saturation_Module_Pointer;
	}
	BasebandReceiverAmplifierSaturationModule * BasebandReceiverAmplifierSaturationPlugin::PluginBasebandReceiverAmplifierSaturation()
	{
		 this->Baseband_Receiver_Amplifier_Saturation_Module_Pointer = new BasebandReceiverAmplifierSaturationModule;
		 return (this->Baseband_Receiver_Amplifier_Saturation_Module_Pointer);
	}
}
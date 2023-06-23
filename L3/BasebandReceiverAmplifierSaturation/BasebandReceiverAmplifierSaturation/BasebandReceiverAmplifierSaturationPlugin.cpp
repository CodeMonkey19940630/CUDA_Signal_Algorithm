// BasebandReceiverAmplifierSaturation.cpp : 定义 DLL 应用程序的导出函数。
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
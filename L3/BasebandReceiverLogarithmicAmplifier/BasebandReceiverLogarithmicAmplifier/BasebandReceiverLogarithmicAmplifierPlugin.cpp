// BasebandReceiverLogarithmicAmplifier.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "BasebandReceiverLogarithmicAmplifierPlugin.h"

namespace GPUSignalAlgorithm
{
	BasebandReceiverLogarithmicAmplifierPlugin::BasebandReceiverLogarithmicAmplifierPlugin()
	{
		this->Baseband_Receiver_Logarithmic_Amplifier_Module_Pointer = nullptr;
	}
	BasebandReceiverLogarithmicAmplifierPlugin::~BasebandReceiverLogarithmicAmplifierPlugin()
	{
		delete this->Baseband_Receiver_Logarithmic_Amplifier_Module_Pointer;
	}
	BasebandReceiverLogarithmicAmplifierModule * BasebandReceiverLogarithmicAmplifierPlugin::PluginBasebandReceiverLogarithmicAmplifier()
	{
		this->Baseband_Receiver_Logarithmic_Amplifier_Module_Pointer = new BasebandReceiverLogarithmicAmplifierModule;
		return(this->Baseband_Receiver_Logarithmic_Amplifier_Module_Pointer);
	}
}





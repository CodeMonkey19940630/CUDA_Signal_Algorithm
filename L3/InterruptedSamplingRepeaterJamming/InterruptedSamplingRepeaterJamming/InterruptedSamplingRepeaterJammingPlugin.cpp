// InterruptedSamplingRepeaterJamming.cpp : ���� DLL Ӧ�ó���ĵ���������
#include "stdafx.h"
#include "InterruptedSamplingRepeaterJammingPlugin.h"

namespace GPUSignalAlgorithm
{
	InterruptedSamplingRepeaterJammingPlugin::InterruptedSamplingRepeaterJammingPlugin()
	{
		this->Interrupted_Sampling_Repeater_Jamming_Module_Pointer = nullptr;
	}
	InterruptedSamplingRepeaterJammingPlugin::~InterruptedSamplingRepeaterJammingPlugin()
	{
		delete this->Interrupted_Sampling_Repeater_Jamming_Module_Pointer;
	}
	InterruptedSamplingRepeaterJammingModule * InterruptedSamplingRepeaterJammingPlugin::PluginInterruptedSamplingRepeaterJamming()
	{
		this->Interrupted_Sampling_Repeater_Jamming_Module_Pointer = new InterruptedSamplingRepeaterJammingModule;
		return(this->Interrupted_Sampling_Repeater_Jamming_Module_Pointer);
	}
}



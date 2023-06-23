// NoiseFrequencyModulationJamming.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "NoiseFrequencyModulationJammingPlugin.h"

namespace GPUSignalAlgorithm
{
	NoiseFrequencyModulationJammingPlugin::NoiseFrequencyModulationJammingPlugin()
	{
		this->Noise_Frequency_Modulation_Jamming_Module_Pointer = nullptr;
	}
	NoiseFrequencyModulationJammingPlugin::~NoiseFrequencyModulationJammingPlugin()
	{
		delete this->Noise_Frequency_Modulation_Jamming_Module_Pointer;
	}
	NoiseFrequencyModulationJammingModule * NoiseFrequencyModulationJammingPlugin::PluginNoiseFrequencyModulationJamming()
	{
		this->Noise_Frequency_Modulation_Jamming_Module_Pointer = new NoiseFrequencyModulationJammingModule;
		return(this->Noise_Frequency_Modulation_Jamming_Module_Pointer);

	}
}

// EchoSignalGenerator.cpp : ���� DLL Ӧ�ó���ĵ���������
#include "stdafx.h"
#include "EchoSignalGeneratorPlugin.h"

namespace GPUSignalAlgorithm
{
	EchoSignalGeneratorPlugin::EchoSignalGeneratorPlugin()
	{
		this->Echo_Signal_Generator_Module_Pointer = nullptr;
	}
	EchoSignalGeneratorPlugin::~EchoSignalGeneratorPlugin()
	{
		delete this->Echo_Signal_Generator_Module_Pointer;
	}
	EchoSignalGeneratorModule * EchoSignalGeneratorPlugin::PluginEchoSignalGenerator()
	{
		this->Echo_Signal_Generator_Module_Pointer = new EchoSignalGeneratorModule;
		return(this->Echo_Signal_Generator_Module_Pointer);
	}
}


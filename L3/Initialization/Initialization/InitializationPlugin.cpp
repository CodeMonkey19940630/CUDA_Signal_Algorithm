// Initialization.cpp : 定义 DLL 应用程序的导出函数
#include "stdafx.h"
#include "InitializationPlugin.h"

namespace GPUSignalAlgorithm
{
	InitializationPlugin::InitializationPlugin()
	{
		this->Initialization_Module_Pointer = nullptr;
	}
	InitializationPlugin::~InitializationPlugin()
	{
		delete this->Initialization_Module_Pointer;
	}
	InitializationModule * InitializationPlugin::PluginInitialization()
	{
		this->Initialization_Module_Pointer = new InitializationModule;
		return(this->Initialization_Module_Pointer);
	}
}


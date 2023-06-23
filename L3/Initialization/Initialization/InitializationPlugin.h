//只对外暴露IJamComponentFactory接口类
#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#ifdef INITIALIZATION_EXPORTS
#define INITIALISATION_EXPORTS __declspec(dllexport)
#else
#define INITIALISATION_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "InitializationModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class INITIALISATION_EXPORTS InitializationPlugin
	{
	public:
		InitializationPlugin();
		~InitializationPlugin();
		InitializationModule * PluginInitialization();
	private:
		InitializationModule * Initialization_Module_Pointer;
	};
}
#endif


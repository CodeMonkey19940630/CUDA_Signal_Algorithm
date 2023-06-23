//只对外暴露IJamComponentFactory接口类
#ifndef ECHOSIGNALGENERATOR_H
#define ECHOSIGNALGENERATOR_H
#ifdef ECHOSIGNALGENERATOR_EXPORTS
#define ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllexport)
#else
#define ECHO_SIGNAL_GENERATOR_EXPORTS __declspec(dllimport)
#endif
//PulseDopplerRadarDisplay接口类所需头文件
#include "EchoSignalGeneratorModule.h"
//PulseDopplerRadarDisplay接口类定义
namespace GPUSignalAlgorithm
{
	class ECHO_SIGNAL_GENERATOR_EXPORTS EchoSignalGeneratorPlugin
	{
	public:
		EchoSignalGeneratorPlugin();
		~EchoSignalGeneratorPlugin();
		EchoSignalGeneratorModule * PluginEchoSignalGenerator();
	private:
		EchoSignalGeneratorModule * Echo_Signal_Generator_Module_Pointer;
	};
}
#endif

